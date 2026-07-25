//
// Created by Administrator on 24/07/2026.
//

#include "partita.h"

#include <stdio.h>
#include <stdlib.h>
#include "turno.h"

static int menuTurno(Giocatore *g) {//uso static int per fare si che il menu di gioco venga ristampato
    //dopo ogni azione del giocatore, chiedendo rispettivamente ai giocatori cosa vogliono fare

    printf("\n--- Turno di %s ---\n", g->nome);
    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");//mostra i dati
    printf("3) Mostra tabellone\n");//mostra le caselle del tabellone
    printf("4) Mostra carte\n");
    printf("5) Salva partita\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    int scelta;//in base alla scelta selezionata la scanf agirà stampando
    //eventuali dati o comunque attingendo alla funzione corrispondente
    scanf("%d", &scelta);

    return scelta;//il mio compilatore dovrà essere in grado di stampare a schermo la scelta quindi
    //uso return per fare si che al giocatore torni la scelta selezionata
}

void avviaPartita(Giocatore *g, int n, Casella *tabellone) {//questa funzione si occupa di avviare la partita

    int turno = 0;//inizializzo in modo consono i turni
    int finePartita = 0;
    Giocatore * giocatori =NULL;
    Carta *mazzo = NULL;

    while (!finePartita) {

        Giocatore *corrente = &g[turno];

        int scelta = menuTurno(corrente);

        switch (scelta) {//questa parte è collegata alla scelta del giocatore, faccio uso di uno switch case per fare si
            //che il giocatore possa scorrere tra le varie opzioni e selezionarle

            case 1: {//tiro dei dadi, il tiro dev'essere randomico quindi uso una funzione di tipo rand time che vada da 1 a 6, inizialmente
                    //l'avrebbe letto come da 0 a 5 ma mettendo il +1 fixa il conto
                int dado = (rand() % 6) + 1;
                printf("%s tira il dado: %d\n", corrente->nome, dado);
                muoviGiocatore(corrente, dado);
                    //attenzione qua non segna su che casella sei, va sistemato!
                break;
            }

            case 2://si occupa di stampare i dati del giocatore, quindi proprietà, cfu ecc ecc
                for (int i = 0; i < n; i++)
                    stampaGiocatore(g[i]);
                break;

            case 3://stampa il tabellone a schermo quindi stamperà tutte e 40 le caselle
            //(40 perchè parte a contare da 0) prendendole in ordine dal file txt
                stampaTabellone(tabellone);
                break;

            case 4://si occupa di fare pescare una carta in modo randomico al giocatore
            //da controllare!
            Carta *carta = pescaCarta(&mazzo);
            printf("Hai pescato: %s\n", carta->nome);
            if (mazzo == NULL) {
                printf("ERRORE: mazzo non caricato!\n");
            }

            break;

            case 5:
            printf("Partita salvata!\n");// salva la partita tramite i file presenti in salvataggio.h,
            //il quale è ricollegato a salvataggio.c, dovrà puntare anche a su che casella del tabellone si sono fermati a stop partita
            salvaPartita(giocatori, n, tabellone);
                break;

            case 0:// serve a uscire dal gioco
                printf("Hai scelto di uscire dal gioco.\n");
                finePartita = 1;
                break;

            default:
                printf("Scelta non valida.\n");//nel momento in cui il giocatore scelga di selezionare
            //un opzione non valida o inesistente, ad esempio 12 dovrò informarlo del
            //problema tramite un messaggio di errore e reindirizzarlo al menu di gioco
        }

        // passa al giocatore successivo
        turno = (turno + 1) % n;
    }
}

void caricaPartita(Giocatore **g, int *n, Casella *tab) {//serve a caricare una partita già esistente dal file di slavataggio savegame.sav
    FILE *fp = fopen("savegame.sav", "rb");
    if (!fp) return;

    fread(n, sizeof(int), 1, fp);

    *g = malloc(sizeof(Giocatore) * (*n));

    for (int i = 0; i < *n; i++) {

        // carica nome, quindi controlla che stia usando i 31 caratteri utili
        fread((*g)[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);

        // carica cfu
        fread(&(*g)[i].cfu, sizeof(int), 1, fp);

        // carica posizione sul tabellone, quindi su che casella si trova il giocatore
        int pos;
        fread(&pos, sizeof(int), 1, fp);
        (*g)[i].posizione = casellaDaIndice(tab, pos);
    }

    fclose(fp);
}
