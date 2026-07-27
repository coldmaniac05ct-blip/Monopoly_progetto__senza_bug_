//Studente:Elisa Alessandra Cataldo (e.cataldo@studenti.unica.it)
//Matricola:60/84/00112
//Tipo Progetto:BASE
//Username Github:Cold Maniac
//Github link: https://github.com/coldmaniac05ct-blip/Monopoly_progetto__senza_bug_
//Necessità:NESSUNA

Il progetto di Monopoly-PR1 edition è un progetto studentesco ed universitario basato sul gioco tradizionale di monopoly, scritto interamente da un singolo studente per versione.
Il mio monopoly permette di:
-Giocare una nuova partita
-Giocare una partita precedente
-Tirare 2 dadi a testa
-Spostarsi in modo automatico sul tabellone
-Pescare eventuali carte bug e ricevere effetti in base alle carte pescate
-Finire in batcaverna e provare ad uscirne
-Usare i cfu per comprare proprietà:caselle, aule, mense, scrivanie e cattedre
-consultare più volte il tabellone di gioco
-consultare i dati di tutti i giocatori aggiornati in base alle azioni fatte

Questo progetto è stato iniziato a Gennaio del 2026, purtroppo però circa 2 mesi più tardi nel creare e spostare file il
file iniziale della Cmake list è andato in crash per via di uno spostamento di cartelle, errore mio nel cercare di fare ordine.
Quindi ho cercato di salvare il salvabile e l'ho caricato su Monopoly_progetto_senzabug, si chiama senza bug perchè quello inizale era crashato.
Ho scoperto solo di recente che andassero fatti dei commit grazie a delle mie colleghe che mi hanno segnalato quanto fosse importante, per questo sono così pochi però dettagliati.
Nel creare questo progetto ho riscontrato vari errori durante la scrittura, motivi per cui non partiva fin dall'inizio:
-Errori nella locazione di memoria
-Errori negli include secondo i quali il file entrava in loop mostrando errori di ricorsione tra le varie cartelle (file c ed header)
-Non caricava il mazzo
-Non caricava correttamente il tabellone
-Ha fatto una fatica estrema a leggere i tipi nelle strutture enumerative per mancanza di array dinamici che ne consentissero la lettura a schermo, stampando numeri anzichè lettere nonostante il tipo stringa
-Non aggiornava i file quando si comprava una proprietà
-Ci sono stati anche errori di distrazione nelle printf, tipi mancati, inizializzavo 4 tipi anzichè 5, mi ero persino dimenticata di scrivere il main e infatti non partiva
-Il menù crashava
-l'opzione 2 non caricava nulla neanche il messaggio di errore
Come ho risolto? ho usato il metodo divide et impera, quindi ho preso i problemi più grossi e li ho spezzettati in problemi più piccoli chiedendomi sempre perchè e come risolvere,
è successo più volte con problemi nella ricorsione dei file che il programma desse errori in blu quindi li ho presi cartella per cartella, ho concellato tutti gli include e li ho riscritti a mano
perchè il mio processore leggeva per ordine Casella->Giocatore->Carta->Effetto, quindi logicamente Carta ad esempio non poteva contenere casella perchè casella conteneva a sua volta carta, però li ho risolti tutti
ho scritto su carta ogni processo logico e ne sono venuta a capo. Però ora basta errori, passiamo al gioco e alla sua struttura.

