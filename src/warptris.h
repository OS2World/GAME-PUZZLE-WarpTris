/* WarpTris - resource and message identifiers.
   Only preprocessor definitions here: this file is also read by the
   resource compiler. */

#ifndef WARPTRIS_H
#define WARPTRIS_H

#define VERSION_STR "1.20"

/* Bitmap resources */
#define BID_ON1 1
#define BID_ON2 2
#define BID_ON3 3
#define BID_ON4 4
#define BID_ON5 5
#define BID_ON6 6
#define BID_ON7 7
#define BID_LOGO 950

#define BID_ZERO 10
#define BID_ONE 11
#define BID_TWO 12
#define BID_THREE 13
#define BID_FOUR 14
#define BID_FIVE 15
#define BID_SIX 16
#define BID_SEVEN 17
#define BID_EIGHT 18
#define BID_NINE 19
#define BID_OFF 20

#define BID_UP 30
#define BID_DOWN 31
#define BID_LEFT 32
#define BID_RIGHT 33
#define BID_NEXTBACKGROUND 34

/* Window identifiers */
#define WID_MAIN 1000
#define WID_PARENT 2000
#define WID_SCORE 3000
#define WID_NEXT 4000
#define WID_HIGH 5000
#define WID_LISTBOX 5001
#define WID_NOTE 2001
#define WID_NOTEBOOK 2002

/* Context menu resources */
#define MNU_GAME 145
#define MNU_PARENT 147

/* Game menu (100-199) */
#define IDM_NEWGAME 101
#define IDM_PAUSE 102
#define IDM_QUIT 103
#define IDM_EXIT 104

/* Options menu (200-299) */
#define IDM_PROPERTIES 201
#define IDM_HIGHDET 210
#define IDM_MEDIUMDET 211
#define IDM_LOWDET 212
#define IDM_BACKGRND 220
#define IDM_FRAME 221
#define IDM_SAVEONEXIT 230

/* Language items (300-399) */
#define IDM_LANG_EN 300
#define IDM_LANG_ES 301
#define IDM_LANG_NL 302
#define IDM_LANG_DE 303
#define IDM_LANG_FR 304
#define IDM_LANG_IT 305

/* Windows menu */
#define IDM_HIGHWINDOW 410
#define IDM_NEXTWINDOW 411
#define IDM_SCOREWINDOW 412
#define IDM_GAMEWINDOW 413
#define IDM_ARRANGE 414

/* Impulse (level) menu */
#define IDM_BEGINNER 501
#define IDM_INTERMEDIATE 502
#define IDM_EXPERT 503

/* Sound menu */
#define IDM_SOUNDON 701
#define IDM_SOUNDOFF 702

/* Help menu (900-999) */
#define IDM_GENERALHELP 901
#define IDM_HELPINDEX 902
#define IDM_HELPONHELP 903
#define IDM_ABOUT 999

/* Submenu cascade identifiers (1000-1099) */
#define IDM_SUBMENU_GAME 1001
#define IDM_SUBMENU_IMPULSE 1002
#define IDM_SUBMENU_SOUND 1003
#define IDM_SUBMENU_OPTIONS 1004
#define IDM_SUBMENU_WINDOWS 1005
#define IDM_SUBMENU_HELP 1006
#define IDM_SUBMENU_DETAIL 1007
#define IDM_SUBMENU_LANGUAGE 1008

/* Impulse timer delays [ms] */
#define LV_BEGINNER 650
#define LV_INTERMEDIATE 400
#define LV_EXPERT 250

/* Timers */
#define TID_TIMER (TID_USERMAX-1)
#define TID_LOGO  (TID_USERMAX-2)

/* Private window messages */
#define WM_VERIFY        (WM_USER+1)
#define WM_DROPED        (WM_USER+2)
#define WM_GAMEOVER      (WM_USER+3)
#define WM_CREATEOBJECTS (WM_USER+4)
#define WM_PAUSEGAME     (WM_USER+5)
#define WM_RESUMEGAME    (WM_USER+6)
#define WM_PLAYSOUND     (WM_USER+7)
#define WM_NEWGAME       (WM_USER+8)
#define WM_CHANGELEVEL   (WM_USER+9)
#define WM_NEXT          (WM_USER+10)
#define WM_CREATELB      (WM_USER+11)
#define WM_POP           (WM_USER+12)
#define WM_DROP          (WM_USER+13)
#define WM_OVER          (WM_USER+14)
#define WM_HIGH          (WM_USER+15)
#define WM_CREATETHREAD  (WM_USER+16)
#define WM_BEEP          (WM_USER+17)
#define WM_SETFIRST      (WM_USER+18)
#define WM_LINE          (WM_USER+19)
#define WM_RELABEL       (WM_USER+20)
#define WM_QUITGAME      (WM_USER+21)

#define APPNORMAL 0
#define USERQUIT -2
#define FULL 1
#define EMPTY 8
#define SID_OVER 670
#define SID_DROP 671
#define SID_HIGH 672
#define SID_POP  673
#define SID_LINE 674
#define SC_PIECESCORE 25
#define SC_LINESCORE 100

/* Dialog identifiers */
#define DID_HIGHSCORE               5500

#define DID_PAGE1                   900
#define DRB_ON                      901
#define DRB_OFF                     902
#define DID_PAGE2                   1500
#define DCB_GAME                    1502
#define DCB_SCORE                   1503
#define DCB_NEXT                    1504
#define DCB_HIGH                    1505
#define DID_PAGE3                   256
#define DRB_FORMULA1                259
#define DRB_WARP                    260
#define DRB_DONKEY                  258
#define EID_NAME                    5502
#define BID_SMALLOGO                5502
#define DID_GAMEOVER                3423
#define BID_GAMEOVER                3425
#define DBT_BITMAP                  3425
#define DID_EXIT                    983
#define DBI_EXIT                    986

/* Static text / group box controls that get translated at run time */
#define DST_NAMEGROUP               5501
#define DST_NAMETEXT                5503
#define DST_PAGE1GROUP              903
#define DST_PAGE2GROUP              1501
#define DST_PAGE3GROUP              257
#define DST_EXITTEXT                987

/* About dialog */
#define IDD_ABOUT                   434

/* Help panels */
#define HID_MAIN         432
#define HID_SUBTABLE     433
#define HID_GENERAL        1
#define HID_NEW           10
#define HID_EXIT          10
#define HID_BEGGINER      11
#define HID_INTERMEDIATE  11
#define HID_EXPERT        11
#define HID_SOUNDON       12
#define HID_SOUNDOFF      12
#define HID_PROPERTIES    13
#define HID_NEXTWINDOW    14
#define HID_HIGHWINDOW    14
#define HID_SCOREWINDOW   14
#define HID_GAMEWINDOW    14
#define HID_ARRANGE       14
#define HID_ABOUT         15
#define HID_GENERALHELP   15
#define HID_HELPINDEX     15
#define HID_HELPONHELP    15

#endif /* WARPTRIS_H */
