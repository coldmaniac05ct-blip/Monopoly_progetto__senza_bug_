//
// Created by Administrator on 10/05/2026.
//

#include "carte.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Carta* caricaMazzo(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Errore: impossibile aprire %s\n", filename);
        return NULL;
    }

    Carta *head = NULL;
    Carta *tail = NULL;

    while (!feof(fp)) {
        Carta *c = malloc(sizeof(Carta));

        fscanf(fp, "%31[^;];%255[^;];%d;%d;",
               c->nome,
               c->descrizione,
               (int*)&c->tipo,
               &c->numero_effetti);

        c->effetti = malloc(sizeof(Effetto) * c->numero_effetti);

        for (int i = 0; i < c->numero_effetti; i++) {
            fscanf(fp, "%d,%d,%d;",
                   (int*)&c->effetti[i].azione,
                   &c->effetti[i].quantita,
                   (int*)&c->effetti[i].tipo_casella);
        }

        c->next = NULL;

        if (!head) {
            head = c;
            tail = c;
        } else {
            tail->next = c;
            tail = c;
        }
    }

    fclose(fp);
    return head;
}

void mescolaMazzo(Carta **mazzo) {
    if (!(*mazzo)) return;

    int count = 0;
    Carta *tmp = *mazzo;
    while (tmp) {
        count++;
        tmp = tmp->next;
    }

    Carta **array = malloc(sizeof(Carta*) * count);
    tmp = *mazzo;
    for (int i = 0; i < count; i++) {
        array[i] = tmp;
        tmp = tmp->next;
    }

    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta *swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }

    for (int i = 0; i < count - 1; i++)
        array[i]->next = array[i + 1];

    array[count - 1]->next = NULL;
    *mazzo = array[0];

    free(array);
}

Carta* pescaCarta(Carta **mazzo) {
    if (!(*mazzo)) return NULL;

    Carta *c = *mazzo;
    *mazzo = (*mazzo)->next;
    c->next = NULL;
    return c;
}

void inserisciInFondo(Carta **mazzo, Carta *c) {
    if (!(*mazzo)) {
        *mazzo = c;
        c->next = NULL;
        return;
    }

    Carta *tmp = *mazzo;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = c;
    c->next = NULL;
}

void stampaMazzo(Carta *mazzo) {
    int i = 0;
    while (mazzo) {
        printf("[%d] %s (%d effetti)\n", i, mazzo->nome, mazzo->numero_effetti);
        mazzo = mazzo->next;
        i++;
    }
}


