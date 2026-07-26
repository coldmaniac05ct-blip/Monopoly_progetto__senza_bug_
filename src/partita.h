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
    PESCA_CARTA,
    SALVATAGGIO,
    ACQUISTO_CASELLA,
    AGISCI,
}Caso;

void avviaPartita(Giocatore *g, int n, Casella *tabellone);
void caricaPartita(Giocatore **giocatori, int *numGiocatori, Casella *tabellone);
Casella* trovaBatcaverna(Casella *tabellone);
void applicaEffetto(Giocatore *g, Effetto e, Casella *tabellone, Carta **mazzo);
void EsciBatcaverna(Giocatore *g, Casella *tabellone, Carta **mazzo);

#endif


#endif //MONOPOLY_PROGETTO__SENZA_BUG__PARTITA_H