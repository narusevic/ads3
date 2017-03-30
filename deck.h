//686
#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdlib.h>
#include "bigInteger.h"

struct deck
{
	int value;
	struct deck* next;
	struct deck* previous;
};

typedef struct deck DECK;

struct deck * createDeck();
struct deck * rmFirst(struct deck *);
struct deck * rmLast(struct deck *);
struct deck * addFirst(struct deck *, int);
struct deck * addLast(struct deck *, int);
longInt deckSize(struct deck *);

#endif
