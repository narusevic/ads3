#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigInteger.h"


int checkNumber(char*);
void printInteger(longInt);
void trimFrontZeros(longInt);
int unSignedBigIntegerCompare(longInt, longInt);
void invertBigIntegerSign(longInt);
longInt copyNumber (longInt);
int checkIfZero(longInt);
int checkLongerNumber(longInt, longInt);
void multByTen(longInt);

//*************************************************************************




char* bigIntegerToString(longInt number)
{
	int i = 0;
	char* string = malloc(sizeof(char));
	if(number != NULL)
	{
		bigInt* temp = number->head;
      if(number->signFlag) 
		{
			string[0] = '-';
			string = realloc(string,2*sizeof(char));
			i++;
		}
        while(temp != NULL)
        {
            string[i] = temp->number+48;
            temp = temp->next;
				string = realloc(string,(i+1)*sizeof(char));
				i++;
        }
    }
	string[i] = '\0';
	return string;
}

longInt divisionResidue(longInt a, longInt b)
{
    longInt tempA = copyNumber(a);
    longInt residue = subtraction(tempA, multiplication(b,division(a,b)));
    freeBigInteger(&tempA);
    return residue;
}

void multByTen(longInt a)
{
	bigInt* num = a->tail;
	bigInt* temp = (bigInt*) malloc(sizeof(bigInt));
	temp->next = NULL;
	temp->number = 0;
	temp->prev = num;
	num->next = temp;
	a->tail = temp;
}


longInt multiplication(longInt a, longInt b)
{
	if((a == NULL) || (b == NULL))
	{
		return NULL;
	}
	if (checkError(a) || checkError(b))
	{
		return NULL;
	}
	longInt result = createBigInteger("0");
	int aSign = a->signFlag;
	int bSign = b->signFlag;
	if(checkIfZero(a) || checkIfZero(b))
	{
		return result;
	}
	if(a->signFlag)
    {
        invertBigIntegerSign(a);
    }
    if(b->signFlag)
    {
        invertBigIntegerSign(b);
    }
	longInt copy = copyNumber(a);
	bigInt* bNum = b->tail;
	int i,count;
	longInt temp;
	while(bNum != NULL)
	{
		count = bNum->number;
		i = 0;
		temp = createBigInteger("0");
		while (i<count)
		{
			i++;
			temp = addition(copy,temp);
		}
		result = addition(result, temp);
		if(temp != NULL)
		{
			freeBigInteger(&temp);
		}
		bNum = bNum->prev;
		multByTen(copy);
	}
	freeBigInteger(&copy);

   if(aSign == bSign)
   {
   	result->signFlag=0;
   }
   else
	{
		result->signFlag=1;
	}
	a->signFlag = aSign;
	b->signFlag = bSign;
   return result;
}
int getLength(longInt a)
{
    int length = 0;
    bigInt* temp = a->head;
    while(temp != NULL)
    {
        temp = temp->next;
        length++;
    }
    return length;
}


