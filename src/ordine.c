//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "ordine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static int tiraDado() {
    return (rand() % 6) + 1;
}

static void swap(Giocatore *a, Giocatore *b) {
    Giocatore tmp = *a;
    *a = *b;
    *b = tmp;
}

void determinaOrdine(Giocatore *g, int n) {

    srand(time(NULL));

    int valori[4];   // max 4 giocatori

    printf("\nOrdine di gioco:\n");//indica in che ordine tireranno i dadi i giocatori

    // Primo tiro
    for (int i = 0; i < n; i++) {
        valori[i] = tiraDado();
        printf("%s tira il dado! è uscito:%d\n", g[i].nome, valori[i]);
    }

    // Gestione pareggi
    int pareggio = 1;
    while (pareggio) {
        pareggio = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                if (valori[i] == valori[j]) {
                    pareggio = 1;

                    printf("\nPareggio tra %s e %s! Ritirate il dado!\n",
                           g[i].nome, g[j].nome);

                    valori[i] = tiraDado();
                    valori[j] = tiraDado();

                    printf("%s ritira e ottiene %d\n", g[i].nome, valori[i]);
                    printf("%s ritira e ottiene %d\n", g[j].nome, valori[j]);
                }
            }
        }
    }

    // Ordina in ordine decrescente
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (valori[j] > valori[i]) {

                int tmp = valori[i];
                valori[i] = valori[j];
                valori[j] = tmp;

                swap(&g[i], &g[j]);
            }
        }
    }

    printf("\nOrdine di gioco stabilito:\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s (dado: %d)\n", i + 1, g[i].nome, valori[i]);
    }
}