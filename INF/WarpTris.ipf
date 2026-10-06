:userdoc.
:title.WarpTris Information
:h1 res=001.Notices
:h2 res=008.License Agreement
.br
:hp4.License Agreement for WarpTris.:ehp4.
:p.
For the purposes of this license agreement, the files that come with WarpTris
(WarpTris.EXE, Scores.INI, WarpTris.INI, Pop.WAV, High.WAV, Over.WAV, WarpTris.HLP, WarpTris.INF, Install.CMD, README)
.br
will be referred from now on, as WarpTris.
:p.
This program is PostcardWare/FreeWare, which means you can Use and Distribute it :hp8.FREELY:ehp8.,
provided you Don't Charge Any Money for it, nor make any Modifications to it.
:p.
The Author/Programmer does not guarantee anything about this game, nor is responsible for
any damage done to your Software and/or Hardware by it.
:p.
The licensee agrees to use WarpTris at his or her own risk, and agrees to accept all
liabilities arising from its use, including all claims by third parties, without
recourse to the Author/Programmer.
:p.
THERE ARE NO WARRANTIES, EXPRESS OR IMPLIED, OF ANY SORT.
.br
BY YOUR USE OF THE PROGRAM YOU AGREE TO THE TERMS OF THIS LICENSE.
.br
:p.
(c) Paulo Gago da Camara 1996.
:h2 res=009.Trademarks
:p.
The following terms are trademarks of the IBM Corporation, in the United States or other countries:
:sl compact.
:li.IBM
:li.OS/2
:li.Presentation Manager (PM)
:esl.
:p.
Any other mentioned Trademarks are owned by their respective owners.
:p.
It is not my intention to infract any copyright, or trademark with this program.
:p.
:h1 res=002.WarpTris History
:h2 res=010.History
:p.The original idea of the game belongs to my former teacher, Dr. Gunther Funk, who taught me C/C++
for a year at the University of Azores, where I study Mathematics/Computer Science.
:p.Initialy I developed a DOS version of the game, with another colleague, with the purpose of academic evaluation on C++.
:p.Later, on the summer, came the idea of developing a full version of the game, for my favorite OS ( OS/2 &colon.-) ),
this time the intention was to learn PM programming, so this game is also my first PM program.
:p.Since this is my first PM program I decided to make it FREEWARE, or better PostcardWare, which means I am
looking forward to receive my first Postcard from someone around the World, who uses this game and likes it,
but this is :hp8.NOT REQUIRED:ehp8. although it would be nice. I am
open to suggestions, for next releases. I am also saving to buy books on PM programming,
so any contribution you would like to send me, (which I assure you will be spent exclusively with OS/2)
will be very much appreciated, again this is :hp8.NOT REQUIRED:ehp8..
:p.
If you want, you can E-mail me at :hp4.pcamara@geocities.com:ehp4. or :hp4.dm03mi@antero.uac.pt:ehp4.,
although I would prefer a postcard (or both).
:p.
You can also visit my personal Home Page at Geocities, the URL follows:
.br
:hp4.
http&colon.&slash.&slash.www.geocities.com/SiliconValley/Heights/1856
:ehp4.
.br
There you'll find some information about me, and the latest version of WarpTris.
:p.
You can send your Postcard/Contribution to the address below:
:p.
:hp4.
Rua Joao Chagas, 32
.br
9560 Rosario-Lagoa
.br
S.Miguel-Azores
.br
PORTUGAL
:ehp4.
:p.
Thanks in advance.
.br
:p.
Paulo Gago da Camara
.br
:hp4.
pcamara@geocities.com
.br
dm03mi@antero.uac.pt
:ehp4.
:h1 res=003.Playing WarpTris
:h2 res=004.Philosophy of the Game
:p.
Well, WarpTris is a rather different (and original) kind of Tetris, instead of pieces dropping from the top side of the Game window,
they appear at the middle of it, and then start falling towards one side, randomly.
:p.
This behavior, has a pseudo-Physical explanation: imagine your in Space, where there's no gravity, if you drop
something, and give it an impulse in a given direction, that's the direction it will start moving (or falling), and it will
continue moving that way, unless it encounters something on its way. So on WarpTris, pieces appear at the middle of the Game
window and then receive an impulse, in a random direction, and immediately start falling on that direction (just like in Space).
:p.
The piece can only fall towards four different directions (Up, Down, Left and Right), and you can make
lines on the four sides of the Game window. You loose when some piece covers any square on the middle gray area.
:p.
There are three levels of difficulty, which I call impulses (it makes more sense). What is different between them is
the impulse strength, thus having direct implication on the speed at which the pieces move.
:p.
Finally, when you make a line on one side, only the area from that side of the game window, to the
first parallel side of the middle gray square will be evaluated, which opens holes on the adjacent sides
of the Game window. For example, the figure below shows which area will be evaluated, if you make
a line on the left side of the Game window.
:p.
:artwork name='Figure.bmp' align=center.
:p.
:nt.
You can only move your piece parallelly to the side it is falling to.
:ent.
:h2 res=005.WarpTris Keys
:p.
The valid keys for this game are:
:parml compact tsize=20 break=none.
:pt.Space
:pd.Drop piece
:pt.Keypad Up
:pd.Move Up
:pt.Keypad Down
:pd.Move Down
:pt.Keypad Left
:pd.Move Left
:pt.Keypad Right
:pd.Move Right
:pt.Keypad 5
:pd.Rotate
:eparml.
:p.
To pause the game just change the focus to another window, or press 'P'.
:nt.
To use the Keypad keys NUMLOCK must be active.
:ent.
:h2 res=015.WarpTris User Interface
:p.WarpTris user interface is composed of five windows. The first is the Main window, which
contains the Menu bar and the other four windows.
:p.
The Game window is where you really play the game, the Score window tells you the score, the Next
window gives you the next piece, and its next impulse, and finally the High Scores window displays
a listbox control with the top ten scores.
:p.
All of these windows are optional, and thus you can disable them. Also there are
context menus on the Main and Game windows, with options relative to them. I also included an Arrange,
option do restore the default position of the four child windows.

