cmake_minimum_required(VERSION 4.1)
project(Monopoly_progetto__senza_bug_ C)

set(CMAKE_C_STANDARD 99)

add_executable(Monopoly_progetto__senza_bug_ main.c
        src/carte.c
        src/carte.h
        src/caselle.c
        src/caselle.h
        src/dadi.c
        src/dadi.h
        src/giocatore.c
        src/giocatore.h
        src/menu.c
        src/menu.h
        src/ordine.c
        src/ordine.h
        src/strutture.h
        src/tabellone.c
        src/tabellone.h
        src/turni.c
        src/turni.h)
