//
// Created by Administrator on 10/05/2026.
//
//Studente:Elisa Alessandra Cataldo (e.cataldo@studenti.unica.it)
//Matricola:60/84/00112
//Tipo Progetto:BASE
//Username Github:Cold Maniac
//Github link: https://github.com/coldmaniac05ct-blip/Monopoly_progetto__senza_bug_
//Necessità:NESSUNA

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include <stdio.h>
#include <stdlib.h>

#include "src/giocatore.h"
#include "src/menu.h"
#include "src/partita.h"
#include "src/tabellone.h"
#include "src/salvataggio.h"

int main(void){//da continuare perchè stampa lo schermo ma non puoi ancora giocarci
    int n;
    int scelta = menuIniziale();   // la funzione è definita in menu.c, serve a stampare a schermo il menu
    Giocatore *giocatori = NULL;

    if (scelta == 2) {
        caricaPartita(&giocatori, &n,caricaTabellone("tabellone.txt"));
    }

    switch (scelta) {

    case 1:
        printf("Nuova partita!\n");
        printf("Quanti giocatori partecipano? (2-4):");
        scanf("%d", &n);
        giocatori = creaGiocatori(n);
        break;

    case 2:
        printf("Caricamento partita...\n");
        caricaPartita(&giocatori, &n, caricaTabellone("tabellone.txt"));
        break;

    case 0:
        printf("Uscita...\n");
        return 0;
    }


        while (n < 2 || n > 4) {
            printf("Valore non valido. Inserisci 2-4: ");
            scanf("%d", &n);
        }

    printf("\nPartita pronta!\n");



        ordinaGiocatori(giocatori, n);

        Casella *tabellone = caricaTabellone("tabellone.txt");

        // Imposta posizione iniziale (VIA)
        for (int i = 0; i < n; i++) {
            giocatori[i].posizione = tabellone;
        }

    //qui devo inserire un ciclo per fare tirare i dadi all'infinito e il menù di gioco a gioco già iniziato
    avviaPartita(giocatori, n, tabellone);

    salvaPartita(giocatori, n, tabellone);

        liberaGiocatori(giocatori);

        return 0;


}