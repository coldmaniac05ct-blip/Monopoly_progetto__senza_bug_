//
// Created by Administrator on 24/07/2026.
//

//
// File: partita.c
// Gestione del turno, movimento, effetti, acquisti e ciclo principale
//

#include "partita.h"
#include "dado.h"
#include "turno.h"

#include <stdio.h>
#include <stdlib.h>

//
// ============================================================================
// TROVA LA CASELLA BATCAVERNA
// ============================================================================
// Scorre la lista circolare finché trova la casella BATCAVERNA.
// Se non la trova (caso teorico), restituisce NULL.
//
Casella* trovaBatcaverna(Casella *tabellone) {
    Casella *c = tabellone;

    do {
        if (c->tipo == BATCAVERNA)
            return c;
        c = c->next;
    } while (c != tabellone);

    return NULL;
}

//
// ============================================================================
// MENÙ DEL TURNO
// ============================================================================
// Il giocatore può tirare i dadi una sola volta.
// Le altre opzioni sono informative e servono a mostrare i dati, il tabellone effettuare un salvataggio
// oppure uscire del gioco senza arrestare in modo brusco il programma.
//
static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome);

    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("4) Salva partita\n");   // <-- CORRETTO
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;
    scanf("%d", &scelta);
    return scelta;
}

//
// ============================================================================
// GESTIONE ACQUISTI
// ============================================================================
// Gestisce:
//  - acquisto casella libera
//  - acquisto sedie/scrivania su casella propria
//  - pagamento pedaggio su casella altrui
//
void gestisciAcquisti(Giocatore *g, Casella *c) {

    printf("\n--- Gestione acquisti ---\n");
    printf("Ti trovi sulla casella: %s (Tipo: %s)\n",
           c->nome, NomiTipo[c->tipo]);

    // CASO 1 — Casella libera
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

    // CASO 2 — Casella del giocatore
    if (c->proprietario == g) {//nel momento in cui il giocatore corrente
        //sia il proprietario della casella allora chiedo come vuole fare

        printf("Questa casella è tua.\n");
        printf("1) Sedia (20 CFU)\n");
        printf("2) Scrivania (50 CFU)\n");
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
            } else printf("Non hai abbastanza CFU.\n");
            break;

        case 2:
            if (c->scrivania == 1) {
                printf("Hai già una scrivania.\n");
                break;
            }
            if (g->cfu >= 50) {
                g->cfu -= 50;
                c->scrivania = 1;
                printf("Hai comprato una scrivania!\n");
            } else printf("Non hai abbastanza CFU.\n");
            break;

        case 0:
            printf("Non compri nulla.\n");
            break;

        default:
            printf("Scelta non valida.\n");
        }

        return;
    }

    // CASO 3 — Casella di un altro giocatore
    printf("Questa casella appartiene a %s. Devi pagare il pedaggio.\n",
           c->proprietario->nome);

    g->cfu -= c->costo;
}
// ============================================================================
// AGGIORNA IL PROPRIETARIO
// ============================================================================
//Senza questa funzione:
//
//il tabellone contiene proprietari invalidi
//
//-le caselle puntano a memoria eliminata
//
//-il gioco crasha quando accedi a c->proprietario->nome
//
//-i pedaggi vengono pagati a giocatori eliminati
//
//-il salvataggio/caricamento diventa incoerente
//
//-la partita non può finire correttamente


//In breve il tabellone diventerebbe un colabrodo di caselle fantasma
void aggiornaProprietari(Casella *tabellone, Giocatore *g, int n) {//nel momento in cui il giocatore
    //che possedeva le caselle venga eliminato allora devo aggiornare l'array

    Casella *c = tabellone;

    do {
        if (c->proprietario != NULL) {

            int idx = indiceGiocatore(g, n, c->proprietario);

            if (idx == -1) {
                // proprietario eliminato
                c->proprietario = NULL;
                c->sedie = 0;
                c->scrivania = 0;
            }
        }

        c = c->next;

    } while (c != tabellone);
}

