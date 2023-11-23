# **Ascii Adventures**

#### *Progetto di programmazione a.s. 2022/2023*
#### *Dervishi Erik, Parazza Gaia, Stephens Thomas*

------------------------------------
## **DESCRIZIONE**

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