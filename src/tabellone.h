//
// Created by Administrator on 10/05/2026.
//

#ifndef MONOPOLY_PROGETTO__SENZA_BUG__TABELLONE_H
#define MONOPOLY_PROGETTO__SENZA_BUG__TABELLONE_H

#include <stdio.h>
#include <stdlib.h>
#include "strutture.h"
#include "caselle.h"
#include "macro.h"

#define NOME_FILE "tabellone.txt"

//ho definito cosa fanno le subroutine nel file.c

Casella* caricaTabellone();
void stampaTabellone(Casella *start);

#endif //MONOPOLY_PROGETTO__SENZA_BUG__TABELLONE_H

