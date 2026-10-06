WarpTris for OS/2 - Version 1.20
================================

OVERVIEW
--------
WarpTris is a 32 bit, multi-threaded Tetris like game for OS/2.
Instead of pieces dropping from the top to the bottom, they appear in the
middle of the game window and then start falling towards one side of it,
randomly. This lets you make lines all around the game window.

Originally written by Paulo Gago da Camara in 1996.
Ported to Open Watcom (ArcaOS / OS/2 Warp 4) by the OS2World community, 2026.

The program uses four windows inside the WarpTris window: Game, Score, Next
(the next piece and its next direction) and High Scores.

HOW TO PLAY
-----------
Choose Game - New (Ctrl+N). A piece appears in the gray square in the middle
of the Game window and, after a short animation, it gets an impulse and starts
falling towards the top, the bottom, the left or the right. The direction of
the next piece is shown in the Next window.

You can move the piece only parallel to the side it is falling to. Fill complete
lines on any of the four sides to remove them and score points. When a piece
covers any square of the gray area in the middle, the game is over.

When you make a line on one side, only the area between that side and the
nearest parallel side of the gray square is evaluated.

There are three levels of difficulty, called impulses: Donkey (slow),
Formula 1 and WARP! (fast).

CONTROLS
--------
  Space                     Drop the piece
  Keypad 4 / Left arrow     Move left
  Keypad 6 / Right arrow    Move right
  Keypad 8 / Up arrow       Move up
  Keypad 2 / Down arrow     Move down
  Keypad 5 / Shift          Rotate (either Shift key)
  P                         Pause / resume

  Left and right work while the piece falls up or down, up and down work while
  it falls to the left or to the right. NUMLOCK must be active to use the keypad.

KEYBOARD SHORTCUTS
------------------
  Ctrl+N    New game (not while a game is running)
  Ctrl+P    Pause / resume the game
  Ctrl+Q    Quit the current game and show the score
  Ctrl+X    Exit WarpTris
  Ctrl+B    Background Run on / off
  Ctrl+F    Frame Controls on / off (hides title bar and menu)
  Ctrl+O    Properties notebook
  Ctrl+1/2/3  Impulse Donkey / Formula 1 / WARP!
  Ctrl+H/E/S/G  Show / hide the High Scores / Next / Score / Game window

MENUS
-----
  Game      New, Pause Game, Quit Game, Exit
  Options   Properties, Impulse (Donkey, Formula 1, WARP!), Sound (On, Off),
            Detail (High, Medium, Low), Language, Background Run,
            Frame Controls, Save settings on exit
  Windows   High Scores, Next, Score, Game, Arrange
  Help      General Help, Help Index, Help on Help, About

  Language    English, Spanish, Dutch, German, French and Italian. Menus, windows,
              dialogs and the help switch at run time.
  Detail      High shows a smooth animation when a piece appears, Medium is the
              original animation and Low switches it off.
  Background Run  Off (default): the game stops when the Game window loses the focus.
  Frame Controls  Hides the title bar and the menu bar of the WarpTris window.

The game window and the other windows have a context menu on the right mouse button.

FILE LIST
---------
  WarpTris.exe        The game
  help\WarpTris_en.hlp  Online help in the help folder next to WarpTris.exe
                      (one file per language: en, es, nl, de, fr, it)
  sounds\Pop.wav      Sounds, in the "sounds" folder next to WarpTris.exe
  sounds\Over.wav
  sounds\High.wav
  Readme.txt, Changelog.txt, LICENSE.txt

  Created by the game in the working directory:
  WarpTris.cfg        Settings and window positions
  Hiscore.bin         High scores

  Sound needs OS/2 Multimedia (MMPM/2). Without it the game simply stays silent.

DISCLAIMER
----------
The Author/Programmer does not guarantee anything about this game, nor is
responsible for any damage done to your Software and/or Hardware by it.
WarpTris is free software under the GNU General Public License v3, WITHOUT ANY
WARRANTY. See LICENSE.txt.

AUTHOR
------
Original game: Paulo Gago da Camara, Azores, Portugal (1996).
Special thanks of the author to Dr. Gunther Funk and to Jorge Cipriano.
OS/2 Open Watcom port: OS2World community (2026).
