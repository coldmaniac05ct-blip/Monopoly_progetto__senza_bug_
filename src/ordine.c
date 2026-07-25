//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "ordine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static int tiraDado() {//stabilisce l'ordine di gioco in modo randomico grazie al tiro dei dadi prima che la partita
    //abbia inizio e avvisa i giocatori dell'ordine stabilito
    return (rand() % 6) + 1;
}

static void swap(Giocatore *a, Giocatore *b) {//serve ad alternare i turni
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

    // Gestione pareggi, nel momento in cui avvenga un pareggio (caso raro), allora il gioco
    // tirerà nuovamente i dadi per entrambi i giocatori finchè nons i stabilisce un ordine di gioco
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

    // Ordina in ordine decrescente in base ai valori che sono usciti, quindi 6,5,4,3,2,1, inizierà chi ha il numero più alto
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