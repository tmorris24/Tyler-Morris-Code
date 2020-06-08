/* COP 3502C Final term Assignment 1
This program is written by: Tyler Morris */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point{
int x;
int y;
};

struct point* ReadData(FILE * infile, int *xcen, int *ycen, int *r, int *N);
struct point* FilterData(struct point* list, int xcen, int ycen, int r, int *N);
void merge(struct point* list, int l, int m, int r);
void mergeSort(struct point* list, int l, int r);
int binarySearch(struct point* list, int x, int y, int N);
int SearchPhase(struct point* list, int N);
void printArray(struct point* list, int size, FILE * outfile);

int main(){
    FILE * infile;
    FILE * outfile;
    struct point* list;
    int xcen, ycen, r, N;

    infile = fopen("in.txt", "r");
    outfile = fopen("out.txt", "w");

    list = ReadData(infile, &xcen, &ycen, &r, &N);
    list = FilterData(list, xcen, ycen, r, &N);

    mergeSort(list, 0, N-1);
    printArray(list, N, outfile);

    fclose(infile);
    fclose(outfile);

    SearchPhase(list, N);
    return 0;

}

struct point* ReadData(FILE *infile, int *xcen, int *ycen, int *r, int *N){
    int i;

    fscanf(infile, "%d", xcen);
    fscanf(infile, "%d", ycen);
    fscanf(infile, "%d", r);
    fscanf(infile, "%d", N);

    struct point* list = (struct point*) malloc(*N * sizeof(struct point));

    for(i = 0; i < *N; i++){
        fscanf(infile, "%d", &list[i].x);
        fscanf(infile, "%d", &list[i].y);

    }
    return list;
}

struct point* FilterData(struct point* list, int xcen, int ycen, int r, int *N){
    int i; int j = 0, filter = 0, fsize;
    for (i = 0; i < *N; i++){
        if(pow(list[i].x - xcen, 2) + pow(list[i].y-ycen, 2) > pow(r,2))
            filter++;
    }
    fsize = *N - filter;
    struct point* flist = (struct point*)malloc(fsize * sizeof(struct point));
    for(i = 0; i < *N; i++){
        if(pow(list[i].x - xcen, 2) + pow(list[i].y-ycen, 2) <= pow(r,2)){
            flist[j].x = list[i].x;
            flist[j].y = list[i].y;
            j++;
        }
    }
    *N = fsize;
    return flist;
}

void mergeSort(struct point* list, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(list, l, m);
        mergeSort(list, m+1, r);

       // printf("Testing l=%d r=%d m=%d\n", l, r, m);

        merge(list, l, m, r);
    }
}

void merge(struct point* list, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    struct point* L = (struct point*) malloc(n1 * sizeof(struct point));
    struct point* R = (struct point*) malloc(n2 * sizeof(struct point));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = list[l + i];
        }
    for (j = 0; j < n2; j++){
        R[j] = list[m + 1+ j];
        }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if(L[i].x != R[j].x){
            if (L[i].x <= R[j].x)
            {
                list[k] = L[i];
                i++;
            }
            else
            {
                list[k] = R[j];
                j++;
            }
        }
        else if(L[i].x == R[j].x){
            if (L[i].y <= R[j].y)
            {
                list[k] = L[i];
                i++;
            }
            else
            {
                list[k] = R[j];
                j++;
            }
        }
    k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        list[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        list[k] = R[j];
        j++;
        k++;
    }
}

void printArray(struct point* list, int size, FILE * outfile)
{
    int i;
    for (i=0; i < size; i++){
        fprintf(outfile, "%d %d\n", list[i].x, list[i].y);
    }
    printf("\nfiltered and sorted data written to out.txt\n");
}
int SearchPhase(struct point* list, int N){
    int x, y, search;
    while(1){
        printf("\nPlease Enter and X and Y coordinate in the form of x(space)y\n");
        printf("Search Input: ");
        scanf("%d %d", &x, &y);
        printf("\nOutput:");
        if((x == -999) || (y == -999)){
            printf("\nExit");
            break;
        }
        search = binarySearch(list, x, y, N);
        if(search == -1)
            printf("Not Found");
        else{
            printf("Found at record %d", search);
        }
    }
    return 0;
}

int binarySearch(struct point* list, int x, int y, int N)
{
    int l = 0, h = N - 1;
    int j = 0, k = N - 1;
    int mid, mid2;
    while (l <= h)
    {
        mid = (l + h) / 2;
        // Check if item is present at mid
        if ((list[mid].x == x) && (list[mid].y == y))
            return mid+1;
         // If item greater, ignore left half
        if ((list[mid].x < x) || ((list[mid].x == x) && (list[mid].y < y)))
            l = mid + 1;

        // If item is smaller, ignore right half
        else
            h = mid - 1;
    }
    // if we reach here, then element was
    // not present
    return -1;
}

