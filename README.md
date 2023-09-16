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
-fixare i bug di cambio livello(inventarsi qualcosa per se si arriva alla fine di tutto il gioco)
-da fixare i problemi causati dall'uscita e rientro nel gioco
-controllo per fare in modo che InitEntities viene chiamato solo per partita nuova, e di conseguenza un nuovo InitEntities che prende i dati dal salvataggio
-salvataggio di stato(da definire quando viene eseguito)
-ideare e implementare powerup
-collisioni livello negozio
-implementare un esc per tornare al menu, cosi da poter accedere al negozio, e poi viceversa
-fare dei punti come scritto nella consegna(10 punti per soldo e 20 per nemico uscciso?)
-diversi tipi di nemici(magari alcuni che ti mandano in alto e basta)


ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 

problemi:
-il numero di soldi e di proiettili si resetta quando alzi di livello
-i soldi che hai preso nel primo livello di difficolta non sono prendibili nelle difficolta piu alte e hanno collisioni strane