longInt division(longInt a, longInt b)
{
	if((a == NULL) || (b == NULL))
	{
		return NULL;
	}
	if (checkError(a) || checkError(b))
	{
		return NULL;
	}

    longInt result = createBigInteger("0");
    int aSign = a->signFlag;
    int bSign = b->signFlag;
    if(checkIfZero(b))
    {
        result->error = 3;
        return result;
    }
    if(a->signFlag)
    {
        invertBigIntegerSign(a);
    }
    if(b->signFlag)
    {
        invertBigIntegerSign(b);
    }
    longInt one = createBigInteger("1");
    if(unSignedBigIntegerCompare(b,one) == 0)
	{
		result = copyNumber(a);
		if(aSign == bSign)
		{
			result->signFlag=0;
		}
        else result->signFlag=1;

        a->signFlag = aSign;
        b->signFlag = bSign;
        return result;
	}
	int lengthDifference = getLength(a) - getLength(b);
    longInt tempA = copyNumber(a);
    longInt copy;
    if(lengthDifference<=0)
    {
        while(unSignedBigIntegerCompare(tempA,b)!= -1)
        {
            copy = tempA;
            tempA = subtraction(tempA, b);
            freeBigInteger(&copy);
            copy = result;
            result = addition(result, one);
            freeBigInteger(&copy);
        }
    }
    else
    {
        int tempLenDif=1;
        while(tempLenDif>0)
        {
            int i=0;
            longInt tempB = copyNumber(b);
            longInt tempResult = createBigInteger("0");
            tempLenDif = getLength(tempA) - getLength(tempB);
            for(i;i<tempLenDif;i++)
            {
                multByTen(tempB);
            }
            i=0;
            if(unSignedBigIntegerCompare(tempA,tempB) == 1)
            {
                while(unSignedBigIntegerCompare(tempA,tempB)!= -1)
                {
                    copy = tempA;
                    tempA = subtraction(tempA, tempB);
                    freeBigInteger(&copy);
                    copy = tempResult;
                    tempResult = addition(tempResult, one);
                    freeBigInteger(&copy);
                }
                for(i;i<tempLenDif;i++)
                {
                    multByTen(tempResult);
                }
            }
            else
            {
                int tempLenDif2 = tempLenDif-1;
                int j=0;
                freeBigInteger(&tempB);
                tempB = copyNumber(b);
                for(j;j<tempLenDif2;j++)
                {
                    multByTen(tempB);
                }
                j=0;
                while(unSignedBigIntegerCompare(tempA,tempB)!= -1)
                {
                    copy = tempA;
                    tempA = subtraction(tempA, tempB);
                    freeBigInteger(&copy);
                    copy = tempResult;
                    tempResult = addition(tempResult, one);
                    freeBigInteger(&copy);
                }
                for(j;j<tempLenDif2;j++)
                {
                    multByTen(tempResult);
                }
            }
            copy = result;
            result = addition(result,tempResult);
            freeBigInteger(&copy);
            freeBigInteger(&tempResult);
            freeBigInteger(&tempB);
        }
    }
    if(aSign == bSign)
    {
        result->signFlag=0;
    }
    else result->signFlag=1;
    a->signFlag = aSign;
    b->signFlag = bSign;
    trimFrontZeros(result);
    return result;
}


int checkIfZero(longInt number)
{
    if( (number->tail->prev == NULL) && (number->tail->number == 0) )
    {
        return 1;
    }
    return 0;
}

longInt copyNumber (longInt a)
{
    if(a != NULL)
    {
        longInt copy = (longInt) malloc(sizeof(BigInteger));
        copy->head = NULL;
        copy->tail = NULL;
        copy->error = 0;
        copy->signFlag = a->signFlag;
        bigInt* temp = a->head;

        bigInt* tempBigInt = (bigInt*) malloc(sizeof(bigInt));
        tempBigInt->next = NULL;
        tempBigInt->prev = NULL;
        tempBigInt->number = temp->number;
        copy->head = tempBigInt;
        temp = temp->next;
        while(temp != NULL)
        {
            bigInt* tempBigInt2 = malloc(sizeof(bigInt));
            tempBigInt->next = tempBigInt2;
            tempBigInt2->prev = tempBigInt;
            tempBigInt2->next = NULL;
            tempBigInt2->number = temp->number;
            tempBigInt = tempBigInt2;
            temp = temp->next;
        }
        copy->tail = tempBigInt;
        return copy;
    }
    else return NULL;

}

int unSignedBigIntegerCompare(longInt a, longInt b)// a<b = -1, a==b = 0, a>b == 1;
{
    int longerNumber = checkLongerNumber(a,b);
    bigInt* tempA = a->head;
    bigInt* tempB = b->head;

    if(longerNumber == -1) return -1;
    if(longerNumber == 1) return 1;
    if(longerNumber == 0)
    {
        while(tempA != NULL && tempB != NULL)
        {
            if(tempA->number > tempB->number) return 1;
            if(tempA->number < tempB->number) return -1;
            tempA = tempA->next;
            tempB = tempB->next;
        }
	return 0;
    }
}

int checkLongerNumber(longInt a, longInt b)
{
    bigInt* tempA = a->head;
    bigInt* tempB = b->head;

    while(tempA->next != NULL && tempB->next != NULL)
    {
        tempA = tempA->next;
        tempB = tempB->next;
    }
    if(tempA->next == NULL && tempB->next != NULL)
    {
        return -1;
    }
    if(tempA->next != NULL && tempB->next == NULL)
    {
        return 1;
    }
    if(tempA->next == NULL && tempB->next == NULL)
    {
        return 0;
    }
}