Il mio progetto è diviso in più cartelle, le quali mi consentono di capire e di tenere conto di dove ho posizionato i file, le subrouitne di ogni file c sono riscirtte in ogni file h, quindi ad esempio le
sbroutine di carta.c sono riscritte in carta.h così che ogni file possa accedervi evitando crash per errori di ricorsione. 
Il main si occupa di stampare a schermo alcune cose, ma diciamo che il cuore del progetto sono menu.c e .h e partita.c e .h, entrambi i file gestiscono 2 menù
però sono 2 menù diversi e collegati tra loro, menu.c e .h si occupa del menù iniziale di gioco dunque, il menù che si vede ad inzio partita prima ancora che il gioco abbia
inzio, stampa a schermo le varie opzioni e ti chiede cosa vuoi fare tramite uno switch case, invece partita.c e .h pensa alle funzioni di gioco,
cosa vuoi fare durante la partita, i tiri, cosa vuoi comprare, il caricamento di eventuali dati e un eventuale salvataggio extra a chiusura gioco tramite il tasto 0.

Eventuali dubbi? In ogni file ho riportato una descrizione di cosa fa il file + di cosa si occupano le subrouine, spezzando in ogni parte alcune cose che 
potrebbero risultare strane e spiegando perchè le faccio e cosa fanno. Ho cercato di evitare di usare magic numers quindi le macro sono definite in macro.h.
Ogni file.c contiene un include che lo rimanda al suo corrispettivo file.h.

IMPORTANTE:
LUNGHEZZA_STRINGA sono i 31 caratteri utili per caricare il nome di 
qualsisi cosa, giocatore, casella, carta etc etc, quindi lo troverete scritto in varie parti del progetto

Abbreviazioni:
c -> carte o casella (c'è scritto nei file quale delle 2 è)
e -> effetto
g -> giocatore
n -> numero

Strutture + informazioni (alcune delle cose scritte qui sono state scritte anche nei file per poterle individuare più facilmente):
Carta.c:
-questa funzione si occupa di caricare il mazzo di carte dal file mazzo.txt.
il file è stato fornito dall'università e NON usa i ';', quindi non posso usare fscanf con formati complessi.
devo leggere il file riga per riga rispettando esattamente la struttura che mi hanno dato.
ogni carta nel file è composta da 7 blocchi:
 1) ID della carta (intero)
 2) tipo della carta (intero)
 3) nome della carta (stringa su una riga)
 4) descrizione della carta (stringa su una riga)
 5) tipo della carta (di nuovo, intero) – il file lo ripete, quindi lo rileggo
 6) numero di effetti (intero)
 7) effetti: ogni effetto è composto da 3 interi (azione, quantità, tipoCasella)
   scritti sulla stessa riga separati da spazi

la funzione deve:
 - leggere tutti questi dati nell’ordine corretto
 - creare dinamicamente una struct Carta per ogni carta
 - collegare tutte le carte in una lista collegata semplice (head → next → next → ...)
 - ritornare la testa del mazzo

Carta.h:
-Contiene le strutture tipoCarta e Carta, entrambe con le specifiche indicate nel file delle specifiche + subroutine del file .c
diciamo che fa da tramite alle altre cartelle e agli altri file per trovare i dati

Casella.c:
-Questa funzione si occupa di creare una singola casella del tabellone del Monopoly.
ogni casella deve avere un nome, un tipo, un colore e un costo, quindi la funzione riceve questi parametri
e li inserisce dentro la struct Casella che poi verrà collegata alle altre caselle formando una lista circolare.
uso malloc per creare dinamicamente la casella, così posso costruire il tabellone in modo flessibile.

