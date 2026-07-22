//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "menu.h"
#include <stdio.h>
#include <stdbool.h>

bool fileEsiste(const char *filename) {//dichiaro il file di gioco, se esiste e quindi
    //c'è una partita dichiaro true altrimenti false grazie al tipo Bool

    FILE *fp = fopen(filename, "read binary");//Dichiara e inizializza un puntatore a FILE, cioè un handle verso
    //un file aperto, non è il file, non è il contenuto, non è un percorso.
    //Un handle è un oggetto che rappresenta il file aperto (fopen), così il sistema operativo sa quale file stiamo usando.
    //E prova ad aprire quel file in modalità rb (read binary).

    if (fp) {
        fclose(fp);
        return true;
    }
    return false;
}

int menuIniziale() {//inizializzo il menù
    int scelta;
    bool save_presente = fileEsiste("savegame.sav");

    printf("Benvenuti a Monopoli - PR1 EDITION!\n\n");//inizio a compilare il menu di gioco e stampare
    printf("Premi:\n");
    printf("\n1) per INIZIARE una nuova Partita\n");

    if (save_presente)//se il file è presente stamperà la partita precedente
        printf("\n2) per CARICARE una partita passata\n");

    else//altrimenti darà errore
        printf("\n2) Nessun salvataggio presente!\n");//siccome siamo ancora a inizio partita se non abbiamo dati
    //da stampare allora bisogna informare l'utente del fatto che non ci siano dati da stampare proprio perchè non ha giocato
        printf("\n0) per USCIRE dal gioco!\n");

    do {
        printf("Inserisci la tua scelta tra 0 e 2: ");
        scanf("%d", &scelta);

        if (scelta < 0 || scelta > 2) {//se la scelta non è tra le presenti e
            //l'utente mi dichiara un numero non incluso allora devo avvisarlo dell'errore
            printf("Errore: la scelta selezionata non esiste, riprovare!\n");
            scelta = -1;
        }

    } while (scelta < 0 || scelta > 2);//continuo a ripetere la condizione finché non seleziona il numero giusto

    return scelta;//è un tipo int quindi dovrà tornare qualcosa, in questo caso la scelta del giocatore
}