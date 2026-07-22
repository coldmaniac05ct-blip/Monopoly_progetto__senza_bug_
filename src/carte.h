//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H

#include "strutture.h"
#include "macro.h"

// Carica il mazzo da file
Carta* caricaMazzo(const char *filename);

// Mescola il mazzo
void mescolaMazzo(Carta **start_mazzo);

// Pesca la prima carta
Carta* pescaCarta(Carta **start_mazzo);

// Inserisce una carta in fondo
void inserisciInFondo(Carta **start_mazzo, Carta *c);

// Debug
void stampaMazzo(Carta *start_mazzo);
//funzione stampaMazzo, stampa il mazzo quindi uso un tipo void

void mescolaMazzo(Carta **head);
Carta* pescaCarta(Carta **head);
void inserisciInFondo(Carta **head, Carta *c);

#endif //MONOPOLY_PROGETTO__SENZA_BUG__CARTE_H
