#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
int num;
int p;
int l;
int r;
double ln;
double cap;
double xloc;
double yloc;
};
struct delay{
    int node;
    double delay;
};

struct node* ReadData(FILE * infile, double *rl, double *lc, double *sc, double *rd, int *S, int *N);
struct node* FilterList(struct node* list, int S, int N);
struct node FindHead(struct node* list, int N);
void CapCalc(struct node* list, double lc, double sc, int N);
double DownSum(struct node* list, int point);
struct delay* DListCreate(struct node* list, struct node* slist, double rl, double rd, int S);
double DelayCalc(struct node* list, int node, double rl, double rd);
struct delay FindMin(struct delay* Dlist, int S);
struct delay FindMax(struct delay* Dlist, int S);
double FindMaxSkew(double min, double max);

int main(int argc, char**argv){
    FILE * infile;
    double rl, lc, sc, rd;
    int S, N;
    struct node* list;
    struct node* slist;
    struct node head;
    struct delay* delayList;
    struct delay min;
    struct delay max;
    double skew;
    double cap;

    infile = fopen("r1_top.txt", "r");

    list = ReadData(infile, &rl, &lc, &sc, &rd, &S, &N);
    slist = FilterList(list, S, N);
    head = FindHead(list, N);
    CapCalc(list, lc, sc, N);
    delayList = DListCreate(list, slist, rl, rd, S);

    int i;
    for(i = 0; i < S; i++){
        printf("\nThe delay at sink %d is %g", delayList[i].node, delayList[i].delay);
    }

    min = FindMin(delayList, S);
    max = FindMax(delayList, S);
    skew = FindMaxSkew(min.delay, max.delay);

}

struct node* ReadData(FILE * infile, double *rl, double *lc, double *sc, double *rd, int *S, int *N){
    char g[100];
    int i;

        fscanf(infile, "%*[^:]%*2c%lf", rl);
        fscanf(infile, "%*[^:]%*2c%lf", lc);
        fscanf(infile, "%*[^:]%*2c%lf", sc);
        fscanf(infile, "%*[^:]%*2c%lf", rd);
        fscanf(infile, "%*[^:]%*2c%d", S);
        fscanf(infile, "%*[^:]%*2c%d", N);
        fscanf(infile, "%*[^1]", g);

        struct node* list = (struct node*) malloc(*N * sizeof(struct node));

        for(i = 0; i < *N; i++){
            fscanf(infile, "%d", &list[i].num);
            fscanf(infile, "%d", &list[i].p);
            fscanf(infile, "%d", &list[i].l);
            fscanf(infile, "%d", &list[i].r);
            fscanf(infile, "%lf", &list[i].ln);
            fscanf(infile, "%lf", &list[i].xloc);
            fscanf(infile, "%lf", &list[i].yloc);
        }
    return list;
}

struct node* FilterList(struct node* list, int S, int N){
    int i, j = 0;
    struct node* slist = (struct node*) malloc(S * sizeof(struct node));
    for(i = 0; i < N; i++){
        if((list[i].l == -1) && (list[i].r == -1)){
            slist[j] = list[i];
            j++;
        }
    }
    return slist;
}

struct node FindHead(struct node* list, int N){
    int i;
    struct node head;
    for(i = 0; i < N; i++){
        if(list[i].p == -1){
            head = list[i];
            break;
        }
    }

    return head;
}

void CapCalc(struct node* list, double lc, double sc, int N){
    int i;
    for(i = 0; i < N; i++){
        if((list[i].l == -1) && (list[i].r == -1))
            list[i].cap = (list[i].ln * lc)/2 + sc;
        else if((list[i].l == -1) && (list[i].r != -1))
            list[i].cap = (list[i].ln * lc)/2 + (list[(list[i].r)-1].ln * lc)/2;
        else if((list[i].l != -1) && (list[i].r == -1))
            list[i].cap = (list[i].ln * lc)/2 + (list[(list[i].l)-1].ln * lc)/2;
        else
            list[i].cap = (list[i].ln * lc)/2 + (list[(list[i].r)-1].ln * lc)/2 + (list[(list[i].l)-1].ln * lc)/2;
    }
}

struct delay* DListCreate(struct node* list, struct node* slist, double rl, double rd, int S){
    struct delay* Dlist = (struct delay*) malloc(S * sizeof(struct delay));
    int i;
    for(i = 0; i < S; i++){
        Dlist[i].node = slist[i].num;
        Dlist[i].delay = DelayCalc(list, slist[i].num, rl, rd);
    }
    return Dlist;
}

double DelayCalc(struct node* list, int node, double rl, double rd){
    double delay;
    if(list[node-1].p == -1){

        delay = rd * DownSum(list, list[node-1].num);
    }
    else{
        delay =  (rl * list[node-1].ln * DownSum(list, list[node-1].num)) + DelayCalc(list, list[node-1].p, rl, rd);
    }
    return delay;
}

double DownSum(struct node* list, int point){
    double cap;

    if((list[point-1].l == -1) && (list[point-1].r == -1)){
        cap = list[point-1].cap;
    }
    else if((list[point-1].l == -1) && (list[point-1].r != -1)){
                cap = list[point-1].cap + DownSum(list, list[point-1].r);
    }
    else if((list[point-1].l != -1) && (list[point-1].r == -1)){
                cap = list[point-1].cap + DownSum(list, list[point-1].l);
    }
    else{
        cap = list[point-1].cap + DownSum(list, list[point-1].l) + DownSum(list, list[point-1].r);

    }
    return cap;
}

struct delay FindMin(struct delay* Dlist, int S){
    int i;
    struct delay min;
    min.delay = 9e50;
    for(i = 0; i < S; i++){
        if(Dlist[i].delay < min.delay)
            min = Dlist[i];
    }
    printf("\nThe minimum delay from the source to a sink is from source to node number # %d at %g time units\n", min.node, min.delay);
    return min;
}

struct delay FindMax(struct delay* Dlist, int S){
    int i;
    struct delay max;
    max.delay = 0;
    for(i = 0; i < S; i++){
        if(Dlist[i].delay > max.delay)
            max = Dlist[i];
    }
    printf("\nThe maximum delay from the source to a sink is from source to node number # %d at %g time units\n", max.node, max.delay);
    return max;
}

double FindMaxSkew(double min, double max){
    double skew;
    skew = max - min;

    printf("\n The max skew is %g", skew);
    return skew;
}
