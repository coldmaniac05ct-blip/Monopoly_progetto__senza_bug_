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

void avviaPartita(Giocatore *g, int n, Casella *tabellone);
void caricaPartita(Giocatore **giocatori, int *numGiocatori, Casella *tabellone);

#endif


#endif //MONOPOLY_PROGETTO__SENZA_BUG__PARTITA_H