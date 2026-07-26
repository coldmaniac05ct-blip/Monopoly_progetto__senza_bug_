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
//il mazzo è una lista collegata semplice, quindi ogni carta punta alla successiva.
//uso malloc per creare dinamicamente ogni carta, così posso aggiungerne quante ne voglio.
//il file deve contenere una carta per riga, con nome, descrizione, tipo e numero_effetti separati da ';'

Carta* caricaMazzo(const char *filename)
{
    FILE *fp = fopen(filename, "r"); //apro il file in modalità lettura

    //se il file non esiste o non riesco ad aprirlo, stampo un messaggio di errore e ritorno NULL
    if (!fp) {
        printf("Errore: impossibile aprire %s\n", filename);
        return NULL;
    }

    Carta *head = NULL; //testa della lista
    Carta *tail = NULL; //ultima carta inserita

    //variabili temporanee per leggere i dati dal file
    char nome[32];
    char descrizione[256];
    int tipo;
    int numero_effetti;

    //leggo il file finché non finisce
    while (fscanf(fp, "%31[^;];%255[^;];%d;%d;",
                  nome, descrizione, &tipo, &numero_effetti) == 4)
    {
        //alloco memoria per una nuova carta
        Carta *c = malloc(sizeof(Carta));

        //copio i dati dentro la struct
        strcpy(c->nome, nome);
        strcpy(c->descrizione, descrizione);
        c->tipo = tipo;
        c->numero_effetti = numero_effetti;

        //alloco memoria per gli effetti della carta
        c->effetti = malloc(sizeof(Effetto) * numero_effetti);

        //leggo gli effetti uno per uno
        for (int i = 0; i < numero_effetti; i++) {
            fscanf(fp, "%d,%d,%d;",
                   (int*)&c->effetti[i].azione,
                   &c->effetti[i].quantita,
                   (int*)&c->effetti[i].tipo_casella);
        }

        //inizializzo il puntatore next
        c->next = NULL;

        //inserisco la carta nella lista
        if (!head) {
            head = c;
            tail = c;
        } else {
            tail->next = c;
            tail = c;
        }
    }

    fclose(fp);
    return head; //ritorno la testa del mazzo
}

//questa funzione si occupa di pescare una carta dal mazzo.
//siccome il mazzo è una lista collegata semplice, la prima carta è quella in cima.
//quindi pesco la prima carta, la scollego dal mazzo e la ritorno al chiamante.

Carta* pescaCarta(Carta **start_mazzo)
{
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
