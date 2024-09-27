// Hilfen für Aufgabenblatt 3: Primzahlen zählen

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "time_measurement.h"
#include "isPrime.h"

#define MAX_CORES 2

//Struktur der Argumente für die Funktion checkPrime
typedef struct {
    unsigned long from;
    unsigned long to;
}CountPrimeArguments;

//Struktur des Rückgabewerts von checkPrime
typedef struct {
    unsigned long count;
}CountPrimeResult;

void *checkPrime(void *args);

unsigned long totalRangeFrom = 2;
unsigned long totalRangeTo = 10000000;


int main(int argc, char *argv[])
{
    unsigned long sizeOfCount = (totalRangeTo - totalRangeFrom) / MAX_CORES; // ist die Anzahl der Werte, die ein Thread berechnen muss
    CountPrimeArguments arguments[MAX_CORES]; // ein Array, welches die Argumente für die Threads enthält
    CountPrimeResult returnValues[MAX_CORES]; // ein Array, welches die Ergebnisse der Threads enthält
    

    // Starten der Zeitmessung
    ...

    // Initialisierung der Argumente für die Threads
	...

    // Erzeugung der Threads
    for(i=0;i<MAX_CORES;i++){
        ... = pthread_create(..., NULL, checkPrime, &arguments[i]);
        ...
    }

    // Warten bis alle Threads fertig sind
    for(i=0;i<MAX_CORES;i++){
        CountPrimeResult *tempR;
        pthread_join(..., (void**)&tempR);
		...
    }

    // Summiere die Ergebnisse der Threads
	...
    
	// Ende der Zeitmessung
	...

	// Ausgabe der Anzahl der gefundenen Primzahlen und der benötigten Rechenzeit

    return 0;
}

void *checkPrime(void *args){
	/* Funktion in jedem Thread */
    CountPrimeArguments *arguments = (CountPrimeArguments *)args;
    CountPrimeResult *result = malloc(sizeof(CountPrimeResult));
	...

    for(i=arguments->from;i<=arguments->to;i++){
        ... isPrime(i)) ...
    }

    result->count = ...
    pthread_exit(result);
}


