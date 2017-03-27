//702
#ifndef STACK_H
#define STACK_H

typedef struct Stack stack;

typedef int data_type;  // Pakeisti int i reikalinga duomenu tipa

struct Stack
{ 
	struct node *top;
	int exists;
};

struct node 
{
	data_type data;
	struct node *next;
};

extern stack st; //declared

// Funkcijos
int create (stack* head);
// return 0 - pavyko sukurti Stack'a
// return 1 - Stack'as jau yra sukurtas
int push (stack* head, data_type *value);
// return 0 - viskas gerai
// return 1 - Stack'as nera sukurtas
// return 2 - nepavyko isskirti atminties
int pop (stack* head, data_type *value);
// return 0 - viskas gerai
// return 1 - Stack'as nera sukurtas
// return 2 - Stack'as tuscias 
int top (stack* head, data_type *value);
// return 0 - viskas gerai
// return 1 - Stack'as nera sukurtas
// return 2 - Stack'as tuscias
int size (stack* head, int *size);
// return 0 - viskas gerai
// return 1 - Stack'as nera sukurtas 
// return 2 - Stack'as tuscias
int destroy (stack* head);
// return 0 - pavyko istrinti Stack'a
// return 1 - nepavyko istrinti Stack'o 
// return 2 - Stack'as tuscias arba jau istrintas
int empty (stack* head);
// return 0 - Stack'as yra tuscias
// return 1 - Stack'as nera tuscias
int full_stack (stack* head);
// return 0 - Stack'as yra pilnas
// return 1 - Stack'as nera pilnas
#endif
