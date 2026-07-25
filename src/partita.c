//
// Created by Administrator on 24/07/2026.
//

#include "partita.h"

#include <stdio.h>
#include <stdlib.h>
#include "turno.h"

static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome);
    printf("1) Tira i dadi\n");
    printf("2) Mostra giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("4) Mostra carte\n");
    printf("5) Salva partita\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;
    scanf("%d", &scelta);

    return scelta;
}

void avviaPartita(Giocatore *g, int n, Casella *tabellone) {

    int turno = 0;
    int finePartita = 0;
    Giocatore * giocatori =NULL;

    while (!finePartita) {

        Giocatore *corrente = &g[turno];

        int scelta = menuTurno(corrente);

        switch (scelta) {

            case 1: {
                int dado = (rand() % 6) + 1;
                printf("%s tira il dado: %d\n", corrente->nome, dado);
                muoviGiocatore(corrente, dado);
                break;
            }

            case 2:
                for (int i = 0; i < n; i++)
                    stampaGiocatore(g[i]);
                break;

            case 3:
                stampaTabellone(tabellone);
                break;

            case 4:
                printf("Le carte non sono ancora implementate.\n");
                break;

            case 5:
            printf("Partita salvata!\n");
            salvaPartita(giocatori, n, tabellone);
                break;

            case 0:
                printf("Hai scelto di uscire dal gioco.\n");
                finePartita = 1;
                break;

            default:
                printf("Scelta non valida.\n");
        }

        // passa al giocatore successivo
        turno = (turno + 1) % n;
    }
}

void caricaPartita(Giocatore **g, int *n, Casella *tab) {
    FILE *fp = fopen("savegame.sav", "rb");
    if (!fp) return;

    fread(n, sizeof(int), 1, fp);

    *g = malloc(sizeof(Giocatore) * (*n));

    for (int i = 0; i < *n; i++) {

        // carica nome
        fread((*g)[i].nome, sizeof(char), 32, fp);

        // carica soldi
        fread(&(*g)[i].cfu, sizeof(int), 1, fp);

        // carica posizione
        int pos;
        fread(&pos, sizeof(int), 1, fp);
        (*g)[i].posizione = casellaDaIndice(tab, pos);
    }

    fclose(fp);
}
