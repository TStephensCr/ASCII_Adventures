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



TO DO:
-livello negozio
-powerup
-decidere possibilità per cosa puo succedere alla fine di mappa 5 livello 2
-mappa con i colori
-il formato in cui vengono salvati i dati si potrebbe ottimizzare ma cambierebbe veramente poco, fare se si ha voglia

ogni volta che si scrive codice bisogna per prima cosa fare : [git pull origin main] e quando si è finito di scrivere codice bisogna fare : [git push origin main] altrimenti bordello 
commit -a -m 'messaggio'

problemi:
-(difficile da replicare)se un nemico ti colpisce e spara allo stesso tempo diventi invisibile?(metti sulla quinta casella di una piattaforma partendo da sinistra, cosi ti spara e colpisce allo stesso tempo)
-non funziona il cambio mappa al contrario
-nel livello 5 non si riesce a fare l'ultimo salto per via degli stats