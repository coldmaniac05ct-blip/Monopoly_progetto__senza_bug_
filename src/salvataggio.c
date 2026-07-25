//
// Created by Administrator on 25/07/2026.
//

#include "salvataggio.h"


void salvaPartita(Giocatore *giocatori, int numGiocatori, Casella *tabellone) {
    FILE *fp = fopen("savegame.sav", "wb");
    if (!fp) {
        printf("Errore: impossibile creare savegame.sav\n");
        return;
    }

    // 1) salva numero giocatori
    fwrite(&numGiocatori, sizeof(int), 1, fp);

    // 2) salva ogni giocatore
    for (int i = 0; i < numGiocatori; i++) {

        // salva nome, cfu, ecc.
        fwrite(&giocatori[i], sizeof(Giocatore), 1, fp);

        // salva posizione come indice
        int posIndex = indiceCasella(tabellone, giocatori[i].posizione);
        fwrite(&posIndex, sizeof(int), 1, fp);
    }

    fclose(fp);
    printf("Partita salvata correttamente!\n");
}
