//
// Created by Administrator on 10/05/2026.
//

#include "menu.h"
#include <stdio.h>
#include <stdbool.h>

bool fileEsiste(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return true;
    }
    return false;
}

int menuIniziale() {
    int scelta;
    bool save_presente = fileEsiste("savegame.sav");

    printf("Benvenuti a Monopoli - PR1 EDITION!\n\n");
    printf("Premi:\n");
    printf("1) per INIZIARE una nuova Partita\n");

    if (save_presente)
        printf("2) per CARICARE una partita da savegame.sav\n");
    else
        printf("2) (DISABILITATO - nessun salvataggio presente)\n");

    printf("0) per USCIRE dal gioco!\n\n");

    do {
        printf("Inserisci la tua scelta tra 0 e 2: ");
        scanf("%d", &scelta);

        if (scelta == 2 && !save_presente) {
            printf("Errore: nessun file di salvataggio presente.\n");
            scelta = -1;
        }

    } while (scelta < 0 || scelta > 2);

    return scelta;
}