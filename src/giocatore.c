//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "giocatore.h"
#include "dadi.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Giocatore* creaGiocatori(int n) {//inizio subroutine
    Giocatore *g = malloc(sizeof(Giocatore) * n);

    for (int i = 0; i < n; i++) {
        printf("Inserisci nome giocatore %d: ", i + 1);//chiedo al giocatore di inserire il proprio nome
        //e scrivo i+1 così che il mio compilatore chieda tot nomi in base a quanti sono i giocatori
        scanf("%s", g[i].nome);//il nome è un tipo stringa quindi %s

        g[i].cfu = 3000;
        g[i].turniCaverna = 0;
        g[i].saltaTurno = 0;
        g[i].numAule = 0;
        g[i].posizione = NULL;
        g[i].carte = NULL;
    }

    return g;
}

void liberaGiocatori(Giocatore *g) {
    free(g);
}


void ordinaGiocatori(Giocatore *g, int n) {//stabilisce in che ordine tireranno il dado i giocatori
    int *tiri = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        tiri[i] = tiraDado();
        printf("%s tira: %d\n", g[i].nome, tiri[i]);
    }

    //bubble sort decrescente per gestire il tiro dei dadi: mi serve per ordinare
    //un array confrontando ripetutamente gli elementi vicini e scambiandoli se sono fuori ordine
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tiri[j] < tiri[j + 1]) {
                int tmp = tiri[j];
                tiri[j] = tiri[j + 1];
                tiri[j + 1] = tmp;

                Giocatore temp = g[j];
                g[j] = g[j + 1];
                g[j + 1] = temp;
            }
        }
    }

    free(tiri);
}
void muoviGiocatore(Giocatore *g, int passi) {//sub 3, qua dichiaro una subroutine
    //muoviGiocatore per fare spostare la pedina sul tabellone di tot caselle
    for (int i = 0; i < passi; i++) {
        g->posizione = g->posizione->next;

        if (g->posizione->tipo == VIA)
            g->cfu += 200;
    }
}
void stampaGiocatore(Giocatore g) {//questa subroutine è di tipo void e mi consente di stampare i dati del giocatore,
    //quali nome, cfu e in che posizione si trova sul tabellone
    printf("Giocatore: %s\n", g.nome);
    printf("CFU: %d\n", g.cfu);
    printf("Posizione: %s\n", g.posizione->nome);
}
