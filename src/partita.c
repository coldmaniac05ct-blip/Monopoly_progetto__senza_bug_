//
// Created by Administrator on 24/07/2026.
//

#include "partita.h"

#include <stdio.h>
#include <stdlib.h>

#include "dado.h"
#include "turno.h"

// ============================================================================
//  TROVA LA CASELLA BATCAVERNA
// ============================================================================

Casella* trovaBatcaverna(Casella *tabellone) {

    Casella *c = tabellone;

    do {
        if (c->tipo == BATCAVERNA)
            return c;
        c = c->next;
    } while (c != tabellone);

    return NULL;
}


// ============================================================================
//  MENÙ DEL TURNO (SPECIFICHE BASE)
// ============================================================================

static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome);

    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("5) Salva partita\n");
    printf("6) Compra proprieta'\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;
    scanf("%d", &scelta);

    return scelta;
}

// ============================================================================
//  GESTIONE ACQUISTI (SPECIFICHE BASE)
// ============================================================================

void gestisciAcquisti(Giocatore *g, Casella *c) {

    printf("\n--- Gestione acquisti ---\n");
    printf("Ti trovi sulla casella: %s (Tipo: %s)\n",
           c->nome, NomiTipo[c->tipo]);

    if (c->proprietario == NULL) {

        printf("Questa casella non ha proprietario.\n");
        printf("Vuoi comprarla per %d CFU? (1=si, 0=no): ", c->costo);

        int scelta;
        scanf("%d", &scelta);

        if (scelta == 1) {
            if (g->cfu >= c->costo) {

                g->cfu -= c->costo;
                c->proprietario = g;

                if (c->tipo == AULA || c->tipo == MENSA)
                    g->numero_aule_mense++;

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

    printf("Questa casella appartiene a %s. Devi pagare il pedaggio.\n",
           c->proprietario->nome);

    g->cfu -= c->costo;
}

// ============================================================================
//  APPLICA EFFETTO DELLA CARTA BUG — SPECIFICHE BASE
// ============================================================================

void applicaEffetto(Giocatore *g, Effetto e, Casella *tabellone, Carta **mazzo) {

    switch (e.azione) {

    case PAGA_QUALCOSA:
        printf("Applico effetto: PAGA_QUALCOSA (%d CFU)\n", e.quantita);
        g->cfu -= e.quantita;
        break;

    case PAGA_TUTTO:
        printf("Applico effetto: PAGA_TUTTO\n");
        g->cfu = 0;
        break;

    case PRENDI:
        printf("Applico effetto: PRENDI (%d CFU)\n", e.quantita);
        g->cfu += e.quantita;
        break;

    case SALTA_TURNO:
        printf("Applico effetto: SALTA_TURNO\n");
        g->saltaTurno = 1;
        break;

    case NUOVO_TURNO:
        printf("Applico effetto: NUOVO_TURNO\n");
        g->nuovo_turno = 1;
        break;

    case ESCI:
        printf("Applico effetto: ESCI dalla BatCaverna\n");
        g->turni_batcaverna = 0;
        g->posizione = trovaBatcaverna(tabellone)->next;
        break;

    case VAI_INDIETRO:
        printf("Applico effetto: VAI_INDIETRO (%d caselle)\n", e.quantita);
        muoviGiocatore(g, -e.quantita);
        break;

    case VAI_AVANTI:
        printf("Applico effetto: VAI_AVANTI (%d caselle)\n", e.quantita);
        muoviGiocatore(g, e.quantita);
        break;

    case REGALA:
        printf("Applico effetto: REGALA (%d aule)\n", e.quantita);
        break;

    default:
        printf("Effetto sconosciuto.\n");
    }
}

// ============================================================================
//  GESTIONE CASELLA DOPO IL MOVIMENTO — SPECIFICHE BASE
// ============================================================================

void gestisciCasella(Giocatore *g, Carta **mazzo, Casella *tabellone) {

    Casella *c = g->posizione;

    printf("\n--- Gestione casella ---\n");
    printf("Ti trovi su: %-25s | Tipo: %-15s | Colore: %-15s | Costo: %d\n\n",
           c->nome,
           NomiTipo[c->tipo],
           NomiColore[c->colore],
           c->costo);

    switch (c->tipo) {

    case VIA:
        printf("Passi dal VIA: guadagni 200 CFU!\n");
        g->cfu += 200;
        break;

    case AULA:
    case MENSA:
    case ABBONAMENTO:
        gestisciAcquisti(g, c);
        break;

    case BUG: {

        printf("Sei finito su una casella BUG! Pesco una carta...\n");

        Carta *carta = pescaCarta(mazzo);

        if (!carta) {
            printf("Il mazzo e' vuoto!\n");
            break;
        }

        printf("Hai pescato: %s\n", carta->nome);
        printf("%s\n", carta->descrizione);

        for (int i = 0; i < carta->numero_effetti; i++) {

            Effetto e = carta->effetti[i];

            printf("Effetto %d: ", i + 1);

            switch (e.azione) {
                case PAGA_QUALCOSA: printf("PAGA_QUALCOSA (%d CFU)\n", e.quantita); break;
                case PAGA_TUTTO:    printf("PAGA_TUTTO\n"); break;
                case PRENDI:        printf("PRENDI (%d CFU)\n", e.quantita); break;
                case SALTA_TURNO:   printf("SALTA_TURNO\n"); break;
                case NUOVO_TURNO:   printf("NUOVO_TURNO\n"); break;
                case ESCI:          printf("ESCI dalla BatCaverna\n"); break;
                case VAI_INDIETRO:  printf("VAI_INDIETRO (%d caselle)\n", e.quantita); break;
                case VAI_AVANTI:    printf("VAI_AVANTI (%d caselle)\n", e.quantita); break;
                case REGALA:        printf("REGALA (%d aule)\n", e.quantita); break;
                default:            printf("Effetto sconosciuto\n"); break;
            }

            applicaEffetto(g, e, tabellone, mazzo);
        }

        break;
    }

    case PARCHEGGIO:
        printf("Sosta gratuita. Non succede nulla.\n");
        break;

    case VAI_BATCAVERNA:
        printf("Vai direttamente nella BatCaverna!\n");
        g->posizione = trovaBatcaverna(tabellone);
        g->turni_batcaverna = 3;
        break;

    case BATCAVERNA: {

        if (g->turni_batcaverna > 0) {

            printf("Sei nella BatCaverna. Turni da scontare: %d\n",
                   g->turni_batcaverna);

            printf("Hai 3 opzioni:\n");
            printf("1) Saltare il turno\n");
            printf("2) Tirare i dadi: se escono uguali esci\n");
            printf("3) Usare una carta ESCI (se ne possiedi)\n");
            printf("Scelta: ");

            int scelta;
            scanf("%d", &scelta);

            if (scelta == 1) {
                printf("Salti il turno.\n");
                g->turni_batcaverna--;
            }

            else if (scelta == 2) {
                int d1, d2;
                dadi(&d1, &d2);
                printf("Hai tirato %d e %d.\n", d1, d2);

                if (d1 == d2) {
                    printf("Dadi uguali! Esci dalla BatCaverna!\n");
                    g->turni_batcaverna = 0;
                    g->posizione = trovaBatcaverna(tabellone)->next;
                } else {
                    printf("Non sono uguali. Rimani in BatCaverna.\n");
                    g->turni_batcaverna--;
                }
            }

            else if (scelta == 3) {
                if (g->carte_esci != NULL) {
                    printf("Usi una carta ESCI!\n");
                    g->turni_batcaverna = 0;
                    g->posizione = trovaBatcaverna(tabellone)->next;
                } else {
                    printf("Non hai carte ESCI!\n");
                }
            }

        } else {
            printf("Non hai turni da scontare: questa casella funziona come PARCHEGGIO.\n");
        }

        break;
    }

    default:
        printf("Casella speciale non gestita.\n");
        break;
    }
}

// ============================================================================
//  CARICAMENTO PARTITA
// ============================================================================

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

// ============================================================================
//  LOGICA PRINCIPALE DELLA PARTITA — SPECIFICHE BASE
// ============================================================================

void avviaPartita(Giocatore *g, int n, Casella *tabellone) {

    int turno = 0;
    int finePartita = 0;

    // carico il mazzo UNA VOLTA SOLA
    Carta *mazzo = caricaMazzo("mazzo.txt");

    while (!finePartita) {

        Giocatore *corrente = &g[turno];
        int turnoFinito = 0;

        printf("\n==============================\n");
        printf("TURNO DEL GIOCATORE: %s\n", corrente->nome);
        printf("CFU: %d\n", corrente->cfu);
        printf("==============================\n");

        while (!turnoFinito) {

            int scelta = menuTurno(corrente);

            switch (scelta) {

            case TIRO_DADI: {

                int d1, d2;
                int totale = dadi(&d1, &d2);

                printf("Risultato dei dadi: %d e %d (totale = %d)\n",
                       d1, d2, totale);

                muoviGiocatore(corrente, totale);

                printf("Ora sei in: %s\n", corrente->posizione->nome);

                gestisciCasella(corrente, &mazzo, tabellone);

                turnoFinito = 1;
                break;
            }

            case STAMPA_DATI:
                for (int i = 0; i < n; i++)
                    stampaGiocatore(g[i]);
                break;

            case STAMPA_TABELLONE:
                stampaTabellone(tabellone);
                break;

            case SALVATAGGIO:
                printf("Partita salvata!\n");
                salvaPartita(g, n, tabellone);
                break;

            case ACQUISTO_CASELLA:
                gestisciAcquisti(corrente, corrente->posizione);
                break;

            case USCITA:
                printf("Hai scelto di uscire dal gioco.\n");
                finePartita = 1;
                turnoFinito = 1;
                break;

            default:
                printf("Scelta non valida.\n");
            }
        }

        turno = (turno + 1) % n;
    }
}
