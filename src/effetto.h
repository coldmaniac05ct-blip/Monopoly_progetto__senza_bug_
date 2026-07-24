//
// Created by Administrator on 14/05/2026.
//


#ifndef MONOPOLY_PROGETTO__SENZA_BUG__EFFETTI_H
#define MONOPOLY_PROGETTO__SENZA_BUG__EFFETTI_H

//ho definito cosa fanno le subroutine nel file.c

typedef enum {
    NESSUNO, AULA, MENSA, PARCHEGGIO, ABBONAMENTO, VIA, BUG,
    VAI_BATCAVERNA, BATCAVERNA
} TipoCasella;

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


typedef struct {
    Azione azione;
    int quantita;
    TipoCasella tipo_casella;
} Effetto;

#endif //MONOPOLY_PROGETTO__SENZA_BUG__EFFETTI_H