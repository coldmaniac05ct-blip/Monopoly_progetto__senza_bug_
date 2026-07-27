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
// Questa funzione serve per individuare la casella “BatCaverna” all’interno del
// tabellone. Il tabellone, nel nostro progetto, è una lista circolare di 40
// caselle: questo significa che non esiste un “ultimo elemento”, perché dopo
// l’ultima casella si ritorna automaticamente alla prima.
//
// Per trovare la BatCaverna, non possiamo usare un indice come in un array,
// quindi dobbiamo scorrere la lista casella per casella finché non troviamo
// quella con tipo == BATCAVERNA.
//
// Il ciclo do/while è fondamentale: ci permette di visitare TUTTE le caselle
// della lista circolare e fermarci solo quando torniamo al punto di partenza.
// Se la BatCaverna non esistesse (cosa impossibile nel tabellone ufficiale),
// la funzione restituirebbe NULL.
//
Casella* trovaBatcaverna(Casella *tabellone) {

    // parto dalla prima casella del tabellone
    Casella *c = tabellone;

    do {// scorro la lista circolare finché non torno al punto di partenza
        if (c->tipo == BATCAVERNA) // se la casella corrente è la BatCaverna, la restituisco subito
            return c;
        c = c->next;// altrimenti passo alla casella successiva
    } while (c != tabellone);// condizione che garantisce la circolarità

    return NULL;// se non ho trovato nulla (caso teorico), restituisco NULL
}


// ============================================================================
//  MENÙ DEL TURNO (SPECIFICHE BASE)
// ============================================================================
// Questa funzione stampa il menù delle azioni disponibili durante il turno di
// un giocatore. Le specifiche del progetto BASE stabiliscono che il giocatore
// può visualizzare informazioni liberamente, ma può tirare i dadi UNA sola
// volta per turno. Dopo il tiro dei dadi, il turno termina automaticamente.
//
// La funzione si limita a stampare le opzioni e leggere la scelta dell’utente.
// Non esegue nessuna logica: si occupa solo dell’input.

static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome);// stampo il nome del giocatore per rendere chiaro di chi è il turno

    // elenco delle azioni disponibili secondo le specifiche BASE
    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("5) Salva partita\n");
    printf("6) Compra proprieta'\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;// leggo la scelta dell’utente
    scanf("%d", &scelta);

    return scelta;// restituisco la scelta al chiamante
}

