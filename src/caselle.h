//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H

#endif //MONOPOLY_PROGETTO__SENZA_BUG__CASELLE_H

#ifndef CASELLE_H
#define CASELLE_H

#include <stdbool.h>

#define DIM_NOME 31

typedef enum {
    NESSUNO, AULA, MENSA, PARCHEGGIO, ABBONAMENTO, VIA, BUG,
    VAI_BATCAVERNA, BATCAVERNA
} TipoCasella;

typedef enum {
    NESSUN_COLORE, MARRONE, CELESTE, FUCSIA, ARANCIONE,
    ROSSO, GIALLO, VERDE, BLU
} ColoreCasella;

struct giocatore; // forward declaration

typedef struct casella {
    char nome[DIM_NOME];
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    struct giocatore *proprietario;
    struct casella *next;
    struct casella *prev;
} Casella;

Casella *creaCasella(char *nome, int tipo, int colore, int costo);
Casella *inserisciInCoda(Casella *head, Casella *nuova);
Casella *caricaTabellone(const char *filename);
void stampaTabellone(Casella *head);

#endif
void testTabellone(Casella *head);
