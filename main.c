#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main ()
{
	if (create (&st) == 0)
		printf ("Stack has been created.\n");
	else printf ("Stack is already created.\n");
		
	printf ("Enter data: ");
	int a;
	scanf ("%d", &a);
	if (push (&st, &a) == 1)
		printf ("Stack is not created.\n");
		
	int b;
	if (pop (&st, &b) == 0) 
		printf ("Popped value: %d\n", b);
		
	int c;
	if (top (&st, &c) == 0) 
		printf ("Stack top element: %d\n", c);
	
	int d;
	if (size (&st, &d) == 1) 
		printf ("Stack is not created.\n");
	else printf ("Stack size: %d elements.\n", d);

	if (destroy (&st) == 1) 
		printf ("Stack elements has not been destroyed.\n");
	else printf ("All stack elements has been destroyed.\n");
	
	if (create (&st) == 0)
		printf ("Stack has been created.\n");
	else printf ("Stack is already created.\n");
	
	printf ("Enter data: ");
	int e;
	scanf ("%d", &e);
	if (push (&st, &e) == 1)
		printf ("Stack is not created.\n");

	if (empty (&st) == 0) 
		printf ("Stack is empty.\n");
	else printf ("Stack is not empty.\n");
	
	int f;
	if (pop (&st, &f) == 0) 
		printf ("Popped value: %d\n", f);
	
	if (full_stack (&st) == 0) 
		printf ("Stack is full.\n");
	else printf ("Stack is not full.\n");
		
	return 0;
}