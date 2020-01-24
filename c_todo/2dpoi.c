========================https://dev-notes.eu/2018/07/double-pointers-and-linked-list-in-c/ =======================
void alloc2(int** p) {
   *p = (int*)malloc(sizeof(int));
   **p = 10;
}

void alloc1(int* p) {
   p = (int*)malloc(sizeof(int));
   *p = 10;
}

int main(){
   int *p = NULL;
   alloc1(p);
   //printf("%d ",*p);//undefined
   alloc2(&p);
   printf("%d ",*p);//will print 10
   free(p);
   return 0;
}
=======================
Observation and Finding, WHY...

I decided to do some experiments and make some conclusion,

OBSERVATION 1- If the linked list is not empty then we can add the nodes in it (obviously at the end) by using a single pointer only.

int insert(struct LinkedList *root, int item){
    struct LinkedList *temp = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    temp->data=item;
    temp->next=NULL;
    struct LinkedList *p = root;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=temp;
    return 0;
}


int main(){
    int m;
    struct LinkedList *A=(struct LinkedList*)malloc(sizeof(struct LinkedList));
    //now we want to add one element to the list so that the list becomes non-empty
    A->data=5;
    A->next=NULL;
    cout<<"enter the element to be inserted\n"; cin>>m;
    insert(A,m);
    return 0;
}
Its simple to explain (Basic). We have a pointer in our main function which points to the first node (root) of the list. In the insert() function we pass the address of the root node and using this address we reach the end of the list and add a node to it. So we can conclude that if we have address of a variable in a function (not the main function) we can make permanent changes in the value of that variable from that function which would reflect in the main function.

OBSERVATION 2- The above method of adding node failed when the list was empty.

int insert(struct LinkedList *root, int item){
    struct LinkedList *temp = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    temp->data=item;
    temp->next=NULL;
    struct LinkedList *p=root;   
    if(p==NULL){
        p=temp;
    }
    else{
      while(p->next!=NULL){
          p=p->next;
      }
      p->next=temp;
    }
    return 0;
}



int main(){
    int m;
    struct LinkedList *A=NULL; //initialise the list to be empty
    cout<<"enter the element to be inserted\n";
    cin>>m;
    insert(A,m);
    return 0;
}
If you keep on adding elements and finally display the list then you would find that the list has undergone no changes and still it is empty. The question which struck my mind was in this case also we are passing the address of the root node then why modifications are not happening as permanent modifications and list in the main function undergoes no changes. WHY? WHY? WHY?

Then I observed one thing, when I write A=NULL the address of A becomes 0. This means now A is not pointing to any location in memory. So I removed the line A=NULL; and made some modification in the insert function.

some modifications,(below insert() function can add only one element to an empty list, just wrote this function for testing purpose)

int insert(struct LinkedList *root, int item){
    root= (struct LinkedList *)malloc(sizeof(struct LinkedList));
    root->data=item;
    root->next=NULL;
    return 0;
}



int main(){
    int m;
    struct LinkedList *A;    
    cout<<"enter the element to be inserted\n";
    cin>>m;
    insert(A,m);
    return 0;
}
the above method also fails because in the insert() function root stores same address as A in the  main() function but after the line root= (struct LinkedList *)malloc(sizeof(struct LinkedList)); the address stored in root changes. Thus now , root (in insert() function) and  A (in main() function) store different addresses.

So the correct final program would be,

int insert(struct LinkedList *root, int item){
    root->data=item;
    root->next=NULL;
    return 0;
}



int main(){
    int m;
    struct LinkedList *A = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    cout<<"enter the element to be inserted\n";
    cin>>m;
    insert(A,m);
    return 0;
}
But we dont want two different functions for insertion, one when list is empty and other when list is not empty. Now comes double pointer which makes things easy.

One thing I noticed which is important is that pointers store address and when used with '*' they give value at that address but pointers themselves have their own address.

Now here is the complete program and later explain the concepts.