:h1 res=006.Thanks
:h2 res=012.Special thanks
:p. Special thanks to my friend, and Team OS/2 member, Jorge Cipriano, for giving me both moral and technical support, during the
making of this game. He was also the Alpha, Beta, and Final version tester.
:p.
I thank him specially for being the person who first showed me OS/2, my OS of election for PC.
:p.
Remember once you've seen the light (a.k.a. OS/2), there's no turning back!
:p.
I also would like to thank my girlfriend Nelia, for her support, and for providing the "Game Over"
giggle soundtrack.
:p.
This game is dedicated to her.

:h1 res=013.About
:h2 res=011.About the Programmer
:p. I am a 3rd grade Mathematics/Computer Science student at the University of Azores.
I'm 22 years old, and I use and program computers since I was 12, I know OS/2 for about
eleven months, I started programming in C/C++ during this year, and I do real PM programming
for about a month, and I must say I love it.
:p.
I'm also a proud Team OS/2 member.

:h1 res=023.Bug Reporting
:p.
If you find any bugs, on this program, please E-mail me at :hp4.pcamara@geocities.com:ehp4. or :hp4.dm03mi@antero.uac.pt:ehp4.,
with a description of the bug.
:p.
I will try my best to correct them, and update the version of the program on the Internet.
:p.
Thanks in advance.

:h1 res=014.Please Read This!
:p.If you use this game and like it, please send me a Postcard!
.br
This is :hp8.NOT REQUIRED:ehp8., but it would be nice. &colon.-)
:p.If you want you can also send me a contribution, to help me buy PM programming books.
.br
Again, this is :hp8.NOT REQUIRED:ehp8..
:p.
If you want, you can E-mail me at :hp4.pcamara@geocities.com:ehp4. or :hp4.dm03mi@antero.uac.pt:ehp4., although I would prefer
a postcard (or both).
:p.
I assure you that any received contribution will be exclusively spent with OS/2.
:p.
:link reftype=hd res=020.(How do you know I'll honor the above sentence?):elink.
:p.
You can send your Postcard/Contribution to the address below:
:p.
:hp4.Rua Joao Chagas, 32
.br
9560 Rosario-Lagoa
.br
S.Miguel-Azores
.br
PORTUGAL
:ehp4.
:p.
Thanks in advance.
:p.
Paulo Gago da Camara
.br
:hp4.
pcamara@geocities.com
.br
dm03mi@antero.uac.pt
:ehp4.


:* hidden headings
:h1 hide res=020.How do I Know?
:p.
You don't. &colon.-)
:euserdoc.

