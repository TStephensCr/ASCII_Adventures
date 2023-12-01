# **Ascii Adventures**

#### *Progetto di programmazione a.s. 2022/2023*
#### *Dervishi Erik, Parazza Gaia, Stephens Thomas*

------------------------------------
## **DESCRIZIONE**
Ascii’ Advantures è un gioco platform in grafica ASCII, sviluppato su più livelli, a punteggio, dove il player viene controllato da tastiera.
Lo scopo del giocatore è non morire mai. Il gioco non ha una fine, quindi il player può continuare a giocare all’infinito finchè ha vite.  Durante il gioco si possono raccogliere monete e sparare ai nemici ( i colpi iniziali sono 10, quindi quando terminano non è più possibile sparare ma si possono comunque acquistare nel negozio).  Il player all’inizio, avrà un range di sparo molto corto. Aumentando i livelli, e di conseguenza i punti, il giocatore potrà decidere di aumentare la lunghezza dello sparo acquistandola nel negozio.

Il gioco è basato su 8 mappe predefinite e 3 livelli di difficoltà. Le mappe sono generate in modo randomico e per accedere alla difficoltà successiva è necessario che il giocatore superi le 8 mappe di livello inferiore.
Le prime 8 mappe di difficoltà base presentano un solo nemico, che non è in grado di sparare, ma di respingere il player in caso di contatto, quindi crea danno quando i due si scontrano, diminuendo così la vita.
Il livello intermedio presenta 3 nemici: 2 normali, che sono in grado di sparare, e un terzo nemico F, ovvero follow, che insegue il player e crea danno quando i due si toccano, diminuendo cosi la vita. La difficoltà qua aumenta, perché il player, oltre a non farsi raggiungere dal follow, deve schivare i colpi dei 2 nemici.
Il livello avanzato presenta 4 nemici: oltre al follow, sono presenti 3 nemici in grado di sparare. 
Dopo aver terminato le mappe del livello più difficile, il gioco rinizia da capo, ma i danni che prende il player vengono aumentati, quindi è più difficile sopravvivere.

In ogni mappa, in alto a destra, sono visualizzate le caratteristiche del player ovvero la vita, le monete che ha raccolto, i colpi rimanenti, quanti punti ha accumulato e, infine, in che direzione è posizionato il player (funzionalità che abbiamo deciso di aggiungere siccome il simbolo del giocatore non ci consente di stabilire se siamo puntati verso destra o verso sinistra. Questa funzionalità può essere utile quando è necessario sparare: per evitare di perdere colpi inutilmente, basta controllare l’ultima direzione del player per sparare nella direzione desiderata). 

Il giocatore è in grado, anche durante il gioco, di entrare nella pagina del negozio e acquistare, tramite i punti e le monete raccolte durante il gioco.  Col le monete è possibile acquistare la vita, i colpi, lo scudo e lo skip mappa. 
Lo scudo consente di
Lo skip mappa , invece, consente di passare alla mappa successiva.
Avere una grande quantità di punti significa che il player ha superato un numero di livelli sufficienti per aumentare il range del colpo.


## **ISTRUZIONI**
- freccia destra o tasto d: il player procede in direzione destra con salto;
- freccia sinistra o tasto a: il player procede in direzione sinistra con salto;
- freccia su o tasto w: il player salta nella direzione in cui sta guardando;
- freccia giu: il player spara;
- barra spaziatrice: il player salta in verticale
- le freccie su e giu consentono anche di navigare all'interno del menu principale e del menu del negozio;
- tasto invio: consente di selezionare la voce desiderata del menu principale e del menu del negozio;
- tasto e: consente di posizionare il player con la direzione verso destra, senza saltare;
- tasto q: consente di posizionare il player con la direzione verso sinistra, senza saltare;
- esc: uscire dal gioco e tornare a navigare sul menu principale salvando su file lo stato corrente del gioco;



git# P.project2023
Progetto di programmazione 2023 UniBO

inclusion tree : https://docs.google.com/drawings/d/1UUb0oqGbRCR2WfaC-HINHZWo360EI35IN0vddv0dTWE/edit

Collisioni:
-player/sparo ->elimina il player e se ha ancora vite lo mette nello spawn altrimenti viene una scritta game over 
-soldo/sparo  ->non succede nulla
-palyer/soldo ->se il soldo è una casella vicino al player lo prende
-bot/player   ->se il bot tocca il player lo scaraventa via
-nemico/soldo ->lo attraversa


ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 
commit -a -m 'messaggio'


IDEE CONTINUO:(cio che succede dopo mappa 5 livello 2)
-incrementa la velocità dei bot
-cap sulla vita massima
-cap sui proiettili?

idea : danni moltiplicati per il livello in cui sei. cosi' all'aumentare dei livelli e' piu' tosta

Erik: rimangono da sistemare --> events, collision, logic, game

Manca ciclare il gioco alla fine dell'ultimo livello, ancora non abbiamo deciso cosa farci.


Modifiche:
-aggiustato il salvataggio della difficolta
-implementato array:
    -salviamo l'array e la posizione corrente nell'array
    -initMappa non prende piu come argomento la mappa
    -aggiustato il cambio mappa in base a sti cambiamenti
    -tanti altri megabordelloni
-fixato la funzione scramble, non scramblava
se dovete cambiare qualcosa riguardo curmap, mapcounter, maparray o le funzioni di cambio mappa chiedetemi e vi spiego tutto