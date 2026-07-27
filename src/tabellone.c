//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "tabellone.h"
#include "giocatore.h"

Casella* caricaTabellone() {

    FILE *fp = fopen(NOME_FILE, "r");
    if (fp == NULL) {
        printf("Errore: impossibile aprire %s\n", NOME_FILE);
        exit(EXIT_FAILURE);
    }

    Casella *start = NULL;
    Casella *prev = NULL;

    for (int i = 0; i < 40; i++) {

        Casella *c = malloc(sizeof(Casella));

        int indice; // <-- il numero all'inizio della riga

        fscanf(fp, "%d %31s %d %d %d",
               &indice,
               c->nome,
               &c->tipo,
               &c->colore,
               &c->costo);

        c->sedie = 0;
        c->scrivania = false;
        c->proprietario = NULL;
        c->next = NULL;
        c->prev = NULL;

        if (!start) {
            start = c;
        } else {
            prev->next = c;
            c->prev = prev;
        }

        prev = c;
    }

    start->prev = prev;
    prev->next = start;

    fclose(fp);
    return start;
}

void stampaTabellone(Casella *start) {

    //array dei nomi dei tipi (enum TipoCasella)
    char *nomiTipo[] = {
        "NESSUNO", "AULA", "MENSA", "PARCHEGGIO", "ABBONAMENTO",
        "VIA", "BUG", "VAI_BATCAVERNA", "BATCAVERNA"
    };

    //array dei nomi dei colori (enum ColoreCasella)
    char *nomiColore[] = {
        "NESSUN_COLORE", "MARRONE", "CELESTE", "FUCSIA", "ARANCIONE",
        "ROSSO", "GIALLO", "VERDE", "BLU"
    };

    Casella *curr = start;
    int i = 0;

    printf("\n--- TABELLONE ---\n");

    do {
        printf("[%2d] Nome: %-25s | Tipo: %-15s | Colore: %-15s | Costo: %d\n",
               i,
               curr->nome,
               nomiTipo[curr->tipo],      // <-- stampa il nome dell’enum
               nomiColore[curr->colore],  // <-- stampa il nome dell’enum
               curr->costo);

        curr = curr->next;
        i++;

    } while (curr != start);

    printf("Totale caselle: %d\n", i);
}
