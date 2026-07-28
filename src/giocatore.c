//
// Created by Administrator on 10/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "giocatore.h"
#include "dado.h"
#include "casella.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funzione: stampaGiocatore

void stampaGiocatore(Giocatore g) {
    printf("Giocatore: %s\n", g.nome);
    printf("CFU: %d\n", g.cfu);
    printf("Turni in caverna: %d\n", g.turni_batcaverna);
    printf("Salta turno: %d\n", g.saltaTurno);
    printf("Aule/Mense possedute: %d\n", g.numero_aule_mense);
    printf("Segnaposto: %s\n", NomiSegnaPosto[g.segna_posto]);
    printf("\n");
}


// Funzione: creaGiocatori, crea un tot di giocatori in base al numero dato

Giocatore* creaGiocatori(int n) {

    Giocatore *g = malloc(sizeof(Giocatore) * n);

    for (int i = 0; i < n; i++) {
        printf("Inserisci il nome del giocatore %d: ", i + 1);
        scanf("%s", g[i].nome);

        // MOSTRA LE OPZIONI DEL SEGNAPOSTO
        printf("\n--- Scegli il tuo segnaposto ---\n");
        for (int s = 0; s < 4; s++) {
            printf("%d) %s\n", s + 1, NomiSegnaPosto[s]);
        }

        int scelta;
        do {
            printf("Scelta (1-4): ");
            scanf("%d", &scelta);

            if (scelta < 1 || scelta > 4)
                printf("Scelta non valida, riprova.\n");

        } while (scelta < 1 || scelta > 4);

        g[i].segna_posto = scelta - 1;   // enum corretto

        printf("Hai scelto: %s\n\n", NomiSegnaPosto[g[i].segna_posto]);

        // inizializzazione campi
        g[i].cfu = 3000;
        g[i].turni_batcaverna = 0;
        g[i].saltaTurno = 0;
        g[i].numero_aule_mense = 0;
        g[i].carte = NULL;
        g[i].posizione = NULL;
    }

    return g;
}

// Funzione: ordinaGiocatori, serve a ordinare in modo randomico i giocatori

void ordinaGiocatori(Giocatore *g, int n) {

    srand(time(NULL));

    int valori[4];

    printf("\n--- Determinazione ordine di gioco ---\n");

    // Primo tiro
    for (int i = 0; i < n; i++) {
        valori[i] = tiraDado();
        printf("%s tira il dado e ottiene %d\n", g[i].nome, valori[i]);
    }

    // Gestione pareggi
    int pareggio = 1;
    while (pareggio) {
        pareggio = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                if (valori[i] == valori[j]) {
                    pareggio = 1;

                    printf("\nPareggio tra %s e %s! Ritirano...\n",
                           g[i].nome, g[j].nome);

                    valori[i] = tiraDado();
                    valori[j] = tiraDado();

                    printf("%s ritira e ottiene %d\n", g[i].nome, valori[i]);
                    printf("%s ritira e ottiene %d\n", g[j].nome, valori[j]);
                }
            }
        }
    }

    // Ordina in ordine decrescente tramite bubble sort, serve a stabilire in modo
    // randomico l'ordine di gioco dei giocatori grazie al tiro del dado
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (valori[j] > valori[i]) {

                int tmp = valori[i];
                valori[i] = valori[j];
                valori[j] = tmp;

                Giocatore temp = g[i];
                g[i] = g[j];
                g[j] = temp;
            }
        }
    }

    printf("\n--- Ordine di gioco stabilito ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s (dado: %d)\n", i + 1, g[i].nome, valori[i]);
    }
}


// Funzione: muoviGiocatore, sposta il giocatore sul tabellone grazie al tiro del dado e segna la posizione

void muoviGiocatore(Giocatore *g, int passi) {
    for (int i = 0; i < passi; i++) {
        g->posizione = g->posizione->next;
    }
}

void eliminaGiocatore(Giocatore **g, int *n, int index) {

    // libera eventuali risorse del giocatore
    // (carte, effetti, ecc. se servono)

    for (int i = index; i < (*n) - 1; i++) {
        (*g)[i] = (*g)[i + 1];
    }

    (*n)--;

    *g = realloc(*g, sizeof(Giocatore) * (*n));

}


// Funzione: liberaGiocatori
void liberaGiocatori(Giocatore *g) {
    free(g);
}

