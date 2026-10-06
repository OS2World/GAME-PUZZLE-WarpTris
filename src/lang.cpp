/* WarpTris - language table. ASCII only (no accents), see plan section 8.6.
   Order of the strings must match the enum in lang.h. */

#include "lang.h"

int current_lang = LANG_EN;

const char *lang_strings[LANG_COUNT][STR_COUNT] = {

/* ======================= LANG_EN ======================= */
{
    "~Game", "~New\tCtrl+N", "~Pause Game\tCtrl+P", "~Quit Game\tCtrl+Q", "E~xit\tCtrl+X",
    "~Impulse", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Sound", "~On", "O~ff",
    "~Options", "~Properties...\tCtrl+O", "~Detail",
    "~High", "~Medium", "~Low",
    "~Language", "~Background Run\tCtrl+B", "~Frame Controls\tCtrl+F", "S~ave settings on exit",
    "~Windows", "~High Scores\tCtrl+H", "~Next\tCtrl+E", "~Score\tCtrl+S",
    "~Game\tCtrl+G", "~Arrange",
    "~Help", "~General Help", "Help ~Index", "~Help on Help",
    "~About...",
    "Game", "Score", "Next", "High Scores", "WarpTris Properties",
    "Game Paused! - Press P to Resume -", "WarpTris Help", "Page 1 of 1",
    "Sound", "Windows", "Impulse",
    "On", "Off", "Enabled Windows",
    "Exit WarpTris!", "Do you really want to exit this fine game?", "~Yes", "~No",
    "Information", "~Ok", "~New",
    "Congratulations!", "You have made a High Score entry!", "Please enter your name:", "~Enter",
    "Anon", "The help file %s was not found.\nPlease put it in the same folder as WarpTris.exe."
},

/* ======================= LANG_ES ======================= */
{
    "~Juego", "~Nuevo\tCtrl+N", "~Pausar Juego\tCtrl+P", "~Abandonar Juego\tCtrl+Q", "~Salir\tCtrl+X",
    "Imp~ulso", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Sonido", "~Activado", "~Desactivado",
    "~Opciones", "~Propiedades...\tCtrl+O", "~Detalle",
    "~Alto", "~Medio", "~Bajo",
    "~Idioma", "~Fondo Activo\tCtrl+B", "Controles de ~Marco\tCtrl+F", "~Guardar al salir",
    "~Ventanas", "~Puntuaciones\tCtrl+H", "~Siguiente\tCtrl+E", "P~untos\tCtrl+S",
    "~Juego\tCtrl+G", "~Ordenar",
    "A~yuda", "Ayuda ~general", "~Indice de ayuda", "Ayuda ~sobre ayuda",
    "~About...",
    "Juego", "Puntos", "Siguiente", "Mejores Puntuaciones", "Propiedades de WarpTris",
    "Juego en pausa! - Pulse P para continuar -", "Ayuda de WarpTris", "Pagina 1 de 1",
    "Sonido", "Ventanas", "Impulso",
    "Activado", "Desactivado", "Ventanas activas",
    "Salir de WarpTris!", "Realmente desea salir de este gran juego?", "~Si", "~No",
    "Informacion", "~Ok", "~Nuevo",
    "Felicidades!", "Ha entrado en la tabla de puntuaciones!", "Introduzca su nombre:", "~Entrar",
    "Anon", "No se encontro el archivo de ayuda %s.\nColoquelo en la misma carpeta que WarpTris.exe."
},

/* ======================= LANG_NL ======================= */
{
    "~Spel", "~Nieuw\tCtrl+N", "~Pauze Spel\tCtrl+P", "S~top Spel\tCtrl+Q", "~Afsluiten\tCtrl+X",
    "~Impuls", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Geluid", "~Aan", "~Uit",
    "~Opties", "~Eigenschappen...\tCtrl+O", "~Detail",
    "~Hoog", "~Middel", "~Laag",
    "~Taal", "~Achtergrond Actief\tCtrl+B", "~Kaderbediening\tCtrl+F", "Instellingen o~pslaan bij afsluiten",
    "~Vensters", "~Hoogste Scores\tCtrl+H", "~Volgende\tCtrl+E", "~Score\tCtrl+S",
    "~Spel\tCtrl+G", "~Rangschik",
    "~Help", "~Algemene Help", "Help-~index", "Help ~over Help",
    "~About...",
    "Spel", "Score", "Volgende", "Hoogste Scores", "WarpTris Eigenschappen",
    "Spel gepauzeerd! - Druk op P om door te gaan -", "WarpTris Help", "Pagina 1 van 1",
    "Geluid", "Vensters", "Impuls",
    "Aan", "Uit", "Actieve vensters",
    "WarpTris afsluiten!", "Wilt u dit mooie spel echt afsluiten?", "~Ja", "~Nee",
    "Informatie", "~Ok", "~Nieuw",
    "Gefeliciteerd!", "U staat in de hoogste scores!", "Voer uw naam in:", "~Invoeren",
    "Anon", "Het helpbestand %s is niet gevonden.\nPlaats het in dezelfde map als WarpTris.exe."
},

/* ======================= LANG_DE ======================= */
{
    "~Spiel", "~Neu\tCtrl+N", "~Pause\tCtrl+P", "Spiel a~bbrechen\tCtrl+Q", "Be~enden\tCtrl+X",
    "~Impuls", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Ton", "~Ein", "~Aus",
    "~Optionen", "~Eigenschaften...\tCtrl+O", "~Detail",
    "~Hoch", "~Mittel", "~Niedrig",
    "~Sprache", "~Hintergrundlauf\tCtrl+B", "~Rahmenelemente\tCtrl+F", "Beim Beenden Einstellungen si~chern",
    "~Fenster", "~Bestenliste\tCtrl+H", "~Naechste\tCtrl+E", "~Punkte\tCtrl+S",
    "~Spielfeld\tCtrl+G", "~Anordnen",
    "~Hilfe", "Allgemeine ~Hilfe", "Hilfe~index", "Hilfe ~zur Hilfe",
    "~About...",
    "Spiel", "Punkte", "Naechste", "Bestenliste", "WarpTris Eigenschaften",
    "Spiel pausiert! - P zum Fortsetzen -", "WarpTris Hilfe", "Seite 1 von 1",
    "Ton", "Fenster", "Impuls",
    "Ein", "Aus", "Aktive Fenster",
    "WarpTris beenden!", "Moechten Sie dieses schoene Spiel wirklich beenden?", "~Ja", "~Nein",
    "Information", "~Ok", "~Neu",
    "Gratulation!", "Sie haben einen Platz in der Bestenliste erreicht!", "Bitte geben Sie Ihren Namen ein:", "~Eingabe",
    "Anon", "Die Hilfedatei %s wurde nicht gefunden.\nBitte legen Sie sie in den Ordner von WarpTris.exe."
},

/* ======================= LANG_FR ======================= */
{
    "~Jeu", "~Nouveau\tCtrl+N", "~Pause Jeu\tCtrl+P", "~Quitter la partie\tCtrl+Q", "~Sortir\tCtrl+X",
    "~Impulsion", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Son", "~Actif", "~Inactif",
    "~Options", "~Proprietes...\tCtrl+O", "~Detail",
    "~Haut", "~Moyen", "~Bas",
    "~Langue", "Arriere-plan ~Actif\tCtrl+B", "~Controles du cadre\tCtrl+F", "~Enregistrer en quittant",
    "~Fenetres", "~Meilleurs scores\tCtrl+H", "~Suivante\tCtrl+E", "S~core\tCtrl+S",
    "~Jeu\tCtrl+G", "~Organiser",
    "~Aide", "Aide ~generale", "~Index de l'aide", "Aide ~sur l'aide",
    "~About...",
    "Jeu", "Score", "Suivante", "Meilleurs Scores", "Proprietes de WarpTris",
    "Jeu en pause! - Appuyez sur P pour reprendre -", "Aide de WarpTris", "Page 1 sur 1",
    "Son", "Fenetres", "Impulsion",
    "Actif", "Inactif", "Fenetres actives",
    "Quitter WarpTris!", "Voulez-vous vraiment quitter ce beau jeu?", "~Oui", "~Non",
    "Information", "~Ok", "~Nouveau",
    "Felicitations!", "Vous etes dans les meilleurs scores!", "Entrez votre nom:", "~Entrer",
    "Anon", "Le fichier d'aide %s est introuvable.\nPlacez-le dans le meme dossier que WarpTris.exe."
},

/* ======================= LANG_IT ======================= */
{
    "~Gioco", "~Nuovo\tCtrl+N", "~Pausa Gioco\tCtrl+P", "~Termina Gioco\tCtrl+Q", "~Esci\tCtrl+X",
    "Imp~ulso", "~Donkey\tCtrl+1", "~Formula 1\tCtrl+2", "~WARP!\tCtrl+3",
    "~Suono", "~Attivo", "~Disattivo",
    "~Opzioni", "~Proprieta...\tCtrl+O", "~Dettaglio",
    "~Alto", "~Medio", "~Basso",
    "~Lingua", "Sfondo ~Attivo\tCtrl+B", "Controlli ~Cornice\tCtrl+F", "Sal~va impostazioni all'uscita",
    "~Finestre", "~Record\tCtrl+H", "~Prossimo\tCtrl+E", "P~unteggio\tCtrl+S",
    "~Gioco\tCtrl+G", "~Ordina",
    "A~iuto", "Guida ~generale", "~Indice della guida", "Guida ~sulla guida",
    "~About...",
    "Gioco", "Punteggio", "Prossimo", "Record", "Proprieta di WarpTris",
    "Gioco in pausa! - Premere P per riprendere -", "Guida di WarpTris", "Pagina 1 di 1",
    "Suono", "Finestre", "Impulso",
    "Attivo", "Disattivo", "Finestre attive",
    "Esci da WarpTris!", "Vuoi davvero uscire da questo bel gioco?", "~Si", "~No",
    "Informazione", "~Ok", "~Nuovo",
    "Congratulazioni!", "Sei entrato nella classifica dei record!", "Inserisci il tuo nome:", "~Invio",
    "Anon", "Il file della guida %s non e' stato trovato.\nMetterlo nella stessa cartella di WarpTris.exe."
}

};
