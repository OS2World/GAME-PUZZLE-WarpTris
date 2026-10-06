.* WarpTris Hilfe - Deutsch
:userdoc.

:h1 res=001.Allgemeine Hilfe
:i1 id=Win.Fenster
:i1 id=HowTo.WarpTris spielen
:i1 id=Menus.Menues
:font facename=Helv size=8x12.
Waehlen Sie eines der folgenden Themen&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.Lizenzvereinbarung:elink.
:li.:link reftype=hd res=017.Marken:elink.
:li.:link reftype=hd res=007.WarpTris spielen:elink.
:li.:link reftype=hd res=008.WarpTris Tasten:elink.
:li.:link reftype=hd res=002.Menuepunkte:elink.
:li.:link reftype=hd res=003.Spielfenster:elink.
:li.:link reftype=hd res=004.Punktefenster:elink.
:li.:link reftype=hd res=005.Fenster Naechste:elink.
:li.:link reftype=hd res=006.Fenster Bestenliste:elink.
:li.:link reftype=hd res=023.Fehler melden:elink.
:li.:link reftype=hd res=009.Danksagung:elink.
:eul.
:p.

:h1 res=023.Fehler melden
:font facename=Helv size=8x12.
:p.
Wenn Sie Fehler in diesem Programm finden, melden Sie diese bitte ueber die OS2World-Gemeinschaft
(https&colon.//www.os2world.com), mit einer Beschreibung des Fehlers.
:p.
Vielen Dank im Voraus.

:h1 res=002.Menuepunkte
:font facename=Helv size=8x12.
:p.
Waehlen Sie einen Verweis aus der folgenden Liste&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Menue Spiel:elink.
:li.:link reftype=hd res=011.Menue Impuls:elink.
:li.:link reftype=hd res=012.Menue Ton:elink.
:li.:link reftype=hd res=013.Menue Optionen:elink.
:li.:link reftype=hd res=014.Menue Fenster:elink.
:li.:link reftype=hd res=015.Menue Hilfe:elink.
:eul.
:p.

:h1 res=003.Spielfenster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Spielfeld
In diesem Fenster spielen Sie das eigentliche Spiel. Die Steine erscheinen im grauen Quadrat in der
Mitte und fallen dann zufaellig zu einer Seite.
:p.
Wenn ein Stein irgendeinen Teil des grauen Quadrats in der Mitte ueberdeckt, ist das Spiel zu Ende.
:p.
Dieses Fenster hat ausserdem ein Kontextmenue mit den Optionen der Menueleiste, die es betreffen.

:h1 res=004.Punktefenster
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Punkte
Zu diesem Fenster gibt es nicht viel zu sagen. Es zeigt Ihre aktuelle Punktzahl.

:h1 res=005.Fenster Naechste
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Naechste
Dieses Fenster zeigt den naechsten Stein und die Richtung seines naechsten Impulses.
:p.
Wenn Sie diese Hilfe nicht moechten, koennen Sie das Fenster mit seiner Schaltflaeche Verbergen ausblenden.

:h1 res=006.Fenster Bestenliste
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Bestenliste
In diesem Fenster speichert das Spiel die zehn besten Ergebnisse und die Namen der jeweiligen Spieler.
:p.
Wenn Sie moechten, koennen Sie alle loeschen, indem Sie die Datei Hiscore.bin entfernen. Beim naechsten Start
des Spiels wird eine leere Bestenliste angelegt.

:h1 res=007.WarpTris spielen
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Spielen
WarpTris ist eine ziemlich andere (und originelle) Art von Tetris. Statt von oben in das Spielfenster zu fallen,
erscheinen die Steine in dessen Mitte und fallen dann zufaellig zu einer Seite.
:p.
Dieses Verhalten hat eine pseudo-physikalische Erklaerung&colon. Stellen Sie sich vor, Sie sind im Weltraum, wo es keine Schwerkraft gibt. Wenn Sie
etwas loslassen und ihm einen Impuls in eine bestimmte Richtung geben, bewegt es sich (oder faellt) in diese Richtung und
bewegt sich so weiter, ausser es trifft auf etwas. In WarpTris erscheinen die Steine in der Mitte des Spielfensters,
erhalten einen Impuls in eine zufaellige Richtung und fallen sofort in diese Richtung (genau wie im Weltraum).
:p.
Der Stein kann nur in vier Richtungen fallen (oben, unten, links und rechts), und Sie koennen
Linien an den vier Seiten des Spielfensters bilden. Sie verlieren, wenn ein Stein ein Feld des grauen Bereichs in der Mitte bedeckt.
:p.
Es gibt drei Schwierigkeitsgrade, die ich Impulse nenne (das ergibt mehr Sinn). Sie unterscheiden sich in
der Staerke des Impulses und damit in der Geschwindigkeit, mit der sich die Steine bewegen.
:p.
Schliesslich wird, wenn Sie an einer Seite eine Linie bilden, nur der Bereich von dieser Seite des Spielfensters bis zur
ersten parallelen Seite des grauen Quadrats in der Mitte ausgewertet, wodurch an den angrenzenden Seiten
des Spielfensters Luecken entstehen. Die folgende Abbildung zeigt zum Beispiel, welcher Bereich ausgewertet wird, wenn Sie
eine Linie an der linken Seite des Spielfensters bilden.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
Sie koennen Ihren Stein nur parallel zu der Seite bewegen, zu der er faellt.
:ent.

:h1 res=008.WarpTris Tasten
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Tasten
Die gueltigen Tasten fuer dieses Spiel sind&colon.
:parml compact tsize=20 break=none.
:pt.Leertaste
:pd.Stein fallen lassen
:pt.Ziffernblock Hoch oder Pfeil hoch
:pd.Nach oben bewegen
:pt.Ziffernblock Runter oder Pfeil runter
:pd.Nach unten bewegen
:pt.Ziffernblock Links oder Pfeil links
:pd.Nach links bewegen
:pt.Ziffernblock Rechts oder Pfeil rechts
:pd.Nach rechts bewegen
:pt.Ziffernblock 5 oder Umschalt (beide)
:pd.Drehen
:pt.P
:pd.Pause / fortsetzen
:eparml.
:p.
Die folgenden Tastenkombinationen funktionieren im gesamten WarpTris-Fenster&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.Neues Spiel
:pt.Ctrl+P
:pd.Spiel anhalten / fortsetzen
:pt.Ctrl+Q
:pd.Aktuelles Spiel abbrechen
:pt.Ctrl+X
:pd.WarpTris beenden
:pt.Ctrl+B
:pd.Hintergrundlauf ein / aus
:pt.Ctrl+F
:pd.Rahmenelemente ein / aus
:pt.Ctrl+1, 2, 3
:pd.Impuls Donkey, Formula 1, WARP!
:eparml.
:p.
Das Spiel haelt auch an, wenn das Spielfenster den Fokus verliert, ausser der Hintergrundlauf ist eingeschaltet.
:nt.
Um die Tasten des Ziffernblocks zu benutzen, muss NUMLOCK aktiv sein.
:ent.

:h1 res=009.Danksagung
:font facename=Helv size=8x12.
:p.
WarpTris ist ein 32-Bit-Spiel im Stil von Tetris fuer OS/2, geschrieben 1996 von Paulo Gago da Camara auf den Azoren, Portugal.
Er schrieb dieses Spiel, um die PM-Programmierung zu lernen.
:p.
Besonderer Dank gilt seinem frueheren C/C++-Lehrer, Dr. Gunther Funk, fuer die urspruengliche Idee, und seinem Freund
Jorge Cipriano fuer die moralische und technische Unterstuetzung. Er war auch der Tester der Alpha-, Beta- und Endversion.
:p.
Die Open-Watcom-Version mit der sechssprachigen Benutzeroberflaeche wurde 2026 von der OS2World-Gemeinschaft erstellt.

:h1 res=010.Menue Spiel
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Spiel
:dl tsize=20.
:dt.:hp2.Neu:ehp2. (Ctrl+N)
:dd.Diese Option startet ein neues Spiel. Sie ist nicht verfuegbar, solange ein Spiel laeuft.
:dt.:hp2.Pause:ehp2. (Ctrl+P)
:dd.Haelt das Spiel an. Waehlen Sie sie noch einmal, um fortzufahren.
:dt.:hp2.Spiel abbrechen:ehp2. (Ctrl+Q)
:dd.Beendet das aktuelle Spiel und zeigt die Punktzahl. WarpTris bleibt geoeffnet.
:dt.:hp2.Beenden:ehp2. (Ctrl+X)
:dd.Beendet WarpTris sofort.
:edl.

:h1 res=011.Menue Impuls
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impuls
Es gibt drei Arten von Impuls, die drei verschiedenen Spielgeschwindigkeiten entsprechen. Dieses Menue
ist in Wirklichkeit das Stufenmenue.
:p.
Der Impuls Donkey ist der schwaechste (langsamste), WARP! ist der staerkste (schnellste).

:h1 res=012.Menue Ton
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Ton
Schaltet den Ton ein oder aus.

:h1 res=013.Menue Optionen
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Optionen
:dl tsize=20.
:dt.:hp2.Eigenschaften:ehp2.
:dd.Zeigt das Eigenschaftenbuch.
:dt.:hp2.Detail:ehp2.
:dd.Hoch zeigt eine fliessende Animation, wenn ein neuer Stein erscheint, Mittel ist die originale Animation
und Niedrig schaltet die Animation aus.
:dt.:hp2.Sprache:ehp2.
:dd.Aendert die Sprache der Menues, Fenster, Dialoge und dieser Hilfe. Die Auswahl wird gespeichert.
:dt.:hp2.Hintergrundlauf:ehp2. (Ctrl+B)
:dd.Wenn eingeschaltet, laeuft das Spiel weiter, waehrend ein anderes Fenster den Fokus hat.
:dt.:hp2.Rahmenelemente:ehp2. (Ctrl+F)
:dd.Blendet die Titelleiste und das Menue des WarpTris-Fensters aus oder ein. Mit Ctrl+F erhalten Sie sie zurueck.
:dt.:hp2.Beim Beenden Einstellungen sichern:ehp2.
:dd.Speichert beim Beenden die Einstellungen und die Fensterpositionen in WarpTris.cfg.
:edl.

:h1 res=014.Menue Fenster
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Fenster
:dl tsize=20.
:dt.:hp2.Bestenliste:ehp2.
:dd.Schaltet das Fenster Bestenliste ein oder aus.
:dt.:hp2.Naechste:ehp2.
:dd.Schaltet das Fenster Naechste ein oder aus.
:dt.:hp2.Punkte:ehp2.
:dd.Schaltet das Fenster Punkte ein oder aus.
:dt.:hp2.Spielfeld:ehp2.
:dd.Schaltet das Spielfenster ein oder aus.
:dt.:hp2.Anordnen:ehp2.
:dd.Stellt die Standardpositionen der Fenster Spielfeld, Punkte, Naechste und Bestenliste wieder her.
:edl.

:h1 res=015.Menue Hilfe
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Hilfe
:dl tsize=20.
:dt.:hp2.Allgemeine Hilfe:ehp2.
:dd.Zeigt das Fenster der allgemeinen Hilfe.
:dt.:hp2.Hilfeindex:ehp2.
:dd.Zeigt das Fenster des Hilfeindex.
:dt.:hp2.Hilfe zur Hilfe:ehp2.
:dd.Zeigt Informationen, die die Benutzung der Hilfe erklaeren.
:dt.:hp2.About:ehp2.
:dd.Zeigt den Dialog About.
:edl.

:h1 res=016.Lizenzvereinbarung
:font facename=Helv size=8x12.
.br
:hp4.Lizenz fuer WarpTris.:ehp4.
:p.
WarpTris ist freie Software&colon. Sie koennen es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veroeffentlicht, weitergeben und/oder aendern, entweder gemaess Version 3 der Lizenz oder (nach Ihrer Wahl) jeder spaeteren Version.
:p.
Dieses Programm wird in der Hoffnung verbreitet, dass es nuetzlich sein wird, aber OHNE JEDE GEWAEHRLEISTUNG, sogar ohne die implizite Gewaehrleistung der MARKTFAEHIGKEIT oder EIGNUNG FUER EINEN BESTIMMTEN ZWECK. Den vollstaendigen Lizenztext finden Sie in der Datei LICENSE.txt.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.Lizenzvereinbarung

:h1 res=017.Marken
:font facename=Helv size=8x12.
:i1.Marken
:p.
Die folgenden Begriffe sind Marken der IBM Corporation in den Vereinigten Staaten oder anderen Laendern&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Alle anderen erwaehnten Marken gehoeren ihren jeweiligen Eigentuemern.
:p.
Es ist nicht meine Absicht, mit diesem Programm Urheberrechte oder Marken zu verletzen.
:p.

:euserdoc.
