//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "tabellone.h"
#include "giocatore.h"

Casella* caricaTabellone() {//questa funzione si occupa di caricare il tabellone, quindi stamperà
    //a schermo le caselle, con costo, tipo, nome ecc
    FILE *fp = fopen(NOME_FILE, "r");
    if (fp == NULL) {
        printf("Errore: impossibile aprire %s\n");//in caso di errore avvisa che non si riesce ad aprire il tabellone
        exit(EXIT_FAILURE);
    }

    Casella *start = NULL;
    Casella *prev = NULL;

    for (int i = 0; i < 40; i++) {
        Casella *c = malloc(sizeof(Casella));

        fscanf(fp, "%31[^;];%d;%d;%d\n",//%31 perchè il massimo dei caratteri utili è 31 per il nome,
            //%d è riferito al tipo, trattandosi di un intero uso %d, quello successivo è per il colore e quello dopo è per il costo dato che i cfu
            //sono un numero intero, altrimenti sarebbe stato un %f o %.2f
               c->nome,
               (int*)&c->tipo,
               (int*)&c->colore,
               &c->costo);

        c->sedie = 0;//sto inizializzando le caselle, c sta per casella
        c->scrivania = false;
        c->next = NULL;
        c->prev = NULL;

        if (!start) {//serve a scorrere il tabellone e quindi le caselle ad inzio partita
            start = c;
        } else {
            prev->next = c;
            c->prev = prev;
        }

        prev = c;
    }

    start->prev = prev;
    prev->next = start;

    fclose(fp);
    return start;
}

void stampaTabellone(Casella *start) {//stampa il tabellone a schermo, quindi stamperà tutte le informazioni legate a tabellone.txt
    Casella *curr = start;
    int i = 0;

    do {
        printf("[%2d] %-30s Tipo=%d Colore=%d Costo=%d\n",
               i, curr->nome, curr->tipo, curr->colore, curr->costo);
        curr = curr->next;
        i++;
    } while (curr != start);
}
