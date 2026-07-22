//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H

#include <stdbool.h>
#include "caselle.h"
#include "effetti.h"
#include "macro.h"

//ho segnato qui tutte le strutture tranne quella del giocatore perchè sennò mi incasinavo

// STRUTTURE

typedef enum {
    PAGA_QUALCOSA,
    PAGA_TUTTO,
    PRENDI,
    SALTA_TURNO,
    NUOVO_TURNO,
    ESCI,
    VAI_INDIETRO,
    VAI_AVANTI,
    REGALA,
} Azione;

typedef enum {
    NORMALE,
    SPECIALE,
} TipoCarta;


typedef struct {
    Azione azione;
    int quantita;
    TipoCasella tipo_casella;
} Effetto;

typedef struct carta {
    char nome[LUNGHEZZA_STRINGA];//definito in macro.h
    char descrizione[DESCRIZIONE];//guarda macro.h
    TipoCarta tipo;
    int numero_effetti;
    Effetto *effetti;
    struct carta *next;
} Carta;

#endif //MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H

//ho definito cosa fanno le subroutine nel file.c
