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

int menuIniziale() {
    int scelta;

    printf("Benvenuti a Monopoli - PR1 EDITION!\n\n");
    printf("Premi:\n");
    printf("1) per INIZIARE una nuova partita\n");
    printf("2) per CARICARE una partita da savegame.sav\n");
    printf("0) ESCI dal gioco\n\n");
    printf("Inserisci la tua scelta: ");

    scanf("%d", &scelta);

    while (scelta < 0 || scelta > 2) {
        printf("Scelta non valida. Inserisci 0,1 o 2: ");
        scanf("%d", &scelta);
    }


    return scelta;
}
