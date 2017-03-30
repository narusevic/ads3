#include "deck.h"
#include "bigInteger.h"

struct deck * newSlot(int value)
{
	struct deck * slot = (struct deck *) malloc(sizeof(struct deck));

	slot->next = NULL;
	slot->previous = NULL;
	slot->value = value;

	return slot;
}

struct deck * createDeck()
{
	return newSlot(0);
}

struct deck * rmFirst(struct deck * head)
{
	struct deck * first = head;

	head = head->next;

	head->previous = NULL;

	free(first);

	return head;
}

struct deck * rmLast(struct deck * head)
{
	struct deck * current = head;

	while (current->next != NULL)
	{
		current = current->next;
	}

	struct deck * penultimate = current->previous;
	printf("\n%d\n", penultimate->value);

	free(current);
	penultimate->next = NULL;

	printf("\n%d\n", penultimate->value);

	return head;
}

struct deck * addFirst(struct deck * head, int value)
{
	if (head == NULL)
	{
		return newSlot(value);
	}

	struct deck * current = head;

	current->previous = newSlot(value);
	current = current->previous;
	current->next = head;

	return current;
}

struct deck * addLast(struct deck * head, int value)
{
	if (head == NULL)
	{
		return newSlot(value);
	}

	struct deck * current = head;

	while (current->next != NULL)
	{
		current = current->next;
	}

	struct deck * penultimate = current;

	current->next = newSlot(value);
	current = current->next;
	current->previous = penultimate;

	return head;
}

longInt deckSize(struct deck * head)
{
	struct deck * current = head;
	int size = 1;
	printf("%d", current->value);

	while (current->next != NULL)
	{
		current = current->next;
		printf("%d", current->value);
		size++;
	}

	return size;
}