Casella.h:
-Contiene coloreCasella e struct casella + le subroutine di Casella.c
Potreste avere eventuali dubbi quindi spiego cos'è struct casella.
è strutturata come:
struct casella{
    char nome[LUNGHEZZA_STRINGA];//evito di usare magic numbers
    TipoCasella tipo;
    ColoreCasella colore;
    int costo;
    int sedie;
    bool scrivania;
    Giocatore *proprietario;
    struct casella *next;
    struct casella *prev;
};
Ma a che serve? Questa struttura aiuta a definire:tipo,colore,costo,sedie,scrivanie,proprietari etc etc
-LUNGHEZZA_STRINGA:è una macro da 32 caratteri, 31 caratteri utili per scrivere il nome della casella, quindi da 0 a 31, per cui se si vede scritto %31 
da qualche parte è per fare sì che il compilatore legga un massimo di 32 caratteri
-TipoCasella tipo: si occupa di scrivere il tipo della casella e fa si che possa essere riutilizzato in altri file, prende le informazioni dalla struttura enumerativa di TipoCasella e 
le applica grazie al file tabellone.txt dove le caselle vengono definite in modo enumerativo tramite ad esempio 0, 1, 2 etc etc, tanti numeri quanti quelli dei tipi.
-ColoreCasella colore:funziona in modo uguale al tipo però prende i dati da ColoreCasella e usa casella per chiamare in altri file il colore giusto in base alla struttura 
enumerativa, tanti numeri quanti i colori della struttura
-int costo:è un intero perchè i cfu sono un numero intero quindi anche il costo dovrà esserlo
-int sedie:non posso usare un float perchè è impossibile avere un numero come 1,2 sedie, non avrebbe senso matematico o logico, quindi intero
-bool scrivania:sto usando un booleano perchè implica 2 condizioni, true o false, quindi puoi avere scrivanie oppure no, in base a quello il programma agisce per registrare eventuali acquisti
-Giocatore *proprietario:è un puntatore, viene utilizzato per individuare chi è il proprietario di una casella nel momento in cui viene acquistata perchè il gioco può registrare da 2 a 4 giocatori per partita
-struct casella *next:serve a capire che caselle viene dopo, infatti next sta per prossimo, però next viene anche utilizzato 
per capire altre cose, ad esempio di quante caselle si sposta ilg iocatore o su che casella si trova dato che le caselle sono scritte in ordine
-struct casella *prev:prev sta per previous cioè ciò che viene prima, è utile per individuare le caselle ma anche in altre situazioni, ad esempio se la carta bug dice di tornare 
indietro di un tot di caselle allora mi è utile per capire su che casella sono e tornare davvero indietro sul tabellone

dado.c:
-In questo caso non ho scritto troppo nel file però posso spiegare ache serve, in pratica si occupa di tenere conto del tiro dei dadi e generare
un numero randomico tra 1 e 6 oltre che stabilire in che ordine tireranno il dado i giocatori, nel mometno in cui si verifichi un pareggio allora i 2 dai vengono ritirati finchè non si arriva in una situazione di spareggio,
successivamente il compilatore leggerà in ordine decrescente i turni, inizia il giocatore che ha tirato il numero più alto e si scorre fino a quello col numero più basso.
Quindi se a tira 5, b tira 2 e c tira 3, inizierà a poi c e poi b, 5,3,2.
I dadi possono essere tirati solo una volta per turno, invece le opzioni di menù possono essere consultate più volte in un turno.

dado.h:
-salva le mie subroutine e le rende utilizzabili per la partita e altri file

effetto.c:
-Salva tutti gli effetti disponibili per le carte bug, il giocatore non può scegliere cosa fare però questi effetti sono collegati a mazzo.txt, quindi per fare funzionare questo è necessario che carta.h e .c
funzionino correttamente e poi siano in grado di ricollegarsi a partita.h e .c (soprattutto .c), successivamente dopo aver letto la carta bug che è uscita applica eventuali effetti

effetto.h:
-contiene TipoCasella ed Azione + subroutine, stesso motivo delle altre strutture di tipo .h serve per fare ricorsione alle strutture e alla subroutine

giocatore.c:
-

giocatore.h:
-

macro.h:
-qui non c'è molto da spiegare, contiene le macro utilizzate in ogni file e le rende utili

menu.c:
-

menu.h:
-

ordine.c:
-

ordine.h:
-

partita.c:
-

partita.h:
-

salvataggio.c:
-

salvataggio.h:
-

tabellone.c:
-

tabellone.h:
-

turno.c:
-

turno.h:
-

main.c:
-

//continuerò domani, i file non scritti sono già stati scritti nel progetto e testati.
