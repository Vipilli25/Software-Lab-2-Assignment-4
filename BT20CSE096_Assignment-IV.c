#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

// structure for storing node data //
typedef struct node
{
    int data;
    bool mark;
    int refCount;
    struct node *link1;
    struct node *link2;
    struct node *link3;
}node;

node *heap_ptr[8];

// function for setting links between nodes//
void set(int so,int dest1,int dest2,int dest3,int temp[])
{
	if(dest1!=-1)
	{
		heap_ptr[so]->link1=heap_ptr[dest1];
		heap_ptr[dest1]->refCount+=1;
	}
	if(dest2!=-1)
	{
		heap_ptr[so]->link2=heap_ptr[dest2]; 
		heap_ptr[dest2]->refCount+=1; 
	}
	if(dest3!=-1)
	{
		heap_ptr[so]->link3=heap_ptr[dest3];
		heap_ptr[dest3]->refCount+=1;
	}	
}

void display_all(node* root)
{
	if(root!=NULL)
	{
		printf("val=%d, ref=%d\n",root->data,root->refCount);
	}
	if(root==NULL)
	{
		return;
	}
	display_all(root->link1);
	display_all(root->link2);
	display_all(root->link3);
}

// function to display adjacent list //
void adj_list()
{
	int i=0;
	for(i=0;i<8;i++)
	{
	
	printf("node=%d is pointing to : ",heap_ptr[i]->data);
	if(heap_ptr[i]->link1!=NULL)
	{
		printf("%d ->",heap_ptr[i]->link1->data);
	}
	
	if(heap_ptr[i]->link2!=NULL)
	{
		printf("%d ->",heap_ptr[i]->link2->data);
	}
	if(heap_ptr[i]->link3!=NULL)
	{
		printf("%d ->",heap_ptr[i]->link3->data);
	}
	printf("NULL\n");
	}
}

// Reference Counting counting collection// 
int isroot(node* root1, node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	if(isroot(root1->link1,temp))
	{
		return 1;
	}
	
	if(isroot(root1->link2,temp))
	{
		return 1;
	}
	if(isroot(root1->link3,temp))
	{
		return 1;
	}
 return 0;
}

void gc_refcounting(node* root)
{
	int i=0;
	while(i<8)
	{
		if(isroot(root,heap_ptr[i])==0 )
		{		
           heap_ptr[i]->link1=NULL;                                //	free(heap_ptr[i]);
           heap_ptr[i]->link2=NULL;
           heap_ptr[i]->link3=NULL;
		}
		 i++;		
	}	 
}

// Marksweep garbage collection

void mark_root_nodes(node* root )
{
	int i;
	while(i<8)
	{
		if(isroot(root,heap_ptr[i])==1 )
		{			
          heap_ptr[i]->mark=true;
		}
		 i++;		
	}	 
}

void gc_marksweep(node* root)    
{
	mark_root_nodes(root);            //  mark as true (marking scheme)
	int i=0;
	while(i<8)
	{
		if(heap_ptr[i]->mark!=true)
		{
			heap_ptr[i]->link1=NULL;
			heap_ptr[i]->link2=NULL;
			heap_ptr[i]->link3=NULL;			
		}
	 i++;	
    }	
}

int main()
{
	int arr[]={1,2,3,5,7,8,9,10}; 
	int i,so,dest1,dest2,dest3;
	
	// Initializing nodes //
	for(i=0;i<8;i++)
	{
		node* newNode = malloc(sizeof(node));
		newNode->data=arr[i];
		newNode->link1=NULL;
		newNode->link2=NULL;
		newNode->link3=NULL;
		newNode->refCount=0;
		heap_ptr[i]=newNode;
	}
	
	node* root1=heap_ptr[3];
	heap_ptr[3]->refCount+=1;
	node* root2=heap_ptr[0];
	heap_ptr[0]->refCount+=1;
	
	set(0,1,6,7,arr);
	set(2,5,7,-1,arr);
	set(3,0,-1,-1,arr);
	set(4,0,5,-1,arr);
	set(5,6,-1,-1,arr);
	
	int choice=0;
	while(1)
	{
		printf(" \n Enter any option: ");
		printf(" \n 1. perform refernce counting garbage collection ");
		printf(" \n 2. perform marksweep garbage collection ");
		printf(" \n ");
	   scanf("%d",&choice);
       fflush(stdin);
       switch(choice)
       {
       	   case 1:
       	   	       printf("\n Displaying reference of each nodes: ");
			       display_all(root1); 
				   printf("\n adj list before performing reference counting:\n");
	               adj_list();	
	               printf("\n ---------PERFORMING REFERENCE COUNTING----------- "); 
	               gc_refcounting(root1); 
	               printf("\n adj list after performing reference counting:\n");
	               adj_list();
				   break; 
       	   case 2:
       	   	       printf("\n adj list before performing markweep:\n");
	               adj_list();	
	               gc_marksweep(root1);
	               printf("\n ---------PERFORMING MARKSWEEP--------------------");
	               printf("\n adj list after performing marksweep: \n");
			       adj_list();
			       break;
            default: printf("\nWrong choice entered\n");  
	   }
	   printf("\n---------------------------\n");
	}
	
}