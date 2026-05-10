//
// Created by Administrator on 10/05/2026.
//

#include "caselle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Casella *creaCasella(char *nome, int tipo, int colore, int costo) {
    Casella *c = malloc(sizeof(Casella));
    if (!c) return NULL;

    strcpy(c->nome, nome);
    c->tipo = tipo;
    c->colore = colore;
    c->costo = costo;

    c->sedie = 0;
    c->scrivania = false;
    c->proprietario = NULL;

    c->next = NULL;
    c->prev = NULL;

    return c;
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

Casella *caricaTabellone(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Errore apertura file tabellone.txt\n");
        return NULL;
    }

    Casella *tabellone = NULL;

    int id, tipo, colore, costo;
    char nome[DIM_NOME];

    while (fscanf(fp, "%d %30s %d %d %d",
                  &id, nome, &tipo, &colore, &costo) == 5) {

        Casella *c = creaCasella(nome, tipo, colore, costo);
        tabellone = inserisciInCoda(tabellone, c);
                  }

    fclose(fp);
    return tabellone;
}

void stampaTabellone(Casella *head) {
    if (!head) return;

    Casella *curr = head;
    int i = 0;

    do {
        printf("%2d) %-30s Tipo=%d Colore=%d Costo=%d\n",
               i, curr->nome, curr->tipo, curr->colore, curr->costo);
        curr = curr->next;
        i++;
    } while (curr != head);
}
void testTabellone(Casella *head) {
    if (!head) {
        printf("Tabellone vuoto.\n");
        return;
    }

    Casella *curr = head;
    int count = 0;

    printf("\n--- TEST TABELLONE ---\n");

    do {
        printf("Nodo %2d | Nome: %-25s | Addr: %p | Next: %p | Prev: %p\n",
               count, curr->nome, (void*)curr, (void*)curr->next, (void*)curr->prev);

        curr = curr->next;
        count++;

        if (count > 100) {
            printf("ERRORE: la lista non è circolare (loop infinito)\n");
            return;
        }

    } while (curr != head);

    printf("\nTotale caselle: %d\n", count);

    if (count == 40)
        printf("OK: Il tabellone contiene 40 caselle.\n");
    else
        printf("ERRORE: Il tabellone NON contiene 40 caselle.\n");

    printf("-----------------------\n\n");
}
