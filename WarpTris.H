// Defines

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

#define WID_MAIN 1000
#define WID_PARENT 2000
#define WID_SCORE 3000
#define WID_NEXT 4000
#define WID_HIGH 5000
#define WID_LISTBOX 5001
#define WID_NOTE 2001
#define WID_NOTEBOOK 2002

#define MID_GAME 100
#define MID_OPTIONS 200
#define MID_WINDOWS 300
#define MID_LEVEL 500
#define MID_HELP 400
#define MID_SOUND 700
#define MNU_GAME 145
#define MNU_PARENT 147
#define CMD_SOUNDON 701
#define CMD_SOUNDOFF 702
#define CMD_PROPERTIES 201
#define CMD_GAMEWINDOW 301
#define CMD_SCOREWINDOW 302
#define CMD_HIGHWINDOW 303
#define CMD_NEXTWINDOW 304
#define CMD_PINFO 401
#define CMD_EXIT 101
#define CMD_NEWGAME 102
#define CMD_BEGINNER 501
#define CMD_INTERMEDIATE 502
#define CMD_EXPERT 503
#define CMD_ARRANGE 305
#define CMD_GENERALHELP 402
#define CMD_HELPINDEX 403
#define CMD_HELPONHELP 404
#define TID_TIMER (TID_USERMAX-1)
#define TID_LOGO  (TID_USERMAX-2)
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
#define LV_BEGINNER 650
#define LV_INTERMEDIATE 400
#define LV_EXPERT 250
#define APPNORMAL 0
#define USERQUIT -2
#define FULL 1
#define EMPTY 8
#define ID_INIPATH 343
#define SID_OVER 670
#define SID_DROP 671
#define SID_HIGH 672
#define SID_POP  673
#define SID_LINE 674
#define SC_PIECESCORE 25
#define SC_LINESCORE 100


// Constants
const MAX_FIGURE_X=5;
const MAX_FIGURE_Y=5;
const LINES=20;
const COLUMNS=20;
enum  DIR{UP=1, DOWN=2, RIGHT=3, LEFT=4, ALL=5};


// Figures
INT FIGURES[7][MAX_FIGURE_X][MAX_FIGURE_Y] = {{0,0,0,0,0, 0,1,1,1,0, 0,1,0,0,0, 0,0,0,0,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,1,1,1,0, 0,0,0,1,0, 0,0,0,0,0 ,0,0,0,0,0},
                                              {9,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,1,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,0,1,0, 0,0,1,1,0, 0,0,1,0,0 ,0,0,0,0,0},
                                              {9,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0 ,0,0,0,0,0}};

#define DID_HIGHSCORE               5500
#define DID_OK                      1

#define DID_PAGE1                   900
#define DRB_ON                      901
#define DRB_OFF                     902
#define DID_PAGE2                   1500
#define DCB_GAME                    1502
#define DCB_SCORE                   1503
#define DCB_NEXT                    1504
#define DCB_HIGH                    1505
#define DID_PAGE3 256
#define DRB_FORMULA1 259
#define DRB_WARP 260
#define EID_NAME 5502
#define BID_SMALLOGO 5502
#define DID_PINFO 434

/* defines for help panels */

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
#define HID_PINFO         15
#define HID_GENERALHELP   15
#define HID_HELPINDEX     15
#define HID_HELPONHELP    15

#define DLG_PINFO 256
#define DID_PAGE4 937
#define BID_SMALLLOGO 5502
#define DRB_DONKEY 258
#define DID_GAMEOVER 3423
#define BID_GAMEOVER 3425
#define DBT_BITMAP 3425
#define DID_EXIT 983
#define PB_NO 988
#define DBI_EXIT 986
