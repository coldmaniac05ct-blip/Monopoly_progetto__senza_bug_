//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "casella.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//questa funzione si occupa di creare una singola casella del tabellone del Monopoly.
//ogni casella deve avere un nome, un tipo, un colore e un costo, quindi la funzione riceve questi parametri
//e li inserisce dentro la struct Casella che poi verrà collegata alle altre caselle formando una lista circolare.
//uso malloc per creare dinamicamente la casella, così posso costruire il tabellone in modo flessibile.

const char *NomiSegnaPosto[4] = {
    "MOUSE",
    "TASTIERA",
    "CAVO_HDMI",
    "PROIETTORE"
}; //array dei nomi dei segnaposti

Casella *creaCasella(char *nome, int tipo, int colore, int costo) {

    Casella *c = malloc(sizeof(Casella));

    strcpy(c->nome, nome);
    c->tipo = tipo;
    c->colore = colore;
    c->costo = costo;

    c->sedie = 0;
    c->scrivania = false;

    // 🔥 INIZIALIZZAZIONE OBBLIGATORIA
    c->proprietario = NULL;

    // per la lista circolare
    c->next = NULL;
    c->prev = NULL;

    return c;

}
//questa funzione serve per inserire una nuova casella in coda alla lista circolare del tabellone.
//la lista è doppiamente collegata (next e prev) e circolare, quindi l’ultima casella punta alla prima
//e la prima punta all’ultima. Questo permette di muovere il giocatore sul tabellone senza mai uscire dai limiti.
//se head è NULL significa che la lista è vuota, quindi la nuova casella diventa sia head che tail.

Casella *inserisciInCoda(Casella *head, Casella *nuova) {

    //se la lista è vuota, la nuova casella diventa l’unico nodo e punta a sé stessa
    if (!head) {
        nuova->next = nuova;
        nuova->prev = nuova;
        return nuova;
    }

    //tail è l’ultima casella della lista, cioè quella puntata da head->prev
    Casella *tail = head->prev;

    //collego la nuova casella dopo la tail
    tail->next = nuova;
    nuova->prev = tail;

    //chiudo il cerchio collegando la nuova casella alla head
    nuova->next = head;
    head->prev = nuova;

    //ritorno la head perché la testa della lista non cambia
    return head;
}
//questa funzione serve per ottenere la casella corrispondente a una posizione numerica sul tabellone.
//siccome il tabellone è una lista circolare, non posso usare gli indici come negli array.
//devo scorrere la lista passo dopo passo finché non raggiungo la posizione richiesta.

Casella* getCasella(Casella* start, int posizione) {

    //parto dalla casella iniziale (VIA)
    Casella* curr = start;

    //scorro la lista posizione volte
    for (int i = 0; i < posizione; i++)
        curr = curr->next;

    //ritorno la casella trovata
    return curr;
}
//questa funzione fa la stessa cosa di getCasella(), ma è più robusta perché controlla che la lista sia valida.
//serve soprattutto quando carico la partita dal file savegame.sav, dove la posizione è salvata come numero.

Casella *casellaDaIndice(Casella *start, int index) {

    //se la lista è vuota, ritorno NULL
    if (!start) return NULL;

    Casella *curr = start;
    int i = 0;

    //scorro la lista finché non trovo l’indice richiesto
    do {
        if (i == index)
            return curr;

        curr = curr->next;
        i++;

    } while (curr != start);

    //se arrivo qui significa che l’indice è fuori range
    return NULL;
}
//questa funzione fa il contrario di getCasella: dato un puntatore a una casella,
//ritorna il suo indice numerico all’interno del tabellone.
//serve per salvare la partita, perché nel file salvo solo il numero della casella,
//non il puntatore (che sarebbe inutile e non valido al prossimo avvio).

int indiceCasella(Casella *start, Casella *target) {

    Casella *curr = start;
    int index = 0;

    //scorro la lista finché non trovo la casella target
    do {
        if (curr == target)
            return index;

        curr = curr->next;
        index++;

    } while (curr != start);

    //se non trovo la casella, ritorno -1 come errore
    return -1;
}
//questa funzione stampa a schermo le informazioni di una singola casella.
//la uso quando il giocatore si muove e voglio informarlo su dove è finito.

void stampaCasella(Casella* c, int posizione) {

    printf("Giocatore è sulla casella [%d]: %s Tipo=%d, Colore=%d, Costo=%d\n",
           posizione, c->nome, c->tipo, c->colore, c->costo);

}
//questa funzione serve per testare il tabellone e verificare che la lista circolare sia stata costruita correttamente.
//stampo ogni nodo, il suo indirizzo, il next e il prev, così posso vedere se ci sono errori nei collegamenti.
//se la lista non è circolare, il ciclo diventerebbe infinito, quindi metto un limite di sicurezza a 100 nodi.

void testTabellone(Casella *head) {

    //se la lista è vuota, stampo un messaggio e termino
    if (!head) {
        printf("Tabellone vuoto.\n");
        return;
    }

    Casella *curr = head;
    int count = 0;

    printf("\n--- TEST TABELLONE ---\n");

    //scorro la lista finché non torno alla head
    do {
        printf("Nodo %2d | Nome: %-25s | Addr: %p | Next: %p | Prev: %p\n",
               count, curr->nome, (void*)curr, (void*)curr->next, (void*)curr->prev);

        curr = curr->next;
        count++;

        //se supero 100 nodi, significa che la lista non è circolare
        if (count > 100) {
            printf("ERRORE: la lista non è circolare (loop infinito)\n");
            return;
        }

    } while (curr != head);

    //stampo il numero totale di caselle
    printf("\nTotale caselle: %d\n", count);

    //controllo se il tabellone ha esattamente 40 caselle
    if (count == 40)
        printf("OK: Il tabellone contiene 40 caselle.\n");
    else
        printf("ERRORE: Il tabellone NON contiene 40 caselle.\n");

    printf("-----------------------\n\n");
}
