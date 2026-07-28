//
// Created by Administrator on 24/07/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__PARTITA_H
#define MONOPOLY_PROGETTO__SENZA_BUG__PARTITA_H

#ifndef TURNO_H
#define TURNO_H

#include "giocatore.h"
#include "tabellone.h"
#include "salvataggio.h"
#include "casella.h"
#include "carta.h"
#include "effetto.h"
#include "turno.h"

typedef enum{
    USCITA,
    TIRO_DADI,
    STAMPA_DATI,
    STAMPA_TABELLONE,
    SALVATAGGIO,
}Caso;

// ============================================================================
//  NOMI ENUM (TIPO E COLORE CASELLA)
// ============================================================================

//array dei nomi dei tipi (enum TipoCasella)
static const char *NomiTipo[] = {
    "NESSUNO", "AULA", "MENSA", "PARCHEGGIO", "ABBONAMENTO",
    "VIA", "BUG", "VAI_BATCAVERNA", "BATCAVERNA"
};

//array dei nomi dei colori (enum ColoreCasella)
static const char *NomiColore[] = {
    "NESSUN_COLORE", "MARRONE", "CELESTE", "FUCSIA", "ARANCIONE",
    "ROSSO", "GIALLO", "VERDE", "BLU"
};


void avviaPartita(Giocatore *g, int n, Casella *tabellone);
void caricaPartita(Giocatore **giocatori, int *numGiocatori, Casella *tabellone);
Casella* trovaBatcaverna(Casella *tabellone);
void applicaEffetto(Giocatore *g, Effetto e, Casella *tabellone, Carta **mazzo);
void EsciBatcaverna(Giocatore *g, Casella *tabellone, Carta **mazzo);
void scegliSegnaPosto(Giocatore *g);

#endif


#endif //MONOPOLY_PROGETTO__SENZA_BUG__PARTITA_H