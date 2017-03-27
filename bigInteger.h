#ifndef BIGINTEGER_H
#define BIGINTEGER_H

/* Darbo atliko:
 * 673
 * 774
 */

typedef struct bigIntHead{
		struct bigInt* head;
        struct bigInt* tail;
        short signFlag;
        short error;
}BigInteger;

typedef BigInteger* longInt;

typedef struct bigInt{
    struct bigInt* next;
    struct bigInt* prev;
    short number;
}bigInt;


/* longInt tipo kintamojo sukurimo pavyzdys
 * longInt a = NULL;
 * longInt a = createBigInteger("1234567890");
 *
 * Pries priskiriant kita reiksme butina atlaisvinti kintamaji
 * freeBigInteger(&a);
 *
 */

char* bigIntegerToString(longInt); 				/* paduodamas longInt tipo kintamasis, o grazinama	*/ 															/* reiksme string'o tipo									*/
void printInteger(longInt); 						/* atspausdina longInt tipo kintamaji					*/
longInt createBigInteger(char*);					/* sukuria longInt tipo kintamaji						*/
void freeBigInteger(longInt*);					/*	atlaisvina atminti nuo kintamojo						*/
int checkError(longInt);							/*	grazina klaidos koda										*/
longInt addition(longInt, longInt);				/* sudeda du longInt tipo kintamuosius					*/
longInt subtraction(longInt, longInt);			/* atima du longInt tipo kintamuosius					*/
longInt multiplication(longInt, longInt);		/* sudaugina du longInt tipo kintamuosius				*/
longInt division(longInt, longInt);				/* padalina pirma longInt tipo kintamaji is antro	*/
longInt divisionResidue(longInt, longInt);	/* grazina dalybos liekana									*/
#endif

/* pavyzdziai
 * longInt c = addition(a,b);
 * longInt d = subtraction(c,a);
 * freeBigInteger(&d);
 * d = division(c,b);
 */ 

/* kilus klaidai, jos numeri galima
 * suzinoti iskvietus funkcija checkError
 ***********Klaidu sarasas********************
 * 1 - netinkamas skaiciu formatas
 * 2 - ivestas string'as nera skaiciu masyvas
 * 3 - dalyba is nulio
 *********************************************
 */


