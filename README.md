#Progetto d'esame

Progetto d'esame per il corso di *Sistemi di calcolo paralleli e distribuiti*, autore Luca Rickler.

---

La cartella `src/Unit Tests` contiene i test dei singoli moduli e delle loro funzionalità. Nello specifico:

- Il test della coda FIFO a due lock (obbiettivo make `FIFOQTest`)
- Il test della classe `Action` (obbiettivo make `ActionTest`)
- Il test della classe `Runtime` e del ciclo di esecuzione (obbiettivo make `RuntimeTest`)
- Il test della classe `Message` e della messaggistica (obbiettivo make `MessageTest`)

---

La cartella `Test  Problems` contiene i problemi di test usati per valutare la scalabilità del codice.

- Il test di scaling in base al numero di thread ed alla pesantezza del carico (cartella `Scaling - No Comms`)
- Il test di scaling delle comunicazioni in base al numero di thread (cartella `Scaling - Comms`)

Entrambi i test richiedono come argomento il numero di thread con cui operare.
