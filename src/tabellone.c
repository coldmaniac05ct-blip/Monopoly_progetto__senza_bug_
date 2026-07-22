//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "tabellone.h"

Casella* caricaTabellone() {
    FILE *fp = fopen(NOME_FILE, "r");
    if (fp == NULL) {
        printf("Errore: impossibile aprire %s\n");
        exit(EXIT_FAILURE);
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
