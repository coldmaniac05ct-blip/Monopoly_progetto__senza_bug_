//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H

#include <stdbool.h>
#include "macro.h"

//definisco le strutture

typedef enum {
    NESSUNO, AULA, MENSA, PARCHEGGIO, ABBONAMENTO, VIA, BUG,
    VAI_BATCAVERNA, BATCAVERNA
} TipoCasella;

typedef enum {
    NESSUN_COLORE, MARRONE, CELESTE, FUCSIA, ARANCIONE,
    ROSSO, GIALLO, VERDE, BLU
} ColoreCasella;

typedef struct casella {
    char nome[DIM_NOME];//evito di usare magic numbers
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    struct giocatore *proprietario;
    struct casella *next;
    struct casella *prev;
    void * occupante;
} Casella;

//ho definito cosa fanno le subroutine nel file.c

Casella *creaCasella(char *nome, int tipo, int colore, int costo);
Casella *inserisciInCoda(Casella *head, Casella *nuova);
void stampaTabellone(Casella *head);

void testTabellone(Casella *head);

#endif //MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H