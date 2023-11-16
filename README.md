git# P.project2023
Progetto di programmazione 2023 UniBO

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


------------------------------------
Roadmap di gaia per il negozio
-implementare il costruttore.il costruttore prende 1)la finastra di gioco 2)il puntatore delle informazioni del player(vita,monete ecc..).Il puntatore si chiama Infoplayer,c'è una funzione che te lo ritorna che si trova il logic.public riga 34,questa funzione andrà richiamata quando apro il negozio

-funzione che ti permette di creare un menu a scelta(ad esempio) sotto alle informazione del player.Dovrai eliminare ciò che è al momento nello schermo e ci sono delle funzioni tipo int werase(WINDOW *win); che ti permettono di farlo.

dopodiche ti serviranno le funzioni che si avviano quando il giocatore sceglie di fare una cosa(ad esempio comprare vite)

-tutte le funzioni fanno dichiarate nel hpp e poi scritte nel cpp.le funzioni che ti servono solo per fare il negozio le metti in private, mentre le funzioni che dovrai richiamare in progetto.cpp le metti in public


-Infoplayer è un puntatore alla struttura dati player che si trova in Player.hpp


COSA CI FACCIAMO CON I PUNTI?   discussione

COSA MANCA DA FARE?
1)negozio(comprare skipmappa e range proiettili)
12)ciclare il gioco quando si arriva a ultima mappa ultimo livello
14)i proiettili alcune volte si buggano e vanno a -1 (wtf?)


