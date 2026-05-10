//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H

#endif //MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H

#ifndef CARTE_H
#define CARTE_H

#include "strutture.h"
#define CARTE_H

#include "strutture.h"

// Carica il mazzo da file
Carta* caricaMazzo(const char *filename);

// Mescola il mazzo
void mescolaMazzo(Carta **mazzo);

// Pesca la prima carta
Carta* pescaCarta(Carta **mazzo);

// Inserisce una carta in fondo
void inserisciInFondo(Carta **mazzo, Carta *c);

// Debug
void stampaMazzo(Carta *mazzo);

#endif