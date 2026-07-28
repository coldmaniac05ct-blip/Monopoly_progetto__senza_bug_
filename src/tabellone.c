//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "tabellone.h"
#include "giocatore.h"

Casella* caricaTabellone() {//si occupa di caricare il tabellone e in caso di problemi di lettura stmampa un messaggio di errore

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

void stampaTabellone(Casella *start) {//stampa a schermo il tabellone, quindi l'array
    //deve essere in grado di leggere tutti i dati necessari

    char *nomiTipo[] = {
        "NESSUNO", "AULA", "MENSA", "PARCHEGGIO", "ABBONAMENTO",
        "VIA", "BUG", "VAI_BATCAVERNA", "BATCAVERNA"
    };

    char *nomiColore[] = {
        "NESSUN_COLORE", "MARRONE", "CELESTE", "FUCSIA", "ARANCIONE",
        "ROSSO", "GIALLO", "VERDE", "BLU"
    };

    Casella *curr = start;
    int i = 0;

    printf("\n--- TABELLONE ---\n");

    do {

        // PRIMA RIGA (breve)
        printf("[%2d] Nome: %-25s | Tipo: %-15s | Colore: %-15s | Costo: %d\n",
               i,
               curr->nome,
               nomiTipo[curr->tipo],
               nomiColore[curr->colore],
               curr->costo);

        // SECONDA RIGA (proprietario)
        if (curr->proprietario != NULL)
            printf("     Proprietario: %-10s | Segnaposto: %s\n",
                   curr->proprietario->nome,
                   NomiSegnaPosto[curr->proprietario->segna_posto]);
        else
            printf("     Proprietario: nessuno | Segnaposto: -\n");

        printf("\n");

        curr = curr->next;
        i++;

    } while (curr != start);

    printf("Totale caselle: %d\n", i);
}
