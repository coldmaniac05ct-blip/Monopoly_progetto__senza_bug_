//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "tabellone.h"
#include "carte.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Carta* caricaMazzo(const char *filename)
{
    FILE *fp = fopen(filename, "r");//cerco di leggere il mazzo con r cioè read
    int i;

    for (i = 0; i < MAX_ID; i++){//creo un ciclo for

        if (fp == NULL) {//in caso di errore allora avviso tramite printf
            printf("Errore: impossibile aprire %s\n", filename);
            exit(EXIT_FAILURE);//avviso il programmatore che c'è un errore
        }

    }

    Carta *head = NULL; //inizializzo l'inizio e la fine del mazzo tramite ricorsione head-tail
    Carta *tail = NULL;


    Carta *c = malloc(sizeof(Carta));//dichiaro uno spazietto di memoria per caricare una nuova carta

    fscanf(fp, "%31[^;];%255[^;];%d;%d;",//qui sto dichiarando i parametri quindi "il numero massimo di
        //caratteri per il nome della carta è 31, 255 è il limite di caratteri per la descrizione della carta,
        //%d indica che la carta è di tipo intero e l'altro %d è per il numero_effetti anch'esso un intero
           c->nome,
           c->descrizione,
           (int*)&c->tipo,
           &c->numero_effetti);

    c->effetti = malloc(sizeof(Effetto) * c->numero_effetti);//creo un array dinamico che prenda da c (carta)
    //gli effetti e li applichi in base al numero

    for (int i = 0; i < c->numero_effetti; i++) {//per ogni effetto sto leggendo:azione, quantità e tipo casella, tutti e 3 sono interi
        fscanf(fp, "%d,%d,%d;",
               (int*)&c->effetti[i].azione,
               &c->effetti[i].quantita,
               (int*)&c->effetti[i].tipo_casella);
    }

    c->next = NULL;

    if (!head) {
        head = c;
        tail = c;
    }
    else{
        tail->next = c;
        tail = c;

        fclose(fp);
        return head;
    }
}

void mescolaMazzo(Carta **start_mazzo) {//mescolo il mazzo, quindi la mia funzione
    //dovrà contare quante carte ho estratto finora e quali
    if (!(*start_mazzo)) return;

    int count = 0;
    Carta *tmp = *start_mazzo;
    while (tmp) {
        count++;
        tmp = tmp->next;
    }

    Carta **array = malloc(sizeof(Carta*) * count);//qua dichiaro un array dinamico
    //perchè la grandezza della carta è variabile
    tmp = *start_mazzo;
    for (int i = 0; i < count; i++) {
        array[i] = tmp;
        tmp = tmp->next;
    }

    srand(time(NULL));//la carta dovrà essere randomica
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta *swap = array[i];
        array[i] = array[j];
        array[j] = swap;
    }

    for (int i = 0; i < count - 1; i++)
        array[i]->next = array[i + 1];

    array[count - 1]->next = NULL;
    *start_mazzo = array[0];

    free(array);
}

Carta* pescaCarta(Carta **start_mazzo) {//faccio pescare una carta al giocatore
    if (!(*start_mazzo)) return NULL;

    Carta *c = *start_mazzo;
    *start_mazzo = (*start_mazzo)->next;
    c->next = NULL;
    return c;
}

void inserisciInFondo(Carta **start_mazzo, Carta *c) {//nel momento in cui devo riporre la carta devo farla finire infondo al mazzo
    if (!(*start_mazzo)) {
        *start_mazzo = c;
        c->next = NULL;
        return;
    }

    Carta *tmp = *start_mazzo;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = c;
    c->next = NULL;
}

void stampaMazzo(Carta *start_mazzo) {//stampo il mazzo e quindi anche la carta estratta
    int i = 0;
    while (start_mazzo) {
        printf("[%d] %s (%d effetti)\n", i, start_mazzo->nome, start_mazzo->numero_effetti);//stampo carta, nome e quanti effetti ha
        start_mazzo = start_mazzo->next;
        i++;
    }
}

int carta() {
    Carta *start_mazzo = caricaMazzo("mazzo.txt");//questa parte di codice si occupa di caricare eventuali carte

    Casella *start_tabellone = caricaTabellone();
    testTabellone(start_tabellone);

    mescolaMazzo(&start_mazzo);//inizia il mazzo

    Carta *c1 = pescaCarta(&start_mazzo);
    inserisciInFondo(&start_mazzo, c1);

    printf("=== TEST COMPLETO ===\n");
    testTabellone(start_tabellone);
    mescolaMazzo(&start_mazzo);


    stampaTabellone(start_tabellone);
    testTabellone(start_tabellone);

    return 0;
}
