.* Aide de WarpTris - Francais
:userdoc.

:h1 res=001.Aide generale
:i1 id=Win.Fenetres
:i1 id=HowTo.Comment jouer a WarpTris
:i1 id=Menus.Menus
:font facename=Helv size=8x12.
Choisissez un des sujets ci-dessous&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.Contrat de licence:elink.
:li.:link reftype=hd res=017.Marques:elink.
:li.:link reftype=hd res=007.Jouer a WarpTris:elink.
:li.:link reftype=hd res=008.Touches de WarpTris:elink.
:li.:link reftype=hd res=002.Options des menus:elink.
:li.:link reftype=hd res=003.Fenetre Jeu:elink.
:li.:link reftype=hd res=004.Fenetre Score:elink.
:li.:link reftype=hd res=005.Fenetre Suivante:elink.
:li.:link reftype=hd res=006.Fenetre Meilleurs Scores:elink.
:li.:link reftype=hd res=023.Signaler des erreurs:elink.
:li.:link reftype=hd res=009.Remerciements:elink.
:eul.
:p.

:h1 res=023.Signaler des erreurs
:font facename=Helv size=8x12.
:p.
Si vous trouvez des erreurs dans ce programme, veuillez les signaler par l'intermediaire de la communaute OS2World
(https&colon.//www.os2world.com), avec une description de l'erreur.
:p.
Merci d'avance.

:h1 res=002.Options des menus
:font facename=Helv size=8x12.
:p.
Choisissez un lien dans la liste ci-dessous&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Menu Jeu:elink.
:li.:link reftype=hd res=011.Menu Impulsion:elink.
:li.:link reftype=hd res=012.Menu Son:elink.
:li.:link reftype=hd res=013.Menu Options:elink.
:li.:link reftype=hd res=014.Menu Fenetres:elink.
:li.:link reftype=hd res=015.Menu Aide:elink.
:eul.
:p.

:h1 res=003.Fenetre Jeu
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Jeu
C'est dans cette fenetre que vous jouez reellement. Les pieces apparaissent dans le carre gris au
centre, puis commencent a tomber vers un cote, au hasard.
:p.
Quand une piece recouvre une partie du carre gris central, la partie est terminee.
:p.
Cette fenetre possede aussi un menu contextuel avec les options de la barre de menus qui la concernent.

:h1 res=004.Fenetre Score
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Score
Il n'y a pas grand-chose a dire sur cette fenetre. Elle affiche votre score actuel.

:h1 res=005.Fenetre Suivante
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Suivante
Cette fenetre affiche la piece suivante et la direction de sa prochaine impulsion.
:p.
Si vous ne voulez pas de cette aide, vous pouvez la masquer avec son bouton de masquage.

:h1 res=006.Fenetre Meilleurs Scores
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Meilleurs Scores
Dans cette fenetre, le jeu conserve les dix meilleurs scores et les noms des joueurs correspondants.
:p.
Si vous le souhaitez, vous pouvez tous les effacer en supprimant le fichier Hiscore.bin. A la prochaine
execution du jeu, un fichier de scores vide sera cree.

:h1 res=007.Jouer a WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Jouer a WarpTris
WarpTris est une sorte de Tetris assez differente (et originale). Au lieu de tomber du haut de la fenetre Jeu,
les pieces apparaissent au milieu, puis commencent a tomber vers un cote, au hasard.
:p.
Ce comportement a une explication pseudo-physique&colon. imaginez que vous etes dans l'espace, ou il n'y a pas de gravite. Si vous lachez
quelque chose et lui donnez une impulsion dans une direction, c'est dans cette direction qu'il se deplacera (ou tombera), et il
continuera ainsi, a moins de rencontrer quelque chose sur son chemin. Dans WarpTris, les pieces apparaissent au milieu de la
fenetre Jeu, recoivent une impulsion dans une direction au hasard et commencent aussitot a tomber dans cette direction (comme dans l'espace).
:p.
La piece ne peut tomber que dans quatre directions (haut, bas, gauche et droite) et vous pouvez former
des lignes sur les quatre cotes de la fenetre Jeu. Vous perdez quand une piece recouvre une case de la zone grise centrale.
:p.
Il y a trois niveaux de difficulte, que j'appelle impulsions (c'est plus logique). Ils different par
la force de l'impulsion, donc par la vitesse a laquelle les pieces se deplacent.
:p.
Enfin, quand vous formez une ligne sur un cote, seule la zone allant de ce cote de la fenetre de jeu jusqu'au
premier cote parallele du carre gris central est evaluee, ce qui ouvre des trous sur les cotes adjacents
de la fenetre Jeu. Par exemple, la figure ci-dessous montre quelle zone est evaluee si vous formez
une ligne sur le cote gauche de la fenetre Jeu.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
Vous ne pouvez deplacer votre piece que parallelement au cote vers lequel elle tombe.
:ent.

:h1 res=008.Touches de WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Touches de WarpTris
Les touches valides pour ce jeu sont&colon.
:parml compact tsize=20 break=none.
:pt.Espace
:pd.Faire tomber la piece
:pt.Pave numerique Haut ou fleche haut
:pd.Deplacer vers le haut
:pt.Pave numerique Bas ou fleche bas
:pd.Deplacer vers le bas
:pt.Pave numerique Gauche ou fleche gauche
:pd.Deplacer vers la gauche
:pt.Pave numerique Droite ou fleche droite
:pd.Deplacer vers la droite
:pt.Pave numerique 5 ou Maj (l'une ou l'autre)
:pd.Tourner
:pt.P
:pd.Pause / reprendre
:eparml.
:p.
Les raccourcis suivants fonctionnent partout dans la fenetre WarpTris&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.Nouvelle partie
:pt.Ctrl+P
:pd.Mettre en pause / reprendre le jeu
:pt.Ctrl+Q
:pd.Quitter la partie en cours
:pt.Ctrl+X
:pd.Quitter WarpTris
:pt.Ctrl+B
:pd.Arriere-plan Actif oui / non
:pt.Ctrl+F
:pd.Controles du cadre oui / non
:pt.Ctrl+1, 2, 3
:pd.Impulsion Donkey, Formula 1, WARP!
:eparml.
:p.
Le jeu s'arrete aussi quand la fenetre Jeu perd le focus, sauf si Arriere-plan Actif est active.
:nt.
Pour utiliser les touches du pave numerique, VERR NUM doit etre actif.
:ent.

:h1 res=009.Remerciements
:font facename=Helv size=8x12.
:p.
WarpTris est un jeu 32 bits de type Tetris pour OS/2, ecrit par Paulo Gago da Camara aux Acores, au Portugal, en 1996.
Il a fait ce jeu dans le but d'apprendre la programmation PM.
:p.
Remerciements particuliers a son ancien professeur de C/C++, le Dr Gunther Funk, pour l'idee d'origine, et a son ami
Jorge Cipriano, pour son soutien moral et technique. Il fut aussi le testeur des versions Alpha, Beta et finale.
:p.
La version Open Watcom, avec l'interface en six langues, a ete preparee par la communaute OS2World en 2026.

:h1 res=010.Menu Jeu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Jeu
:dl tsize=20.
:dt.:hp2.Nouveau:ehp2. (Ctrl+N)
:dd.Cette option demarre une nouvelle partie. Elle n'est pas disponible pendant une partie.
:dt.:hp2.Pause Jeu:ehp2. (Ctrl+P)
:dd.Arrete le jeu. Choisissez-la de nouveau pour continuer.
:dt.:hp2.Quitter la partie:ehp2. (Ctrl+Q)
:dd.Arrete la partie en cours et affiche le score. WarpTris reste ouvert.
:dt.:hp2.Sortir:ehp2. (Ctrl+X)
:dd.Quitte WarpTris immediatement.
:edl.

:h1 res=011.Menu Impulsion
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impulsion
Il y a trois sortes d'impulsion, qui correspondent a trois vitesses de jeu. Ce menu
est en fait le menu des niveaux.
:p.
L'impulsion Donkey est la plus faible (la plus lente) et WARP! la plus forte (la plus rapide).

:h1 res=012.Menu Son
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Son
Active ou desactive le son.

:h1 res=013.Menu Options
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Options
:dl tsize=20.
:dt.:hp2.Proprietes:ehp2.
:dd.Affiche le bloc-notes des proprietes.
:dt.:hp2.Detail:ehp2.
:dd.Haut affiche une animation fluide quand une nouvelle piece apparait, Moyen est l'animation d'origine
et Bas la supprime.
:dt.:hp2.Langue:ehp2.
:dd.Change la langue des menus, des fenetres, des boites de dialogue et de cette aide. Le choix est conserve.
:dt.:hp2.Arriere-plan Actif:ehp2. (Ctrl+B)
:dd.Si cette option est active, le jeu continue pendant qu'une autre fenetre a le focus.
:dt.:hp2.Controles du cadre:ehp2. (Ctrl+F)
:dd.Masque ou affiche la barre de titre et le menu de la fenetre WarpTris. Utilisez de nouveau Ctrl+F pour les retrouver.
:dt.:hp2.Enregistrer en quittant:ehp2.
:dd.Enregistre les parametres et les positions des fenetres dans WarpTris.cfg a la sortie.
:edl.

:h1 res=014.Menu Fenetres
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Fenetres
:dl tsize=20.
:dt.:hp2.Meilleurs scores:ehp2.
:dd.Affiche ou masque la fenetre Meilleurs Scores.
:dt.:hp2.Suivante:ehp2.
:dd.Affiche ou masque la fenetre Suivante.
:dt.:hp2.Score:ehp2.
:dd.Affiche ou masque la fenetre Score.
:dt.:hp2.Jeu:ehp2.
:dd.Affiche ou masque la fenetre Jeu.
:dt.:hp2.Organiser:ehp2.
:dd.Restaure les positions par defaut des fenetres Jeu, Score, Suivante et Meilleurs Scores.
:edl.

:h1 res=015.Menu Aide
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Aide
:dl tsize=20.
:dt.:hp2.Aide generale:ehp2.
:dd.Affiche la fenetre d'aide generale.
:dt.:hp2.Index de l'aide:ehp2.
:dd.Affiche la fenetre de l'index de l'aide.
:dt.:hp2.Aide sur l'aide:ehp2.
:dd.Affiche des informations expliquant comment utiliser l'aide.
:dt.:hp2.About:ehp2.
:dd.Affiche la boite de dialogue About.
:edl.

:h1 res=016.Contrat de licence
:font facename=Helv size=8x12.
.br
:hp4.Licence de WarpTris.:ehp4.
:p.
WarpTris est un logiciel libre&colon. vous pouvez le redistribuer et/ou le modifier selon les termes de la Licence Publique Generale GNU telle que publiee par la Free Software Foundation, soit la version 3 de la Licence, soit (a votre gre) toute version ulterieure.
:p.
Ce programme est distribue dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE, sans meme la garantie implicite de COMMERCIALISATION ou d'ADAPTATION A UN OBJECTIF PARTICULIER. Consultez le fichier LICENSE.txt pour le texte complet de la licence.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.Contrat de licence

:h1 res=017.Marques
:font facename=Helv size=8x12.
:i1.Marques
:p.
Les termes suivants sont des marques d'IBM Corporation aux Etats-Unis ou dans d'autres pays&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Toute autre marque citee appartient a son proprietaire respectif.
:p.
Ce n'est pas mon intention de porter atteinte a un droit d'auteur ou a une marque avec ce programme.
:p.

:euserdoc.
