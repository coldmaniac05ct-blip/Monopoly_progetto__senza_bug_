//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "turni.h"
#include <stdio.h>
#include "giocatore.h"
#include "giocatore.c"

void turno(Giocatore *g) {
    printf("\n--- Turno di %s ---\n", g->nome);//annuncio a chi tocca grazie alla printf, il nome del giocatore è un tipo stringa quindi
    //scrivo %s e faccio sì che g (giocatore) punti a nome così il compilatore sa da dove ricavare il nome

    printf("CFU: %d\n", g->cfu);//stessa cosa faccio qua, però uso %d perchè i CFU vengono dichiarati come un numero
    //intero e faccio puntare sempre dalla struttura giocatore ma punto ai cfu

    int scelta;//scrivo le varie opzioni di gioco tramite ciclo do while così che ripeta l'azione dove necessario
    do {
        printf("1) Lancia dadi\n");
        printf("2) Info giocatore\n");
        printf("0) Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        if (scelta == 2)//se la scelta è 2 allora faccio stampare al programma le info del giocatore
            stampaGiocatore(*g);

    } while (scelta != 1 && scelta != 0);

    if (scelta == 1) {//se la scelta è 1 allora faccio tirare i dadi e poi stampo a schermo la somma data dal lancio dei 2 dadi
        int d1 = tiraDado();
        int d2 = tiraDado();
        int somma = d1 + d2;

        printf("Hai tirato %d + %d = %d\n", d1, d2, somma);

        muoviGiocatore(g, somma);//il giocatore si muoverà automaticamente sul tabellone grazie al tiro dei dadi

        printf("Ora sei in: %s\n", g->posizione->nome);//stampo in che casella si trova attualmente il giocatore
    }
}
