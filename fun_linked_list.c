#include<stdio.h>
#include<stdlib.h>
typedef struct linkedlist{//double linked list
	char name[20];
	int id;
	struct linkedlist *flink;//forward link
	struct linkedlist *blink;//backward link
}node;
node * head=NULL;
/*create before :
 *step1:create a new memory using malloc and point to new address returned by malloc
 *step2:+if it is first node to be created then 
 		*point to new address returned by malloc using head pointer as start reference.
		*store "NULL" to the 'forwardlink' of new mem block and, store "value" to data memeber 'id'.
 	+if it is not the first node to be created/if alread n blocks with start reference exists then 
		*store "head/start reference" to the 'forwardlink' of new mem block[by this we have connected new node to beginning(Head)] and, store "value" to data memeber 'id'.
 		*now point to new address using head pointer has the start reference.
 *step3:return if necessary
 * */
void create_before(int value){//todo: use blink also
	node *new=(node*)malloc(sizeof(node));
	new->id=value;
	if(NULL==head){
		new->flink=NULL;
		head=new;
	}
	else{
		new->flink=head;
		head=new;
	}
}
/*create after :
 *step1:create a new memory using malloc and point to new address returned by malloc.
 *step3:store "value" to data memeber 'id'
 *step2:+if it is first node to be created then 
 		*point to new address returned by malloc using head pointer as start reference.
		*store "NULL" to the 'forwardlink' of new mem block and, store "value" to data memeber 'id'.
 	+if it is not the first node to be created/if alread 'n' blocks with start reference exists then
       		*store "head/start reference" to 'temp' pointer	for traverese to the last.
		*traverse to the end the list.
		*store "new memory refernce(new poinetr)" to the 'forwardlink' of 'last/temp' mem block .
 		*now point to forward/next link to "NULL"  has the end of the list.
 *step3:return if necessary
 * */
void create_after(int value){
	node *temp=NULL;
	node *new=(node*)malloc(sizeof(node));
	new->id=value;
	if(NULL==head){
		new->flink=NULL;
		head=new;
	}
	else{
		temp=head;
		while(temp->flink!=NULL)
			temp=temp->flink;
		temp->flink=new;
		new->flink=NULL;
	}
}
/*create at :
 *step0:take two new pointers 'current' and 'previous' and varible for count:(w).
 *step1:create a new memory using malloc and point to new address returned by malloc.
 *step3:store "value" to data memeber 'id'
 *step4:+if it is first node to be created then 
 		*point to new address returned by malloc using head pointer as start reference.
		*store "NULL" to the 'forwardlink' of new mem block and, store "value" to data memeber 'id'.
 	+if it is not the first node to be created/if alread 'n' blocks with start reference exists then
       		*store "head/start reference" to 'curr' pointer	for traveresing to the position.
		*traverse to the position using 'flink' and also point to "curr pointer" using 'pre' pointer.
		*store "new memory refernce(new poinetr)" to the 'previouslink' of 'last/temp' mem block .
 		*now point to forward/next link to "curr poinetr addr"  has the next/end of the list.
 *step3:return if necessary
 * */
void create_at(int value,int pos){
	node *curr=NULL;
	node *pre=NULL;
	int w=0;
	printf("pos=%d  value=%d\n",pos,value);
	node *new=(node*)malloc(sizeof(node));
	new->id=value;
	if(NULL==head){
		new->flink=NULL;
		head=new;
	}
	else{
		curr=head;
		while(w!=pos){
			pre=curr;
			curr=curr->flink;
			w++;
		}
		pre->flink=new;
		new->flink=curr;
	}
}

void print_list(){
	int i=0;
	node* temp=head;
	while(temp!=NULL){
		printf("i am %d node with value %d\n",++i,temp->id);
		temp=temp->flink;
	}
}

void delete(int value){
	node *curr=head;
	node *pre=NULL;
	while(value!=(curr->id)){
		pre=curr;
		curr=curr->flink;
	}
	if(curr==head)
		head=head->flink;
	else
		pre->flink=curr->flink;
	free(curr);
}
void exit_fun(){
	printf("thankyou\n");
	exit(0);
}
void main(){
	int value,choice;
	while(1){
		printf("enter the choice\n1)create_before\n2)createafter\n3)create_at\n4)printlist\n5)delete\n6)exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("enter the value\n");
				scanf("%d",&value);
				create_before(value);// code to be executed if n = 1;
				print_list();        
				break;
			case 2: printf("enter the value\n");
				scanf("%d",&value); 
				create_after(value);// code to be executed if n = 2;
				print_list();        
				break;
			case 3: printf("enter the value\n");
				int pos=0;
				scanf("%d",&value);
				printf("enter the position\n");
				scanf("%d",&pos); 
				//printf("2\n");
				create_at(value,pos);// code to be executed if n = 3;
				print_list();        
				break;
			case 4: print_list();// code to be executed if n = 4
				break;
			case 5:
				printf("enter the value and position\n");
				scanf("%d",&value);
				delete(value);// code to be executed if n = 5
				print_list();
				break;
			case 6: exit_fun();// code to be executed if n is 6 
				break;
			default: printf("kindly enter a valid option\n"); 
		}

	}
}
