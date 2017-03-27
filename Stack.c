#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

stack st;

int create (stack* head)
{
	if (head -> exists == 1) 
		return 1;
	else head -> top = NULL;
	head -> exists = 1;
	return 0;
}

int push (stack* head, data_type *value)
{
	if (head -> exists != 1)
		return 1;
	struct node *temp;
	temp = (struct node *) malloc (sizeof (struct node));
	if (temp == NULL)
		return 2;
	temp -> data = *value;
	temp -> next = head -> top;
	head -> top = temp;
	return 0;
}

int pop (stack* head, data_type *value)
{
	if (head -> top == NULL)
		return 2;
	
	if (head -> exists != 1)	
		return 1;

	struct node *temp;
	temp = head -> top -> next;
	*value = head -> top -> data;
	free (head -> top);
	head -> top = temp;
	return 0;
}

int top (stack* head, data_type *value)
{
	if (head -> top == NULL)
		return 2;
	
	if (head -> exists != 1)
		return 1;
		
	*value = head -> top -> data;
	return 0;
}

int size (stack* head, int *size)
{
	if (head -> exists != 1)	
		return 1;

	*size = 0;

	if (head -> top == NULL)
		return 2;
		
	struct node *temp = head -> top;
	do
	{
		(*size)++;
		temp = temp->next;
	}while (temp != NULL);
	return 0;
}

int destroy (stack* head)
{
	if (head -> top == NULL)
		return 2;
		
	struct node *temp;
	
	do
	{
		temp = head -> top;
		head -> top = head -> top -> next;
		free (temp);

	} while (temp != NULL && temp -> next != NULL);

	head -> top = NULL;
	head -> exists = 0;
	if (head -> top == NULL) 
		return 0;
	else return 1;
}

int empty (stack* head)
{
	if (head -> top == NULL)
		return 0;
	else return 1;
}
int full_stack (stack* head)
{
	struct node *temp;
	temp = (struct node *) malloc (sizeof (struct node));
	if (temp == NULL)
		return 0;
	else return 1;
}