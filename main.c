//
// Created by Administrator on 10/05/2026.
//
//Studente:Elisa Alessandra Cataldo (e.cataldo@studenti.unica.it)
//Matricola:60/84/00112
//Tipo Progetto:BASE2
//Username Github:Cold Maniac
//Github link: https://github.com/coldmaniac05ct-blip/Monopoly_progetto__senza_bug_
//Necessità:NESSUNA

//ATTENZIONE:le subroutines sono riportate nei file header appositi

//inizio scrittura codice
//questa è la funzione principale del programma, cioè il punto di ingresso del gioco Monopoly.
//qui dentro si gestisce il menù iniziale, la creazione dei giocatori, il caricamento del tabellone,
//l’avvio della partita e il salvataggio finale. In pratica è il “regista” che coordina tutte le funzioni
//presenti negli altri file.c del progetto.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "src/giocatore.h"
#include "src/menu.h"
#include "src/partita.h"
#include "src/tabellone.h"
#include "src/salvataggio.h"
#include "src/dado.h"

int main(void) {

    //inizializzo la randomizzazione del programma, fondamentale perché il tiro del dado,
    //la pesca delle carte e altre funzioni che usano numeri casuali devono generare valori diversi
    //ogni volta che il programma viene eseguito. Se non mettessi srand(time(NULL)) all’inizio,
    //il programma genererebbe sempre la stessa sequenza di numeri, rendendo il gioco prevedibile.
    srand(time(NULL));

    int n;                     //numero dei giocatori che parteciperanno alla partita
    Giocatore *giocatori = NULL;  //array dinamico dei giocatori, inizialmente vuoto

    //stampo il menù iniziale e leggo la scelta dell’utente. Il menù è gestito da menuIniziale()
    //che si trova nel file menu.c. La funzione restituisce un intero che rappresenta la scelta.
    int scelta = menuIniziale();

    //carico il tabellone dal file tabellone.txt. Il tabellone è una lista circolare di 40 caselle,
    //quindi è fondamentale caricarlo UNA SOLA VOLTA e poi passarlo alle funzioni che ne hanno bisogno.
    //Se lo caricassi più volte, avrei più liste diverse e incoerenti, causando errori nelle posizioni.
    Casella *tabellone = caricaTabellone("tabellone.txt");
    if (!tabellone) {
        //se il file non esiste o è corrotto, il gioco non può partire perché il tabellone è la struttura
        //fondamentale del Monopoly. Senza tabellone non esiste il concetto di “casella”.
        printf("Errore: impossibile caricare il tabellone.\n");
        return 1;
    }

    //in base alla scelta del giocatore, il programma dovrà avviare una nuova partita,
    //caricare una partita esistente oppure uscire dal gioco.
    switch (scelta) {

        case 1:  //NUOVA PARTITA
            //se il giocatore sceglie di iniziare una nuova partita, devo chiedere quanti giocatori partecipano.
            //il regolamento del Monopoly prevede da 2 a 4 giocatori, quindi devo controllare che il valore sia valido.
            printf("Nuova partita!\n");
            printf("Quanti giocatori partecipano? (2-4): ");
            scanf("%d", &n);

            //se il valore inserito non è valido, stampo un messaggio di errore e richiedo il valore
            while (n < 2 || n > 4) {
                printf("Valore non valido. Inserisci 2-4: ");
                scanf("%d", &n);
            }

            //creo l’array dinamico dei giocatori tramite la funzione creaGiocatori()
            //che si occupa di chiedere i nomi e inizializzare i dati di ciascun giocatore.
            giocatori = creaGiocatori(n);

            //imposto la posizione iniziale di ogni giocatore sulla casella VIA.
            //siccome il tabellone è una lista circolare, la casella iniziale è semplicemente il puntatore
            //alla prima casella della lista, cioè tabellone.
            for (int i = 0; i < n; i++)
                giocatori[i].posizione = tabellone;

            break;

        case 2:  //CARICA PARTITA
            //se il giocatore sceglie di caricare una partita, devo leggere il file savegame.sav
            //e ricostruire l’array dei giocatori, le loro posizioni e i loro dati.
            printf("Caricamento partita...\n");
            caricaPartita(&giocatori, &n, tabellone);
            break;

        case 0:  //USCITA
            //se il giocatore sceglie di uscire dal gioco, termino il programma.
            printf("Uscita...\n");
            return 0;

        default:
            //se il giocatore inserisce un valore non valido, stampo un messaggio di errore e termino.
            printf("Scelta non valida.\n");
            return 1;
    }

    //se arrivo qui significa che la partita è pronta per essere avviata.
    //prima di iniziare, devo ordinare i giocatori in base al tiro del dado iniziale,
    //come da regolamento del Monopoly.
    printf("\nPartita pronta!\n");
    ordinaGiocatori(giocatori, n);

    //avvio la partita vera e propria. Questa funzione contiene il ciclo dei turni,
    //la gestione del movimento dei giocatori sul tabellone, la pesca delle carte, il salvataggio e tutto ciò che riguarda il gioco.
    avviaPartita(giocatori, n, tabellone);

    //al termine della partita, salvo lo stato su file tramite salvaPartita().
    //questo permette di riprendere la partita in un secondo momento.
    salvaPartita(giocatori, n, tabellone);

    //libero la memoria dinamica allocata per i giocatori.
    //anche se il programma sta per terminare, è buona pratica farlo sempre.
    liberaGiocatori(giocatori);

    return 0;
}
