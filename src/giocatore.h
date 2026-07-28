//
// Created by Administrator on 10/05/2026.
//


#ifndef MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H


#include "macro.h"
#include "carta.h"
#include <stdbool.h>

typedef struct casella Casella;

typedef struct {
    char nome[LUNGHEZZA_STRINGA]; //31 caratteri utili è esattamente quello richiesto dalle specifiche per i nomi (coerenza con il resto del progetto).
    int cfu;   //Tiene i cfu del giocatore. Serve per pagare pedaggi, comprare aule, ecc.
    bool saltaTurno;  //Serve per gestire carte/effetti che fanno saltare il turno.
    int nuovo_turno;
    Casella *posizione;  //Puntatore alla casella in cui si trova il giocatore sul tabellone (lista circolare di Casella).
    Carta *carte;  //Lista di carte in possesso del giocatore (es. carte ESCI dalla caverna).//
    int segna_posto;
    Carta *carte_esci;
    int turni_batcaverna;//Serve per gestire i turni da scontare in BATCAVERNA (specifiche: deve restare 3 turni, o uscire con dadi/carta).
    Effetto* effettiDisponibili;
    int numEffettiDisponibili;
    Carta *ultimaCartaPescata;
    int numero_aule_mense;//Tiene traccia di quante aule/mense possiede (utile per pedaggi, carte speciali, ecc.).
} Giocatore;

void stampaGiocatore(Giocatore g);
void muoviGiocatore(Giocatore *g, int passi);
void ordinaGiocatori(Giocatore *g, int n);
void liberaGiocatori(Giocatore *g);
Giocatore* creaGiocatori(int n);
void eliminaGiocatore(Giocatore **g, int *n, int index);

#endif //MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H

//ho definito cosa fanno le subroutine nel file.c
