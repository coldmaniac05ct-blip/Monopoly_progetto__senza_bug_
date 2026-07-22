//
// Created by Administrator on 10/05/2026.
//
//Studente:Elisa Alessandra Cataldo (e.cataldo@studenti.unica.it)
//Matricola:60/84/00112
//Tipo Progetto:MEDIO
//Username Github:Cold Maniac
//Github link: https://github.com/coldmaniac05ct-blip/Monopoly_progetto__senza_bug_
//Necessità:NESSUNA

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include <stdio.h>
#include <stdlib.h>

#include "src/carte.h"
#include "src/caselle.h"
#include "src/giocatore.h"
#include "src/tabellone.h"
#include "src/dadi.h"
#include "src/effetti.h"
#include "src/menu.h"
#include "src/strutture.h"
#include "src/turni.h"
#include "src/giocatore.c"

//sub partita
void nuovaPartita(Giocatore **giocatori, int *numGiocatori, Casella *tabellone);//stiamo iniziando una nuova partita quindi ci serve una funzione
//che non restituisca valori già dichiarati precedentemente


//inizio codice, qua registro la partita:
void nuovaPartita(Giocatore **giocatori, int *numGiocatori, Casella *tabellone){//sub 2
    printf("Quanti giocatori? (2-4): "); //indico il numero massimo e minimo di giocatori registrabili
    scanf("%d", numGiocatori);

    *giocatori = creaGiocatori(*numGiocatori);

    // posiziona tutti sul VIA
    Casella *via = tabellone;
    while (via->tipo != VIA)
        via = via->next;

    for (int i = 0; i < *numGiocatori; i++)
        (*giocatori)[i].posizione = via;

    printf("Partita inizializzata!\n");
}//non necessita di return alla fine poiché di tipo void



