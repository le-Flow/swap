// Hilfen für Aufgabenblatt 3: Matrixmultiplikation

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DIM 5

int mA[DIM][DIM];
int mB[DIM][DIM];
int mR[DIM][DIM];

void init(int m[DIM][DIM], int value);
void print(int m[DIM][DIM]);
void mult();
void mult_with_threads();
void *threadMult(void *pl);


int main(int argc, char *argv[]){
    const int range = 5;
    time_t t;
    srand((unsigned) time(&t)); // Initialisierung des Zuffallszahlengenerators

    init(mA,range);
    init(mB,range);

    print(mA);
    print(mB);

    mult(); /* sequentielle Implementierung --> ist zu ersetzen durch parallele Implementierung */
    // mult_with_threads();

    print(mR);
}


// Initialisierung einer Matrix; value gibt den Maximalwert vor
void init(int m[DIM][DIM], int value){
    int l,n;
    for(l=0;l<DIM;l++){
        for(n=0;n<DIM;n++){
            m[l][n] = rand()%value;
        }
    }
}

void zero(int m[DIM][DIM]){
    int l,n;
    for(l=0;l<DIM;l++){
	for(n=0;n<DIM;n++){
            m[l][n] = 0;
        }
    } 
}

void print(int m[DIM][DIM]){
    int l,n;
    printf("\n----------------------------------------------\n");
    for(l=0;l<DIM;l++){
	for(n=0;n<DIM;n++){
            printf("\t%d",m[l][n]);
        }
        printf("\n");
    }
    printf("----------------------------------------------\n");
}

// Multipliziert zwei Matrizen miteinander und nutzt dafür Threads (einen Thread pro Zeile)
void mult_parallel(){
	
	...
	int al[DIM]; /* Es ist notwendig, dass während des Ablaufens der Threads die Parameter erhalten bleiben */
    pthread_t thread[DIM];
	...

    // Für jede Zeile der Ergebnismatrix einen Thread starten	
    for(l=0;l<DIM;l++){   
    	al[l]=l;
        ... = pthread_create(&thread[l], NULL, threadMult, &( al[l] ) );
        ... 
	}

    // Auf die Beendigung aller Threads warten	
    for(l=0;l<DIM;l++){
        pthread_join(...);
	}
    
}

void *threadMult(void *pl){
	// Thread-Funktion berechnet die Zeile l der Ergebnismatrix
    ...
    for(n=0;n<DIM;n++){         // Schleife über alle Spalten der Ergebnismatrix
        for(m=0;m<DIM;m++){     // Schleife für Skalarprodukt "Zeilenvektor l von mA * Spaltenvektor n von mB"
            ...
        }
    }
	...
}

void mult(){
    int l,n,m;
    
    zero(mR);

    for(l=0;l<DIM;l++){             // Schleife über Zeilen der Ergebnismatrix
		for(n=0;n<DIM;n++){         // Schleife über Spalten der Ergebnismatrix
			for(m=0;m<DIM;m++){     // Schleife für Skalarprodukt "Zeilenvektor l von mA * Spaltenvektor n von mB"
				mR[l][n] = mR[l][n] + mA[l][m] * mB[m][n];
			}
		}
    }
}
