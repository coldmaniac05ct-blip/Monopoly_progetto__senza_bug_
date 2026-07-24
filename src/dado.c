//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "dado.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//inizio scrittura codice

//il dado dovrà tirare un numero diverso randomico ogni volta che tiro quindi dovrà eseguire a randtime

int dadi(){

    int tiroDado;

    srand(time(NULL)); //inizializza la randomizzazione del tiro

    int tiro = (rand() % 6) + 1; //il dado ha 6 facce quindi il numero
    //dovrà essere da 1 a 6, siccome si tratta di un intero dichiaro come int tiro,
    //se non avessi messo +1 avrebbe contato da 0 a 5 dando un numero tecnicamente impossibile
    //per un dado e mancando una delle 6 facce dato che si sarebbe fermato a 5

    int d1 = tiroDado; // ponendo caso di avere 2 dadi dichiaro 2 interi e li chiamo d1 e d2 per indicare dado1 e dado2
    int d2 = tiroDado;
    printf("Hai tirato: %d e %d\n", d1, d2); //stampo il numero randomico

    return (rand() % 6) + 1; //dovrà tornarmi il numero estratto quindi uso return e scrivo %6 per
    //fare si che dia un numero da 0 a 5 e metto +1 per aggiustare i conti da 1 a 6

}
// Funzione: tiraDado (privata)

int tiraDado() {
    return (rand() % 6) + 1;
}
