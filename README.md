# WarpTris for ArcaOS / eComStation / OS/2

WarpTris is a Tetris like game for the OS/2 Presentation Manager. Instead of
pieces dropping from the top, they appear in the middle of the game window and
start falling towards one side of it, randomly, so lines can be made all around
the window.

Originally written by Paulo Gago da Camara in 1996.

## Version

1.20

## License

GNU General Public License v3 - see `doc/LICENSE.txt`

## Features

- Four windows (Game, Score, Next, High Scores) inside the WarpTris window
- Three impulses (levels): Donkey, Formula 1, WARP!
- High score table with name entry (`Hiscore.bin`)
- 6-language UI: English, Spanish, Dutch, German, French, Italian
- Rotate with keypad 5 or either Shift key
- Online help in the six languages
- Sound effects (OS/2 Multimedia, loaded at run time, optional)
- Pause Game (Ctrl+P), Quit Game (Ctrl+Q), Exit (Ctrl+X)
- Background Run (Ctrl+B) and Frame Controls (Ctrl+F)
- Detail level (High / Medium / Low) for the piece animation
- Settings saved to `WarpTris.cfg`

## Compile Tools

- Open Watcom 2.0 (`wmake`, `wpp386`, `wlink`, `wrc`, `wipfc`)
- OS/2 Toolkit 4.5

## Build

```
compile-wat.cmd
```

Output: `bin\WarpTris.exe`, `bin\WarpTris_xx.hlp` and `bin\sounds\`

## Requirements

- OS/2 Warp 4, eComStation, or ArcaOS
- 32-bit Presentation Manager
- OS/2 Multimedia (optional, for sound effects)

## Authors

- Original: Paulo Gago da Camara - 1996
- OS/2 port: OS2World community - 2026

## Links

- OS2World: https://www.os2world.com
