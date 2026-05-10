#include <stdio.h>
#include <stdlib.h>
#include "src/caselle.h"

int main() {
    Casella *tab = caricaTabellone("tabellone.txt");

    if (tab == NULL) {
        printf("Errore nel caricamento del tabellone.\n");
        return 1;
    }

    stampaTabellone(tab);
    testTabellone(tab);

    return 0;
}