//
// Created by Administrator on 24/07/2026.
//

#include "partita.h"

#include <stdio.h>
#include <stdlib.h>

#include "dado.h"
#include "turno.h"

// Questo file gestisce:
// - il menù del turno
// - la logica principale della partita (avviaPartita)
// - caricamento da savegame
// - funzioni di supporto per BatCaverna e acquisti
// - applicazione degli effetti delle carte BUG

// -----------------------------------------------------------------------------
// MENÙ DEL TURNO
// -----------------------------------------------------------------------------

static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome);

    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("4) Pesca una carta dal mazzo\n");
    printf("5) Salva partita\n");
    printf("6) Compra proprieta'\n");
    printf("7) Agisci\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;
    scanf("%d", &scelta);

    return scelta;
}

// -----------------------------------------------------------------------------
// GESTIONE ACQUISTI
// -----------------------------------------------------------------------------

void gestisciAcquisti(Giocatore *g, Casella *c) {

    printf("\n--- Gestione acquisti ---\n");
    printf("Ti trovi sulla casella: %s, colore=%d, tipo=%d\n", c->nome, c->colore, c->tipo);

    if (c->proprietario == NULL) {
        printf("Questa casella non ha proprietario.\n");
        printf("Vuoi comprarla per %d CFU? (1=si, 0=no): ", c->costo);

        int scelta;
        scanf("%d", &scelta);

        if (scelta == 1) {
            if (g->cfu >= c->costo) {
                g->cfu -= c->costo;
                c->proprietario = g;
                printf("Hai comprato %s!\n", c->nome);
            } else {
                printf("Non hai abbastanza CFU.\n");
            }
        }
        return;
    }

    if (c->proprietario == g) {

        printf("Questa casella è tua.\n");
        printf("Cosa vuoi comprare?\n");
        printf("1) Una sedia (20 CFU)\n");
        printf("2) Una scrivania (50 CFU)\n");
        printf("0) Niente\n");
        printf("Scelta: ");

        int scelta;
        scanf("%d", &scelta);

        switch (scelta) {

        case 1:
            if (g->cfu >= 20) {
                g->cfu -= 20;
                c->sedie++;
                printf("Hai comprato una sedia! Ora ne hai %d.\n", c->sedie);
            } else {
                printf("Non hai abbastanza CFU.\n");
            }
            break;

        case 2:
            if (c->scrivania == 1) {
                printf("Hai gia' una scrivania qui.\n");
                break;
            }

            if (g->cfu >= 50) {
                g->cfu -= 50;
                c->scrivania = 1;
                printf("Hai comprato una scrivania!\n");
            } else {
                printf("Non hai abbastanza CFU.\n");
            }
            break;

        case 0:
            printf("Non compri nulla.\n");
            break;

        default:
            printf("Scelta non valida.\n");
        }

        return;
    }

    printf("Questa casella appartiene a %s. Non puoi comprare qui.\n", c->proprietario->nome);
}

// -----------------------------------------------------------------------------
// SUPPORTO BATCAVERNA
// -----------------------------------------------------------------------------

Casella *Batcaverna(Casella *tabellone) {

    Casella *c = tabellone;

    do {
        if (c->tipo == BATCAVERNA)
            return c;

        c = c->next;

    } while (c != tabellone);

    return NULL;
}

Casella *VaiInBatcaverna(Casella *tabellone) {

    Casella *c = tabellone;

    do {
        if (c->tipo == VAI_BATCAVERNA)
            return c;

        c = c->next;

    } while (c != tabellone);

    return NULL;
}

void EsciBatcaverna(Giocatore *g, Casella *tabellone, Carta **mazzo) {

    g->turni_batcaverna = 0;

    Casella *c = tabellone;
    while (c->tipo != PARCHEGGIO)
        c = c->next;

    g->posizione = c;

    printf("%s esce dalla BatCaverna!\n", g->nome);

    if (g->carte_esci != NULL) {

        Carta *uscita = g->carte_esci;
        g->carte_esci = g->carte_esci->next;

        inserisciInFondo(mazzo, uscita);

        printf("La carta ESCI e' stata rimessa in fondo al mazzo.\n");
    }
}

// -----------------------------------------------------------------------------
// APPLICAZIONE EFFETTI
// -----------------------------------------------------------------------------

void applicaEffetto(Giocatore *g, Effetto e, Casella *tabellone, Carta **mazzo) {

    switch (e.azione) {

    case PAGA_QUALCOSA:
        g->cfu -= e.quantita;
        printf("Hai pagato %d CFU.\n", e.quantita);
        break;

    case PAGA_TUTTO:
        g->cfu = 0;
        printf("Perdi tutti i tuoi CFU!\n");
        break;

    case PRENDI:
        g->cfu += e.quantita;
        printf("Hai guadagnato %d CFU!\n", e.quantita);
        break;

    case SALTA_TURNO:
        g->saltaTurno = 1;
        printf("Salti il prossimo turno!\n");
        break;

    case NUOVO_TURNO:
        g->nuovo_turno = 1;
        printf("Hai diritto a un nuovo turno!\n");
        break;

    case ESCI:
        EsciBatcaverna(g, tabellone, mazzo);
        break;

    case VAI_INDIETRO:
        muoviGiocatore(g, -e.quantita);
        printf("Vai indietro di %d caselle.\n", e.quantita);
        break;

    case VAI_AVANTI:
        muoviGiocatore(g, e.quantita);
        printf("Avanzi di %d caselle.\n", e.quantita);
        break;

    case REGALA:
        printf("Regali %d aule (logica da implementare).\n", e.quantita);
        break;

    default:
        printf("Effetto sconosciuto.\n");
    }
}

