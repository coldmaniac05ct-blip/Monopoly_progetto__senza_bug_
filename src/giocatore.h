//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H

#include "caselle.h"
#include "carte.h"
#include "macro.h"

typedef struct {
    char nome[LUNGHEZZA_STRINGA]; //31 caratteri utili è esattamente quello richiesto dalle specifiche per i nomi (coerenza con il resto del progetto).
    int cfu;   //Tiene i cfu del giocatore. Serve per pagare pedaggi, comprare aule, ecc.
    int turniCaverna;  //Serve per gestire i turni da scontare in BATCAVERNA (specifiche: deve restare 3 turni, o uscire con dadi/carta).
    int saltaTurno;  //Serve per gestire carte/effetti che fanno saltare il turno.
    int numAule;  //Tiene traccia di quante aule/mense possiede (utile per pedaggi, carte speciali, ecc.).
    Casella *posizione;  //Puntatore alla casella in cui si trova il giocatore sul tabellone (lista circolare di Casella).
    Carta *carte;  //Lista di carte in possesso del giocatore (es. carte ESCI dalla caverna).//
} Giocatore;

#endif //MONOPOLY_PROGETTO__SENZA_BUG__GIOCATORE_H

//ho definito cosa fanno le subroutine nel file.c