void invertBigIntegerSign(longInt a)
{
    if (a->signFlag == 0)
    {
        a->signFlag = 1;
        return;
    }
    else if (a->signFlag == 1)
    {
        a->signFlag = 0;
        return;
    }
}


longInt subtraction(longInt a, longInt b)
{
	if((a == NULL) || (b == NULL))
	{
		return NULL;
	}
	if (checkError(a) || checkError(b))
	{
		return NULL;
	}
	longInt dif = malloc(sizeof(longInt));
	dif->error = 0;
	int d = unSignedBigIntegerCompare(a,b);
	if (d == 0)
	{
		if (a->signFlag == b->signFlag)
		{
			dif = createBigInteger("0");
			return dif;
		}
		else if ((a->signFlag == 1) && (b->signFlag == 0))
		{
			b->signFlag = 1;
			dif = addition(a,b);
			b->signFlag = 0;
			return dif;
		}
		else
		{
			b->signFlag = 0;
			dif = addition(a,b);
			b->signFlag = 1;
			return dif;
		}
	}
	else if (a->signFlag != b->signFlag)
	{
		if(a->signFlag == 1)
		{
			b->signFlag = 1;
			dif = addition(a,b);
			b->signFlag = 0;
			return dif;
		}
		else
		{
			b->signFlag = 0;
			dif = addition(a,b);
			b->signFlag = 1;
			return dif;
		}
	}
	else
	{
		dif = createBigInteger("0");
		bigInt* aNum;
		bigInt* bNum;
		int carry = 0;
		bigInt* t = (bigInt*) malloc(sizeof(bigInt));
		bigInt* p = NULL;
		t->next = NULL;
		t->prev = NULL;
		dif->tail = t;
		if (d == 1)
		{
			aNum = a->tail;
			bNum = b->tail;
			dif->signFlag = a->signFlag;
		}
		else
		{
			aNum = b->tail;
			bNum = a->tail;
			if(b->signFlag == 1)
			{
				dif->signFlag = 0;
			}
			else
			{
				dif->signFlag = 1;
			}
		}

		t->number = (aNum->number - bNum->number - carry)%10;
		if(t->number<0)
		{
			carry = 1;
			t->number+=10;
		}
		aNum = aNum->prev;
		bNum = bNum->prev;
		while((aNum != NULL) && (bNum != NULL))
		{
			p = t;
			t = (bigInt*) malloc(sizeof(bigInt));
			t->next = p;
			t->prev = NULL;
			p->prev = t;
			t->number = (aNum->number - bNum->number - carry)%10;
			if((t->number<0))
			{
				carry = 1;
				t->number+=10;
			}
			else
			{
				carry = 0;
			}
			aNum = aNum->prev;
			bNum = bNum->prev;
		}
		while(aNum != NULL)
		{
			p = t;
			t = (bigInt*) malloc(sizeof(bigInt));
			t->next = p;
			t->prev = NULL;
			p->prev = t;
			t->number = (aNum->number - carry)%10;
			if (t->number < 0)
				{
					carry = 1;
					t->number += 10;
				}
			else
			{
				carry = 0;
			}
			aNum = aNum->prev;
		}
		dif->head = t;
		trimFrontZeros(dif);
		return dif;
	}
}


