//
// Created by Administrator on 10/05/2026.
//

#include "tabellone.h"
#include <stdio.h>
#include <stdlib.h>

Casella* caricaTabellone(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Errore: impossibile aprire %s\n", filename);
        return NULL;
    }

    Casella *start = NULL;
    Casella *prev = NULL;

    for (int i = 0; i < 40; i++) {
        Casella *c = malloc(sizeof(Casella));

        fscanf(fp, "%31[^;];%d;%d;%d\n",
               c->nome,
               (int*)&c->tipo,
               (int*)&c->colore,
               &c->costo);

        c->sedie = 0;
        c->scrivania = false;
        c->occupante = NULL;
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
    Casella *curr = start;
    int i = 0;

    do {
        printf("[%2d] %-30s Tipo=%d Colore=%d Costo=%d\n",
               i, curr->nome, curr->tipo, curr->colore, curr->costo);
        curr = curr->next;
        i++;
    } while (curr != start);
}
Casella *inserisciInCoda(Casella *head, Casella *nuova) {
    if (!head) {
        nuova->next = nuova;
        nuova->prev = nuova;
        return nuova;
    }

    Casella *tail = head->prev;

    tail->next = nuova;
    nuova->prev = tail;

    nuova->next = head;
    head->prev = nuova;

    return head;
}
