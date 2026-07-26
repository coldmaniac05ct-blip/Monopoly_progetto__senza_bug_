//
// Created by Administrator on 24/07/2026.
//

#include "partita.h"

#include <stdio.h>
#include <stdlib.h>
#include "turno.h"

//questa funzione si occupa di stampare il menù del turno del giocatore e di leggere la scelta che il giocatore seleziona
//uso static int per fare si che la funzione rimanga privata all'interno del file e non venga esportata altrove, dato che
//il menù del turno è una cosa interna alla gestione della partita e non deve essere richiamato da altri moduli
static int menuTurno(Giocatore *g) {

    printf("\n--- Turno di %s ---\n", g->nome); //stampo a schermo il nome del giocatore che sta effettuando il turno,
    //così da rendere chiaro chi deve scegliere cosa fare


    //stampo tutte le opzioni disponibili per il giocatore durante il suo turno
    //ognuna di queste opzioni corrisponde a un'azione che verrà gestita dallo switch-case nella funzione avviaPartita()
    printf("1) Tira i dadi\n");
    printf("2) Mostra dati dei giocatori\n");
    printf("3) Mostra tabellone\n");
    printf("4) Pesca una carta dal mazzo\n");
    printf("5) Salva partita\n");
    printf("0) Esci dal gioco\n");
    printf("Scelta: ");

    //dichiaro la variabile scelta che conterrà il numero selezionato dal giocatore
    //la scanf leggerà il valore inserito da tastiera e lo memorizzerà in scelta
    int scelta;
    scanf("%d", &scelta);

    //ritorno la scelta al chiamante, cioè avviaPartita(),
    //che poi si occuperà di interpretare il numero e di eseguire l'azione corrispondente
    return scelta;
}

void avviaPartita(Giocatore *g, int n, Casella *tabellone) {
    //questa funzione si occupa di avviare la partita vera e propria, cioè il ciclo dei turni dei giocatori
    //qui dentro avviene tutta la logica del gioco: tiro dei dadi, movimento sul tabellone, pesca delle carte, salvataggio, ecc.
    //la funzione riceve:
    // - g: l'array dei giocatori
    // - n: il numero dei giocatori
    // - tabellone: la lista circolare delle caselle del Monopoly

    int turno = 0;//inizializzo il turno a 0, cioè il primo giocatore nell'array
    //ogni volta che un turno finisce, incremento questa variabile e uso il modulo per tornare al primo giocatore

    int finePartita = 0; //questa variabile serve per capire quando la partita deve terminare
    //rimane a 0 finché il giocatore non sceglie di uscire dal gioco

    Carta *mazzo = NULL;//dichiaro il mazzo di carte, inizialmente vuoto
    //verrà caricato quando il giocatore sceglie di pescare una carta


    while (!finePartita) {//ciclo principale della partita: finché finePartita rimane 0, il gioco continua

        Giocatore *corrente = &g[turno];//corrente è il giocatore che sta effettuando il turno
        //uso &g[turno] per ottenere il puntatore al giocatore corretto

        int scelta = menuTurno(corrente);//richiamo il menù del turno e memorizzo la scelta del giocatore


        switch (scelta) {//in base alla scelta del giocatore, eseguo l'azione corrispondente

        case 1: {//tiro dei dadi
                //il dado deve generare un numero randomico da 1 a 6
                //uso rand() % 6 per ottenere un numero da 0 a 5 e aggiungo +1 per ottenere da 1 a 6

                int dado = (rand() % 6) + 1;

                printf("%s tira il dado: %d\n", corrente->nome, dado);

                //muovo il giocatore sul tabellone in base al numero ottenuto dal dado
                //questa funzione aggiorna la posizione del giocatore e gestisce eventuali effetti della casella
                muoviGiocatore(corrente, dado);

                break;
            }

        case 2://stampa i dati di tutti i giocatori
            //scorro l'array dei giocatori e stampo le informazioni di ciascuno


                for (int i = 0; i < n; i++)
                    stampaGiocatore(g[i]);
                break;

        case 3://stampa il tabellone
            //stampo tutte le caselle del tabellone, una per una


                stampaTabellone(tabellone);
                break;

        case 4: {//pesca una carta dal mazzo
                //se il mazzo non è stato ancora caricato, lo carico ora

                Carta *carta = pescaCarta(&mazzo);
                //pesco una carta dal mazzo

                if (!carta) { //controllo che la carta esista, se la carta non esiste allora avverto dell'eventuale problema
                    printf("Il mazzo e' vuoto o non e' stato caricato!\n");
                    break;
                }

                //stampo il nome e la descrizione della carta pescata
                printf("Hai pescato: %s\n", carta->nome);
                printf("%s\n", carta->descrizione);

                break;
            }

            case 5://salva la partita

                printf("Partita salvata!\n");
                salvaPartita(g, n, tabellone);
                break;

            case 0://uscita dal gioco

                printf("Hai scelto di uscire dal gioco.\n");
                finePartita = 1;//imposto il flag per terminare il ciclo
                break;

            default://scelta non valida

                printf("Scelta non valida.\n");
        }


        turno = (turno + 1) % n;//passo al giocatore successivo
        //uso il modulo per tornare al primo giocatore quando arrivo all'ultimo
    }
}

void caricaPartita(Giocatore **g, int *n, Casella *tab) {
    //questa funzione si occupa di caricare una partita già esistente dal file savegame.sav
    //il file è binario e contiene:
    // - il numero dei giocatori
    // - i nomi dei giocatori
    // - i loro cfu
    // - la loro posizione sul tabellone (salvata come indice da 0 a 39)
    //la funzione deve ricostruire l'array dei giocatori e ricollegare la posizione alla casella corretta

    FILE *fp = fopen("savegame.sav", "rb");//apro il file savegame.sav in modalità lettura binaria
    if (!fp)//se il file non esiste, non faccio nulla e ritorno
        return;

    fread(n, sizeof(int), 1, fp);//leggo il numero dei giocatori dal file

    *g = malloc(sizeof(Giocatore) * (*n));//alloco memoria per l'array dei giocatori


    for (int i = 0; i < *n; i++) {//scorro tutti i giocatori e carico i loro dati

        fread((*g)[i].nome, sizeof(char), LUNGHEZZA_STRINGA, fp);//carico il nome del giocatore, saranno tanti
        //nomi quanti il numero di giocatori inseriti


        fread(&(*g)[i].cfu, sizeof(int), 1, fp);//carico i cfu del giocatore


        int pos;
        fread(&pos, sizeof(int), 1, fp);//carico la posizione salvata come indice numerico

        (*g)[i].posizione = casellaDaIndice(tab, pos);//converto l'indice in un puntatore alla casella corretta del tabellone
    }

    fclose(fp);//chiudo il file
}