// ============================================================================
//  GESTIONE ACQUISTI (SPECIFICHE BASE)
// ============================================================================
// Questa funzione gestisce TUTTA la logica di acquisto delle caselle AULA,
// MENSA e ABBONAMENTO. Le specifiche BASE prevedono che:
//
//  - se la casella è libera, il giocatore può comprarla pagando il costo
//  - se la casella è sua, può acquistare sedie o scrivania
//  - se la casella è di un altro giocatore, deve pagare il pedaggio
//
// La funzione è chiamata automaticamente dopo il movimento del giocatore,
// quando finisce su una casella acquistabile.
//
void gestisciAcquisti(Giocatore *g, Casella *c) {

    // stampo informazioni sulla casella corrente
    printf("\n--- Gestione acquisti ---\n");
    printf("Ti trovi sulla casella: %s (Tipo: %s)\n",
           c->nome, NomiTipo[c->tipo]);

    if (c->proprietario == NULL) {

        // ============================
        // CASO 1: casella libera
        // ============================
        printf("Questa casella non ha proprietario.\n");
        printf("Vuoi comprarla per %d CFU? (1=si, 0=no): ", c->costo);

        int scelta;
        scanf("%d", &scelta);

        if (scelta == 1) {// se il giocatore decide di comprare
            if (g->cfu >= c->costo) {// controllo che abbia abbastanza CFU

                g->cfu -= c->costo; // pago il costo della casella
                c->proprietario = g;// assegno la casella al giocatore

                if (c->tipo == AULA || c->tipo == MENSA)// se è un’AULA o una MENSA, incremento il numero
                    //di proprietà, però non funziona ancora al momento quindi è da controllare
                    g->numero_aule_mense++;

                printf("Hai comprato %s!\n", c->nome);

            } else {
                printf("Non hai abbastanza CFU.\n");
            }
        }
        return;
    }

    if (c->proprietario == g) {

        // ============================
        // CASO 2: casella del giocatore
        // ============================
        printf("Questa casella è tua.\n");
        printf("Cosa vuoi comprare?\n");
        printf("1) Una sedia (20 CFU)\n");
        printf("2) Una scrivania (50 CFU)\n");
        printf("0) Niente\n");
        printf("Scelta: ");

        int scelta;
        scanf("%d", &scelta);

        switch (scelta) {

        case 1:// acquisto di una sedia
            if (g->cfu >= 20) {
                g->cfu -= 20;
                c->sedie++;
                printf("Hai comprato una sedia! Ora ne hai %d.\n", c->sedie);
            } else {
                printf("Non hai abbastanza CFU.\n");
            }
            break;

        case 2:// acquisto della scrivania (solo se non già presente)
            if (c->scrivania == 1) {
                printf("Hai gia' una scrivania qui.\n");
                break;
            }

            if (g->cfu >= 50) {//Questo blocco di codice viene eseguito quando il giocatore si trova su una
                //casella che già possiede (cioè c->proprietario == g) e ha scelto l’opzione:"compra una scrivania"
                //Prima di tutto, il gioco controlla se il giocatore ha abbastanza CFU per comprare la scrivania.
//La scrivania costa 50 CFU, quindi se il giocatore ha meno di 50 CFU, l’acquisto non può essere effettuato.
                g->cfu -= 50;//se il giocatore ha abbastanza cfu e decide di pagare allora toglie 50 cfu dal numero di cfu attuali
                c->scrivania = 1;//Questa riga aggiorna lo stato della casella: c->scrivania è un campo della struttura Casella
                //indica se la casella possiede una scrivania oppure no
                //il valore 1 significa “scrivania presente”, quindi posseduta, prima dell'acquisto sarà 0 dopo l'acquisto 1
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

    //c'è un terzo caso:la casella è stata già comprata da un altor giocatore
    printf("Questa casella appartiene a %s. Devi pagare il pedaggio.\n",
           c->proprietario->nome);//se la casella appartiene ad un altro giocatore
    //faccio pagare il pedaggio in cfu in base al valore della casella

    g->cfu -= c->costo;
}

// ============================================================================
//  APPLICA EFFETTO DELLA CARTA BUG — SPECIFICHE BASE
// ============================================================================
// Questa funzione applica l’effetto di UNA singola azione contenuta in una
// carta BUG. Le specifiche BASE stabiliscono che gli effetti devono essere
// applicati SUBITO, nell’ordine in cui compaiono nella carta.
//
// La funzione riceve:
//  - il giocatore che deve subire l’effetto
//  - la struttura Effetto che contiene l’azione da eseguire
//  - il tabellone (necessario per ESCI e movimenti)
//  - il mazzo (necessario per eventuali carte speciali)
//
// Ogni caso dello switch corrisponde a un’azione definita nell’enum Azione.
//
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
// Questa funzione è il cuore della logica del turno: dopo che il giocatore ha
// tirato i dadi e si è mosso, il gioco deve capire cosa succede nella casella
// in cui è arrivato.
//
// Ogni tipo di casella ha un comportamento diverso, definito dalle specifiche
// del progetto BASE.
//
void gestisciCasella(Giocatore *g, Carta **mazzo, Casella *tabellone) {

    Casella *c = g->posizione;

    printf("\n--- Gestione casella ---\n");
    printf("Ti trovi su: %-25s | Tipo: %-15s | Colore: %-15s | Costo: %d\n\n",// stampo informazioni sulla casella corrente
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

    case BUG: {// pesco una carta dal mazzo

        printf("Sei finito su una casella BUG! Peschi una carta...\n");

        Carta *carta = pescaCarta(mazzo);

        if (!carta) {//questa parte di codice è utile nel momento in cui il programma non riesca a leggere
            //correttamente il mazzo perchè risulta esserci un errore nell'allocazione di memoria,
            //quindi se carta è inesistente il mazzo è vuoto
            printf("Il mazzo e' vuoto!\n");
            break;
        }

        printf("Hai pescato: %s\n", carta->nome);// stampo nome e descrizione della carta
        printf("%s\n", carta->descrizione);

        for (int i = 0; i < carta->numero_effetti; i++) {// applico tutti gli effetti della carta

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
//
// Questa funzione ricostruisce una partita salvata leggendo il file
// savegame.sav. Vengono ripristinati:
//
//  - numero dei giocatori
//  - nome di ciascun giocatore
//  - CFU
//  - posizione sul tabellone
//
// Il tabellone deve essere già stato caricato prima di chiamare questa funzione.
//
void caricaPartita(Giocatore **g, int *n, Casella *tab) {

    FILE *fp = fopen("savegame.sav", "rb");
    if (!fp)
        return;

    fread(n, sizeof(int), 1, fp);// leggo il numero dei giocatori

    *g = malloc(sizeof(Giocatore) * (*n));// alloco l’array dinamico dei giocatori

    for (int i = 0; i < *n; i++) {

        fread((*g)[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);
        fread(&(*g)[i].cfu, sizeof(int), 1, fp);

        int pos;
        fread(&pos, sizeof(int), 1, fp);

        (*g)[i].posizione = casellaDaIndice(tab, pos);// ricostruisco la posizione sul tabellone
    }

    fclose(fp);
}

// ============================================================================
//  LOGICA PRINCIPALE DELLA PARTITA — SPECIFICHE BASE
// ============================================================================
//
// Questa funzione contiene il ciclo principale del gioco: ogni turno viene
// gestito qui. Il giocatore può:
//
//  - visualizzare informazioni
//  - tirare i dadi (una sola volta)
//  - acquistare proprietà
//  - salvare la partita
//
// Dopo il tiro dei dadi, il turno termina automaticamente.
//
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

        turno = (turno + 1) % n;//passa al turno successivo
    }
}
