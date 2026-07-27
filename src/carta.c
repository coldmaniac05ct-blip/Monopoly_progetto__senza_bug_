//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "carta.h"
#include "macro.h"
#include "casella.h"
#include "tabellone.h"
#include "effetto.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//questa funzione si occupa di caricare il mazzo di carte dal file mazzo.txt.
//il file è stato fornito dall'università e NON usa i ';', quindi non posso usare fscanf con formati complessi.
//devo leggere il file riga per riga rispettando esattamente la struttura che mi hanno dato.
//ogni carta nel file è composta da 7 blocchi:
// 1) ID della carta (intero)
// 2) tipo della carta (intero)
// 3) nome della carta (stringa su una riga)
// 4) descrizione della carta (stringa su una riga)
// 5) tipo della carta (di nuovo, intero) – il file lo ripete, quindi lo rileggo
// 6) numero di effetti (intero)
// 7) effetti: ogni effetto è composto da 3 interi (azione, quantità, tipoCasella)
//    scritti sulla stessa riga separati da spazi
//
//la funzione deve:
// - leggere tutti questi dati nell’ordine corretto
// - creare dinamicamente una struct Carta per ogni carta
// - collegare tutte le carte in una lista collegata semplice (head → next → next → ...)
// - ritornare la testa del mazzo

Carta* caricaMazzo(const char *nomeFile) {

    FILE *fp = fopen(nomeFile, "r");
    if (!fp) {
        printf("Errore: impossibile aprire %s\n", nomeFile);
        return NULL;
    }

    Carta *mazzo = NULL;
    Carta *ultimo = NULL;

    while (1) {

        int id;
        int tipoCarta1;
        char nome[LUNGHEZZA_STRINGA];
        char descrizione[DESCRIZIONE];
        int tipoCarta2;
        int numero_effetti;

        // 1) ID
        if (fscanf(fp, "%d", &id) != 1)
            break;

        // 2) TipoCarta (prima volta)
        if (fscanf(fp, "%d", &tipoCarta1) != 1)
            break;

        // 3) Nome (riga intera)
        if (fscanf(fp, " %31[^\n]", nome) != 1)
            break;

        // 4) Descrizione (riga intera)
        if (fscanf(fp, " %255[^\n]", descrizione) != 1)
            break;

        // 5) TipoCarta (seconda volta)
        if (fscanf(fp, "%d", &tipoCarta2) != 1)
            break;

        // 6) NumeroEffetti
        if (fscanf(fp, "%d", &numero_effetti) != 1)
            break;

        // Alloco la carta
        Carta *c = malloc(sizeof(Carta));
        c->next = NULL;
        snprintf(c->nome, LUNGHEZZA_STRINGA, "%s", nome);
        snprintf(c->descrizione, DESCRIZIONE, "%s", descrizione);
        c->tipo = tipoCarta2;
        c->numero_effetti = numero_effetti;

        // Alloco effetti
        c->effetti = malloc(sizeof(Effetto) * numero_effetti);

        // 7) Leggo gli effetti
        for (int i = 0; i < numero_effetti; i++) {
            int azione, quantita, tipoCasella;
            fscanf(fp, "%d %d %d", &azione, &quantita, &tipoCasella);

            c->effetti[i].azione = azione;
            c->effetti[i].quantita = quantita;
            c->effetti[i].tipo_casella = tipoCasella;
        }

        // Inserisco nel mazzo
        if (mazzo == NULL)
            mazzo = c;
        else
            ultimo->next = c;

        ultimo = c;
    }

    fclose(fp);
    return mazzo;
}


//questa funzione si occupa di pescare una carta dal mazzo.
//siccome il mazzo è una lista collegata semplice, la prima carta è quella in cima.
//quindi pesco la prima carta, la scollego dal mazzo e la ritorno al chiamante.

Carta* pescaCarta(Carta **start_mazzo)
{
    srand(time(NULL));
    //se il mazzo è vuoto, ritorno NULL
    if (!(*start_mazzo)) return NULL;

    //c è la carta pescata, cioè la prima del mazzo
    Carta *c = *start_mazzo;

    //aggiorno la testa del mazzo alla carta successiva
    *start_mazzo = (*start_mazzo)->next;

    //scollego la carta pescata
    c->next = NULL;

    return c;
}
//questa funzione si occupa di mescolare il mazzo di carte.
//per farlo trasformo la lista collegata in un array di puntatori,
//poi applico l’algoritmo di Fisher-Yates per mescolare l’array,
//infine ricostruisco la lista collegata con l’ordine mescolato.

void mescolaMazzo(Carta **start_mazzo)
{
    if (!(*start_mazzo)) return; //se il mazzo è vuoto non faccio nulla

    //conto quante carte ci sono nel mazzo
    int count = 0;
    Carta *tmp = *start_mazzo;
    while (tmp) {
        count++;
        tmp = tmp->next;
    }

    //creo un array dinamico di puntatori a Carta
    Carta **array = malloc(sizeof(Carta*) * count);

    //riempio l’array con le carte del mazzo
    tmp = *start_mazzo;
    for (int i = 0; i < count; i++) {
        array[i] = tmp;
        tmp = tmp->next;
    }

    //mescolo l’array con Fisher-Yates
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta *swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }

    //ricostruisco la lista collegata
    for (int i = 0; i < count - 1; i++)
        array[i]->next = array[i + 1];

    array[count - 1]->next = NULL;

    //aggiorno la testa del mazzo
    *start_mazzo = array[0];

    free(array);
}
// Inserisce una carta in fondo al mazzo (lista singolarmente concatenata)
// mazzo è un puntatore al puntatore alla testa della lista (Carta **)
// nuova è la carta da inserire
void inserisciInFondo(Carta **mazzo, Carta *nuova) {

    // Se il mazzo è vuoto, la nuova carta diventa la testa
    if (*mazzo == NULL) {
        nuova->next = NULL;
        *mazzo = nuova;
        return;
    }

    // Altrimenti scorro fino all'ultima carta
    Carta *curr = *mazzo;
    while (curr->next != NULL)
        curr = curr->next;

    // Inserisco la carta in fondo
    curr->next = nuova;
    nuova->next = NULL;
}
// -----------------------------------------------------------------------------
// PESCA UNA CARTA BUG E ASSEGNA GLI EFFETTI AL GIOCATORE
// -----------------------------------------------------------------------------

void pescaCartaBug(Giocatore *g, Carta **mazzo) {

    // Pesco la carta dal mazzo
    Carta *carta = pescaCarta(mazzo);

    if (!carta) {
        printf("Il mazzo è vuoto!\n");
        return;
    }

    // Stampo le informazioni della carta
    printf("\nHai pescato: %s\n", carta->nome);
    printf("%s\n", carta->descrizione);

    // Assegno gli effetti della carta al giocatore
    g->effettiDisponibili = carta->effetti;
    g->numEffettiDisponibili = carta->numero_effetti;

    // Memorizzo la carta pescata (se ti serve per rimetterla in fondo)
    g->ultimaCartaPescata = carta;

    printf("Puoi ora usare AGISCI per applicare gli effetti.\n");
}