int insert(struct LinkedList **root,int item){
    if(*root==NULL){
        (*root)=(struct LinkedList *)malloc(sizeof(struct LinkedList));
        (*root)->data=item;
        (*root)->next=NULL;
    }
    else{
        struct LinkedList *temp=(struct LinkedList *)malloc(sizeof(struct LinkedList));
        temp->data=item;
        temp->next=NULL;
        struct LinkedList *p;
        p=*root;
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=temp;
    }
    return 0;
}


int main(){
    int n,m;
    struct LinkedList *A=NULL;
    cout<<"enter the no of elements to be inserted\n";
    cin>>n;
    while(n--){
        cin>>m;
        insert(&A,m);
    }
    display(A);
    return 0;
}
following are the observations,

1. root stores the address of pointer A (&A) , *root stores the address stored by pointer A and **root stores the value at address stored by A. In simple language root=&A, *root= A and **root= *A.

2. if we write *root= 1528 then it means that value at address stored in root becomes 1528 and since address stored in root is the address of pointer A (&A) thus now A=1528 (i.e. address stored in A is 1528) and this change is permanent.

whenever we are changing value of *root we are indeed changing value at address stored in root and since root=&A ( address of pointer A) we are indirectly changing value of A or address stored in A.

so now if A=NULL (list is empty) *root=NULL , thus we create the first node and store its address at *root i.e. indirectly we storing the address of first node at A. If list is not empty , everything is same as done in previous functions using single pointer except we have changed root to *root since what was stored in root is now stored in *root.
=======================
It is clear that both methods (single pointer and double pointer ) lead to the same result.

Double-pointers are used as arguments of function when the function modifies head of the linked list (updates the list) without needing to return the head again,

but when using Single-pointers as arguments of function that changes/modifies the head (updates the list) you must return the head pointer ,else the effect won’t be noticed.

Explanation to this is the simple-C rule : -

“if you want to modify local variable of one function inside another function, pass pointer to that variable.”

for example consider the very basic swap function below :-

void swap1(int* a ,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
/*
	Note: try the same but in your function pass arguments as int and not- 			  as int*.
*/
If you tried passing the values as int and not as int* you may have noticed that swap won’t happen, similarly here in case of linked list you pass a pointer that points to the linked list (**head_ref) in order for the change to happen in the linked list.

following are implementations of linked list in both versions :-

Using Double pointers

void push(node** head_ref,int data){
	node * new_node = new node;
 
	new_node->nxt = NULL;
	new_node->val = data;
 
	if(*head_ref == NULL){
		*head_ref = new_node;
		cout<<"empty"<<endl;
	}else{
	    cout<<"not empty"<<endl;
		// node *temp = *head_ref;
		while((*head_ref)->nxt != NULL){
			(*head_ref) = (*head_ref)->nxt;
		}
		(*head_ref)->nxt = new_node;
	}
}
 
int main(){
	node * head_main = NULL;
	push(&head_main,1);
	push(&head_main,2);
	push(&head_main,3);
	print(&head_main);
	return 0;
}
Using Single pointers

node* push(int data,node* head){
  node* new_node = new node;
  new_node ->val = data;
  new_node ->nxt = NULL;
 
  if(head == NULL){
    // cout<<"empty ";
    head = new_node;
  }else{
    // cout<<"not empty ";
    node* temp1 = head;
    while(temp1->nxt != NULL){
      temp1 = temp1->nxt;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    temp1->nxt = new_node;
  }
  return head;
}
 
int main(){
  node* head_main=NULL;
  head_main =  Insert_front(1,head_main);
  head_main =  Insert_front(2,head_main);
  head_main =  Insert_front(3,head_main);
  head_main =  Insert_front(4,head_main);
  head_main =  Insert_front(5,head_main);
  print_list(head_main);
  delete(head_main);
  return 0;
}

=======================
#include <stdio.h>

void func(int (*B)[10]){   // ptr to array of 10 ints.
        (*B)[0] = 5;   // note, *B[0] means *(B[0])
         //B[0][0] = 5;  // same, but could be misleading here; see below.
}

int main(void){

        int B[10] = {0};   // not NULL, which is for pointers.
        printf("b[0] = %d\n\n", B[0]);
        func(&B);            // &B is ptr to arry of 10 ints.
        printf("b[0] = %d\n\n", B[0]);

        return 0;
}
