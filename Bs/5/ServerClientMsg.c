/*
 ============================================================================
 ServerClientMsg.c

 HAW Landshut
 Fakultät Informatik
 Modul: Betriebssysteme


 Aufgabenblatt 5

 Aufgabenstellung: Vervollständigen Sie die Stellen im Code, die mit
 "Bitte vervollständigen" gekennzeichnet sind.

 ============================================================================
 */

#include "ServerClientMsg.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

/* Methode zum Einrichten bzw. Öffnen einer Message-Queue */
static int msqid = 0;
int setupQueue(){
	/* Bitte vervollständigen */
    if (msqid) {
        return msqid;
    } else {
        puts("neu");
        return msgget(MQ_KEY, IPC_CREAT | 0777);
    }
}

/* Methode zum Verschicken einer Nachricht
 *
 * type 	Nachrichtentyp
 * content  Nachrichteninhalt (vgl. ServerClientMsg.h)
 *
 */
int sendMessage(long type, msg_content content){
    int qid,msgres;
    msg message;

    /* Einrichten bzw. Öffnen der Message-Queue */
    qid = setupQueue();
    if(qid<0){
        printf("Fehler beim Einrichten oder Öffnen der Message Queue\n");
        return -1;
    }else{
        message.type = type;
        message.content = content;

        /* Das eigentliche Senden der Nachricht */
        /* Bitte vervollständigen */
        msgsnd(qid, &message, sizeof(message) - sizeof(long), 0);
        return 0;
    }
}