//
// ============================================================================
// APPLICA EFFETTO DI UNA CARTA BUG
// ============================================================================
// Applica l’effetto contenuto nella struttura Effetto.
//
void applicaEffetto(Giocatore *g, Effetto e, Casella *tabellone, Carta **mazzo) {

    switch (e.azione) {

    case PAGA_QUALCOSA:
        printf("PAGA_QUALCOSA (%d CFU)\n", e.quantita);
        g->cfu -= e.quantita;
        break;

    case PAGA_TUTTO:
        printf("PAGA_TUTTO\n");
        g->cfu = 0;
        break;

    case PRENDI:
        printf("PRENDI (%d CFU)\n", e.quantita);
        g->cfu += e.quantita;
        break;

    case SALTA_TURNO:
        printf("SALTA_TURNO\n");
        g->saltaTurno = 1;
        break;

    case NUOVO_TURNO:
        printf("NUOVO_TURNO\n");
        g->nuovo_turno = 1;
        break;

    case ESCI:
        printf("ESCI dalla BatCaverna\n");
        g->turni_batcaverna = 0;
        g->posizione = trovaBatcaverna(tabellone)->next;
        break;

    case VAI_INDIETRO:
        printf("VAI_INDIETRO (%d caselle)\n", e.quantita);
        muoviGiocatore(g, -e.quantita);
        break;

    case VAI_AVANTI:
        printf("VAI_AVANTI (%d caselle)\n", e.quantita);
        muoviGiocatore(g, e.quantita);
        break;

    case REGALA:
        printf("REGALA (%d aule)\n", e.quantita);
        break;

    default:
        printf("Effetto sconosciuto.\n");
    }
}

//
// ============================================================================
// GESTIONE CASELLA DOPO IL MOVIMENTO
// ============================================================================
// Determina cosa succede quando il giocatore arriva su una casella.
//
void gestisciCasella(Giocatore *g, Carta **mazzo, Casella *tabellone) {

    Casella *c = g->posizione;

    printf("\n--- Gestione casella ---\n");
    printf("Ti trovi su: %-25s | Tipo: %-15s | Colore: %-15s | Costo: %d\n\n",
           c->nome, NomiTipo[c->tipo], NomiColore[c->colore], c->costo);

    switch (c->tipo) {

    case VIA:
        printf("Passi dal VIA: +200 CFU!\n");
        g->cfu += 200;//aggiorna il numero di cfu nel momento in cui si ripassi dal via
        break;

    case AULA:
    case MENSA:
    case ABBONAMENTO:
        gestisciAcquisti(g, c);
        break;

    case BUG: {

        printf("Casella BUG! Peschi una carta...\n");

        Carta *carta = pescaCarta(mazzo);
        if (!carta) {
            printf("Il mazzo è vuoto!\n");
            break;
        }

        printf("Hai pescato: %s\n", carta->nome);
        printf("%s\n", carta->descrizione);

        for (int i = 0; i < carta->numero_effetti; i++)
            applicaEffetto(g, carta->effetti[i], tabellone, mazzo);

        break;
    }

    case PARCHEGGIO:
        printf("Sosta gratuita.\n");
        break;

    case VAI_BATCAVERNA:
        printf("Vai nella BatCaverna!\n");
        g->posizione = trovaBatcaverna(tabellone);
        g->turni_batcaverna = 3;
        break;

    case BATCAVERNA: {

        if (g->turni_batcaverna > 0) {

            printf("Sei nella BatCaverna. Turni da scontare: %d\n",
                   g->turni_batcaverna);

            printf("1) Saltare il turno\n");
            printf("2) Tirare i dadi (se uguali esci)\n");
            printf("3) Usare carta ESCI\n");
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
                    printf("Esci dalla BatCaverna!\n");
                    g->turni_batcaverna = 0;
                    g->posizione = trovaBatcaverna(tabellone)->next;
                } else {
                    printf("Rimani in BatCaverna.\n");
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
            printf("Nessun turno da scontare: funziona come PARCHEGGIO.\n");
        }

        break;
    }

    default:
        printf("Casella speciale non gestita.\n");
        break;
    }
}

