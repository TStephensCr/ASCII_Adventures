git# P.project2023
Progetto di programmazione 2023 UniBO

NOTE:
-nelle mappe ci sono P per power-up, che dovranno essere diversi dai power-up che si comprano nello shop.

Collisioni:
-player/sparo ->elimina il player e se ha ancora vite lo mette nello spawn altrimenti viene una scritta game over 
-soldo/sparo  ->non succede nulla
-palyer/soldo ->se il soldo è una casella vicino al player lo prende
-bot/player   ->se il bot tocca il player lo scaraventa via
-nemico/soldo ->lo attraversa


ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 
commit -a -m 'messaggio'

problemi:



IDEE CONTINUO:(cio che succede dopo mappa 5 livello 2)
-incrementa la velocità dei bot
-cap sulla vita massima
-cap sui proiettili?


------------------------------------
Roadmap di gaia per il negozio
-implementare il costruttore.il costruttore prende 1)la finastra di gioco 2)il puntatore delle informazioni del player(vita,monete ecc..).Il puntatore si chiama Infoplayer,c'è una funzione che te lo ritorna che si trova il logic.public riga 34,questa funzione andrà richiamata quando apro il negozio

-funzione che ti permette di creare un menu a scelta(ad esempio) sotto alle informazione del player.Dovrai eliminare ciò che è al momento nello schermo e ci sono delle funzioni tipo int werase(WINDOW *win); che ti permettono di farlo.

dopodiche ti serviranno le funzioni che si avviano quando il giocatore sceglie di fare una cosa(ad esempio comprare vite)

-tutte le funzioni fanno dichiarate nel hpp e poi scritte nel cpp.le funzioni che ti servono solo per fare il negozio le metti in private, mentre le funzioni che dovrai richiamare in progetto.cpp le metti in public


-Infoplayer è un puntatore alla struttura dati player che si trova in Player.hpp

NEGOZIO:
La schermata del negozio è in negozio. cpp (commentata al momento). Gestisco la scelta delle cose da comprare tramite un menu come quello nella home, e in base a quello che il giocatore sceglie, richiamo le funzioni dove controllo se si riescono a comprare le quantità scelte.
in alto a destra voglio inserire i dati del player ( quante vite ha, quante monete .. ) che si aggiornano ogni volta che compor qualcosa


COSA CI FACCIAMO CON I PUNTI?   discussione

cosa fare quando chiudo il negozio

COSA MANCA DA FARE?
1)negozio(comprare proiettili e powerup)
2)controllare ovunque che l'aggiunta di mappe non abbia creato errori
3)aggiungere entita a mappe nuove
5)power up
    -armatura che assorbe un colpo(quindi non fa prendere danno al player per un colpo)
    -si puo' avanzare di una mappa con le monete
    -aumentare il range del proiettile
    -comprare extra vita, vista come barre viola nella barra della vita
6)salvare queue
7)aggiungere tasti per cambiare direzione senza muoversi
8)mettere nelle statistiche la dirzione in cui il player sta guardando