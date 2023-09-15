# P.project2023
Progetto di programmazione 2023 UniBO

Erik
-logica gioco
-collisioni
-player  X
-npc

Thomas
-mappa
-menu  X
-negozio
-potenziamenti
-salvataggio di stato


NOTE:
-nelle mappe ci sono P per power-up, che dovranno essere diversi dai power-up che si comprano nello shop.

Collisioni:
-player/sparo ->elimina il player e se ha ancora vite lo mette nello spawn altrimenti viene una scritta game over 
-soldo/sparo  ->non succede nulla
-palyer/soldo ->se il soldo è una casella vicino al player lo prende
-bot/player   ->se il bot tocca il player lo scaraventa via
-nemico/soldo ->lo attraversa



TO DO:
-cambia mappa(include anche l'inserimento del lovello negozio)(inventarsi qualcosa per se si arriva alla fine di tutto il gioco)
-salvataggio di stato per ogni mappa gia visitata quando si procede a una nuova, e aggiungere lista di liste per quali entities ci sono in ogni mappa per poterle ristampare
-aggiungere healthpack(la P) FATTO
-ideare e implementare powerup
-aggiungere statistiche player in alto a destra(o fuori dalla window se non c'è spazio) FATTO
-aggiungere danno per la caduta nei fossi FATTO
-collisioni livello negozio
-aggiungere aesthetic tipo scritta titolo/game over
-fare dei punti come scritto nella consegna 
-diversi tipi di nemici(magari alcuni che ti mandano in alto e basta)

ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 

