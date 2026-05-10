//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H

#endif //MONOPOLY_PROGETTO__SENZA_BUG__STRUTTURE_H
#ifndef MONOPOLY_STRUTTURE_H
#define MONOPOLY_STRUTTURE_H

#endif //MONOPOLY_STRUTTURE_H

#ifndef STRUTTURE_H
#define STRUTTURE_H

#include <stdbool.h>

// ENUMERAZIONI

typedef enum {
    NESSUNO, AULA, MENSA, PARCHEGGIO, ABBONAMENTO, VIA, BUG,
    VAI_BATCAVERNA, BATCAVERNA
} TipoCasella;

typedef enum {
    NESSUN_COLORE, MARRONE, CELESTE, FUCSIA, ARANCIONE,
    ROSSO, GIALLO, VERDE, BLU
} ColoreCasella;

typedef enum {
    MOUSE, TASTIERA, CAVO_HDMI, PROIETTORE
} Segnaposto;

typedef enum {
    NORMALE, SPECIALE
} TipoCarta;

typedef enum {
    PAGA_QUALCOSA,
    PAGA_TUTTO,
    PRENDI,
    SALTA_TURNO,
    NUOVO_TURNO,
    ESCI,
    VAI_INDIETRO,
    VAI_AVANTI,
    REGALA
} Azione;

// STRUTTURE

typedef struct {
    Azione azione;
    int quantita;
    TipoCasella tipo_casella;
} Effetto;

typedef struct carta {
    char nome[32];
    char descrizione[256];
    TipoCarta tipo;
    int numero_effetti;
    Effetto *effetti;
    struct carta *next;
} Carta;

struct giocatore; // forward declaration

typedef struct casella {
    char nome[32];
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    struct giocatore *occupante;
    struct casella *next;
    struct casella *prev;
} Casella;

typedef struct giocatore {
    char nome[32];
    Segnaposto segnaposto;
    int cfu;
    int turni_batcaverna;
    bool salta_turno;
    int numero_aule_mense;
    Casella *posizione;
    Carta *carte_uscita;
} Giocatore;

#endif
