#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigInteger.h"
#include "Stack.h"
#include "deck.h"

int ArriveRandom(int arriveChance)
{
    return rand() % 100 < arriveChance ? 1 : 0;
}

int main ()
{
	if (create (&st) == 0)
    {
		printf ("Stack has been created.\n");
    }
	else
    {
        printf ("Stack is already created.\n");
    }

	DECK* washMachine = NULL;
	DECK* clients = NULL;

	//nuskaitymas
	int plateCount = 0;
	int eatTime = 0;
	int arrivePercent = 0;
	int washTime = 0;
	int timeStart = 0;
	int timeEnd = 0;
	printf("Plate count: ");
	scanf("%d", &plateCount);
	printf("Client Eat time: ");
	scanf("%d", &eatTime);
	printf("CLient Arrive Percent: ");
	scanf("%d", &arrivePercent);
	printf("Wash Time: ");
	scanf("%d", &washTime);
	printf("User Time Start: ");
	scanf("%d", &timeStart);
	printf("User Time End: ");
	scanf("%d", &timeEnd);

	int i;
	int lostClients = 0;
	int allPlates = 0;
	int minPlates = plateCount;
    
    for (i = 0; i < timeEnd; i++)
    {
		//jei atvyko naujas
        if (ArriveRandom(arrivePercent))
        {
			if (plateCount == 0)
			{
				lostClients++;				
			}
			else
			{
				plateCount--;
				clients = addLast(clients, eatTime);
			}
        }

        //patikrinti ar kas nebaige valgyti
		DECK* tempClients = clients;

		if (tempClients != NULL)
		{
			tempClients->value--;

			while (tempClients->next != NULL)
			{
				tempClients = tempClients->next;
				tempClients->value--;
			}

			if (clients->value == 0)
			{
				clients = rmFirst(clients);
				washMachine = addLast(washMachine, washTime);
			}
		}

        //patikrinti ar neisiplove
		DECK* tempMachine = washMachine;

		if (tempMachine != NULL)
		{
			tempMachine->value--;

			while (tempMachine->next != NULL)
			{
				tempMachine = tempMachine->next;
				tempMachine->value--;
			}

			if (washMachine->value == 0)
			{
				washMachine = rmFirst(washMachine);
				int plate = 1;
				push(&st, &plate);
			}
		}

		//count medium and min plateCount in rick
		if (i >= timeStart)
		{
			allPlates += plateCount;

			if (minPlates > plateCount)
			{
				minPlates = plateCount;
			}
		}
    }

	float mediocrePlates = (float)allPlates / (timeEnd - timeStart);

	printf("Mediocre plates: %f, minimum plates: %d", mediocrePlates, minPlates);

	scanf("%d", eatTime);

    return 0;
}

//03-27 12h-13:00h
//03-31 24h-02:00h