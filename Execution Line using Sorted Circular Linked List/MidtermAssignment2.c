/* COP 3502C Midterm Assignment Two
This program is written by: Tyler Morris */
#include <stdio.h>
#include <stdlib.h>

struct soldier {
int position;
struct soldier* next;
struct soldier* prev;
};

struct soldier* create_soldier (int i);
struct soldier* create_reverse_circle(int n);
struct soldier* rearrange_circle(struct soldier* head);
int kill(struct soldier* head, int n, int k);
void display(struct soldier* head);

int main(){
    /*struct queue* myQueue = (struct queue*) malloc(sizeof(struct queue));
    init(myQueue);*/
    struct soldier* lead = (struct soldier*) malloc(sizeof(struct soldier));
    struct soldier* test = lead;

    int count;
    int k;
    int safe;

    printf("The war is over. We have won. We will now start culling the prisoners. How many did we capture sir?\n");
    scanf("%d", &count);

    lead = create_reverse_circle(count);

    printf("\nAlright scum! Line up!\n");
    display(lead);

    printf("\nWait a minute! This isn't the correct order! Get sorted!\n");

    lead = rearrange_circle(lead);
    display(lead);

    printf("\nWhat position do you want killed sir?\n");
    scanf("%d", &k);
    printf("\nAlright sir. Every %d positions will be killed.\n", k);
    printf("\nPrisoners! Begin killing!\n");

    safe = kill(lead, count, k);

    printf("\nAlright, position %d, you're free to go. Enjoy life.\n", safe);

}

struct soldier* create_soldier (int i){
    struct soldier* prisoner = (struct soldier*) malloc(sizeof(struct soldier));
    prisoner -> position = i;
    prisoner -> next = NULL;
    prisoner -> prev = NULL;
    return prisoner;
};
struct soldier* create_reverse_circle(int n){
    struct soldier* lead = NULL;
    struct soldier* rear = NULL;
    int i;
    for(i = n; i > 0; i--){
        if(lead == NULL){
            lead = create_soldier (i);
        }
        else if(rear == NULL){
            rear = create_soldier (i);
            lead -> next = rear;
            rear -> prev = lead;
        }
        else{
            rear -> next = create_soldier (i);
            rear -> next -> prev = rear;
            rear = rear -> next;
        }
    }
    lead -> prev = rear;
    rear -> next = lead;
    return lead;
}
struct soldier* rearrange_circle(struct soldier* head){
    struct soldier* tail;
    struct soldier* current;
    struct soldier* temp;
    tail = head;
    while(tail -> next != head)
        tail = tail -> next;
    head -> prev = NULL;
    tail -> next = NULL;
    current = head;
    while(current != NULL){
        temp = current -> next;
        current -> next = current -> prev;
        current -> prev = temp;

        current = temp;
    }
    temp = head;
    head = tail;
    tail = temp;
    tail -> next = head;
    head -> prev = tail;
}

int kill(struct soldier* head, int n, int k){
    struct soldier* temp;
    int i;
    while((head -> next != head) && (head -> prev != head)){
          for(i = 0; i < k; i++){
            temp = head;
            head = head -> next;
          }
          head -> prev = temp -> prev;
          temp -> prev -> next = head;
          free(temp);
          display(head);
    }
    return head -> position;
}

void display(struct soldier* head)
{
    struct soldier* t;
    t = head;
    printf("\nQueue is : \n");
    printf("%d ", t -> position);
        t = t-> next;
    while(t != head){
        printf("%d ", t -> position);
        t = t-> next;
    }
    printf("\n\n");
} /*End of display() */
