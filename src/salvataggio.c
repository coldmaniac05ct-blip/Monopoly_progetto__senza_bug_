//
// Created by Administrator on 25/07/2026.
//

#include "salvataggio.h"

int indiceGiocatore(Giocatore *giocatori, int numGiocatori, Giocatore *g) {
    for (int i = 0; i < numGiocatori; i++) {
        if (&giocatori[i] == g)
            return i;
    }
    return -1; // giocatore non trovato (casella libera)
}

void salvaPartita(Giocatore *g, int n, Casella *tabellone) {

    FILE *fp = fopen("savegame.sav", "wb");
    if (!fp) {
        printf("Errore: impossibile creare savegame.sav\n");
        return;
    }

    // 1) salva numero giocatori
    fwrite(&n, sizeof(int), 1, fp);

    // 2) salva ogni giocatore
    for (int i = 0; i < n; i++) {

        fwrite(g[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);
        fwrite(&g[i].cfu, sizeof(int), 1, fp);
        fwrite(&g[i].turni_batcaverna, sizeof(int), 1, fp);
        fwrite(&g[i].saltaTurno, sizeof(bool), 1, fp);
        fwrite(&g[i].nuovo_turno, sizeof(int), 1, fp);
        fwrite(&g[i].numero_aule_mense, sizeof(int), 1, fp);
        fwrite(&g[i].segna_posto, sizeof(int), 1, fp);

        // salva posizione come indice
        int posIndex = indiceCasella(tabellone, g[i].posizione);
        fwrite(&posIndex, sizeof(int), 1, fp);
    }

    // 3) salva tutte le caselle del tabellone
    Casella *c = tabellone;
    do {
        fwrite(&c->sedie, sizeof(int), 1, fp);
        fwrite(&c->scrivania, sizeof(int), 1, fp);

        int proprietarioIndex = -1;
        if (c->proprietario != NULL)
            proprietarioIndex = indiceGiocatore(g, n, c->proprietario);

        fwrite(&proprietarioIndex, sizeof(int), 1, fp);

        c = c->next;
    } while (c != tabellone);

    fclose(fp);
    printf("Partita salvata correttamente!\n");
}
