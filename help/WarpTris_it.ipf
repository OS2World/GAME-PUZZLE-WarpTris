.* Guida di WarpTris - Italiano
:userdoc.

:h1 res=001.Guida generale
:i1 id=Win.Finestre
:i1 id=HowTo.Come giocare a WarpTris
:i1 id=Menus.Menu
:font facename=Helv size=8x12.
Scegliere uno degli argomenti seguenti&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.Accordo di licenza:elink.
:li.:link reftype=hd res=017.Marchi:elink.
:li.:link reftype=hd res=007.Giocare a WarpTris:elink.
:li.:link reftype=hd res=008.Tasti di WarpTris:elink.
:li.:link reftype=hd res=002.Opzioni dei menu:elink.
:li.:link reftype=hd res=003.Finestra Gioco:elink.
:li.:link reftype=hd res=004.Finestra Punteggio:elink.
:li.:link reftype=hd res=005.Finestra Prossimo:elink.
:li.:link reftype=hd res=006.Finestra Record:elink.
:li.:link reftype=hd res=023.Segnalare errori:elink.
:li.:link reftype=hd res=009.Ringraziamenti:elink.
:eul.
:p.

:h1 res=023.Segnalare errori
:font facename=Helv size=8x12.
:p.
Se trovate errori in questo programma, segnalateli tramite la comunita OS2World
(https&colon.//www.os2world.com), con una descrizione dell'errore.
:p.
Grazie in anticipo.

:h1 res=002.Opzioni dei menu
:font facename=Helv size=8x12.
:p.
Scegliere un collegamento dall'elenco seguente&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Menu Gioco:elink.
:li.:link reftype=hd res=011.Menu Impulso:elink.
:li.:link reftype=hd res=012.Menu Suono:elink.
:li.:link reftype=hd res=013.Menu Opzioni:elink.
:li.:link reftype=hd res=014.Menu Finestre:elink.
:li.:link reftype=hd res=015.Menu Aiuto:elink.
:eul.
:p.

:h1 res=003.Finestra Gioco
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Gioco
E in questa finestra che si gioca davvero. I pezzi compaiono nel quadrato grigio al
centro e poi iniziano a cadere verso un lato a caso.
:p.
Quando un pezzo ricopre una parte del quadrato grigio centrale, la partita finisce.
:p.
Questa finestra ha anche un menu contestuale con le opzioni della barra dei menu che la riguardano.

:h1 res=004.Finestra Punteggio
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Punteggio
Non c'e molto da dire su questa finestra. Mostra il punteggio attuale.

:h1 res=005.Finestra Prossimo
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Prossimo
Questa finestra mostra il pezzo successivo e la direzione del suo prossimo impulso.
:p.
Se non volete questo aiuto, potete nasconderla con il suo pulsante di occultamento.

:h1 res=006.Finestra Record
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Record
In questa finestra il gioco conserva i dieci punteggi migliori e i nomi dei rispettivi giocatori.
:p.
Se volete, potete cancellarli tutti eliminando il file Hiscore.bin. La prossima volta che avviate
il gioco, verra creato un file dei record vuoto.

:h1 res=007.Giocare a WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Giocare a WarpTris
WarpTris e un tipo di Tetris piuttosto diverso (e originale). Invece di cadere dall'alto della finestra Gioco,
i pezzi compaiono al centro e poi iniziano a cadere verso un lato, a caso.
:p.
Questo comportamento ha una spiegazione pseudo-fisica&colon. immaginate di essere nello spazio, dove non c'e gravita. Se lasciate
andare qualcosa e gli date un impulso in una direzione, quella e la direzione in cui inizia a muoversi (o a cadere) e
continua a muoversi cosi, a meno che incontri qualcosa sulla sua strada. In WarpTris i pezzi compaiono al centro della
finestra Gioco, ricevono un impulso in una direzione casuale e iniziano subito a cadere in quella direzione (proprio come nello spazio).
:p.
Il pezzo puo cadere solo in quattro direzioni (alto, basso, sinistra e destra) e potete formare
righe sui quattro lati della finestra Gioco. Perdete quando un pezzo copre un quadretto dell'area grigia centrale.
:p.
Ci sono tre livelli di difficolta, che chiamo impulsi (ha piu senso). Differiscono per
la forza dell'impulso e quindi per la velocita con cui si muovono i pezzi.
:p.
Infine, quando formate una riga su un lato, viene valutata solo l'area che va da quel lato della finestra di gioco fino al
primo lato parallelo del quadrato grigio centrale, il che apre dei buchi sui lati adiacenti
della finestra Gioco. Per esempio, la figura seguente mostra quale area viene valutata se formate
una riga sul lato sinistro della finestra Gioco.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
Potete muovere il pezzo solo parallelamente al lato verso cui sta cadendo.
:ent.

:h1 res=008.Tasti di WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Tasti di WarpTris
I tasti validi per questo gioco sono&colon.
:parml compact tsize=20 break=none.
:pt.Spazio
:pd.Far cadere il pezzo
:pt.Tastierino Su o freccia su
:pd.Muovere in alto
:pt.Tastierino Giu o freccia giu
:pd.Muovere in basso
:pt.Tastierino Sinistra o freccia sinistra
:pd.Muovere a sinistra
:pt.Tastierino Destra o freccia destra
:pd.Muovere a destra
:pt.Tastierino 5 o Maiusc (entrambi)
:pd.Ruotare
:pt.P
:pd.Pausa / riprendi
:eparml.
:p.
Le scorciatoie seguenti funzionano in tutta la finestra di WarpTris&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.Nuova partita
:pt.Ctrl+P
:pd.Mettere in pausa / riprendere il gioco
:pt.Ctrl+Q
:pd.Terminare la partita in corso
:pt.Ctrl+X
:pd.Uscire da WarpTris
:pt.Ctrl+B
:pd.Sfondo Attivo si / no
:pt.Ctrl+F
:pd.Controlli Cornice si / no
:pt.Ctrl+1, 2, 3
:pd.Impulso Donkey, Formula 1, WARP!
:eparml.
:p.
Il gioco si ferma anche quando la finestra Gioco perde il focus, a meno che Sfondo Attivo sia attivato.
:nt.
Per usare i tasti del tastierino numerico deve essere attivo BLOC NUM.
:ent.

:h1 res=009.Ringraziamenti
:font facename=Helv size=8x12.
:p.
WarpTris e un gioco a 32 bit simile a Tetris per OS/2, scritto da Paulo Gago da Camara alle Azzorre, in Portogallo, nel 1996.
Ha creato questo gioco con lo scopo di imparare la programmazione PM.
:p.
Un ringraziamento speciale al suo ex insegnante di C/C++, il Dr. Gunther Funk, per l'idea originale, e al suo amico
Jorge Cipriano, per il sostegno morale e tecnico. E stato anche il collaudatore delle versioni Alfa, Beta e finale.
:p.
La versione per Open Watcom, con l'interfaccia in sei lingue, e stata preparata dalla comunita OS2World nel 2026.

:h1 res=010.Menu Gioco
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Gioco
:dl tsize=20.
:dt.:hp2.Nuovo:ehp2. (Ctrl+N)
:dd.Questa opzione avvia una nuova partita. Non e disponibile mentre una partita e in corso.
:dt.:hp2.Pausa Gioco:ehp2. (Ctrl+P)
:dd.Ferma il gioco. Sceglietela di nuovo per continuare.
:dt.:hp2.Termina Gioco:ehp2. (Ctrl+Q)
:dd.Ferma la partita in corso e mostra il punteggio. WarpTris resta aperto.
:dt.:hp2.Esci:ehp2. (Ctrl+X)
:dd.Esce subito da WarpTris.
:edl.

:h1 res=011.Menu Impulso
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impulso
Ci sono tre tipi di impulso, che corrispondono a tre velocita di gioco. Questo menu
rappresenta in realta il menu dei livelli.
:p.
L'impulso Donkey e il piu debole (il piu lento) e WARP! e il piu forte (il piu veloce).

:h1 res=012.Menu Suono
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Suono
Attiva o disattiva il suono.

:h1 res=013.Menu Opzioni
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Opzioni
:dl tsize=20.
:dt.:hp2.Proprieta:ehp2.
:dd.Mostra il blocco delle proprieta.
:dt.:hp2.Dettaglio:ehp2.
:dd.Alto mostra un'animazione fluida quando compare un nuovo pezzo, Medio e l'animazione originale
e Basso la disattiva.
:dt.:hp2.Lingua:ehp2.
:dd.Cambia la lingua dei menu, delle finestre, dei dialoghi e di questa guida. La scelta viene ricordata.
:dt.:hp2.Sfondo Attivo:ehp2. (Ctrl+B)
:dd.Se e attivato, il gioco continua mentre un'altra finestra ha il focus.
:dt.:hp2.Controlli Cornice:ehp2. (Ctrl+F)
:dd.Nasconde o mostra la barra del titolo e il menu della finestra di WarpTris. Usate di nuovo Ctrl+F per riaverli.
:dt.:hp2.Salva impostazioni all'uscita:ehp2.
:dd.Salva le impostazioni e le posizioni delle finestre in WarpTris.cfg all'uscita.
:edl.

:h1 res=014.Menu Finestre
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Finestre
:dl tsize=20.
:dt.:hp2.Record:ehp2.
:dd.Mostra o nasconde la finestra Record.
:dt.:hp2.Prossimo:ehp2.
:dd.Mostra o nasconde la finestra Prossimo.
:dt.:hp2.Punteggio:ehp2.
:dd.Mostra o nasconde la finestra Punteggio.
:dt.:hp2.Gioco:ehp2.
:dd.Mostra o nasconde la finestra Gioco.
:dt.:hp2.Ordina:ehp2.
:dd.Ripristina le posizioni predefinite delle finestre Gioco, Punteggio, Prossimo e Record.
:edl.

:h1 res=015.Menu Aiuto
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Aiuto
:dl tsize=20.
:dt.:hp2.Guida generale:ehp2.
:dd.Mostra la finestra della guida generale.
:dt.:hp2.Indice della guida:ehp2.
:dd.Mostra la finestra dell'indice della guida.
:dt.:hp2.Guida sulla guida:ehp2.
:dd.Mostra informazioni che spiegano come usare la guida.
:dt.:hp2.About:ehp2.
:dd.Mostra il dialogo About.
:edl.

:h1 res=016.Accordo di licenza
:font facename=Helv size=8x12.
.br
:hp4.Licenza di WarpTris.:ehp4.
:p.
WarpTris e software libero&colon. potete ridistribuirlo e/o modificarlo secondo i termini della GNU General Public License pubblicata dalla Free Software Foundation, nella versione 3 della Licenza o (a vostra scelta) in qualsiasi versione successiva.
:p.
Questo programma e distribuito nella speranza che sia utile, ma SENZA ALCUNA GARANZIA, nemmeno la garanzia implicita di COMMERCIABILITA o IDONEITA PER UN PARTICOLARE SCOPO. Consultate il file LICENSE.txt per il testo completo della licenza.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.Accordo di licenza

:h1 res=017.Marchi
:font facename=Helv size=8x12.
:i1.Marchi
:p.
I termini seguenti sono marchi di IBM Corporation negli Stati Uniti o in altri paesi&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Ogni altro marchio citato appartiene ai rispettivi proprietari.
:p.
Non e mia intenzione violare alcun diritto d'autore o marchio con questo programma.
:p.

:euserdoc.
