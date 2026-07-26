//
// Created by Administrator on 14/05/2026.
//

//ATTENZIONE:le subroutines sono riportate nei file header appositi

#include "effetto.h"
#include <stdio.h>


//QUA TECNICAMENTE NON CI VA NULLA-RICONTROLLARE LE SLIDES APPENA PUOI

int menuEffetti(Effetto *effetti, int numero_effetti) {

    printf("\n--- Scegli un'azione disponibile ---\n");

    for (int i = 0; i < numero_effetti; i++) {

        Effetto e = effetti[i];

        printf("%d) ", i + 1);

        switch (e.azione) {
        case PAGA_QUALCOSA: printf("PAGA_QUALCOSA (%d CFU)\n", e.quantita); break;
        case PAGA_TUTTO:    printf("PAGA_TUTTO\n"); break;
        case PRENDI:        printf("PRENDI (%d CFU)\n", e.quantita); break;
        case SALTA_TURNO:   printf("SALTA_TURNO\n"); break;
        case NUOVO_TURNO:   printf("NUOVO_TURNO\n"); break;
        case ESCI:          printf("ESCI dalla BatCaverna\n"); break;
        case VAI_INDIETRO:  printf("VAI_INDIETRO (%d caselle)\n", e.quantita); break;
        case VAI_AVANTI:    printf("VAI_AVANTI (%d caselle)\n", e.quantita); break;
        case REGALA:        printf("REGALA (%d aule)\n", e.quantita); break;
        default:            printf("Effetto sconosciuto\n"); break;
        }
    }

    printf("Scelta: ");
    int scelta;
    scanf("%d", &scelta);

    return scelta - 1; // ritorno indice 0-based
}

