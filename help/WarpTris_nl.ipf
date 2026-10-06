.* WarpTris Help - Nederlands
:userdoc.

:h1 res=001.Algemene Help
:i1 id=Win.Vensters
:i1 id=HowTo.WarpTris spelen
:i1 id=Menus.Menus
:font facename=Helv size=8x12.
Kies een van de onderstaande onderwerpen&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.Licentieovereenkomst:elink.
:li.:link reftype=hd res=017.Handelsmerken:elink.
:li.:link reftype=hd res=007.WarpTris spelen:elink.
:li.:link reftype=hd res=008.WarpTris toetsen:elink.
:li.:link reftype=hd res=002.Menu-opties:elink.
:li.:link reftype=hd res=003.Spelvenster:elink.
:li.:link reftype=hd res=004.Scorevenster:elink.
:li.:link reftype=hd res=005.Volgende-venster:elink.
:li.:link reftype=hd res=006.Hoogste Scores-venster:elink.
:li.:link reftype=hd res=023.Fouten melden:elink.
:li.:link reftype=hd res=009.Dankwoord:elink.
:eul.
:p.

:h1 res=023.Fouten melden
:font facename=Helv size=8x12.
:p.
Als u fouten in dit programma vindt, meld ze dan via de OS2World-gemeenschap
(https&colon.//www.os2world.com), met een beschrijving van de fout.
:p.
Alvast bedankt.

:h1 res=002.Menu-opties
:font facename=Helv size=8x12.
:p.
Kies een verwijzing uit de onderstaande lijst&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Menu Spel:elink.
:li.:link reftype=hd res=011.Menu Impuls:elink.
:li.:link reftype=hd res=012.Menu Geluid:elink.
:li.:link reftype=hd res=013.Menu Opties:elink.
:li.:link reftype=hd res=014.Menu Vensters:elink.
:li.:link reftype=hd res=015.Menu Help:elink.
:eul.
:p.

:h1 res=003.Spelvenster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Spel
In dit venster speelt u het spel. De stukken verschijnen in het grijze vierkant in het
midden en beginnen dan willekeurig naar een kant te vallen.
:p.
Wanneer een stuk een deel van het grijze vierkant in het midden bedekt, is het spel afgelopen.
:p.
Dit venster heeft ook een contextmenu met de opties van de menubalk die erop van invloed zijn.

:h1 res=004.Scorevenster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Score
Er valt niet veel te zeggen over dit venster. Het toont uw huidige score.

:h1 res=005.Volgende-venster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Volgende
Dit venster toont het volgende stuk en de richting van de volgende impuls.
:p.
Als u deze hulp niet wilt, kunt u het venster verbergen met de verbergknop.

:h1 res=006.Hoogste Scores-venster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Hoogste Scores
In dit venster bewaart het spel de tien hoogste scores en de namen van de bijbehorende spelers.
:p.
Als u wilt, kunt u ze allemaal wissen door het bestand Hiscore.bin te verwijderen. De volgende keer dat u
het spel start, wordt een leeg bestand met hoogste scores gemaakt.

:h1 res=007.WarpTris spelen
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.WarpTris spelen
WarpTris is een nogal andere (en originele) vorm van Tetris. In plaats van stukken die van boven in het Spelvenster vallen,
verschijnen ze in het midden en beginnen dan willekeurig naar een kant te vallen.
:p.
Dit gedrag heeft een pseudo-natuurkundige verklaring&colon. stel u voor dat u in de ruimte bent, waar geen zwaartekracht is. Als u
iets loslaat en het een impuls in een bepaalde richting geeft, beweegt (of valt) het in die richting en
blijft zo bewegen, tenzij het iets op zijn weg tegenkomt. In WarpTris verschijnen de stukken in het midden van het Spelvenster,
krijgen een impuls in een willekeurige richting en vallen direct die kant op (net als in de ruimte).
:p.
Het stuk kan maar naar vier richtingen vallen (omhoog, omlaag, links en rechts) en u kunt
lijnen maken aan de vier kanten van het Spelvenster. U verliest als een stuk een vakje van het grijze gebied in het midden bedekt.
:p.
Er zijn drie moeilijkheidsgraden, die ik impulsen noem (dat klinkt logischer). Ze verschillen in
de sterkte van de impuls en dus in de snelheid waarmee de stukken bewegen.
:p.
Tot slot&colon. als u een lijn maakt aan een kant, wordt alleen het gebied van die kant van het spelvenster tot de
eerste parallelle kant van het grijze vierkant in het midden beoordeeld, waardoor gaten ontstaan aan de aangrenzende kanten
van het Spelvenster. De onderstaande figuur toont bijvoorbeeld welk gebied wordt beoordeeld als u
een lijn maakt aan de linkerkant van het Spelvenster.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
U kunt uw stuk alleen verplaatsen parallel aan de kant waar het naartoe valt.
:ent.

:h1 res=008.WarpTris toetsen
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.WarpTris toetsen
De geldige toetsen voor dit spel zijn&colon.
:parml compact tsize=20 break=none.
:pt.Spatiebalk
:pd.Stuk laten vallen
:pt.Numeriek Omhoog of pijl omhoog
:pd.Omhoog bewegen
:pt.Numeriek Omlaag of pijl omlaag
:pd.Omlaag bewegen
:pt.Numeriek Links of pijl links
:pd.Naar links bewegen
:pt.Numeriek Rechts of pijl rechts
:pd.Naar rechts bewegen
:pt.Numeriek 5 of Shift (beide)
:pd.Draaien
:pt.P
:pd.Pauze / doorgaan
:eparml.
:p.
De volgende sneltoetsen werken overal in het WarpTris-venster&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.Nieuw spel
:pt.Ctrl+P
:pd.Spel pauzeren / hervatten
:pt.Ctrl+Q
:pd.Huidig spel stoppen
:pt.Ctrl+X
:pd.WarpTris afsluiten
:pt.Ctrl+B
:pd.Achtergrond Actief aan / uit
:pt.Ctrl+F
:pd.Kaderbediening aan / uit
:pt.Ctrl+1, 2, 3
:pd.Impuls Donkey, Formula 1, WARP!
:eparml.
:p.
Het spel stopt ook wanneer het Spelvenster de focus verliest, tenzij Achtergrond Actief aan staat.
:nt.
Om de numerieke toetsen te gebruiken moet NUMLOCK actief zijn.
:ent.

:h1 res=009.Dankwoord
:font facename=Helv size=8x12.
:p.
WarpTris is een 32-bits Tetris-achtig spel voor OS/2, geschreven door Paulo Gago da Camara op de Azoren, Portugal, in 1996.
Hij maakte dit spel om PM-programmeren te leren.
:p.
Speciale dank aan zijn voormalige C/C++-docent, Dr. Gunther Funk, voor het oorspronkelijke idee, en aan zijn vriend
Jorge Cipriano, voor zijn morele en technische steun. Hij was ook de tester van de Alfa-, Beta- en eindversie.
:p.
De Open Watcom-versie, met de gebruikersinterface in zes talen, is in 2026 gemaakt door de OS2World-gemeenschap.

:h1 res=010.Menu Spel
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Spel
:dl tsize=20.
:dt.:hp2.Nieuw:ehp2. (Ctrl+N)
:dd.Deze optie start een nieuw spel. Ze is niet beschikbaar terwijl een spel loopt.
:dt.:hp2.Pauze Spel:ehp2. (Ctrl+P)
:dd.Stopt het spel. Kies het opnieuw om verder te gaan.
:dt.:hp2.Stop Spel:ehp2. (Ctrl+Q)
:dd.Stopt het huidige spel en toont de score. WarpTris blijft open.
:dt.:hp2.Afsluiten:ehp2. (Ctrl+X)
:dd.Sluit WarpTris direct af.
:edl.

:h1 res=011.Menu Impuls
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impuls
Er zijn drie soorten impuls, die overeenkomen met drie spelsnelheden. Dit menu
is in feite het niveaumenu.
:p.
De Donkey-impuls is de zwakste (langzaamste) en WARP! is de sterkste (snelste).

:h1 res=012.Menu Geluid
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Geluid
Zet het geluid aan of uit.

:h1 res=013.Menu Opties
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Opties
:dl tsize=20.
:dt.:hp2.Eigenschappen:ehp2.
:dd.Toont het eigenschappennotitieboek.
:dt.:hp2.Detail:ehp2.
:dd.Hoog toont een vloeiende animatie wanneer een nieuw stuk verschijnt, Middel is de originele animatie
en Laag zet de animatie uit.
:dt.:hp2.Taal:ehp2.
:dd.Wijzigt de taal van de menu's, vensters, dialogen en van deze help. De keuze wordt onthouden.
:dt.:hp2.Achtergrond Actief:ehp2. (Ctrl+B)
:dd.Als dit aan staat, blijft het spel lopen terwijl een ander venster de focus heeft.
:dt.:hp2.Kaderbediening:ehp2. (Ctrl+F)
:dd.Verbergt of toont de titelbalk en het menu van het WarpTris-venster. Gebruik Ctrl+F opnieuw om ze terug te krijgen.
:dt.:hp2.Instellingen opslaan bij afsluiten:ehp2.
:dd.Bewaart de instellingen en de vensterposities in WarpTris.cfg bij het afsluiten.
:edl.

:h1 res=014.Menu Vensters
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Vensters
:dl tsize=20.
:dt.:hp2.Hoogste Scores:ehp2.
:dd.Zet het venster Hoogste Scores aan of uit.
:dt.:hp2.Volgende:ehp2.
:dd.Zet het venster Volgende aan of uit.
:dt.:hp2.Score:ehp2.
:dd.Zet het venster Score aan of uit.
:dt.:hp2.Spel:ehp2.
:dd.Zet het venster Spel aan of uit.
:dt.:hp2.Rangschik:ehp2.
:dd.Herstelt de standaardposities van de vensters Spel, Score, Volgende en Hoogste Scores.
:edl.

:h1 res=015.Menu Help
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Help
:dl tsize=20.
:dt.:hp2.Algemene Help:ehp2.
:dd.Toont het algemene hulpvenster.
:dt.:hp2.Help-index:ehp2.
:dd.Toont het venster met de helpindex.
:dt.:hp2.Help over Help:ehp2.
:dd.Toont informatie die uitlegt hoe u de help gebruikt.
:dt.:hp2.About:ehp2.
:dd.Toont het dialoogvenster About.
:edl.

:h1 res=016.Licentieovereenkomst
:font facename=Helv size=8x12.
.br
:hp4.Licentie van WarpTris.:ehp4.
:p.
WarpTris is vrije software&colon. u mag het verspreiden en/of wijzigen onder de voorwaarden van de GNU General Public License, zoals gepubliceerd door de Free Software Foundation, versie 3 van de Licentie of (naar uw keuze) een latere versie.
:p.
Dit programma wordt verspreid in de hoop dat het nuttig is, maar ZONDER ENIGE GARANTIE, zelfs zonder de impliciete garantie van VERHANDELBAARHEID of GESCHIKTHEID VOOR EEN BEPAALD DOEL. Zie het bestand LICENSE.txt voor de volledige licentietekst.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.Licentieovereenkomst

:h1 res=017.Handelsmerken
:font facename=Helv size=8x12.
:i1.Handelsmerken
:p.
De volgende termen zijn handelsmerken van IBM Corporation in de Verenigde Staten of andere landen&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Alle andere genoemde handelsmerken zijn eigendom van hun respectievelijke eigenaars.
:p.
Het is niet mijn bedoeling met dit programma enig auteursrecht of handelsmerk te schenden.
:p.

:euserdoc.
