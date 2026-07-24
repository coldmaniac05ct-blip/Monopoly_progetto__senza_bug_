cmake_minimum_required(VERSION 4.1)
project(Monopoly_progetto__senza_bug_ C)

set(CMAKE_C_STANDARD 99)

add_executable(Monopoly_progetto__senza_bug_ main.c
        src/carta.c
        src/carta.h
        src/casella.c
        src/casella.h
        src/dado.c
        src/dado.h
        src/giocatore.c
        src/giocatore.h
        src/menu.c
        src/menu.h
        src/ordine.c
        src/ordine.h
        src/tabellone.c
        src/tabellone.h
        src/turno.c
        src/turno.h
        src/effetto.c
        src/effetto.h
        src/macro.h
        src/partita.c
        src/partita.h
)
