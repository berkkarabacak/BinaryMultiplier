#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int data;
    struct node* next;
};

#define MAXSIZE 1000

struct stack
{
    int stk[MAXSIZE];
    int top;
};

typedef struct stack STACK;

STACK s;

/*  Function to push an element to the stack */
void push (int num)
{
    if (s.top == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = num;
    }
    return;
}

/*  Function to delete an element from the stack */
int pop ()
{
    int num;
    if (s.top == -1)
    {
        return (25);
    }
    else
    {
        num = s.stk[s.top];
        s.top = s.top - 1;
    }
    return(num);
}

/*  Function to reverse linked list */
static void reverse(struct node**start)
{
    struct node* prev   = NULL;
    struct node* current = *start;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next; current->next = prev;
        prev = current;        current = next;
    }
    *start = prev;
}

/*  Function to print linked list */
void printList(struct node *node)
{
    //Loop for deleting leading zeros
    while( node != NULL && node->data == 0 )
    {
        node = node->next;
    }

    while(node != NULL)
    {
        printf("%d", node->data);
        node = node->next;
    }
    printf("\n");
}

/*  Function to append an element to the linked list */
void append(struct node **start,int newdata)
{
    struct node *new_node=(struct node *)malloc(sizeof(struct node));

    struct node *last=*start;

    new_node->data= newdata;

    new_node->next=NULL;

    if((*start)!=NULL)

    {
        while(last->next!=NULL)

            last=last->next;

        last->next=new_node;
    }
    else
        *start =new_node;

}

/*  Function to get binary number from user to the linked list */
struct node *getInputToLinkedList(){
    char number[1000];
    struct node*linkedNumber = NULL;
    int i;
    scanf(" %[^\n]", number);
    int len = strlen(number);
    for(i=0;i<len;i++){

        if(!((((char) number[i])-'0')==0||(((char) number[i])-'0')==1)){
            printf("Only binary numbers are allowed,exiting program");
            exit(8);//8 is my lucky number :)
        }
        else
        {
            append(&linkedNumber,((char) number[i])-'0');
        }
    }
    return linkedNumber;
}

/*  Function to convert binary to decimal */
void convertToDecimal(struct node **nodehead)
{

    reverse(nodehead);
    struct node *node=*nodehead;
    long int decimal=0;
    int order =0;

    while(node != NULL)
    {
        if(node->data==1){
            decimal+=pow(2, order);
        }
        node = node->next;
        order++;
    }

    if(decimal<10000000&&decimal>=0){
        printf("Decimal value : ");
        printf("%ld \n", decimal);
    }
    reverse(nodehead);
}

/*  Function to convert binary to hexadecimal */
void convertToHex(struct node *node)
{
    printf("Hex     value : ");
    int order =0;
    int tempprint=0;
    reverse(&node);
    int count=0;
    while(node != NULL)
    {
        count++;
        if(node->data==1){
            tempprint+=pow(2, order);
        }
        order++;
        if(count%4==0){
            push(tempprint);
            order=0;
            tempprint=0;
        }
        node = node->next;
    }

    if(count%4!=0){
        push(tempprint);
    }

    int printhex=pop();

    while (printhex!=25){
        printf("%hhX",printhex);
        printhex=pop();
    }
    printf("\n");

}

/*  Function to create new node */
struct node *newNode(int data)
{
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/*  Function to push to the linked list */
void pushToLL(struct node** old, int data)
{
    struct node* newnode = newNode(data);

    newnode->next = (*old);

    (*old)    = newnode;
}

/*  Function to sum to binary numbers represented as linked list*/
struct node*sumTwoList(struct node *first, struct node *second)
{
    struct node* res = NULL;
    struct node *temp, *prev = NULL;
    int carry = 0;
    int sum;

    while ( second != NULL || first != NULL )
    {
        sum = (first? first->data: 0) + (second? second->data: 0);
        sum += carry ;

        if(sum >= 2)
            carry =  1;
        else
            carry =  0;

        sum = sum % 2;

        temp = newNode(sum);

        if(res == NULL)
            res = temp;
        else
            prev->next = temp;

        prev  = temp;

        if (first)
            first = first->next;

        if (second)
            second = second->next;
    }

    if (carry > 0)
        temp->next = newNode(carry);

    return res;
}

int main(){
    printf("***** Binary Multiplication ******\n");
    s.top = -1;

    struct node* first  = NULL;
    struct node* second = NULL;
    struct node* result = NULL;

    // Get first number from user
    printf("Enter First Binary\n");
    first= getInputToLinkedList();
    printf("\n");
    printList(first);

    // Get second number from user
    printf("Enter Second Binary\n");
    second= getInputToLinkedList();
    printList(second);

    printf("\n");

    reverse(&first);
    reverse(&second);

    //This loop is where multiplication is done
    while(second!=NULL){
        int digit = second->data;

        if(digit ==1){
            result= sumTwoList(first, result);
        }
        pushToLL(&first,0);
        second=second->next;
    }

    reverse(&result);

    printf("********** Results **********\n\n");

    printf("Binary  value : ");

    printList(result);

    convertToDecimal(&result);

    convertToHex(result);

    printf(" \n********** Written by Berk Karabacak **********\n");

    return 0;
}