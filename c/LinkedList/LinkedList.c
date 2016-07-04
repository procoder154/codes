#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
#define SUCCESS 0
#define FAILURE -1
typedef struct Node
{
	int data;
	struct Node *next;
}Node;
int readInteger()
{
	int num;
	char *buff=malloc(SIZE);
	fgets(buff,SIZE-1,stdin);
	sscanf(buff,"%d",&num);
	return num;
}
void initialize(Node **head)
{
	head=malloc(sizeof(Node));
	*head=NULL;
}
Node *createNode(int data)
{
	Node *head=malloc(sizeof(Node));
	head->data=data;
	head->next=NULL;
	return head;
}
int createList(Node **head)
{
	int number,element;
	Node *p;
	printf("\nEnter the count of the Nodes in the linked list to be created : ");
	number = readInteger();
	if(number>0)
	{
		printf("\nEnter the element to be inserted : ");
		element = readInteger();
		*head=createNode(element);
		p=*head;
		while(number>1)
		{
			printf("\nEnter the element to be inserted : ");
			element = readInteger();
			p->next=createNode(element);
			p=p->next;
			number--;
		}
		p=NULL;
		return SUCCESS;
	}
	else
	{
		printf("\nYou entered an invalid number");
		return FAILURE;
	}

}
int displayList(Node *head)
{
	if (head==NULL)
	{
		printf("\nLinked List is empty!!!");
		return FAILURE;
	}
	else
	{
		while(head)
		{
			if (head->next)
				printf("%d -->",head->data);
			else
				printf("%d",head->data);
			head=head->next;
		}
		return SUCCESS;
	}
}
int linkedListLength(Node *head)
{
	int count=0;
	Node *iterator=head;
	while(iterator)
	{
		count++;
		iterator=iterator->next;
	}
	return count;
}
int searchList(Node *head,int element)
{
	int position=FAILURE,i=0;
	if (head!=NULL)
	{
		while(head)
		{
			if(head->data==element)
			{
				position=i;
				return position;
			}
			head=head->next;
			i++;
		}
	}
	else
	{
		printf("\nThe linked list is empty!!!!");
		return FAILURE;
	}
	return position;
}
int insertInTheBeginning(Node **head)
{
	int count,element;
	Node *reference,*iterator;
	printf("\nEnter the number of elements to be inserted : ");
	count=readInteger();

	if(count>0)
	{
			
		printf("\nEnter the element : ");
		element = readInteger();
		reference=createNode(element);
		iterator=reference;
		count--;
		while(count>0)
		{	
			printf("\nEnter the element : ");
			element = readInteger();
			iterator->next=createNode(element); //Order matters
			iterator=iterator->next;			// of theese statements
			count--;
			
		}
		iterator->next=*head;
		*head=reference;
		return SUCCESS;
	}
	else
		return FAILURE;
}
int insertAfterAnElement(Node **head)
{
	int number,key,position,i=0;
	Node *iterator,*tail;
	printf("\nEnter the element after which you want to insert data : ");
	key = readInteger();
	position=searchList(*head,key);
	if(position!=FAILURE)
	{
		printf("\nEnter the element which you want to insert : ");
		number = readInteger();
		iterator=*head;
		while(i++<position)
			iterator=iterator->next;
		tail=iterator->next;			
		iterator->next=createNode(number);
		iterator->next->next=tail;	
		return SUCCESS;
	}
	else
	{
		printf("\nElement does not exist in the list.");
		return FAILURE;
	}


}
int insertAtTheEnd(Node **head)
{
	Node *iterator=*head;
	int element;

	if(iterator)
	{
		printf("\nEnter the element to insert at the end : ");
		element=readInteger();
		while(iterator->next)
			iterator=iterator->next;
		iterator->next=createNode(element);
		return SUCCESS;

	}
	else
	{
		printf("\nThe linked list is empty!!!");
		return FAILURE;
	}	
}
int insertAtAPosition(Node **head)
{
	int position,length,i=0,number;
	Node *iterator=*head,*tail;
	length=linkedListLength(*head);

	printf("\nEnter the position where you want to enter the element : ");
	position=readInteger();

	if(0<=position && length>=position)
	{
		if (position==0)
		{
			return insertInTheBeginning(head);
		}
		else if (position==length)
		{
			return insertAtTheEnd(head);
		}
		else
		{
			while(i<position-1)
			{
				i++;
				iterator=iterator->next;
			}
			tail=iterator->next;

			printf("\nEnter the element you want to enter : ");
			number=readInteger();
			iterator->next=createNode(number);
			iterator->next->next=tail;
			return SUCCESS;
		}
	}
	else
	{
		printf("\nYou have entered an invalid position");
		return FAILURE;
	}
}
int insert(Node **head)
{
	int position,status;
	printf("\nEnter the position where to insert the element\n1.Beginning\n2.After an element\n3.At a position\n4.At the end\n\nChoice : ");
	position = readInteger();
	if (position==1)
	{
		//Insert in the beginning
		status=insertInTheBeginning(head);
	}
	else if (position==2)
	{
		status=insertAfterAnElement(head);

	}
	else if (position==3)
	{
		status=insertAtAPosition(head);
	}
	else if (position==4)
	{
		status=insertAtTheEnd(head);
	}
	else
	{
		printf("\nInvalid choice!!");
		return FAILURE;
	}
	if (status==SUCCESS)
		printf("\nInsertion Successful!!!"); 
	else
		printf("\nInsertion Failed!!!");
	return SUCCESS;

}
int deleteNodeByPosition(Node **head, int position)
{
	Node *iterator=*head,*temp;
	int i=1,length=linkedListLength(*head);
	if(!*head)
	{
		printf("\nThe linked list is empty!! Cannot perform deletion!");
		return FAILURE;
	}
	if (position==0)
	{
		temp=iterator;
		*head=(*head)->next;
		iterator=*head;
		free(temp);
	}	
	else if(position<length)
	{
		while(i<position)
		{
			i++;
			iterator=iterator->next;
		}
		temp=iterator->next;
		iterator->next=temp->next;
		free(temp);
	}
	printf("\nSuccessfully deleted node!!!");
	return SUCCESS;
}
int main(int argc, char const *argv[])
{
	int choice=0,status,number,position,length;
	Node **head,*iterator;
	initialize(head);
	while(choice!=8)
	{
		char *displayText="\tLinked List Operations\n1.Create a linked list\n2.Display the linked list\n3.Insert into linked list\n4.Search into linked list\n5.Delete from linked list\n6.Length of the linked list\n7.Print reversed linked list\n8.Reverse the linked list\n9.Exit\n\nEnter your choice - ";	
		printf("\n%s",displayText);
		choice=readInteger();
		switch(choice)
		{
			case 1: status=createList(head);
					if (status==FAILURE)
						printf("\nLinked list creation failed!!");
					else
						printf("\nLinked list created successfully");
					break;
			case 2: printf("\nThe linked list contains : ");
					status=displayList(*head);
					if(status==SUCCESS)
						printf("\n\nThe linked list elements displayed successfully!!!!");
					else
						printf("\nNothing to display!!");
					break;
			case 3: status=insert(head);
					break;
			case 4: if(head && *head)
					{
						printf("\nEnter the element to be searched : ");
						number = readInteger();
						position=searchList(*head,number);
						if(position!=FAILURE)
							printf("\nThe element exists at position %d",position);
						else
							printf("\nThe element does not exist in the linked list");
					}
					else
						printf("\nThe linked list is empty!!!!");

					break;
			case 5: printf("\nLinked List Deletion\n1.Delete by position\n2.Delete from beginning\n3.Delete from end\n4.Delete by element\n\nChoice - ");
					choice=readInteger();
					length=linkedListLength(*head);
					if (choice==1)
					{
						printf("\nEnter the position of the element which needs to be deleted : ");
						position=readInteger();
						if (position>=0 && position<length)
						{
							status=deleteNodeByPosition(head,position);
						}

					}
					else if (choice==2)
					{
						status=deleteNodeByPosition(head,0);
					}
					else if(choice==3)
					{
						status=deleteNodeByPosition(head,length-1);
					}
					else if(choice==4)
					{
						printf("\nEnter the element to be deleted from the list : ");
						number=readInteger();
						position=searchList(*head,number);
						if (position!=-1)
							status=deleteNodeByPosition(head,position);
						else
							printf("\nThe number does not exist in the linked list!!");
					}	
					else
					{
						printf("\nInvalid Entry!!!");
						continue;
					}
					if (status==FAILURE)
						printf("\nLinked List Deletion Failed!!!");
					break;
			case 6:	length = linkedListLength(*head);
					if (length!=0)
						printf("\nThe length of the linked list is : %d",length);
					else
						printf("\nThe linked list is empty!!!");
					break;
			case 7:
					break;
			case 8:
					break;
			case 9:
					exit(0);
			default:printf("\nInvalid choice!!! Try again....");

		}
		getchar();
	}	
	

	return 0;
}