longInt addition(longInt a, longInt b)
{
	if((a == NULL) || (b == NULL))
	{
		return NULL;
	}
	if (checkError(a) || checkError(b))
	{
		return NULL;
	}
	int d;
	longInt sum = malloc(sizeof(longInt));
	sum->error = 0;
	if (a->signFlag != b->signFlag)
	{
		if(a->signFlag == 1)
		{
			a->signFlag = 0;
			sum = subtraction(b,a);
			a->signFlag = 1;
		}
		else
		{
			b->signFlag = 0;
			sum = subtraction(a,b);
			b->signFlag = 1;
		}
		d = unSignedBigIntegerCompare(a,b);
		if (d==0)
		{
			return sum;
		}
		else if( d == -1)
		{
			sum->signFlag = b->signFlag;
		}
		else
		{
			sum->signFlag = a->signFlag;
		}
		return sum;
	}
	else
	{
		bigInt* aNum = a->tail;
		bigInt* bNum = b->tail;
		bigInt* t = (bigInt*) malloc(sizeof(bigInt));
		bigInt* p = NULL;
		t->next = NULL;
		t->prev = NULL;
		sum->tail = t;
		sum->signFlag = a->signFlag;
		t->number = (aNum->number + bNum->number)%10;
		int carry = (aNum->number + bNum->number)/10;
		aNum = aNum->prev;
		bNum = bNum->prev;
		while ((aNum != NULL) && (bNum != NULL))
		{
			p = t;
			t = (bigInt*) malloc(sizeof(struct bigInt));
			t->next = p;
			t->prev = NULL;
			p->prev = t;
			t->number = (aNum->number + bNum->number + carry) % 10;
			carry = (aNum->number + bNum->number + carry) / 10;
			aNum = aNum->prev;
			bNum = bNum->prev;
			}
		bigInt* e = NULL;
		if (aNum != NULL)
		{
			e = aNum;
		}
		else if (bNum != NULL)
		{
			e = bNum;
		}
		else
		{
			if (carry)
			{
				p = t;
				t = (bigInt*) malloc(sizeof(bigInt));
				p->prev = t;
				t->prev = NULL;
				t->number = 1;
				t->next = p;
			}
			sum->head = t;
			trimFrontZeros(sum);
			return sum;
		}

		while (e != NULL)
		{
			p = t;
			t =(bigInt*) malloc(sizeof(bigInt));
			t->number = e->number + carry;
			carry = 0;
			t->next = p;
			t->prev = NULL;
			p->prev = t;
			e = e->prev;
		}
		sum->head = t;
        trimFrontZeros(sum);
		return sum;
	}
}



int checkNumber(char* string)
{
    int i = 0;
	 if(string[0] == '0' && string[1] != 0)
	 {
		return -1;
	 }
	 else if(string[0] == '-' && string[1] == '\0')
	 {
		return -1;
	 }
	 else if (string[0] == '-' && string[1] == '0')
	 {
		return -1;
	 }
	 else if(string[0]=='-')
	 {
		i++;
	 }
		while(string[i])
    	{
        if((string[i]<'0') || (string[i]>'9'))
        {
            return 0;
        }
        i++;
    	}
    	return 1;
}


longInt createBigInteger(char* string)
{
	int d = checkNumber(string);
    if(d == 1)
    {
        longInt number = (longInt) malloc(sizeof(BigInteger));
        if(number == NULL)
        {
            return NULL;
        }
        else
        {
            number->head = NULL;
            number->tail = NULL;
            number->error = 0;

            int i = 0;
            bigInt* tempBigInt = NULL;
            if(string[0] == '-')
            {
                number->signFlag = 1;
                i++;
            }
            else number->signFlag = 0;
            tempBigInt = (bigInt*) malloc(sizeof(bigInt));
            tempBigInt->next = NULL;
            tempBigInt->prev = NULL;
            tempBigInt->number = string[i] - 48;
            number->head = tempBigInt;
            i++;
            while(string[i])
            {
                bigInt* temp = malloc(sizeof(bigInt));
                tempBigInt->next = temp;
                temp->prev = tempBigInt;
                temp->next = NULL;
                temp->number = string[i] - 48;
                tempBigInt = temp;
                i++;
            }
            number->tail = tempBigInt;
        }
   //     trimFrontZeros(number);
        return number;
    }
    else if (d == 0)
    {
        longInt number = (longInt) malloc(sizeof(longInt));
        number->error = 2;
        return number;
    }
	 else
	 {
		  longInt number = (longInt) malloc(sizeof(longInt));
		  number->error = 1;
		  return number;
	 }
}


void printInteger(longInt number)
{
    if(number != NULL)
    {
        bigInt* temp = number->head;
        if(number->signFlag) printf("%c", '-');
        while(temp != NULL)
        {
            printf("%d", temp->number);
            temp = temp->next;
        }
    }
}

void trimFrontZeros(longInt number)
{
    bigInt* temp = number->head;
	if (temp->next == NULL)
	{
		return;
	}
    while (temp->number == 0 && temp->next !=NULL)
    {
        number->head = temp->next;
        free (temp);
        temp = number->head;
        temp->prev = NULL;  
    }
}


void freeBigInteger(longInt* number)
{
	longInt temp = *number;
	if (temp != NULL)
	{
		bigInt* tempBigInt = temp->head;
		while(tempBigInt->next != NULL)
        {
            tempBigInt = tempBigInt->next;
            free(tempBigInt->prev);
        }
        free(tempBigInt);
        free(temp);
	}
}
int checkError(longInt number)
{
    return number->error;
}


