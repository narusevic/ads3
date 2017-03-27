#include <stdio.h>
#include <stdlib.h>
#include "bigInteger.h"
#include "Stack.h"

int ArriveRandom(int arriveChance)
{
    return rand() % 100 < arriveChance ? 1 : 0;
}

int main ()
{
	/*if (create (&st) == 0)
    {
		printf ("Stack has been created.\n");
    }
	else
    {
        printf ("Stack is already created.\n");
    }*/

    printf("labas");

    int plateCount = 5000;
    int eatTime = 300;
    int arrivePercent = 50;
    int washTime = 30;
    int timeStart = 500;
    int timeEnd = 1000;

    int currentPlates
    
    time_t t;
    srand((unsigned) time(&t));
    int i;
    for (i = 0; i < 10000; i++)
    {
        int hasArrived = ArriveRandom(arrivePercent);

        if (hasArrived)
        {
            printf("%d\n", i);
        }

        int minPlates = 

        if (i >= timeStart && i <= timeEnd)
        {

        }
    }

    return 0;
}

//03-27 12h-13:30h