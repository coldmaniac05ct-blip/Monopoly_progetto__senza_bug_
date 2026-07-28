//Studente:Elisa Alessandra Cataldo (e.cataldo@studenti.unica.it)
//Matricola:60/84/00112
//Tipo Progetto:BASE
//Username Github:Cold Maniac
//Github link: https://github.com/coldmaniac05ct-blip/Monopoly_progetto__senza_bug_
//Necessità:NESSUNA

DESCRIZIONE GENERALE:
Questo progetto implementa una versione testuale del Monopoly, completamente scritta in C e organizzata in moduli.
Il gioco permette di:

-avviare una nuova partita
-caricare una partita precedente
-tirare due dadi per ogni giocatore
-muoversi automaticamente sul tabellone (lista circolare di 40 caselle)
-pescare carte “bug” e applicarne gli effetti
-gestire la BATCAVERNA (turni da scontare o uscita tramite dadi/carta)
-acquistare proprietà usando i CFU
-consultare tabellone e stato dei giocatori
-salvare la partita su file binario

Il progetto è stato iniziato a gennaio 2026.
Una riorganizzazione delle cartelle ha corrotto la CMakeList originale, portando alla creazione della versione Monopoly_progetto_senzabug.

PROBLEMI AFFRONTATI E RISOLTI:
Durante lo sviluppo sono stati risolti numerosi errori:

-allocazioni di memoria errate
-include ricorsivi tra file .c e .h
-caricamento del mazzo non funzionante
-tabellone non caricato correttamente
-difficoltà nella lettura delle enumerazioni (stampava numeri invece che stringhe)
-mancato aggiornamento dei file di salvataggio
-errori nelle printf, tipi mancanti, inizializzazioni incomplete
-menù iniziale che crashava
-opzione 2 che non caricava nulla

La strategia usata è stata divide et impera: scomporre ogni problema in parti più piccole e risolverle una alla volta.

STRUTTURA DEL PROGETTO:
Il progetto è suddiviso in cartelle e moduli.
Ogni file .c ha il suo corrispondente .h che contiene:

-strutture
-enumerazioni
-prototipi delle funzioni

Questo evita ricorsioni e crash dovuti agli include.

MODULI PRINCIPALI:
-Carta:
Carica il mazzo da mazzo.txt.
Il file contiene 7 blocchi per ogni carta (ID, tipo, nome, descrizione, tipo ripetuto, numero effetti, effetti).
La funzione:

-legge i dati nell’ordine corretto
-crea dinamicamente ogni carta
-collega le carte in una lista collegata semplice
-restituisce la testa del mazzo

-Casella:
Crea una singola casella del tabellone e la collega alle altre formando una lista circolare.
Struttura:
struct casella {
    char nome[LUNGHEZZA_STRINGA];
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    Giocatore *proprietario;
    struct casella *next;
    struct casella *prev;
};

Serve per gestire:

-tipo e colore
-costo
-sedie e scrivanie
-proprietario
-movimento sul tabellone tramite next e prev

-Dado:
Genera numeri casuali tra 1 e 6 e stabilisce l’ordine dei turni.
In caso di pareggio, ritira i dadi finché non si ottiene uno spareggio.

-Effetto:
Applica gli effetti delle carte bug pescate dal mazzo.
Dipende dal corretto funzionamento di Carta.c.

-Giocatore:
Gestisce:

-nome
-CFU
-turni saltati
-posizione sul tabellone
-carte possedute
-carte ESCI
-turni in BATCAVERNA
-effetti disponibili
-ultima carta pescata
-numero di aule/mense possedute

Struttura:
typedef struct {
    char nome[LUNGHEZZA_STRINGA];
    int cfu;
    bool saltaTurno;
    int nuovo_turno;
    Casella *posizione;
    Carta *carte;
    int segna_posto;
    Carta *carte_esci;
    int turni_batcaverna;
    Effetto* effettiDisponibili;
    int numEffettiDisponibili;
    Carta *ultimaCartaPescata;
    int numero_aule_mense;
} Giocatore;

La funzione liberaGiocatori libera la memoria dinamica dell’array creato da creaGiocatori.

-Menu:
Gestisce il menù iniziale del gioco:

-nuova partita
-carica partita
-esci
-Controlla la validità della scelta e reindirizza l’utente.

-Ordine:
Stabilisce l’ordine dei giocatori tramite tiro dei dadi, gestendo eventuali pareggi.

-Partita:
Contiene il 90% della logica di gioco:

-gestione turni
-movimento
-effetti
-acquisti
-ciclo principale
-ricerca della BATCAVERNA
-applicazione delle carte bug

-Salvataggio:
Gestisce la scrittura e lettura del file savegame.sav.
In caso di errore stampa:
"Errore: impossibile creare savegame.sav"

-Tabellone:
Carica le 40 caselle da tabellone.txt e le collega in una lista circolare.
Stampa nome, tipo, colore e costo.

-Main:
Coordina tutto:

-include dei moduli
-menù iniziale
-creazione giocatori
-aricamento tabellone
-avvio partita
-salvataggio finale
-Inizializza la randomizzazione con srand(time(NULL)).

-File richiesti:
tabellone.txt
mazzo.txt
savegame.sav

Autrice:
Elisa Alessandra Cataldo  
Email: e.cataldo@studenti.unica.it
GitHub: Cold Maniac
Progetto: BASE – PR1 Edition
