.* WarpTris help - English
:userdoc.

:h1 res=001.General Help
:i1 id=Win.Windows
:i1 id=HowTo.How to play WarpTris
:i1 id=Menus.Menus
:font facename=Helv size=8x12.
Choose one of the topics below&colon.
:p.
:ul compact.
:li.:link reftype=hd res=016.License Agreement:elink.
:li.:link reftype=hd res=017.Trademarks:elink.
:li.:link reftype=hd res=007.Playing WarpTris:elink.
:li.:link reftype=hd res=008.WarpTris Keys:elink.
:li.:link reftype=hd res=002.Menu Options:elink.
:li.:link reftype=hd res=003.Game Window:elink.
:li.:link reftype=hd res=004.Score Window:elink.
:li.:link reftype=hd res=005.Next Window:elink.
:li.:link reftype=hd res=006.High Scores Window:elink.
:li.:link reftype=hd res=023.Bug Reporting:elink.
:li.:link reftype=hd res=009.Credits:elink.
:eul.
:p.

:h1 res=023.Bug Reporting
:font facename=Helv size=8x12.
:p.
If you find any bugs in this program, please report them through the OS2World community
(https&colon.//www.os2world.com), with a description of the bug.
:p.
Thanks in advance.

:h1 res=002.Menu Options
:font facename=Helv size=8x12.
:p.
Choose one link from the list below&colon.
:p.
:ul compact.
:li.:link reftype=hd res=010.Game Menu:elink.
:li.:link reftype=hd res=011.Impulse Menu:elink.
:li.:link reftype=hd res=012.Sound Menu:elink.
:li.:link reftype=hd res=013.Options Menu:elink.
:li.:link reftype=hd res=014.Windows Menu:elink.
:li.:link reftype=hd res=015.Help Menu:elink.
:eul.
:p.

:h1 res=003.Game Window
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Game
It's in this window, where you actually play the game. The pieces appear at the gray square in the
center, and then start falling towards one side randomly.
:p.
When some piece overlays any part of the center gray square, the game ends.
:p.
There is also a context menu on this window, with the options from the menu bar, which affect it.

:h1 res=004.Score Window
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Score
There's not much to say about this window. It displays your current score.

:h1 res=005.Next Window
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.Next
This window displays the next piece, and its next impulse direction.
:p.
If you don't want this assistance, you can hide it by clicking its hide button.

:h1 res=006.High Scores Window
:font facename=Helv size=8x12.
:p.
:i2 refid=Win.High Scores
In this window, the game keeps the ten highest scores, and the names of their respective players.
:p.
If you want, you can erase all of them by deleting the file Hiscore.bin. The next time you run
the game, it will create an empty high scores file.

:h1 res=007.Playing WarpTris
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.Playing WarpTris
Well, WarpTris is a rather different (and original) kind of Tetris. Instead of pieces dropping from the top side of the Game window,
they appear at the middle of it, and then start falling towards one side, randomly.
:p.
This behavior has a pseudo-physical explanation&colon. imagine you're in space, where there's no gravity. If you drop
something, and give it an impulse in a given direction, that's the direction it will start moving (or falling), and it will
continue moving that way, unless it encounters something on its way. So in WarpTris, pieces appear at the middle of the Game
window and then receive an impulse, in a random direction, and immediately start falling towards that direction (just like in space).
:p.
The piece can only fall towards four different directions (Up, Down, Left and Right), and you can make
lines on the four sides of the Game window. You lose when some piece covers any square of the middle gray area.
:p.
There are three levels of difficulty, which I call impulses (it makes more sense). What is different between them is
the impulse strength, thus having direct implication on the speed at which the pieces move.
:p.
Finally, when you make a line on one side, only the area from that side of the game window to the
first parallel side of the middle gray square will be evaluated, which opens holes on the adjacent sides
of the Game window. For example, the figure below shows which area will be evaluated, if you make
a line on the left side of the Game window.
:p.
:artwork name='help\Figure.bmp' align=center.
:p.
:nt.
You can only move your piece parallel to the side it is falling to.
:ent.

:h1 res=008.WarpTris Keys
:font facename=Helv size=8x12.
:p.
:i2 refid=HowTo.WarpTris Keys
The valid keys for this game are&colon.
:parml compact tsize=20 break=none.
:pt.Space
:pd.Drop piece
:pt.Keypad Up or Up arrow
:pd.Move Up
:pt.Keypad Down or Down arrow
:pd.Move Down
:pt.Keypad Left or Left arrow
:pd.Move Left
:pt.Keypad Right or Right arrow
:pd.Move Right
:pt.Keypad 5 or Shift (either one)
:pd.Rotate
:pt.P
:pd.Pause / resume
:eparml.
:p.
The following shortcuts work everywhere in the WarpTris window&colon.
:parml compact tsize=20 break=none.
:pt.Ctrl+N
:pd.New game
:pt.Ctrl+P
:pd.Pause / resume the game
:pt.Ctrl+Q
:pd.Quit the current game
:pt.Ctrl+X
:pd.Exit WarpTris
:pt.Ctrl+B
:pd.Background Run on / off
:pt.Ctrl+F
:pd.Frame Controls on / off
:pt.Ctrl+1, 2, 3
:pd.Impulse Donkey, Formula 1, WARP!
:eparml.
:p.
The game also stops when the Game window loses the focus, unless Background Run is on.
:nt.
To use the Keypad keys NUMLOCK must be active.
:ent.

:h1 res=009.Credits
:font facename=Helv size=8x12.
:p.
WarpTris is a 32 bit, Tetris like game for OS/2, written by Paulo Gago da Camara in Azores, Portugal, in 1996.
He made this game with the purpose of learning PM programming.
:p.
Special thanks to his former C/C++ teacher, Dr. Gunther Funk, for the original idea, and to his friend
Jorge Cipriano, for his moral and technical support. He was also the Alpha, Beta and Final version tester.
:p.
The Open Watcom version, with the six language user interface, was prepared by the OS2World community in 2026.

:h1 res=010.Game Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Game
:dl tsize=20.
:dt.:hp2.New:ehp2. (Ctrl+N)
:dd.This option starts a new game. It is not available while a game is running.
:dt.:hp2.Pause Game:ehp2. (Ctrl+P)
:dd.Stops the game. Choose it again to continue.
:dt.:hp2.Quit Game:ehp2. (Ctrl+Q)
:dd.Stops the current game and shows the score. WarpTris stays open.
:dt.:hp2.Exit:ehp2. (Ctrl+X)
:dd.Exits WarpTris at once.
:edl.

:h1 res=011.Impulse Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Impulse
There are three kinds of impulse, which correspond to three different game speeds. This menu
actually represents the level menu.
:p.
Donkey impulse strength is the weakest (slowest) one, and WARP! is the strongest (fastest) one.

:h1 res=012.Sound Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Sound
Toggles the sound on or off.

:h1 res=013.Options Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Options
:dl tsize=20.
:dt.:hp2.Properties:ehp2.
:dd.Displays the properties notebook.
:dt.:hp2.Detail:ehp2.
:dd.High shows a smooth animation when a new piece appears, Medium is the original animation
and Low switches the animation off.
:dt.:hp2.Language:ehp2.
:dd.Changes the language of the menus, windows, dialogs and of this help. The choice is remembered.
:dt.:hp2.Background Run:ehp2. (Ctrl+B)
:dd.When it is on, the game keeps running while another window has the focus.
:dt.:hp2.Frame Controls:ehp2. (Ctrl+F)
:dd.Hides or shows the title bar and the menu of the WarpTris window. Use Ctrl+F again to get them back.
:dt.:hp2.Save settings on exit:ehp2.
:dd.Saves the settings and the window positions in WarpTris.cfg when you exit.
:edl.

:h1 res=014.Windows Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Windows
:dl tsize=20.
:dt.:hp2.High Scores:ehp2.
:dd.Toggles the High Scores window on or off.
:dt.:hp2.Next:ehp2.
:dd.Toggles the Next window on or off.
:dt.:hp2.Score:ehp2.
:dd.Toggles the Score window on or off.
:dt.:hp2.Game:ehp2.
:dd.Toggles the Game window on or off.
:dt.:hp2.Arrange:ehp2.
:dd.Restores the default window positions, for the Game, Score, Next and High Scores windows.
:edl.

:h1 res=015.Help Menu
:font facename=Helv size=8x12.
:p.
:i2 refid=Menus.Help
:dl tsize=20.
:dt.:hp2.General Help:ehp2.
:dd.Displays the general help window.
:dt.:hp2.Help index:ehp2.
:dd.Displays the help index window.
:dt.:hp2.Help on help:ehp2.
:dd.Displays information, which explains how to use help.
:dt.:hp2.About:ehp2.
:dd.Displays the About dialog.
:edl.

:h1 res=016.License Agreement
:font facename=Helv size=8x12.
.br
:hp4.License for WarpTris.:ehp4.
:p.
WarpTris is free software&colon. you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
:p.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file LICENSE.txt for the complete license text.
:p.
(c) Paulo Gago da Camara 1996. (c) 2026 OS2World.
:i1.License Agreement

:h1 res=017.Trademarks
:font facename=Helv size=8x12.
:i1.Trademarks
:p.
The following terms are trademarks of the IBM Corporation, in the United States or other countries&colon.
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Any other mentioned trademarks are owned by their respective owners.
:p.
It is not my intention to infringe any copyright or trademark with this program.
:p.

:euserdoc.
