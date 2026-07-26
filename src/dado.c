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

int dadi(int *d1, int *d2){

    *d1 = (rand() % 6) + 1;   // primo dado
    *d2 = (rand() % 6) + 1;   // secondo dado

    printf("Risultato dei dadi: %d e %d\n", *d1, *d2);

    int totale = *d1 + *d2;
    printf("Totale ottenuto: %d\n", totale);

    return totale;

}
// Funzione: tiraDado (privata)

int tiraDado() {
    return (rand() % 6) + 1;
}
