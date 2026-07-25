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

    if (scelta == 2) {//il problema maggiore era sistemare il menù di gioco, quindi se la scelta dal menù è 2 il mio compilatore dovrà
        //occuparsi di caricare una partita e poi iniziare il gioco
        caricaPartita(&giocatori, &n,caricaTabellone("tabellone.txt"));//carica la partita e poi i giocatori
    }

    switch (scelta) {//ovviamente il giocatore dovrà avere la possibilità di scegliere tra più opzioni e
        //nel momento in cui scelga di fare una nuova partita il gioco dovrà
        //avviarsi e chiedere informazioni, quali il numero di giocatori da registrare e i nomi

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
            printf("Valore non valido. Inserisci 2-4: ");//se il valore inserito non è consono allora stampo un messaggio di errore
            scanf("%d", &n);
        }

    printf("\nPartita pronta!\n");//informo che la partita è pronta per essere giocata e avvio il gioco partendo
    //dall'ordine dei giocatori e poi passo al caricamento del tabellone e del menù di gioco



        ordinaGiocatori(giocatori, n);

        Casella *tabellone = caricaTabellone("tabellone.txt");

        // Imposta posizione iniziale (VIA)
        for (int i = 0; i < n; i++) {
            giocatori[i].posizione = tabellone;
        }

    avviaPartita(giocatori, n, tabellone);//avvia una partita nuova

    salvaPartita(giocatori, n, tabellone);//salva la partita in savegame.sav tramite salvataggio.h e dunque salvataggio.c

        liberaGiocatori(giocatori);//serve a fare uscire dal menù di gioco e quindi dal programma

        return 0;


}