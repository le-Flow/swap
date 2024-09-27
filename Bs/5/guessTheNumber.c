/*
 ============================================================================
 GuessTheNumber.c

 HAW Landshut
 Fakultät Informatik
 Modul: Betriebssysteme

 Aufgabenblatt 5


 Aufgabenstellung: Vervollständigen Sie die Stellen im Code, die mit
 "Bitte vervollständigen" gekennzeichnet sind.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>
#include <signal.h>

signed char evaluateNumber(unsigned int numberToGuess, unsigned int guessedNumber);
unsigned int guessNumber(unsigned int min, unsigned int max);
void parent_job(pid_t childPid);
void child_job();

int counter = 0;
int pipe1[2];  // parent
int pipe2[2];  // son

/* Die Filedeskriptoren zu den beiden Pipes*/
/* Bitte vervollständigen */


int main(void) {
	pid_t pid;
	int status;

	/* Einrichten der Pipes */
	/* Bitte vervollständigen */
    pipe(pipe1);
    pipe(pipe2);

	//fork() erzeugen
	switch(pid=fork()){
		case -1: /* Fehler bei fork() aufgetreten */
			return EXIT_FAILURE;
		case 0:  /* Kindprozess */
			child_job();
			break;
		default: /* Vaterprozess */
			parent_job(pid);
			break;
	}
	wait (&status);

	return EXIT_SUCCESS;


}

/* Der Vaterprozess */
void parent_job(pid_t childPid){

	printf("%d: Vater: Start\n",getpid());

	/* nicht benötigte Lese- und Schreibdeskriptoren schließen */
	/* Bitte vervollständigen */
    close(pipe1[1]);
    close(pipe2[0]);

	//* Eine Sekunde warten um sicher zu stellen, dass der Kindprozess bereit ist. */
	sleep(1);

	unsigned int resultGuess = guessNumber(0,RAND_MAX);

	printf("%d: Das Ergebnis %d wurde nach %d Versuchen ermittelt.\n", getpid(),resultGuess,counter);

	/* Vater beendet den Kindprozess */
	/* Bitte vervollständigen */
    kill(childPid, SIGKILL);

}

/* Der eigentliche Kindprozess */
void child_job(){

	/* Zufallszahl generieren */
	time_t t; /* Zeit für Zufallszahlengenerator */
	srand((unsigned) time(&t)); /* Initialisierung des Zufallszahlengenerators */
	unsigned int randNumber = rand();

	printf("%d: \t\t\t\tKind: Die zu erratende Zahl ist %d.\n",getpid(),randNumber);

	/* nicht benötigte Lese- und Schreibdeskriptoren schließen */
	/* Bitte vervollständigen */
    close(pipe1[0]);
    close(pipe2[1]);


	//der Kindprozess läuft so lange bis er vom Vater durch SIGKILL beendet wird
	while(1){
		unsigned int rcv;
		signed char result;
		/* Pipe auslesen */
		/* Bitte vervollständigen */
        read(pipe2[0], &rcv, sizeof(rcv));

#if 1
		char msg[200];
		sprintf(msg,"%d: \t\t\t\tKind: %d empfangen\n",getpid(),rcv);
		write (STDOUT_FILENO, msg, strlen(msg));
#endif

		/* Vergleich durchführen */
		result = evaluateNumber(randNumber,rcv);

		/* Ergebnis des Vergleichs in Pipe schreiben */
		/* Bitte vervollständigen */
        write(pipe1[1], &result, sizeof(result));

	}
}



signed char evaluateNumber(unsigned int numberToGuess, unsigned int guessedNumber){
	if(guessedNumber==numberToGuess){
		return 0;
	}
	return guessedNumber>numberToGuess ? 1 : -1; /* vgl. Aufgabenblatt */
}


unsigned int guessNumber(unsigned int min, unsigned int max) {

	signed char resultGuess;

	/* Intervallhalbierung ergibt die nächste Zahl, die geraten werden soll */
	unsigned int nextGuess = min + (max - min) / 2;

	/* Die nächste, geratene Zahl in die Pipe schreiben */
	/* Bitte vervollständigen */
    write(pipe2[1], &nextGuess, sizeof(nextGuess));


	/* Warten bis in der Pipe genug Daten enthalten sind und Antwort auslesen */
	/* Bitte vervollständigen */
    read(pipe1[0], &resultGuess, sizeof(resultGuess));

	counter++;

	/* Wenn die Zahl noch nicht erraten wurde: rekursiver Aufruf,
	   ansonsten wird die erratene Zahl zurückgegeben */
	switch (resultGuess) {
	case 1:
		return guessNumber(min, nextGuess);
	case -1:
		return guessNumber(nextGuess, max);
	default:
		return nextGuess;
	}

}


