//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "casella.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Casella *creaCasella(char *nome, int tipo, int colore, int costo) {//creo le caselle, ognuna di esse
    //dovrà avere un nome, un tipo, un colore e un costo
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

Casella *inserisciInCoda(Casella *head, Casella *nuova) {//è una funzione ricorsiva di tipo head-tail,
    //serve per capire su che casella ci troviamo
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

void testTabellone(Casella *head) {//faccio un test di prova per vedere se funziona a codice finito, in breve voglio capire se si avvia
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

    printf("\nTotale caselle: %d\n", count);//qua controllo le caselle per vedere se sono state generate correttamente

    if (count == 40)
        printf("OK: Il tabellone contiene 40 caselle.\n");
    else
        printf("ERRORE: Il tabellone NON contiene 40 caselle.\n");

    printf("-----------------------\n\n");
}