// -----------------------------------------------------------------------------
// CARICAMENTO PARTITA
// -----------------------------------------------------------------------------

void caricaPartita(Giocatore **g, int *n, Casella *tab) {

    FILE *fp = fopen("savegame.sav", "rb");
    if (!fp)
        return;

    fread(n, sizeof(int), 1, fp);

    *g = malloc(sizeof(Giocatore) * (*n));

    for (int i = 0; i < *n; i++) {

        fread((*g)[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);
        fread(&(*g)[i].cfu, sizeof(int), 1, fp);

        int pos;
        fread(&pos, sizeof(int), 1, fp);

        (*g)[i].posizione = casellaDaIndice(tab, pos);
    }

    fclose(fp);
}

// -----------------------------------------------------------------------------
// LOGICA PRINCIPALE DELLA PARTITA
// -----------------------------------------------------------------------------

void avviaPartita(Giocatore *g, int n, Casella *tabellone) {

    int turno = 0;          // indice del giocatore corrente
    int finePartita = 0;    // flag per terminare la partita

    Carta *mazzo = NULL;    // mazzo delle carte BUG

    while (!finePartita) {

        Giocatore *corrente = &g[turno];   // giocatore del turno corrente

        // ---------------------------------------------------------------------
        // CICLO DEL TURNO DEL GIOCATORE
        // Il menù deve ripetersi finché il giocatore NON tira i dadi.
        // ---------------------------------------------------------------------
        int turnoFinito = 0;

        while (!turnoFinito) {

            int scelta = menuTurno(corrente);

            switch (scelta) {

            // -------------------------------------------------------------
            // TIRA I DADI → il turno FINISCE
            // -------------------------------------------------------------
            case TIRO_DADI: {

                int d1, d2;
                int totale = dadi(&d1, &d2);

                printf("%s ha ottenuto un totale di %d.\n", corrente->nome, totale);

                muoviGiocatore(corrente, totale);

                turnoFinito = 1;   // <<<<<< IL TURNO TERMINA QUI
                break;
            }

            // -------------------------------------------------------------
            // MOSTRA DATI → NON consuma il turno
            // -------------------------------------------------------------
            case STAMPA_DATI:
                for (int i = 0; i < n; i++)
                    stampaGiocatore(g[i]);
                break;             // <<<<<< IL TURNO CONTINUA

            // -------------------------------------------------------------
            // MOSTRA TABELLA → NON consuma il turno
            // -------------------------------------------------------------
            case STAMPA_TABELLONE:
                stampaTabellone(tabellone);
                break;             // <<<<<< IL TURNO CONTINUA

            // -------------------------------------------------------------
            // PESCA CARTA → NON consuma il turno
            // -------------------------------------------------------------
            case PESCA_CARTA: {
                    if (mazzo == NULL) {
                        printf("DEBUG: Carico il mazzo...\n");
                        mazzo = caricaMazzo("mazzo.txt");
                    }

                    // Pesco la carta
                    Carta *carta = pescaCarta(&mazzo);

                    if (!carta) {
                        printf("Il mazzo e' vuoto!\n");
                        break;
                    }

                    printf("Hai pescato: %s\n", carta->nome);
                    printf("%s\n", carta->descrizione);

                    // 🔥 ASSEGNO GLI EFFETTI AL GIOCATORE
                    corrente->effettiDisponibili = carta->effetti;
                    corrente->numEffettiDisponibili = carta->numero_effetti;

                    printf("Puoi ora usare AGISCI per applicare gli effetti.\n");
                break;             // <<<<<< IL TURNO CONTINUA
            }

            // -------------------------------------------------------------
            // SALVA PARTITA → NON consuma il turno
            // -------------------------------------------------------------
            case SALVATAGGIO:
                printf("Partita salvata!\n");
                salvaPartita(g, n, tabellone);
                break;             // <<<<<< IL TURNO CONTINUA

            // -------------------------------------------------------------
            // ACQUISTO CASELLA → NON consuma il turno
            // -------------------------------------------------------------
            case ACQUISTO_CASELLA:
                gestisciAcquisti(corrente, corrente->posizione);
                break;             // <<<<<< IL TURNO CONTINUA

            // -------------------------------------------------------------
            // AGISCI → usa gli effetti disponibili, NON consuma il turno
            // -------------------------------------------------------------
            case AGISCI: {

                    Effetto *effetti = corrente->effettiDisponibili;
                    int numero_effetti = corrente->numEffettiDisponibili;

                    if (effetti == NULL || numero_effetti == 0) {
                        printf("Non ci sono azioni disponibili.\n");
                        break;
                    }

                    int idx = menuEffetti(effetti, numero_effetti);

                    if (idx < 0 || idx >= numero_effetti) {
                        printf("Scelta non valida.\n");
                        break;
                    }

                    Effetto scelto = effetti[idx];

                    applicaEffetto(corrente, scelto, tabellone, &mazzo);
                break;             // <<<<<< IL TURNO CONTINUA
            }

            // -------------------------------------------------------------
            // USCITA → termina la partita
            // -------------------------------------------------------------
            case USCITA:
                printf("Hai scelto di uscire dal gioco.\n");
                finePartita = 1;
                turnoFinito = 1;
                break;

            default:
                printf("Scelta non valida.\n");
            }
        }

        // ---------------------------------------------------------------------
        // PASSA AL GIOCATORE SUCCESSIVO SOLO QUANDO IL TURNO È FINITO
        // ---------------------------------------------------------------------
        turno = (turno + 1) % n;
    }
}