//
// ============================================================================
// CARICAMENTO PARTITA
// ============================================================================
void caricaPartita(Giocatore **g, int *n, Casella *tabellone) {

    FILE *fp = fopen("savegame.sav", "rb");
    if (!fp) {
        printf("Nessun file di salvataggio trovato.\n");
        return;
    }

    fread(n, sizeof(int), 1, fp);

    *g = malloc(sizeof(Giocatore) * (*n));

    // 1) carica giocatori
    for (int i = 0; i < *n; i++) {

        fread((*g)[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);
        fread(&(*g)[i].cfu, sizeof(int), 1, fp);
        fread(&(*g)[i].turni_batcaverna, sizeof(int), 1, fp);
        fread(&(*g)[i].saltaTurno, sizeof(bool), 1, fp);
        fread(&(*g)[i].nuovo_turno, sizeof(int), 1, fp);
        fread(&(*g)[i].numero_aule_mense, sizeof(int), 1, fp);
        fread(&(*g)[i].segna_posto, sizeof(int), 1, fp);

        int pos;
        fread(&pos, sizeof(int), 1, fp);
        (*g)[i].posizione = casellaDaIndice(tabellone, pos);

        // puntatori sempre NULL dopo il caricamento
        (*g)[i].carte = NULL;
        (*g)[i].carte_esci = NULL;
        (*g)[i].effettiDisponibili = NULL;
        (*g)[i].numEffettiDisponibili = 0;
        (*g)[i].ultimaCartaPescata = NULL;
    }

    // 2) carica caselle
    Casella *c = tabellone;
    do {
        fread(&c->sedie, sizeof(int), 1, fp);
        fread(&c->scrivania, sizeof(int), 1, fp);

        int proprietarioIndex;
        fread(&proprietarioIndex, sizeof(int), 1, fp);

        if (proprietarioIndex >= 0)
            c->proprietario = &((*g)[proprietarioIndex]);
        else
            c->proprietario = NULL;

        c = c->next;
    } while (c != tabellone);

    fclose(fp);
    printf("Partita caricata correttamente!\n");
}
//SCELTA SEGNA POSTO
void scegliSegnaPosto(Giocatore *g) {

    printf("\n--- Scegli il tuo segnaposto ---\n");

    for (int i = 0; i < 4; i++) {
        printf("%d) %s\n", i + 1, NomiSegnaPosto[i]);
    }

    int scelta;

    do {
        printf("Scegli un numero da 1-4: ");
        scanf("%d", &scelta);

        if (scelta < 1 || scelta > 4)
            printf("Scelta non valida, riprova.\n");

    } while (scelta < 1 || scelta > 4);

    g->segna_posto = (SegnaPosto)(scelta - 1);

    printf("Hai scelto: %s\n", NomiSegnaPosto[g->segna_posto]);
}

//
// ============================================================================
// AVVIA PARTITA
// ============================================================================
//Questa funzione si occupa principalmente di gestire le opzioni del menù di gioco e farle funzionare a partita iniziata
void avviaPartita(Giocatore *g, int n, Casella *tabellone) {

    int turno = 0;
    int finePartita = 0;

    Carta *mazzo = caricaMazzo("mazzo.txt");//carica il mazzo dal file.txt

    while (!finePartita) {

        Giocatore *corrente = &g[turno];
        int turnoFinito = 0;

        printf("\n==============================\n");
        printf("TURNO DI: %s\n", corrente->nome);
        printf("CFU: %d\n", corrente->cfu);
        printf("==============================\n");

        while (!turnoFinito) {//questa struttura di tipo enumerativo è stata definita da me nel file.h,
            //serve a fare ordine tra le opzioni del menù e renderle utilizzabili

            int scelta = menuTurno(corrente);

            switch (scelta) {

            case TIRO_DADI: {

                int d1, d2;
                int totale = dadi(&d1, &d2);

                printf("Dadi: %d e %d (totale = %d)\n", d1, d2, totale);

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

            case USCITA:
                printf("Uscita dal gioco.\n");
                finePartita = 1;
                turnoFinito = 1;
                break;

            default:
                printf("Scelta non valida.\n");
            }
        }

        // Dopo che il giocatore ha fatto il turno
        if (corrente->cfu <= 0) {
            printf("%s e' stato eliminato!\n", corrente->nome);

            // elimina il giocatore dall’array
            eliminaGiocatore(&g, &n, turno);

            // aggiorna i proprietari delle caselle
            aggiornaProprietari(tabellone, g, n);

            // se resta un solo giocatore allora la partita finisce
            if (n == 1) {
                printf("\n==============================\n");
                printf("   PARTITA TERMINATA\n");
                printf("   Ha vinto: %s!\n", g[0].nome);
                printf("==============================\n");
                return;
            }

            continue;
        }
        turno = (turno + 1) % n;//l'incremento avviene solo se nessuno
        //è stato ancora eliminato per passare al turno del giocatore successivo
    }
}
