git# P.project2023
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
-controllo per fare in modo che InitEntities viene chiamato solo per partita nuova, e di conseguenza un nuovo InitEntities che prende i dati dal salvataggio
-salvataggio di stato
-collisioni livello negozio
-diversi tipi di nemici(magari alcuni che ti mandano in alto e basta)
-decidere possibilità per cosa puo succedere alla fine di mappa 5 livello 2
-mappa con i colori

ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 
commit -a -m 'messaggio'

problemi:
-quando premi esc il titolo ci mette un secondo ad apparire, ma se premi una freccia per muovere il menu diventa instantaneo
-ogni tanto il respawn si bugga e il player spawna sotto la mappa

PROBLEMONE DEI PROBLEMONI:
    1)ho perso tipo 2 ore della mia vita per sto cazzo di problema
    HANDLEBOT va prima di managecollison per far si che le collsioni tra player e bot siano giuste!
    pero' c'e' il problema che quando i bot sparano si muovo nella stessa direzione dello sparo e quindi 
    si killano da soli.
    2)rimetti KillEntity in collisione per codice + leggibile