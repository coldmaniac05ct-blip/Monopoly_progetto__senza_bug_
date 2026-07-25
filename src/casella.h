//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H

#include <stdbool.h>
#include "macro.h"
#include "giocatore.h"

//definisco le strutture



typedef enum {
    NESSUN_COLORE, MARRONE, CELESTE, FUCSIA, ARANCIONE,
    ROSSO, GIALLO, VERDE, BLU
} ColoreCasella;

typedef struct  Giocatore giocatore;

struct casella{
    char nome[LUNGHEZZA_STRINGA];//evito di usare magic numbers
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    Giocatore *proprietario;
    struct casella *next;
    struct casella *prev;
};

typedef enum{
    MOUSE,
    TASTIERA,
    CAVO_HDMI,
    PROIETTORE
}SegnaPosto;

typedef struct casella Casella;

//ho definito cosa fanno le subroutine nel file.c

Casella *creaCasella(char *nome, int tipo, int colore, int costo);
Casella *inserisciInCoda(Casella *head, Casella *nuova);
void stampaTabellone(Casella *head);

void testTabellone(Casella *head);
Casella *casellaDaIndice(Casella *start, int index);
int indiceCasella(Casella *start, Casella *target);


#endif //MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H