// This is the main program file.
// You have permission to distribute, modify, copy, use parts of this code in
// other programs, provided you don't charge any money for it, and always
// distribute the source code, this is a way of helping novice OS/2 programmers.
//
// ** WARNING **     ** WARNING **           ** WARNING **
// Remember this is my first PM program, so there are some bits and parts that
// could be written more effectively, after all I'm also a novice OS/2 programmer :)
// ** WARNING **     ** WARNING **           ** WARNING **
//
// (c)Paulo Gago da Camara 1996
//
// Licensed under the GNU General Public License v3 (see doc\LICENSE.txt).
//
// 2026: Ported to Open Watcom by the OS2World community. Standardized menus,
//       six language user interface, WarpTris.cfg / Hiscore.bin, pause,
//       background run, frame controls, per language help, About dialog.


// defines
#define INCL_WIN // Include Win*  API functions
#define INCL_GPI // Include Gpi*  API functions
#define INCL_DOS // Include Dos*  API functions

// includes
#include <os2.h> // os2 API header file

#include <stdio.h> // standard C includes
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "warptris.h" // various defines for the program
#include "lang.h"     // run time language table

#pragma off(unreferenced)
static const char bldlevel[] =
    "@#Paulo Gago da Camara:1.20#@##1## 06 Oct 2026 12:00:00      "
    "ARCAOS:::0::::@@WarpTris - Tetris like game for OS/2\r\n\x1a";
#pragma on(unreferenced)

// Forward classes definitions
class Board;
class Figure;
class DigitalPanel;
class HighScore;

// Constants
const int MAX_FIGURE_X=5;
const int MAX_FIGURE_Y=5;
const int LINES=20;
const int COLUMNS=20;
#define SCALE 2              // size factor of the inner windows
#define CELL  (16*SCALE)     // size of one square in pixels
enum  DIR{UP=1, DOWN=2, RIGHT=3, LEFT=4, ALL=5};

// Figures
INT FIGURES[7][MAX_FIGURE_X][MAX_FIGURE_Y] = {{0,0,0,0,0, 0,1,1,1,0, 0,1,0,0,0, 0,0,0,0,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,1,1,1,0, 0,0,0,1,0, 0,0,0,0,0 ,0,0,0,0,0},
                                              {9,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,1,0 ,0,0,0,0,0},
                                              {0,0,0,0,0, 0,0,0,1,0, 0,0,1,1,0, 0,0,1,0,0 ,0,0,0,0,0},
                                              {9,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0 ,0,0,0,0,0}};

// Structures that belong to windows

typedef struct {
                ULONG saveonexit, detaillevel, current_lang; // required cfg fields (plan, section 10)
                ULONG sound, high, game, next, score, level;
                RECTL rclParent, rclGame, rclScore, rclNext, rclHigh;
                ULONG bgrun;
               } SETTINGSDATA;
typedef SETTINGSDATA *PSETTINGSDATA; // structure that contains the various window
                                     // positions, so that the program can
                                     // remember where the windows were, since
                                     // last time it was executed.

typedef struct {
                HWND hwndObject, hwndGame;
                BOOL threadRunning;
                TID  tid;
                PFNTHREAD pfThread;
                PSETTINGSDATA psd;
               } OBJECTWINDOWDATA;
typedef OBJECTWINDOWDATA *POBJECTWINDOWDATA; // sound thread object window data

typedef struct {
                HWND hwndFrame, hwndNoteBook, hwndDlg1, hwndDlg2, hwndDlg3;
                ULONG ulPage1ID, ulPage2ID, ulPage3ID;
               } PROPERTIESWINDOWDATA; // properties notebook window data

typedef PROPERTIESWINDOWDATA *PPROPERTIESWINDOWDATA;


typedef struct {
                HWND hwndFrame, hwndListBox;
                PSETTINGSDATA psd;
               } HIGHWINDOWDATA; // private high scores window data

typedef HIGHWINDOWDATA *PHIGHWINDOWDATA;


typedef struct {
                 HWND hwndFrame;
                 HBITMAP hbmp[7];
                 HBITMAP hbmpDirection[4];
                 HBITMAP hbmpBackground;
                 HPS hps;
                 PSETTINGSDATA psd;
                } NEXTWINDOWDATA;

typedef NEXTWINDOWDATA *PNEXTWINDOWDATA; // private next window data

typedef struct {
                HWND hwndNext, hwndGame;
                PSZ pszName;
                DigitalPanel *digitalPanel;
                Figure *figure;
                HighScore *highScore;
                DIR dir;
               } SHAREDDATA;

typedef SHAREDDATA *PSHAREDDATA; // shared data between various windows

typedef struct {
                HWND hwndFrame, hwndParent;
                PSETTINGSDATA psd;
               } SCOREWINDOWDATA;

typedef SCOREWINDOWDATA *PSCOREWINDOWDATA; // private score window data

typedef struct {
                HWND hwndGame,
                     hwndScore,
                     hwndMenu,
                     hwndFrame,
                     hwndNext,
                     hwndHigh,
                     hwndNote,
                     hwndPop,
                     hwndPopGame,
                     hwndTitleBar,   // frame controls, hidden by Frame Controls
                     hwndSysMenu,
                     hwndMinMax,
                     hwndPark;       // parking window for the hidden frame controls
                PSETTINGSDATA psd;
                BOOL frameHidden,
                     exitNow;
               } PARENTWINDOWDATA;

typedef PARENTWINDOWDATA *PPARENTWINDOWDATA; // WarpTris window data

typedef struct {
                HPS     hps;
                HBITMAP hbmp[7];
                HWND    hwndFrame, hwndParent, hwndPop;
                ULONG   ulTimerID;
                INT     currentBitmapID;
                BOOL    hasFocus, gamePaused, gamePlaying;
                DIR     direction;
                Board   *board;
                Figure  *figure;
                PSETTINGSDATA psd;
               } WINDOWDATA;

typedef WINDOWDATA *PWINDOWDATA; // private game window data

// Prototypes for Window and Dialog Procedures
MRESULT EXPENTRY     MainWindowProc(HWND, ULONG, MPARAM, MPARAM); // Game window
MRESULT EXPENTRY     LogoWindowProc(HWND, ULONG, MPARAM, MPARAM); // Logo window
MRESULT EXPENTRY   ParentWindowProc(HWND, ULONG, MPARAM, MPARAM); // WarpTris window
MRESULT EXPENTRY    ScoreWindowProc(HWND, ULONG, MPARAM, MPARAM); // Score window
MRESULT EXPENTRY     NextWindowProc(HWND, ULONG, MPARAM, MPARAM); // Next window
MRESULT EXPENTRY     HighWindowProc(HWND, ULONG, MPARAM, MPARAM); // High Scores window
MRESULT EXPENTRY NoteBookWindowProc(HWND, ULONG, MPARAM, MPARAM); // Properties window
MRESULT EXPENTRY   ObjectWindowProc(HWND, ULONG, MPARAM, MPARAM); // Object window used
                                                                  // on the sound thread
MRESULT EXPENTRY        NameDlgProc(HWND, ULONG, MPARAM, MPARAM); // High Score Dialog
MRESULT EXPENTRY       Page1DlgProc(HWND, ULONG, MPARAM, MPARAM); // Notebook page 1 Dialog
MRESULT EXPENTRY       Page2DlgProc(HWND, ULONG, MPARAM, MPARAM); // Notebook page 2 Dialog
MRESULT EXPENTRY       Page3DlgProc(HWND, ULONG, MPARAM, MPARAM); // Notebook page 3 Dialog
MRESULT EXPENTRY       AboutDlgProc(HWND, ULONG, MPARAM, MPARAM); // About Dialog
MRESULT EXPENTRY    GameOverDlgProc(HWND, ULONG, MPARAM, MPARAM); // Game Over Dialog
MRESULT EXPENTRY        ExitDlgProc(HWND, ULONG, MPARAM, MPARAM); // Exit Game Dialog
// Sound Thread
VOID    _System         SoundThread(HWND game); // Function executed by the sound thread

// Other functions prototypes
VOID    DrawSquareOnGame(HWND, LONG, LONG, INT); // Draws a square on the game window
VOID    DrawSquareOnNext(HWND, LONG, LONG, INT); // Draws a square on the next window
VOID         ClearSquare(HWND, LONG, LONG); // Clears a square on the game window
VOID          InitWindow(HWND); // Initialize the game window position and client area
VOID         PaintWindow(HWND); // Paints the game window
VOID           Animation(HWND); // Does the animation of the gray square
VOID           PlaySound(ULONG); // Plays a given sound
VOID           OpenPopFile(VOID);// Opens the pop.wav file
VOID          ClosePopFile(VOID);// Closes the pop.wav file
VOID          LogoWindow(VOID); // Shows the logotype at startup
VOID        ReadSettings(PSETTINGSDATA); // Reads the settings saved on WarpTris.cfg
VOID        SaveSettings(PSETTINGSDATA); // Saves the settings on WarpTris.cfg
VOID      ArrangeWindows(PSETTINGSDATA, LONG, LONG); // Restores the default window positions
VOID      SetHelpLanguage(HWND, INT); // (Re)creates the help instance for a language
INT               Random(INT); // Gives a random number in the range [0..argument]
DIR         NewDirection(VOID);// Gives a new direction randomly
HWND        ParentClient(VOID); // Client window of the WarpTris (parent) window
VOID          SetLanguage(PPARENTWINDOWDATA, INT); // Switches the user interface language
VOID       UpdateGameMenus(BOOL, BOOL); // Enables/disables the game dependent menu items

// Include the objects that were defined on top
#include "Board.H"
#include "Figure.H"
#include "Digital.H"
#include "HighScore.H"

// Global variables
static CHAR  szExeDir[CCHMAXPATH];   // directory of the executable (with trailing \)
static BOOL  cfgLoaded = FALSE;      // TRUE if WarpTris.cfg was read
static HWND  hwndHelpInst = NULLHANDLE;
static CHAR  szHelpLib[CCHMAXPATH];

typedef ULONG (APIENTRY *PFNMCISENDSTRING)(PSZ, PSZ, USHORT, HWND, USHORT);
static PFNMCISENDSTRING pfnMciSendString = NULL; // MDM.DLL is loaded dynamically, so that
                                                 // the game starts without MMPM/2 installed

// Program entry point
INT main()
{
 HAB   hab; // Handle of the anchor block
 HMQ   hmq; // Handle of the Message Queue
 QMSG  qmsg; // Message structure

 HWND  hwndFrame, // Handles of the windows used on the main thread
       hwndClient,
       hwndParentFrame,
       hwndParentClient,
       hwndScoreFrame,
       hwndScoreClient,
       hwndNextFrame,
       hwndNextClient,
       hwndHighFrame,
       hwndHighClient,
       hwndNoteFrame,
       hwndNoteClient;

 PSZ   pszClassName = "WarpTris for OS/2";
 PSZ   pszParentTitle = "WarpTris";
 PSZ   pszParentClassName = "Parent Class";
 PSZ   pszScoreClassName= "Score Window Class";
 PSZ   pszNextClassName = "Next Window Class";
 PSZ   pszHighClassName = "High Window Class";
 PSZ   pszNoteClassName = "Properties Window Class";
  // Various windows creation flags
 ULONG ulParentCreateFlags = FCF_SYSMENU       |   FCF_TITLEBAR     |
                             FCF_SIZEBORDER    |   FCF_TASKLIST     |
                             FCF_MINBUTTON     |   FCF_MAXBUTTON    |
                             FCF_MENU          |   FCF_ICON         |
                             FCF_ACCELTABLE;
 ULONG ulCreateFlags       = FCF_TITLEBAR | FCF_DLGBORDER | FCF_SHELLPOSITION | FCF_HIDEBUTTON;
 ULONG ulScoreCreateFlags  = FCF_TITLEBAR | FCF_DLGBORDER | FCF_SHELLPOSITION | FCF_HIDEBUTTON;
 ULONG ulNextCreateFlags   = FCF_TITLEBAR | FCF_DLGBORDER | FCF_SHELLPOSITION | FCF_HIDEBUTTON;
 ULONG ulHighCreateFlags   = FCF_TITLEBAR | FCF_DLGBORDER | FCF_SHELLPOSITION | FCF_HIDEBUTTON;
 ULONG ulNoteCreateFlags   = FCF_TITLEBAR | FCF_DLGBORDER | FCF_SHELLPOSITION |
                             FCF_SYSMENU  | FCF_HIDEBUTTON;

 ULONG  appState = APPNORMAL; // Used to control the external while loop that
                              // lets us intercept all the manners that an user can
                              // use to close our application, specially those who
                              // don't get caught in the parent window procedure.
 PSHAREDDATA sd;
 PPARENTWINDOWDATA pwd;
 LONG  cxScreen, cyScreen, winW, winH, winX, winY;
 RECTL rcl;
 PFN   pfn;
 HMODULE hmodMDM;
 CHAR  errbuf[64];

 if(bldlevel[0] != '@') // keeps the BLDLEVEL string in the executable
    return(1);

 srand((unsigned) time(NULL));

 // Directory of the executable: sounds and help files are searched there
 {
  PTIB ptib;
  PPIB ppib;
  CHAR *p;

  szExeDir[0] = '\0';
  if(DosGetInfoBlocks(&ptib, &ppib) == 0)
     if(DosQueryModuleName(ppib->pib_hmte, sizeof(szExeDir), szExeDir) == 0)
        {
         p = strrchr(szExeDir, '\\');
         if(p) *(p+1) = '\0';
          else szExeDir[0] = '\0';
        }
 }

 LogoWindow(); //Display Logotype

 hab = WinInitialize(0); // Initialize PM and get an HAB
 hmq = WinCreateMsgQueue(hab, 25); // Create the Msg Queue

 // MDM.DLL needs PM to be initialized, so it is loaded here
 if(DosLoadModule(errbuf, sizeof(errbuf), (PSZ) "MDM", &hmodMDM) == 0)
    if(DosQueryProcAddr(hmodMDM, 0, (PSZ) "mciSendString", &pfn) == 0)
       pfnMciSendString = (PFNMCISENDSTRING) pfn;

  // Register the main thread window classes
 WinRegisterClass(hab,
                  pszParentClassName,
                  ParentWindowProc,
                  CS_SIZEREDRAW | CS_CLIPCHILDREN,
                  4);

 WinRegisterClass(hab,
                  pszClassName,
                  MainWindowProc,
                  CS_SIZEREDRAW,
                  12);

 WinRegisterClass(hab,
                  pszScoreClassName,
                  ScoreWindowProc,
                  CS_SIZEREDRAW,
                  8);

 WinRegisterClass(hab,
                  pszNextClassName,
                  NextWindowProc,
                  CS_SIZEREDRAW,
                  8);

 WinRegisterClass(hab,
                  pszHighClassName,
                  HighWindowProc,
                  CS_SIZEREDRAW,
                  8);

 WinRegisterClass(hab,
                  pszNoteClassName,
                  NoteBookWindowProc,
                  CS_SIZEREDRAW,
                  4);
   // Next create this thread standard windows.
   // The Warptris client window is the parent off all the other frame windows.
   // It is created invisible and shown when everything is in place.
 hwndParentFrame = WinCreateStdWindow(HWND_DESKTOP,
                                      WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                      &ulParentCreateFlags,
                                      pszParentClassName,
                                      pszParentTitle,
                                      NULL,
                                      NULLHANDLE,
                                      WID_PARENT,
                                      &hwndParentClient);

 pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParentClient, 0);
 pwd->hwndTitleBar = WinWindowFromID(hwndParentFrame, FID_TITLEBAR);
 pwd->hwndSysMenu  = WinWindowFromID(hwndParentFrame, FID_SYSMENU);
 pwd->hwndMinMax   = WinWindowFromID(hwndParentFrame, FID_MINMAX);
 pwd->hwndMenu     = WinWindowFromID(hwndParentFrame, FID_MENU);
 pwd->hwndPark     = WinCreateWindow(HWND_OBJECT, WC_FRAME, "", 0L, 0, 0, 0, 0,
                                     NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Size the main window: 1024x768 centered (or the whole screen if smaller)
 cxScreen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
 cyScreen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
 winW = (cxScreen >= 1024L) ? 1024L : cxScreen;
 winH = (cyScreen >= 768L)  ? 768L  : cyScreen;
 winX = (cxScreen - winW) / 2;
 winY = (cyScreen - winH) / 2;
 WinSetWindowPos(hwndParentFrame, HWND_TOP, winX, winY, winW, winH, SWP_SIZE | SWP_MOVE);

  // Without a settings file, the windows are arranged in the middle of the client area
 rcl.xLeft = 0; rcl.yBottom = 0; rcl.xRight = winW; rcl.yTop = winH;
 WinCalcFrameRect(hwndParentFrame, &rcl, TRUE);
 if(!cfgLoaded)
    ArrangeWindows(pwd->psd, rcl.xRight - rcl.xLeft, rcl.yTop - rcl.yBottom);

 hwndFrame = WinCreateStdWindow(hwndParentClient,
                                WS_VISIBLE,
                                &ulCreateFlags,
                                pszClassName,
                                tr(STR_WIN_GAME),
                                NULL,
                                NULLHANDLE,
                                WID_MAIN,
                                &hwndClient);

 hwndScoreFrame = WinCreateStdWindow(hwndParentClient,
                                     WS_VISIBLE,
                                     &ulScoreCreateFlags,
                                     pszScoreClassName,
                                     tr(STR_WIN_SCORE),
                                     NULL,
                                     NULLHANDLE,
                                     WID_SCORE,
                                     &hwndScoreClient);

 hwndNextFrame = WinCreateStdWindow(hwndParentClient,
                                    WS_VISIBLE,
                                    &ulNextCreateFlags,
                                    pszNextClassName,
                                    tr(STR_WIN_NEXT),
                                    NULL,
                                    NULLHANDLE,
                                    WID_NEXT,
                                    &hwndNextClient);

 hwndHighFrame = WinCreateStdWindow(hwndParentClient,
                                    WS_VISIBLE,
                                    &ulHighCreateFlags,
                                    pszHighClassName,
                                    tr(STR_WIN_HIGH),
                                    NULL,
                                    NULLHANDLE,
                                    WID_HIGH,
                                    &hwndHighClient);

 hwndNoteFrame = WinCreateStdWindow(hwndParentClient,
                                    0,
                                    &ulNoteCreateFlags,
                                    pszNoteClassName,
                                    tr(STR_WIN_PROPS),
                                    NULL,
                                    NULLHANDLE,
                                    WID_NOTE,
                                    &hwndNoteClient);
   // initialize the warptris window data structures
 pwd->hwndGame = hwndClient;
 pwd->hwndScore = hwndScoreClient;
 pwd->hwndNext = hwndNextClient;
 pwd->hwndHigh = hwndHighClient;
 pwd->hwndNote = hwndNoteFrame;
  // allocate and initialize the shared data structure
 sd = (PSHAREDDATA) malloc(sizeof(SHAREDDATA));
 sd->digitalPanel = new DigitalPanel(hwndScoreClient, 0, 0, 7);
 sd->hwndNext = hwndNextClient;
 sd->hwndGame = hwndClient;
 sd->figure = NULL;
 sd->dir = DOWN;
 sd->highScore = NULL;
 sd->pszName = (PSZ) calloc(40,sizeof(CHAR));
   // Set window words, of windows that share data, to point to the shared data structure
 WinSetWindowPtr(hwndClient, 4, sd);
 WinSetWindowPtr(hwndScoreClient, 4, sd);
 WinSetWindowPtr(hwndNextClient, 4, sd);
 WinSetWindowPtr(hwndHighClient, 4, sd);

 SetLanguage(pwd, current_lang); // menus, titles and the help manager in the saved language
 UpdateGameMenus(FALSE, FALSE);

  // Everything is ready: position the child windows and show the main window
 WinSendMsg(hwndClient, WM_SHOW, 0, 0);
 WinSendMsg(hwndScoreClient, WM_SHOW, 0, 0);
 WinSendMsg(hwndNextClient, WM_SHOW, 0, 0);
 WinSendMsg(hwndHighClient, WM_SHOW, 0, 0);
 WinSetWindowPos(hwndParentFrame, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER | SWP_ACTIVATE | SWP_SHOW);

 while(appState == APPNORMAL) // external while loop (see the comment on the appState var)
 {
  while(WinGetMsg(hab, &qmsg, 0, 0, 0)) // main application loop
     WinDispatchMsg(hab, &qmsg);

  if(pwd->exitNow || (INT) WinSendMsg(hwndParentClient, WM_VERIFY, 0, 0) == DID_OK) // Verify exit
     appState = USERQUIT;
  else
     WinPostMsg(hwndClient, WM_RESUMEGAME, 0, 0);
 }

 if(pwd->psd->saveonexit)
    SaveSettings(pwd->psd);

 // Put the frame controls back, so they are destroyed together with the frame
 if(pwd->frameHidden)
    {
     WinSetParent(pwd->hwndTitleBar, hwndParentFrame, FALSE);
     WinSetParent(pwd->hwndSysMenu, hwndParentFrame, FALSE);
     WinSetParent(pwd->hwndMinMax, hwndParentFrame, FALSE);
     WinSetParent(pwd->hwndMenu, hwndParentFrame, FALSE);
    }
 WinDestroyWindow(pwd->hwndPark);

 // Destroy all windows
 // (When a window is destroyed, all her child windows are also destroyed)
 WinDestroyWindow(hwndParentFrame);
 WinDestroyMsgQueue(hmq); // Destroy the message queue
 WinTerminate(hab); // Release the PM resources used by WarpTris

 free(sd->pszName); // free memory used by the string pszName
 free(sd); // free memory used by the shared data structure

 return(0);
}

HWND ParentClient(VOID)
// The client window of the WarpTris (parent) window, owner of the window data
{
 return(WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT));
}

// ---------------------------------------------------------------------------
// Menus and language
// ---------------------------------------------------------------------------

typedef struct {
                USHORT id;
                INT    str;
               } MENUTEXT;

static const MENUTEXT mtAll[] = {  // every translatable menu item (the ones missing
                                   // from a given menu are simply ignored)
 {IDM_SUBMENU_GAME,     STR_MENU_GAME},     {IDM_SUBMENU_IMPULSE,  STR_MENU_IMPULSE},
 {IDM_SUBMENU_SOUND,    STR_MENU_SOUND},    {IDM_SUBMENU_OPTIONS,  STR_MENU_OPTIONS},
 {IDM_SUBMENU_WINDOWS,  STR_MENU_WINDOWS},  {IDM_SUBMENU_HELP,     STR_MENU_HELP},
 {IDM_SUBMENU_DETAIL,   STR_MENU_DETAIL},   {IDM_SUBMENU_LANGUAGE, STR_MENU_LANGUAGE},
 {IDM_NEWGAME,          STR_MENU_NEW},      {IDM_PAUSE,            STR_MENU_PAUSE},
 {IDM_QUIT,             STR_MENU_QUIT},     {IDM_EXIT,             STR_MENU_EXIT},
 {IDM_BEGINNER,         STR_MENU_DONKEY},   {IDM_INTERMEDIATE,     STR_MENU_FORMULA1},
 {IDM_EXPERT,           STR_MENU_WARP},     {IDM_SOUNDON,          STR_MENU_SOUNDON},
 {IDM_SOUNDOFF,         STR_MENU_SOUNDOFF}, {IDM_PROPERTIES,       STR_MENU_PROPERTIES},
 {IDM_HIGHDET,          STR_MENU_DET_HIGH}, {IDM_MEDIUMDET,        STR_MENU_DET_MEDIUM},
 {IDM_LOWDET,           STR_MENU_DET_LOW},  {IDM_BACKGRND,         STR_MENU_BACKGRND},
 {IDM_FRAME,            STR_MENU_FRAME},    {IDM_SAVEONEXIT,       STR_MENU_SAVEONEXIT},
 {IDM_HIGHWINDOW,       STR_MENU_HIGHWIN},  {IDM_NEXTWINDOW,       STR_MENU_NEXTWIN},
 {IDM_SCOREWINDOW,      STR_MENU_SCOREWIN}, {IDM_GAMEWINDOW,       STR_MENU_GAMEWIN},
 {IDM_ARRANGE,          STR_MENU_ARRANGE},  {IDM_GENERALHELP,      STR_MENU_GENHELP},
 {IDM_HELPINDEX,        STR_MENU_HELPINDEX},{IDM_HELPONHELP,       STR_MENU_HELPONHELP},
 {IDM_ABOUT,            STR_MENU_ABOUT}
};

static const USHORT usSubMenus[] = {IDM_SUBMENU_GAME, IDM_SUBMENU_IMPULSE, IDM_SUBMENU_SOUND,
                                    IDM_SUBMENU_OPTIONS, IDM_SUBMENU_WINDOWS, IDM_SUBMENU_HELP};

static HWND GetSubMenu(HWND hMenu, USHORT id)
// Returns the handle of the submenu with the given identity (or NULLHANDLE)
{
 MENUITEM mi;

 memset(&mi, 0, sizeof(mi));
 if((BOOL) WinSendMsg(hMenu, MM_QUERYITEM, MPFROM2SHORT(id, FALSE), MPFROMP(&mi)))
    return(mi.hwndSubMenu);

 return(NULLHANDLE);
}

static VOID ApplyMenuTable(HWND hMenu)
// Sets the text of every known menu item of the menu in the current language
{
 INT i;

 for(i=0; i<(INT)(sizeof(mtAll)/sizeof(mtAll[0])); ++i)
    WinSendMsg(hMenu, MM_SETITEMTEXT, MPFROMSHORT(mtAll[i].id), MPFROMP(tr(mtAll[i].str)));
}

static VOID RelabelMenu(HWND hMenu)
// Translates a complete menu (menu bar or context menu)
{
 INT  i;
 HWND hSub, hSub2;

 if(hMenu == NULLHANDLE)
    return;

 ApplyMenuTable(hMenu);
 for(i=0; i<(INT)(sizeof(usSubMenus)/sizeof(usSubMenus[0])); ++i)
    {
     hSub = GetSubMenu(hMenu, usSubMenus[i]);
     if(hSub)
        {
         ApplyMenuTable(hSub);
         hSub2 = GetSubMenu(hSub, IDM_SUBMENU_DETAIL);
         if(hSub2)
            ApplyMenuTable(hSub2);
         hSub2 = GetSubMenu(hSub, IDM_SUBMENU_IMPULSE);
         if(hSub2)
            ApplyMenuTable(hSub2);
         hSub2 = GetSubMenu(hSub, IDM_SUBMENU_SOUND);
         if(hSub2)
            ApplyMenuTable(hSub2);
        }
    }
}

static VOID MenuCheck(PPARENTWINDOWDATA wd, USHORT id, BOOL on)
// Sets the check mark of an item on the menu bar and on both context menus
{
 WinCheckMenuItem(wd->hwndMenu, id, on);
 WinCheckMenuItem(wd->hwndPop, id, on);
 WinCheckMenuItem(wd->hwndPopGame, id, on);
}

static VOID MenuEnable(PPARENTWINDOWDATA wd, USHORT id, BOOL on)
{
 WinEnableMenuItem(wd->hwndMenu, id, on);
 WinEnableMenuItem(wd->hwndPop, id, on);
 WinEnableMenuItem(wd->hwndPopGame, id, on);
}

static VOID SyncMenus(PPARENTWINDOWDATA wd)
// Puts every check mark in the state given by the settings
{
 INT i;

 MenuCheck(wd, IDM_SCOREWINDOW, (BOOL) wd->psd->score);
 MenuCheck(wd, IDM_HIGHWINDOW,  (BOOL) wd->psd->high);
 MenuCheck(wd, IDM_GAMEWINDOW,  (BOOL) wd->psd->game);
 MenuCheck(wd, IDM_NEXTWINDOW,  (BOOL) wd->psd->next);
 MenuCheck(wd, IDM_SOUNDON,     wd->psd->sound != 0);
 MenuCheck(wd, IDM_SOUNDOFF,    wd->psd->sound == 0);
 MenuCheck(wd, IDM_BEGINNER,    wd->psd->level == 1);
 MenuCheck(wd, IDM_INTERMEDIATE,wd->psd->level == 2);
 MenuCheck(wd, IDM_EXPERT,      wd->psd->level == 3);
 for(i=0; i<3; ++i)
    MenuCheck(wd, (USHORT)(IDM_HIGHDET+i), (ULONG) i == wd->psd->detaillevel);
 for(i=0; i<LANG_COUNT; ++i)
    MenuCheck(wd, (USHORT)(IDM_LANG_EN+i), (ULONG) i == wd->psd->current_lang);
 MenuCheck(wd, IDM_BACKGRND,    wd->psd->bgrun != 0);
 MenuCheck(wd, IDM_SAVEONEXIT,  wd->psd->saveonexit != 0);
 MenuCheck(wd, IDM_FRAME,       wd->frameHidden);
}

VOID UpdateGameMenus(BOOL playing, BOOL paused)
// New is only available when no game runs, Pause and Quit only while playing
{
 PPARENTWINDOWDATA wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(ParentClient(), 0);

 if(wd == NULL || wd->hwndMenu == NULLHANDLE)
    return;

 MenuEnable(wd, IDM_NEWGAME, !playing);
 MenuEnable(wd, IDM_PAUSE, playing);
 MenuEnable(wd, IDM_QUIT, playing);
 MenuCheck(wd, IDM_PAUSE, playing && paused);
}

VOID SetLanguage(PPARENTWINDOWDATA wd, INT lang)
// Switches the language of the whole user interface (menus, window titles,
// notebook, help library)
{
 HWND hwndAux, hwndFrame;
 PWINDOWDATA gwd;

 if(lang < 0 || lang >= LANG_COUNT)
    lang = LANG_EN;

 current_lang = lang;
 wd->psd->current_lang = lang;

 RelabelMenu(wd->hwndMenu);
 RelabelMenu(wd->hwndPop);
 RelabelMenu(wd->hwndPopGame);
 SyncMenus(wd);

 if(wd->hwndGame != NULLHANDLE)  // not yet when called during start up
    {
     gwd = (PWINDOWDATA) WinQueryWindowPtr(wd->hwndGame, 0);
     if(gwd && gwd->gamePaused && gwd->gamePlaying)
        WinSetWindowText(gwd->hwndFrame, tr(STR_WIN_PAUSED));
     else
        WinSetWindowText(WinQueryWindow(wd->hwndGame, QW_PARENT), tr(STR_WIN_GAME));
     WinSetWindowText(WinQueryWindow(wd->hwndScore, QW_PARENT), tr(STR_WIN_SCORE));
     WinSetWindowText(WinQueryWindow(wd->hwndNext, QW_PARENT), tr(STR_WIN_NEXT));
     WinSetWindowText(WinQueryWindow(wd->hwndHigh, QW_PARENT), tr(STR_WIN_HIGH));
     hwndFrame = wd->hwndNote;
     hwndAux = WinWindowFromID(hwndFrame, FID_CLIENT);
     WinSendMsg(hwndAux, WM_RELABEL, 0, 0);
     SetHelpLanguage(wd->hwndFrame, lang);
    }
}

// ---------------------------------------------------------------------------
// Properties notebook
// ---------------------------------------------------------------------------

static VOID RelabelNoteBook(PPROPERTIESWINDOWDATA wd)
// Puts the texts of the notebook in the current language
{
 WinSetWindowText(wd->hwndFrame, tr(STR_WIN_PROPS));

 WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage1ID, MPFROMP(tr(STR_PAGE_OF)));
 WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage2ID, MPFROMP(tr(STR_PAGE_OF)));
 WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage3ID, MPFROMP(tr(STR_PAGE_OF)));

 WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage1ID), MPFROMP(tr(STR_TAB_SOUND)));
 WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage2ID), MPFROMP(tr(STR_TAB_WINDOWS)));
 WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage3ID), MPFROMP(tr(STR_TAB_IMPULSE)));

 WinSetDlgItemText(wd->hwndDlg1, DST_PAGE1GROUP, tr(STR_TAB_SOUND));
 WinSetDlgItemText(wd->hwndDlg1, DRB_ON, tr(STR_ON));
 WinSetDlgItemText(wd->hwndDlg1, DRB_OFF, tr(STR_OFF));

 WinSetDlgItemText(wd->hwndDlg2, DST_PAGE2GROUP, tr(STR_ENABLED_WINDOWS));
 WinSetDlgItemText(wd->hwndDlg2, DCB_HIGH, tr(STR_WIN_HIGH));
 WinSetDlgItemText(wd->hwndDlg2, DCB_NEXT, tr(STR_WIN_NEXT));
 WinSetDlgItemText(wd->hwndDlg2, DCB_SCORE, tr(STR_WIN_SCORE));
 WinSetDlgItemText(wd->hwndDlg2, DCB_GAME, tr(STR_WIN_GAME));

 WinSetDlgItemText(wd->hwndDlg3, DST_PAGE3GROUP, tr(STR_TAB_IMPULSE));
}

MRESULT EXPENTRY NoteBookWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 MRESULT ret;
 PPROPERTIESWINDOWDATA wd;

 switch(msg)
    {
     case WM_CREATE: // Allocate memory for the window data structure and create
                     // the notebook control
         ret = WinDefWindowProc(hwnd, msg, mp1, mp2);
         wd = (PPROPERTIESWINDOWDATA) malloc(sizeof(PROPERTIESWINDOWDATA));
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hwndNoteBook = WinCreateWindow(hwnd,
                                            WC_NOTEBOOK,
                                            NULL,
                                            BKS_SPIRALBIND    |  BKS_BACKPAGESBR   |
                                            BKS_MAJORTABRIGHT |  BKS_ROUNDEDTABS   |
                                            BKS_TABTEXTCENTER |  BKS_STATUSTEXTLEFT,
                                            0, -30*SCALE, 350*SCALE, 300*SCALE,
                                            hwnd,
                                            HWND_TOP,
                                            WID_NOTEBOOK,
                                            NULL,
                                            NULL);

         wd->ulPage1ID = (ULONG) WinSendMsg(wd->hwndNoteBook, BKM_INSERTPAGE, (MPARAM)NULL,
                                           MPFROM2SHORT(BKA_MAJOR |BKA_STATUSTEXTON, BKA_LAST));
         wd->ulPage2ID = (ULONG) WinSendMsg(wd->hwndNoteBook, BKM_INSERTPAGE, (MPARAM)NULL,
                                           MPFROM2SHORT(BKA_MAJOR |BKA_STATUSTEXTON, BKA_LAST));
         wd->ulPage3ID = (ULONG) WinSendMsg(wd->hwndNoteBook, BKM_INSERTPAGE, (MPARAM)NULL,
                                           MPFROM2SHORT(BKA_MAJOR |BKA_STATUSTEXTON, BKA_LAST));

         wd->hwndDlg1 = WinLoadDlg(wd->hwndNoteBook,
                                  wd->hwndNoteBook,
                                  Page1DlgProc,
                                  NULLHANDLE,
                                  DID_PAGE1,
                                  NULL);

         wd->hwndDlg2 = WinLoadDlg(wd->hwndNoteBook,
                                   wd->hwndNoteBook,
                                   Page2DlgProc,
                                   NULLHANDLE,
                                   DID_PAGE2,
                                   NULL);

         wd->hwndDlg3 = WinLoadDlg(wd->hwndNoteBook,
                                   wd->hwndNoteBook,
                                   Page3DlgProc,
                                   NULLHANDLE,
                                   DID_PAGE3,
                                   NULL);

         RelabelNoteBook(wd);

         WinSendMsg(wd->hwndNoteBook, BKM_SETDIMENSIONS, MPFROM2SHORT(83*SCALE, 25*SCALE), MPFROMSHORT(BKA_MAJORTAB));

         WinSendMsg(wd->hwndNoteBook,
                    BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG(wd->ulPage1ID),
                    MPFROMHWND(wd->hwndDlg1));

         WinSendMsg(wd->hwndNoteBook,
                    BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG(wd->ulPage2ID),
                    MPFROMHWND(wd->hwndDlg2));

         WinSendMsg(wd->hwndNoteBook,
                    BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG(wd->ulPage3ID),
                    MPFROMHWND(wd->hwndDlg3));

         WinSendMsg(wd->hwndNoteBook,
                    BKM_SETNOTEBOOKCOLORS,
                    MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                    MPFROMLONG(BKA_BACKGROUNDPAGECOLORINDEX));

         WinShowWindow(wd->hwndNoteBook, TRUE);
         WinSetWindowPtr(hwnd, 0, wd);
        return(ret);

     case WM_RELABEL: // The user interface language has changed
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(wd) RelabelNoteBook(wd);
        return(0);

     case WM_CLOSE: // if the window is closed, then don't destroy it, just hide it
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinShowWindow(wd->hwndFrame, FALSE);
        return((MRESULT) FALSE);

     case WM_SHOW: // When window is shown, set its position
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(wd)
            WinSetWindowPos(wd->hwndFrame, HWND_TOP, 100, 50, 355*SCALE, 296*SCALE, SWP_SIZE | SWP_MOVE);
        break;

     case WM_DESTROY: // When window is destroyed, free the memory used by its data structure
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         free(wd);
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2)); // The rest of the events are processed by
                                                // the default window procedure
}

MRESULT EXPENTRY NameDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 HWND hwndEntryField;
 static PSHAREDDATA sd;

 switch(msg)
    {
     case WM_INITDLG: // Initialize the controls in the dialog
         hwndEntryField = WinWindowFromID(hwnd, EID_NAME);
         WinSetWindowText(hwndEntryField, "");
         WinSendMsg(hwndEntryField, EM_SETTEXTLIMIT, (MPARAM) (HS_NAMELEN-1), 0);
         WinSetPresParam(hwndEntryField, PP_FONTNAMESIZE, 14, (PVOID) "10.System VIO");
         WinSetWindowText(hwnd, tr(STR_NAME_TITLE));
         WinSetDlgItemText(hwnd, DST_NAMETEXT, tr(STR_NAME_TEXT));
         WinSetDlgItemText(hwnd, DST_NAMEGROUP, tr(STR_NAME_GROUP));
         WinSetDlgItemText(hwnd, DID_OK, tr(STR_ENTER));
         sd = (PSHAREDDATA) PVOIDFROMMP(mp2); // Get the shared data pointer from mp2
                                              // to save the name after the dialog is
                                              // dismissed
        break;

     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_OK: // If the user has pressed the ENTER button, then
                         // get the text from the entryfield and save it
                         // on sd->pszName.
                hwndEntryField = WinWindowFromID(hwnd, EID_NAME);
                WinQueryWindowText(hwndEntryField, HS_NAMELEN, sd->pszName);
               break;

            default:
               break;
           }
        break;

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2)); // Let WinDefDlgProc do the rest
}

MRESULT EXPENTRY AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
    {
     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_OK:
            case DID_CANCEL:
                WinDismissDlg(hwnd, TRUE);
               return(0);
           }
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2));
}

MRESULT EXPENTRY HighWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 RECTL rcl;
 POINTL p;
 HWND hwndAux;
 PHIGHWINDOWDATA wd;
 PPARENTWINDOWDATA pwd;
 PSHAREDDATA sd;

 switch(msg)
    {
     case WM_CREATE: // Allocate and initialize the window data structure
         wd = (PHIGHWINDOWDATA) malloc(sizeof(HIGHWINDOWDATA));
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         wd->psd = pwd->psd;
         WinSetWindowPtr(hwnd, 0, wd); // set the window words to point to the window data structure
         WinPostMsg(hwnd, WM_CREATELB, 0, 0); // Hey! I'm done. Know you can create the list box.
        break;

     case WM_SHOW: // When shown, set its position based on the settings previously saved
         wd = (PHIGHWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinSetWindowPos(wd->hwndFrame, HWND_TOP, wd->psd->rclHigh.xLeft, wd->psd->rclHigh.yBottom,
                         wd->psd->rclHigh.xRight, wd->psd->rclHigh.yTop, SWP_SIZE | SWP_MOVE);
         if(!wd->psd->high) // if it was hidden then don't show it
            WinShowWindow(wd->hwndFrame, FALSE);
        break;


     case WM_CREATELB: // Create a listbox control...
         wd = (PHIGHWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinQueryWindowRect(hwnd, &rcl); //...that fits the entire window
         p.x = rcl.xRight;
         p.y = rcl.yTop;
         wd->hwndListBox = WinCreateWindow(hwnd,
                                           WC_LISTBOX,
                                           NULL,
                                           LS_NOADJUSTPOS,
                                           0,0,
                                           p.x,
                                           p.y,
                                           NULLHANDLE,
                                           HWND_TOP,
                                           WID_LISTBOX,
                                           NULL,
                                           NULL);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         sd->highScore = new HighScore(wd->hwndListBox, hwnd); // create the highscore object,
                                                               // it reads Hiscore.bin and fills the listbox
         WinSetPresParam(wd->hwndListBox, PP_FONTNAMESIZE, 12, (PVOID) "16.Courier");
         WinShowWindow(wd->hwndListBox, TRUE); // Finally, show it!
        break;

     case WM_FOCUSCHANGE: // This is a way of changing the check status  of the
                          // menuitem High Score on the menu Windows when the window
                          // is hidden from the hide button. It must exist
                          // a better way of doing this, but I haven't found it,
                          // so... anyway it works!
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->high && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_HIGHWINDOW, 0), 0);
              // it's the same as clicking on the menuitem High Score on the menu Windows
        break;

     case WM_DESTROY: // as always, free the memory used by the window data structure
         wd = (PHIGHWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         delete sd->highScore;
         free(wd);
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2)); // Let the rest be processed by WinDefWindowProc
}

MRESULT EXPENTRY NextWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 HPS hps;
 POINTL p;
 RECTL rcl;
 INT i;
 HWND hwndAux;
 PNEXTWINDOWDATA wd;
 PSHAREDDATA sd;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_CREATE://Allocate and initialize the window data structure
         wd = (PNEXTWINDOWDATA) malloc(sizeof(NEXTWINDOWDATA));
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hps = WinGetPS(hwnd); // get the window Presentation Space
         for(i=0; i<=6; ++i)
          wd->hbmp[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+1, CELL, CELL);
           // Load the bitmaps of the pieces
         for(i=0; i<4; ++i)
          wd->hbmpDirection[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+30, 32*SCALE, 32*SCALE);
           // Load the bitmaps of the direction arrows
         wd->hbmpBackground = GpiLoadBitmap(wd->hps, NULLHANDLE, BID_NEXTBACKGROUND, 150*SCALE, 100*SCALE);
           // Load the background bitmap
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         wd->psd = pwd->psd;
         WinSetWindowPtr(hwnd, 0, wd); // Set the window words to point to the window data structure
        break;

     case WM_NEXT: // Hey! Create and show the next figure and direction.
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         i = Random(6);
         if(sd->figure !=NULL) // if an old figure object exists, delete him
          delete sd->figure;
         sd->figure = new Figure(hwnd, i+1, FIGURES[i], 8 ,8, FALSE, FALSE);
          // create the new figure
         sd->dir = NewDirection();
          // get the next direction
         WinQueryWindowRect(hwnd, &rcl); // How big are you?
         WinInvalidateRect(hwnd, &rcl, TRUE); // Paint yourself!
        break;

     case WM_PAINT: // Paints the window.
         hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl); // get the window PS
         p.x = 0;
         p.y = 0;
         wd = (PNEXTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinDrawBitmap(hps, wd->hbmpBackground, NULL, &p, 0, 0, DBM_NORMAL);
          // Draw the background bitmap
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         if(sd->figure != NULL)
         {
          sd->figure->DrawNext(0,1);   // Draw the next figure
          p.x = 100*SCALE;
          p.y = 34*SCALE;
          switch(sd->dir) // Draw an arrow bitmap, depending on the next direction
            {
             case UP:
                 WinDrawBitmap(hps, wd->hbmpDirection[0], NULL, &p, 0, 0, DBM_NORMAL);
                break;

             case DOWN:
                 WinDrawBitmap(hps, wd->hbmpDirection[1], NULL, &p, 0, 0, DBM_NORMAL);
                break;

             case LEFT:
                 WinDrawBitmap(hps, wd->hbmpDirection[2], NULL, &p, 0, 0, DBM_NORMAL);
                break;

             case RIGHT:
                 WinDrawBitmap(hps, wd->hbmpDirection[3], NULL, &p, 0, 0, DBM_NORMAL);
                break;

             default:
                break;
            }
          }
         WinEndPaint(hps); // Release the window Presentation Space
        break;

     case WM_SHOW: // About to show! Time to initialize the size and position.
         wd = (PNEXTWINDOWDATA) WinQueryWindowPtr(hwnd ,0);
         WinSetWindowPos(wd->hwndFrame, HWND_TOP, wd->psd->rclNext.xLeft, wd->psd->rclNext.yBottom,
                         wd->psd->rclNext.xRight, wd->psd->rclNext.yTop, SWP_SIZE | SWP_MOVE);
         if(!wd->psd->next) // If I was hidden then don't show me!
            WinShowWindow(wd->hwndFrame, FALSE);
        break;

     case WM_FOCUSCHANGE: // The same trick, used on the HighScores window.:)
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->next && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_NEXTWINDOW, 0), 0);
        break;

     case WM_DESTROY: // About to be destroyed!
         wd = (PNEXTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinReleasePS(wd->hps); // Release the PS
         for(i=0; i<=6; ++i)
          GpiDeleteBitmap(wd->hbmp[i]); // Remove bitmaps from memory
         for(i=0; i<4; ++i)
          GpiDeleteBitmap(wd->hbmpDirection[i]);
         GpiDeleteBitmap(wd->hbmpBackground);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4); // free memory used
         if(sd->figure!=NULL)
           delete sd->figure;
         free(wd);
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2)); // then, execute the default procedure
}

MRESULT EXPENTRY ScoreWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 PSCOREWINDOWDATA wd;
 HPS hps;
 RECTL rcl;
 HWND hwndAux;
 PSHAREDDATA sd;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_CREATE: // Allocate and initialize private data structure
         wd = (PSCOREWINDOWDATA) malloc(sizeof(SCOREWINDOWDATA));
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hwndParent = WinQueryWindow(wd->hwndFrame, QW_PARENT);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         wd->psd = pwd->psd;
         WinSetWindowPtr(hwnd, 0, wd); // Set window words to point to the private data structure
        break;

     case WM_PAINT: // Window needs to be painted
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
         WinFillRect(hps, &rcl, CLR_PALEGRAY);
         sd->digitalPanel->Draw(hps);
         WinEndPaint(hps);
        break;

     case WM_SHOW: // Window is about to show, so set its size and position
         wd = (PSCOREWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinSetWindowPos(wd->hwndFrame, HWND_TOP, wd->psd->rclScore.xLeft, wd->psd->rclScore.yBottom,
                         wd->psd->rclScore.xRight, wd->psd->rclScore.yTop, SWP_SIZE | SWP_MOVE);
         if(!wd->psd->score) // if it wasn't visible, then don't show it
            WinShowWindow(wd->hwndFrame, FALSE);
        break;

     case WM_FOCUSCHANGE: // The same trick to intercept the hide button (explanation above)
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->score && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_SCOREWINDOW, 0), 0);
        break;

     case WM_DESTROY: // Window is about to be destroyed...
         wd = (PSCOREWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         free(wd); // ...so free up memory used...
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         delete sd->digitalPanel; // ... and destroy the digital panel object
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2)); //Let the default Wnd procedure handle the rest
}

MRESULT EXPENTRY Page1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static BOOL first = TRUE;
 static HWND hwndAux;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_INITDLG:// Dialogs equivalent of windows WM_CREATE
         WinDefDlgProc(hwnd, msg, mp1, mp2);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(pwd->psd->sound == 1)
         {
          WinCheckButton(hwnd, DRB_ON, 1);
          WinCheckButton(hwnd, DRB_OFF, 0);
         }
         else
         {
          WinCheckButton(hwnd, DRB_ON, 0);
          WinCheckButton(hwnd, DRB_OFF, 1);
         }
         WinPostMsg(hwnd, WM_SETFIRST, 0, 0);
        return(0);

     case WM_SETFIRST: //Set the control variable "first"
        first = FALSE;
       return(0);

    case WM_CHAR:
        if(SHORT1FROMMP(mp1) & KC_VIRTUALKEY)
           switch(SHORT2FROMMP(mp2))
              {
               case VK_ESC: // Don't let the notebook page 1 dialog be dissmissed by ESC
                  return(0);

               default:
                  break;
              }
       break;

     case WM_CONTROL: // Handle the various control events
        switch(SHORT1FROMMP(mp1))
           {
            case DRB_ON:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
               {
                pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinCheckButton(hwnd, DRB_ON, 1);
                WinCheckButton(hwnd, DRB_OFF, 0);
                pwd->psd->sound = 1;
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_SOUNDON, 0), 0);
               }
              return 0;

            case DRB_OFF:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
                 {
                  pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                  WinCheckButton(hwnd, DRB_ON, 0);
                  WinCheckButton(hwnd, DRB_OFF, 1);
                  pwd->psd->sound = 0;
                  WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_SOUNDOFF, 0), 0);
                 }
              return 0;

            default:
              break;
           }
          return 0;

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2)); //This is a dialog, so pass the rest to the
                                             //default dialog procedure
}

MRESULT EXPENTRY Page2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static HWND hwndParent;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_INITDLG: // Initialize controls state
         hwndParent = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
         WinCheckButton(hwnd, DCB_HIGH, pwd->psd->high);
         WinCheckButton(hwnd, DCB_GAME, pwd->psd->game);
         WinCheckButton(hwnd, DCB_NEXT, pwd->psd->next);
         WinCheckButton(hwnd, DCB_SCORE, pwd->psd->score);
        return 0;

    case WM_CHAR:
        if(SHORT1FROMMP(mp1) & KC_VIRTUALKEY)
           switch(SHORT2FROMMP(mp2))
              {
               case VK_ESC: // Don't let this dialog be dismissed by ESC
                  return(0);

               default:
                  break;
              }
       break;

     case WM_CONTROL://Handle the controls events
        switch(SHORT1FROMMP(mp1))
           {
            case DCB_HIGH:
                WinDefDlgProc(hwnd, msg, mp1, mp2);
                pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
                pwd->psd->high = WinQueryButtonCheckstate(hwnd, DCB_HIGH);
                WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(IDM_HIGHWINDOW,0),0);
              return(0);

            case DCB_NEXT:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->next = WinQueryButtonCheckstate(hwnd, DCB_NEXT);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(IDM_NEXTWINDOW,0),0);
              return(0);

            case DCB_SCORE:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->score = WinQueryButtonCheckstate(hwnd, DCB_SCORE);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(IDM_SCOREWINDOW,0),0);
              return(0);

            case DCB_GAME:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->game = WinQueryButtonCheckstate(hwnd, DCB_GAME);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(IDM_GAMEWINDOW,0),0);
              return(0);

           default:
              return 0;
           }

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2)); //Let the default dialog procedure handle the rest
}

MRESULT EXPENTRY Page3DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static BOOL first = TRUE;
 static HWND hwndAux;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_INITDLG: //Initialize data structures and controls
         WinDefDlgProc(hwnd, msg, mp1, mp2);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         WinCheckButton(hwnd, DRB_DONKEY,   pwd->psd->level == 1);
         WinCheckButton(hwnd, DRB_FORMULA1, pwd->psd->level == 2);
         WinCheckButton(hwnd, DRB_WARP,     pwd->psd->level == 3);
         WinPostMsg(hwnd, WM_SETFIRST, 0, 0);
        return(0);

     case WM_SETFIRST: //Set the first time variable
        first = FALSE;
       return 0;

    case WM_CHAR:
        if(SHORT1FROMMP(mp1) & KC_VIRTUALKEY)
           switch(SHORT2FROMMP(mp2))
              {
               case VK_ESC: // don't let this dialog be dismissed by ESC
                  return(0);

               default:
                  break;
              }
       break;

     case WM_CONTROL://Handle the various control events
        switch(SHORT1FROMMP(mp1))
           {
            case DRB_DONKEY:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
               {
                pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinCheckButton(hwnd, DRB_DONKEY, 1);
                WinCheckButton(hwnd, DRB_FORMULA1, 0);
                WinCheckButton(hwnd, DRB_WARP, 0);
                pwd->psd->level = 1;
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_BEGINNER,0),0);
               }
              return 0;

           case DRB_FORMULA1:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
               {
                pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinCheckButton(hwnd, DRB_DONKEY, 0);
                WinCheckButton(hwnd, DRB_FORMULA1, 1);
                WinCheckButton(hwnd, DRB_WARP, 0);
                pwd->psd->level = 2;
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_INTERMEDIATE,0),0);
               }
              return 0;

           case DRB_WARP:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
               {
                pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinCheckButton(hwnd, DRB_DONKEY, 0);
                WinCheckButton(hwnd, DRB_FORMULA1, 0);
                WinCheckButton(hwnd, DRB_WARP, 1);
                pwd->psd->level = 3;
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_EXPERT,0),0);
               }
              return 0;

            default:
               break;
           }
        return 0;

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2)); // the default dialog procedure will do the rest
}

MRESULT EXPENTRY ExitDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
    {
     case WM_INITDLG: // Put the texts in the current language
         WinSetWindowText(hwnd, tr(STR_EXIT_TITLE));
         WinSetDlgItemText(hwnd, DST_EXITTEXT, tr(STR_EXIT_TEXT));
         WinSetDlgItemText(hwnd, DID_OK, tr(STR_YES));
         WinSetDlgItemText(hwnd, DID_CANCEL, tr(STR_NO));
        break;

     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_OK: // If the OK button has been pressed, dismiss and return DID_OK
                WinDismissDlg(hwnd, DID_OK);
               return(0);

            case DID_CANCEL:
                WinDismissDlg(hwnd, DID_CANCEL); //If canceled, dismiss and return DID_CANCEL
               return(0);
           }
        break;

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2));//The default dialog procedure will handle the rest
}

// ---------------------------------------------------------------------------
// Frame controls (Ctrl+F)
// ---------------------------------------------------------------------------

static VOID ToggleFrameControls(PPARENTWINDOWDATA wd, HWND hwndClient)
// Hides or shows title bar, system menu, min/max buttons and menu bar of the
// WarpTris window. The controls are parked in an object window, so they keep
// their visible state.
{
 RECTL rcl;
 HWND  hwndNew;

 WinQueryWindowRect(hwndClient, &rcl); // the client area keeps its size

 hwndNew = wd->frameHidden ? wd->hwndFrame : wd->hwndPark;
 WinSetParent(wd->hwndTitleBar, hwndNew, FALSE);
 WinSetParent(wd->hwndSysMenu, hwndNew, FALSE);
 WinSetParent(wd->hwndMinMax, hwndNew, FALSE);
 WinSetParent(wd->hwndMenu, hwndNew, FALSE);
 wd->frameHidden = !wd->frameHidden;

 WinSendMsg(wd->hwndFrame, WM_UPDATEFRAME,
            MPFROMLONG(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_MENU), 0);

 WinCalcFrameRect(wd->hwndFrame, &rcl, FALSE);
 WinSetWindowPos(wd->hwndFrame, HWND_TOP, 0, 0,
                 rcl.xRight - rcl.xLeft, rcl.yTop - rcl.yBottom, SWP_SIZE);

 WinInvalidateRect(wd->hwndFrame, NULL, TRUE);
 WinUpdateWindow(wd->hwndFrame);
 MenuCheck(wd, IDM_FRAME, wd->frameHidden);
}

static VOID ToggleChildWindow(PPARENTWINDOWDATA wd, HWND hwndChildClient, USHORT cmd, ULONG *pFlag)
// Shows or hides one of the child windows (the menu check mark has the old state)
{
 BOOL  newOn;
 HWND  hwndAux, hwndFrame;
 PPROPERTIESWINDOWDATA npd;

 newOn = !WinIsMenuItemChecked(wd->hwndMenu, cmd);
 hwndFrame = WinQueryWindow(hwndChildClient, QW_PARENT);
 WinShowWindow(hwndFrame, newOn);
 MenuCheck(wd, cmd, newOn);
 *pFlag = newOn ? 1 : 0;

 hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
 npd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
 if(npd)
    WinPostMsg(npd->hwndDlg2, WM_INITDLG, 0, 0);
}

static VOID ChangeLevel(PPARENTWINDOWDATA wd, USHORT cmd)
// Impulse menu: Donkey, Formula 1 or WARP!
{
 HWND  hwndAux;
 PPROPERTIESWINDOWDATA npd;
 ULONG ulDelay;

 switch(cmd)
    {
     case IDM_INTERMEDIATE:
        wd->psd->level = 2;
        ulDelay = LV_INTERMEDIATE;
       break;

     case IDM_EXPERT:
        wd->psd->level = 3;
        ulDelay = LV_EXPERT;
       break;

     default:
        wd->psd->level = 1;
        ulDelay = LV_BEGINNER;
       break;
    }
 WinPostMsg(wd->hwndGame, WM_CHANGELEVEL, MPFROMLONG(ulDelay), 0);
 MenuCheck(wd, IDM_BEGINNER, wd->psd->level == 1);
 MenuCheck(wd, IDM_INTERMEDIATE, wd->psd->level == 2);
 MenuCheck(wd, IDM_EXPERT, wd->psd->level == 3);
 hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
 npd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
 if(npd)
    WinPostMsg(npd->hwndDlg3, WM_INITDLG, 0, 0);
}

static VOID ChangeSound(PPARENTWINDOWDATA wd, BOOL on)
{
 HWND  hwndAux;
 PPROPERTIESWINDOWDATA npd;

 wd->psd->sound = on ? 1 : 0;
 MenuCheck(wd, IDM_SOUNDON, on);
 MenuCheck(wd, IDM_SOUNDOFF, !on);
 hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
 npd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
 if(npd)
    WinPostMsg(npd->hwndDlg1, WM_INITDLG, 0, 0);
}

MRESULT EXPENTRY ParentWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 RECTL rcl;
 ULONG usResponse;
 POINTL ptl;
 HPS   hps;
 HWND  hwndHelp;
 INT   i;
 PPARENTWINDOWDATA wd;
 PWINDOWDATA gwd;

 switch(msg)
    {
     case WM_CREATE: //Initialize data structures and menus
         WinDefWindowProc(hwnd, msg, mp1, mp2);
         wd = (PPARENTWINDOWDATA) calloc(1, sizeof(PARENTWINDOWDATA));
         wd->psd = (PSETTINGSDATA) malloc(sizeof(SETTINGSDATA));
         ReadSettings(wd->psd);
         current_lang = (INT) wd->psd->current_lang;
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hwndMenu = WinWindowFromID(wd->hwndFrame, FID_MENU);
         wd->hwndPop = WinLoadMenu(hwnd, 0, MNU_PARENT);
         wd->hwndPopGame = WinLoadMenu(hwnd, 0, MNU_GAME);
         WinSetWindowPtr(hwnd, 0, wd);
        return(0);

     case WM_CONTEXTMENU: // a context menu needs to be shown
         wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(SHORT2FROMMP(mp2))
            WinQueryPointerPos(HWND_DESKTOP, &ptl); //Where's the mouse pointer?
         else
            {
             ptl.x = SHORT1FROMMP(mp1);
             ptl.y = SHORT2FROMMP(mp1);
             WinMapWindowPoints(hwnd, HWND_DESKTOP, &ptl, 1);
            }
         WinPopupMenu(HWND_DESKTOP, hwnd, wd->hwndPop, ptl.x, ptl.y, 0,
                      PU_HCONSTRAIN | PU_VCONSTRAIN | PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 | PU_KEYBOARD);
                      // Pop goes the menu!
        break;

     case WM_VERIFY: // Verify that the user really wants to quit
        wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        WinSendMsg(wd->hwndGame, WM_PAUSEGAME, 0, 0);
        usResponse = WinDlgBox(HWND_DESKTOP,
                               hwnd,
                               ExitDlgProc,
                               NULLHANDLE,
                               DID_EXIT,
                               NULL);
        return((MRESULT) usResponse);

     case WM_PAINT: // Window needs repainting
        hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
        WinFillRect(hps, &rcl, CLR_DARKGREEN);//Just give it a nice green colour
        WinEndPaint(hps);
        break;

     case WM_COMMAND://Handle menu events
        wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        gwd = (PWINDOWDATA) WinQueryWindowPtr(wd->hwndGame, 0);
        switch(SHORT1FROMMP(mp1))
           {
            case IDM_PROPERTIES:
                WinShowWindow(wd->hwndNote, TRUE);
                WinSetFocus(HWND_DESKTOP, wd->hwndNote);
               break;

            case IDM_EXIT:
               wd->exitNow = TRUE; // Ctrl+X exits at once
               WinPostMsg(hwnd, WM_CLOSE, 0, 0);
               break;

            case IDM_NEWGAME:
               if(gwd && gwd->gamePlaying) // a game is already running
                  break;
               WinFocusChange(HWND_DESKTOP,
                              wd->hwndGame,
                              0);
               WinPostMsg(wd->hwndNext, WM_NEXT, 0, 0);
               WinPostMsg(wd->hwndGame, WM_NEWGAME, 0, 0);
               break;

            case IDM_PAUSE:
               if(gwd && gwd->gamePlaying)
                  WinPostMsg(wd->hwndGame, gwd->gamePaused ? WM_RESUMEGAME : WM_PAUSEGAME, 0, 0);
               break;

            case IDM_QUIT:
               if(gwd && gwd->gamePlaying) // stop the game, show the score
                  WinPostMsg(wd->hwndGame, WM_GAMEOVER, 0, 0);
               break;

            case IDM_GAMEWINDOW:
                ToggleChildWindow(wd, wd->hwndGame, IDM_GAMEWINDOW, &wd->psd->game);
               break;

            case IDM_SCOREWINDOW:
                ToggleChildWindow(wd, wd->hwndScore, IDM_SCOREWINDOW, &wd->psd->score);
               break;

            case IDM_NEXTWINDOW:
                ToggleChildWindow(wd, wd->hwndNext, IDM_NEXTWINDOW, &wd->psd->next);
               break;

            case IDM_HIGHWINDOW:
                ToggleChildWindow(wd, wd->hwndHigh, IDM_HIGHWINDOW, &wd->psd->high);
                break;

            case IDM_BEGINNER:
            case IDM_INTERMEDIATE:
            case IDM_EXPERT:
                ChangeLevel(wd, SHORT1FROMMP(mp1));
               break;

            case IDM_SOUNDON:
                ChangeSound(wd, TRUE);
               break;

            case IDM_SOUNDOFF:
                ChangeSound(wd, FALSE);
               break;

            case IDM_HIGHDET:
            case IDM_MEDIUMDET:
            case IDM_LOWDET:
                wd->psd->detaillevel = SHORT1FROMMP(mp1) - IDM_HIGHDET;
                for(i=0; i<3; ++i)
                   MenuCheck(wd, (USHORT)(IDM_HIGHDET+i), (ULONG) i == wd->psd->detaillevel);
               break;

            case IDM_LANG_EN:
            case IDM_LANG_ES:
            case IDM_LANG_NL:
            case IDM_LANG_DE:
            case IDM_LANG_FR:
            case IDM_LANG_IT:
                SetLanguage(wd, SHORT1FROMMP(mp1) - IDM_LANG_EN);
               break;

            case IDM_BACKGRND:
                wd->psd->bgrun = !wd->psd->bgrun;
                MenuCheck(wd, IDM_BACKGRND, wd->psd->bgrun != 0);
               break;

            case IDM_FRAME:
                ToggleFrameControls(wd, hwnd);
               break;

            case IDM_SAVEONEXIT:
                wd->psd->saveonexit = !wd->psd->saveonexit;
                MenuCheck(wd, IDM_SAVEONEXIT, wd->psd->saveonexit != 0);
               break;

            case IDM_ABOUT:
                WinDlgBox(HWND_DESKTOP, hwnd, AboutDlgProc, NULLHANDLE, IDD_ABOUT, NULL);
               break;

            case IDM_ARRANGE:
                WinQueryWindowRect(hwnd, &rcl);
                ArrangeWindows(wd->psd, rcl.xRight - rcl.xLeft, rcl.yTop - rcl.yBottom);
                WinPostMsg(wd->hwndGame, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndScore, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndNext, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndHigh, WM_SHOW, 0, 0);
               break;

            case IDM_GENERALHELP:
                hwndHelp = WinQueryHelpInstance(hwnd);
                if(hwndHelp)
                   WinSendMsg (hwndHelp,
                               HM_DISPLAY_HELP,
                               MPFROMSHORT(HID_GENERAL),
                               MPFROMSHORT(HM_RESOURCEID));
               break;

            case IDM_HELPINDEX:
                hwndHelp = WinQueryHelpInstance(hwnd);
                if(hwndHelp)
                   WinSendMsg(hwndHelp, HM_HELP_INDEX, 0, 0);
               break;

            case IDM_HELPONHELP:
                hwndHelp = WinQueryHelpInstance(hwnd);
                if(hwndHelp)
                   WinSendMsg(hwndHelp, HM_DISPLAY_HELP, 0, 0);
               break;

            default:
               break;
           }
        break;

     case WM_DESTROY://Window is about to be destroyed, so free up resources
         wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         free(wd->psd);
         WinDestroyWindow(wd->hwndPop);
         WinDestroyWindow(wd->hwndPopGame);
         free(wd);
         hwndHelp = WinQueryHelpInstance (hwnd);
         if(hwndHelp)
            WinDestroyHelpInstance (hwndHelp);
         WinAssociateHelpInstance (NULLHANDLE, hwnd);
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2));//The default window procedure will handle the other events
}

MRESULT EXPENTRY GameOverDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
    {
     case WM_INITDLG: // Put the texts in the current language
         WinSetWindowText(hwnd, tr(STR_OVER_TITLE));
         WinSetDlgItemText(hwnd, DID_OK, tr(STR_OK));
         WinSetDlgItemText(hwnd, DID_CANCEL, tr(STR_NEW));
        break;

     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_CANCEL:
                WinDismissDlg(hwnd, DID_CANCEL);// If canceled, dismiss and return DID_CANCEL
               return(0);

            case DID_OK:
                WinDismissDlg(hwnd, DID_OK);// If OK pressed, dismiss and return DID_OK
               return(0);
           }
        break;
    }
 return((MRESULT) WinDefDlgProc(hwnd, msg, mp1, mp2));// The rest is up to the default dialog procedure
}

MRESULT EXPENTRY MainWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 INT i, linesRemoved = 0;
 ULONG ulTimerDelay, fsKey;
 SHORT key;
 HWND hwndAux;
 POINTL ptl;
 PWINDOWDATA wd;
 POBJECTWINDOWDATA owd;
 PSHAREDDATA sd;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_CREATE://Initialize data structures, load bitmaps, ....
         wd = (PWINDOWDATA) malloc(sizeof(WINDOWDATA));
         wd->hps = WinGetPS(hwnd);
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         for(i=0; i<=6; ++i)
          wd->hbmp[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+1, CELL, CELL);
         wd->direction = NewDirection();
         wd->hasFocus = TRUE;
         wd->gamePaused = FALSE;
         wd->gamePlaying = FALSE;
         wd->board = NULL;
         wd->figure = NULL;
         wd->hwndParent = WinQueryWindow(WinQueryWindow(wd->hwndFrame, QW_PARENT), QW_PARENT);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         wd->hwndPop = pwd->hwndPopGame;
         wd->psd = pwd->psd;
         switch(wd->psd->level)
            {
             case 2:
                 ulTimerDelay = LV_INTERMEDIATE;
                break;
             case 3:
                 ulTimerDelay = LV_EXPERT;
                break;
             default:
                 ulTimerDelay = LV_BEGINNER;
                break;
            }
         wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, ulTimerDelay);
         WinSetWindowPtr(hwnd, 0, wd);
         owd = (POBJECTWINDOWDATA) malloc(sizeof(OBJECTWINDOWDATA));
         owd->hwndGame = hwnd;
         owd->hwndObject = NULLHANDLE;
         owd->threadRunning = FALSE;
         owd->tid = 2;
         owd->pfThread = &SoundThread;
         owd->psd = wd->psd;
         WinSetWindowPtr(hwnd, 8, owd);
         WinPostMsg(hwnd, WM_CREATETHREAD, 0, 0);
        break;

     case WM_CREATETHREAD: // Create the sound thread
         owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
         owd->hwndGame = hwnd;
         DosCreateThread(&(owd->tid), owd->pfThread, hwnd, CREATE_READY|STACK_COMMITTED, 23192);
         owd->threadRunning = TRUE; // yep, the thread is running!
        break;

     case WM_CONTEXTMENU: // Show the context menu
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         hwndAux = ParentClient();
         if(SHORT2FROMMP(mp2))
            WinQueryPointerPos(HWND_DESKTOP, &ptl);
         else
            {
             ptl.x = SHORT1FROMMP(mp1);
             ptl.y = SHORT2FROMMP(mp1);
             WinMapWindowPoints(hwnd, HWND_DESKTOP, &ptl, 1);
            }
         WinPopupMenu(HWND_DESKTOP, hwndAux, wd->hwndPop, ptl.x, ptl.y, 0,
                      PU_HCONSTRAIN | PU_VCONSTRAIN | PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 | PU_KEYBOARD);
                      // Pop goes the menu!
        break;

     case WM_CREATEOBJECTS: // Create the board and figure objects
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         if(wd->board != NULL)
            delete wd->board;
         if(wd->figure != NULL)
            delete wd->figure;
         wd->board = new Board(hwnd);
         i = Random(6);
         wd->figure = new Figure(hwnd, i+1, FIGURES[i], 8 ,8, FALSE, FALSE);
         wd->currentBitmapID = wd->figure->GetBitmapID();
         WinPostMsg(sd->hwndNext, WM_NEXT, 0, 0);
         Animation(hwnd);// Make the gray area animation
        break;

     case WM_PAINT: // Window needs repainting
        PaintWindow(hwnd);
       break;

    case WM_HELP: //Help!!
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        if(wd->gamePlaying) // If the a game was interrupted, then pause it
         WinPostMsg(hwnd, WM_PAUSEGAME, 0, 0);
       break;

    case WM_CHAR:
       wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
       fsKey = SHORT1FROMMP(mp1);
       if(fsKey & KC_KEYUP) // only react to the key press, not to the release
          break;
       key = 0;
       if(fsKey & KC_CHAR)
          key = SHORT1FROMMP(mp2);
       else if(fsKey & KC_VIRTUALKEY)
          switch(SHORT2FROMMP(mp2)) // the cursor keys do the same as the keypad keys
             {
              case VK_LEFT:  key = '4'; break;
              case VK_RIGHT: key = '6'; break;
              case VK_UP:    key = '8'; break;
              case VK_DOWN:  key = '2'; break;
              case VK_SHIFT: if(!(fsKey & KC_PREVDOWN)) key = '5'; break; // both Shift keys rotate
              default:       break;
             }
       if((key == 'p' || key=='P') && wd->gamePaused && wd->gamePlaying)
          WinPostMsg(hwnd, WM_RESUMEGAME, 0, 0);// P was pressed and the game was paused, in this case: resume the game
       else if((key == 'p' || key=='P') && wd->gamePlaying)
          WinPostMsg(hwnd, WM_PAUSEGAME, 0, 0); // else pause the game
       if(wd->hasFocus && !wd->gamePaused && wd->gamePlaying)
           switch(key) // handle the game keys
              {
               case '5':
                   wd->figure->Rotate(*(wd->board));
                  break;

               case '4':
                   if(wd->direction == UP || wd->direction == DOWN)
                     wd->figure->Move(LEFT, *(wd->board));
                  break;

               case '6':
                   if(wd->direction == UP || wd->direction == DOWN)
                     wd->figure->Move(RIGHT, *(wd->board));
                  break;

               case '8':
                    if(wd->direction == LEFT || wd->direction == RIGHT)
                      wd->figure->Move(UP, *(wd->board));
                  break;

               case '2':
                  if(wd->direction == LEFT || wd->direction == RIGHT)
                    wd->figure->Move(DOWN, *(wd->board));
                  break;

               case ' ':
                   wd->figure->Fall(wd->direction, *(wd->board));
                   WinPostMsg(hwnd, WM_DROPED, 0, 0);
                  break;

               default:
                  break;
              }
       break;

    case WM_CHANGELEVEL: // Change the speed to the delay stored in mp1
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        ulTimerDelay = LONGFROMMP(mp1);
        WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, wd->ulTimerID);
        wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, ulTimerDelay);
       break;

    case WM_DROPED: // A piece as droped, it's time to see if there are lines to remove
        owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        if(!wd->gamePlaying)
           break;
        linesRemoved = wd->board->Evaluate(wd->direction);
        if(linesRemoved)
           {
            sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
            sd->digitalPanel->AddToValue(linesRemoved*SC_LINESCORE*wd->psd->level);
            sd->digitalPanel->Draw();
            linesRemoved=0;
           }
        if(wd->board->Finished())
          WinPostMsg(hwnd, WM_GAMEOVER, 0, 0);
        else
        {
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         sd->digitalPanel->AddToValue(SC_PIECESCORE*wd->psd->level);
         *(wd->figure) = *(sd->figure);
         Animation(hwnd);
         wd->figure->Draw();
         wd->currentBitmapID = wd->figure->GetBitmapID();
         wd->direction = sd->dir;
         WinPostMsg(sd->hwndNext, WM_NEXT, 0, 0);
        }
       break;

    case WM_GAMEOVER: // Game's over, too bad!
        owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        if(!wd->gamePlaying)
           break;
        wd->gamePlaying = FALSE; // the game is no longer being played
        wd->gamePaused = FALSE;
        WinSetWindowText(wd->hwndFrame, tr(STR_WIN_GAME));
        UpdateGameMenus(FALSE, FALSE);
        sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
        if(!sd->highScore->New(sd->digitalPanel->GetValue(), wd->psd->level))
         // if there wasn't a highscore, play the game over sound
        {
          if(owd->threadRunning)
           WinPostMsg(owd->hwndObject, WM_OVER, 0, 0);
        }
        sd->highScore->Show();
        if(WinDlgBox(HWND_DESKTOP, // Show the game over dialog
                     hwnd,
                     GameOverDlgProc,
                     NULLHANDLE,
                     DID_GAMEOVER,
                     NULL) == DID_CANCEL)
           WinPostMsg(hwnd, WM_NEWGAME, 0, 0);
       break;

     case WM_TIMER: // The timer message that, makes pieces move
           owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
           wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
           // The game stops while the window has no focus, unless Background Run is on
           if((wd->hasFocus || wd->psd->bgrun) && !wd->gamePaused && wd->gamePlaying)
           if(!wd->figure->Move(wd->direction, *(wd->board)))
              {
               if(wd->board->Finished())
                  WinPostMsg(hwnd, WM_GAMEOVER, 0, 0);
               else
               {
                sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
                sd->digitalPanel->AddToValue(SC_PIECESCORE*wd->psd->level);
                linesRemoved = wd->board->Evaluate(wd->direction);
               if(linesRemoved)
                 {
                  sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
                  sd->digitalPanel->AddToValue(linesRemoved*SC_LINESCORE*wd->psd->level);
                  sd->digitalPanel->Draw();
                  linesRemoved=0;
                }
                sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
                *(wd->figure) = *(sd->figure);
                Animation(hwnd);
                wd->figure->Draw();
                wd->currentBitmapID = wd->figure->GetBitmapID();
                wd->direction = sd->dir;
                WinPostMsg(sd->hwndNext, WM_NEXT, 0, 0);
               }
              }
        break;

     case WM_PLAYSOUND: // Play the new piece sound
         owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
         if(owd->threadRunning && owd->hwndObject)
           WinPostMsg(owd->hwndObject, WM_POP, 0, 0);
        break;

     case WM_SHOW: // Window about to show
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        InitWindow(hwnd);
        if(!wd->psd->game) // If it was hidden, then don't show it
           WinShowWindow(wd->hwndFrame, FALSE);
         break;

     case WM_NEWGAME: // Start a new game
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         sd->digitalPanel->SetValue(0);
         sd->digitalPanel->Draw();
         WinSendMsg(hwnd, WM_CREATEOBJECTS, 0, 0);
         wd->gamePaused = FALSE;
         WinSetWindowText(wd->hwndFrame, tr(STR_WIN_GAME));
         wd->board->DrawArea(ALL);
         *(wd->figure) = *(sd->figure);
         wd->figure->Draw();
         wd->gamePlaying = TRUE;
         UpdateGameMenus(TRUE, FALSE);
         WinPostMsg(sd->hwndNext, WM_NEXT, 0, 0);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         sd->digitalPanel->AddToValue(SC_PIECESCORE*wd->psd->level);
        break;

     case WM_PAUSEGAME: // Pause the game
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(wd->gamePlaying && !wd->gamePaused)
            {
             wd->gamePaused = TRUE;
             WinSetWindowText(wd->hwndFrame, tr(STR_WIN_PAUSED));
             UpdateGameMenus(TRUE, TRUE);
            }
        break;

     case WM_RESUMEGAME: // Resume game
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(wd->gamePlaying && wd->gamePaused)
            {
             wd->gamePaused = FALSE;
             WinSetWindowText(wd->hwndFrame, tr(STR_WIN_GAME));
             UpdateGameMenus(TRUE, FALSE);
            }
        break;

     case WM_FOCUSCHANGE:// again a trick to intercept the hide button message
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         wd->hasFocus = (BOOL) SHORT1FROMMP(mp2);
         hwndAux = ParentClient();
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->game && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(IDM_GAMEWINDOW, 0), 0);
        break;

     case WM_DESTROY: // Window about to be destroyed
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinReleasePS(wd->hps); // Release the Presentation Space
         WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, wd->ulTimerID);
          // stop the timer
         for(i=0; i<=6; ++i)
          GpiDeleteBitmap(wd->hbmp[i]); // Delete the bitmaps from memory
         if(wd->board!=NULL)
          delete wd->board; // delete the board object
         if(wd->figure!=NULL)
          delete wd->figure; // delete the figure object
         free(wd); // free memory used by the private window data
         owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
         if(owd->threadRunning)
            {
             if(owd->hwndObject)
                WinPostMsg(owd->hwndObject, WM_QUIT, 0, 0);// quit the object window
             DosKillThread(owd->tid); // Kill the sound thread
            }
         free(owd);// Free memory used by the object window data
        break;

     default:
        break;
    }
  return(WinDefWindowProc(hwnd, msg, mp1, mp2)); // the other events are handled by the
                                                // default window procedure
}


VOID DrawSquareOnGame(HWND hwnd, LONG x, LONG y, INT bitmapID)
// Draws a square at a given position on the game window
{
 POINTL p;
 PWINDOWDATA wd;

 y = 19-y;
 p.x = (x)*CELL;
 p.y = (y)*CELL;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinDrawBitmap(wd->hps, wd->hbmp[bitmapID-1], NULL, &p, 0, 0, DBM_NORMAL);
 return;
}

VOID DrawSquareOnNext(HWND hwnd, LONG x, LONG y, INT bitmapID)
//Draws a square at a given position on the next window
{
 POINTL p;
 PNEXTWINDOWDATA wd;

 p.x = (x)*CELL;
 p.y = (y)*CELL;

 wd = (PNEXTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinDrawBitmap(wd->hps, wd->hbmp[bitmapID-1], NULL, &p, 0, 0, DBM_NORMAL);
 return;
}

static VOID DrawCenterBevel(HPS hps)
// Draws the 3D look of the gray square in the middle of the game window
{
 POINTL pt[3];

 pt[0].x = 8*CELL;
 pt[0].y = 8*CELL;
 pt[1].x = 8*CELL;
 pt[1].y = 12*CELL;
 pt[2].x = 12*CELL;
 pt[2].y = 12*CELL;
 GpiMove(hps, &pt[0]);
 GpiSetColor(hps, CLR_DARKGRAY);
 GpiPolyLine(hps, 2, pt+1);

 pt[1].x = 12*CELL;
 pt[1].y = 8*CELL;
 pt[2].x = 12*CELL;
 pt[2].y = 12*CELL;
 GpiMove(hps, &pt[0]);
 GpiSetColor(hps, CLR_WHITE);
 GpiPolyLine(hps, 2, pt+1);
}

VOID ClearSquare(HWND hwnd, LONG x, LONG y)
//Clears a square
{
 PWINDOWDATA wd;
 RECTL rcl;
 ULONG color = CLR_BLACK;

 if((x >= 8) && (y >=8) && (x <= 11) && (y <= 11)) // if the position is on the gray square
     color = CLR_PALEGRAY;

 y = 19-y;
 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 rcl.xLeft =   (x)*CELL;
 rcl.yBottom = (y)*CELL;
 rcl.xRight =  (x)*CELL+CELL;
 rcl.yTop =    (y)*CELL+CELL;
 WinFillRect(wd->hps, &rcl, color);

 DrawCenterBevel(wd->hps);

 return;
}

VOID InitWindow(HWND hwnd)
// Initializes the game window
{
 PWINDOWDATA wd;
 RECTL rcl;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinSetWindowPos(wd->hwndFrame, HWND_TOP, wd->psd->rclGame.xLeft, wd->psd->rclGame.yBottom,
                 wd->psd->rclGame.xRight, wd->psd->rclGame.yTop, SWP_SIZE | SWP_MOVE);
 WinQueryWindowRect(hwnd, &rcl);
 WinInvalidateRect(hwnd, &rcl, FALSE);
}

VOID PaintWindow(HWND hwnd)
// Paints the game window
{
 RECTL rcl;
 PWINDOWDATA wd;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinQueryWindowRect(hwnd, &rcl);
 WinFillRect(wd->hps, &rcl, CLR_BLACK);
 rcl.xLeft =   8*CELL;
 rcl.yBottom = 8*CELL;
 rcl.xRight =  12*CELL;
 rcl.yTop =    12*CELL;
 WinFillRect(wd->hps, &rcl, CLR_PALEGRAY);

 DrawCenterBevel(wd->hps);

 if(wd->board != NULL && wd->figure != NULL)
    {
     wd->board->DrawArea(ALL);
     wd->figure->Draw();
    }
}

INT Random(INT range)
// Gives a random number in [0..range]
{
 INT i=-1;

 while((i<0) || (i>range))
    i=rand()%(range+1);
 return(i);
}

DIR NewDirection()
// Gives a new direction randomly
{
 switch(Random(3))
    {
     case 0:
        return(UP);

     case 1:
        return(DOWN);

     case 2:
        return(LEFT);

     case 3:
        return(RIGHT);

     default:
        break;
    }

 return(DOWN);
}

VOID Animation(HWND hwnd)
// Animates the gray square. The Detail menu selects the animation:
// High = smooth, Medium = like the original, Low = none.
{
 POINTL p1, p2;
 INT    x, y, cx, cy, step, delay;
 PWINDOWDATA wd;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);

 switch(wd->psd->detaillevel)
    {
     case 0:
        step = 5; delay = 15;
       break;

     case 1:
        step = 10; delay = 30;
       break;

     default:
        step = 0; delay = 0;
       break;
    }

 step *= SCALE;
 if(step)
    for(y=150*SCALE,x=150*SCALE,cx=170*SCALE, cy=170*SCALE ; x>8*CELL && y>8*CELL && cx<200*SCALE && cy<200*SCALE; x-=step, y-=step, cx+=step, cy+=step)
       {
        p1.x = x;
        p1.y = y;
        p2.x = cx;
        p2.y = cy;
        GpiMove(wd->hps, &p1);
        GpiSetColor(wd->hps, CLR_BLUE);
        GpiBox(wd->hps, DRO_OUTLINE, &p2, 0, 0);
        DosSleep(delay);
        GpiSetColor(wd->hps, CLR_PALEGRAY);
        GpiBox(wd->hps, DRO_OUTLINE, &p2, 0, 0);
       }
 WinPostMsg(hwnd, WM_PLAYSOUND, 0, 0);
}


// ---------------------------------------------------------------------------
// Logo window shown at startup
// ---------------------------------------------------------------------------

VOID LogoWindow()
// Displays the logo window at startup
{
 HWND    hwndFrame, hwndClient;
 HMQ     hmq;
 HAB     hab;
 QMSG  qmsg;
 PSZ   pszTitle = "";
 PSZ   pszClassName = "Logo";
 ULONG ulCreateFlags = FCF_DLGBORDER  |   FCF_SHELLPOSITION;
 ULONG ulTimerID;

 hab = WinInitialize(0);
 hmq = WinCreateMsgQueue(hab, 0);
 WinRegisterClass(hab,
                  pszClassName,
                  LogoWindowProc,
                  CS_SIZEREDRAW,
                  0);

 hwndFrame = WinCreateStdWindow(HWND_DESKTOP,
                                WS_VISIBLE,
                                &ulCreateFlags,
                                pszClassName,
                                pszTitle,
                                NULL,
                                NULLHANDLE,
                                WID_MAIN,
                                &hwndClient);

  ulTimerID = WinStartTimer(hab, hwndClient, TID_LOGO, 3500);
  while(WinGetMsg(hab, &qmsg, 0, 0, 0))
     WinDispatchMsg(hab, &qmsg);

  WinStopTimer(hab, hwndClient, ulTimerID);
  WinDestroyWindow(hwndFrame);
  WinDestroyMsgQueue(hmq);
  WinTerminate(hab);
}

MRESULT EXPENTRY LogoWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
// This is the logotype window procedure
{
 static HBITMAP hbmp = NULLHANDLE;
 HPS     hps;
 RECTL   rcl,desktopRcl;
 POINTL  ptl;
 HWND    hwndFrame;

 switch(msg)
    {
     case WM_CREATE: // Load the logotype bitmap
        hps = WinGetPS(hwnd);
        hbmp = GpiLoadBitmap(hps, NULLHANDLE, BID_LOGO, 400, 200);
        WinReleasePS(hps);
       break;

     case WM_SHOW: // When shown, center it at the desktop, and invalidate it to be painted
        hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
        WinQueryWindowRect(HWND_DESKTOP, &desktopRcl);
        ptl.x =(LONG) (desktopRcl.xRight - 408)/2;
        ptl.y =(LONG) (desktopRcl.yTop - 208)/2;
        WinSetWindowPos(hwndFrame, HWND_TOP, ptl.x, ptl.y, 408, 208, SWP_SIZE | SWP_MOVE);
        WinQueryWindowRect(hwnd, &rcl);
        WinInvalidateRect(hwnd, &rcl, FALSE);
       break;

     case WM_PAINT: // Paint the window with the Warptris bitmap
        hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
        ptl.x=0;
        ptl.y=0;
        if(hbmp != NULLHANDLE)
           WinDrawBitmap(hps, hbmp, NULL, &ptl, 0, 0, DBM_NORMAL);
        WinEndPaint(hps);
       return(0);

     case WM_TIMER: // At timer event, just quit
         WinPostMsg(hwnd, WM_QUIT, 0, 0);
        break;

     case WM_BUTTON1CLICK: // At button click, quit
         WinPostMsg(hwnd, WM_QUIT, 0, 0);
        break;

     case WM_DESTROY: // When Destroyed delete the bitmap
        if(hbmp != NULLHANDLE)
           GpiDeleteBitmap(hbmp);
        hbmp = NULLHANDLE;
       break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2));
  // The rest is handled by the default window procedure
}

// ---------------------------------------------------------------------------
// Sound. The WAV files are in the "sounds" directory next to WarpTris.exe.
// ---------------------------------------------------------------------------

static VOID MciSend(PSZ pszCommand)
{
 if(pfnMciSendString)
    pfnMciSendString(pszCommand, NULL, 0, 0, 0);
}

static VOID MciOpen(const CHAR *pszFile, const CHAR *pszAlias)
// open <exe directory>\sounds\<file> alias <alias> wait
{
 CHAR szBuffer[CCHMAXPATH+64];

 strcpy(szBuffer, "open ");
 strcat(szBuffer, szExeDir);
 strcat(szBuffer, "sounds\\");
 strcat(szBuffer, pszFile);
 strcat(szBuffer, " alias ");
 strcat(szBuffer, pszAlias);
 strcat(szBuffer, " wait");
 MciSend((PSZ) szBuffer);
}

VOID OpenPopFile() // opens the pop.wav file, using the mci string interpreter
{
 MciOpen("pop.wav", "pop");
}

VOID ClosePopFile() // closes the pop.wav file
{
 MciSend((PSZ) "close pop wait");
}

VOID PlaySound(ULONG ulSoundID)
// Note: The pop.wav file must always be open when the game is playing, in order
//        not to show disk activity everytime the pop sound is heard.
//       That's why the code below, isn't very effective.
//       I still have to learn how to work with play lists.:)
{
 switch(ulSoundID)
    {
     case SID_POP: // Pop sound is to be played
       MciSend((PSZ) "play pop wait");
       MciSend((PSZ) "seek pop to 0 wait");
       break;

     case SID_OVER: // Game over sound is to be played
       ClosePopFile();
       MciOpen("over.wav", "over");
       MciSend((PSZ) "play over wait");
       MciSend((PSZ) "close over wait");
       OpenPopFile();
        break;

     case SID_HIGH: // Highscore sound is to be played
       ClosePopFile();
       MciOpen("high.wav", "high");
       MciSend((PSZ) "play high wait");
       MciSend((PSZ) "close high wait");
       OpenPopFile();
        break;

     default:
        break;
    }
}

VOID _System SoundThread(HWND game)
 // This is the sound thread function, the handle of the game window is passed as the argument
 // in order for this thread to access the private game window data.
{
 HAB  hab;
 HMQ  hmq;
 QMSG qmsg;
 PSZ  pszObjectClass = "Object Window Class";
 HWND hwndObject;
 POBJECTWINDOWDATA owd;

 hab = WinInitialize(0);
 hmq = WinCreateMsgQueue(hab, 0);
 WinRegisterClass(hab,
                  pszObjectClass,
                  ObjectWindowProc,
                  0,
                  0);

 hwndObject = WinCreateWindow( HWND_OBJECT, pszObjectClass, "",
             0, 0, 0, 0, 0, HWND_OBJECT, HWND_BOTTOM, 0, NULL, NULL );

 owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(game, 8); // get the pointer for the
                                                      // game window private data structure
 owd->hwndObject = hwndObject;// give it the handle of the object window

 while(WinGetMsg(hab, &qmsg, 0, 0, 0)) // just loop
    WinDispatchMsg(hab, &qmsg);

 WinDestroyWindow(hwndObject); // destroy the object window
 WinDestroyMsgQueue(hmq); // destroy the message queue
 WinTerminate(hab); // Free up PM resources
}

MRESULT EXPENTRY ObjectWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static HWND hwndAux;
 PPARENTWINDOWDATA pwd;
 switch(msg)
    {
     case WM_CREATE: // Get the parent window handle and open the pop.wav file
         hwndAux = ParentClient();
         OpenPopFile();
        break;

     case WM_POP: // Play pop sound
        pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
        if(pwd->psd->sound)
         PlaySound(SID_POP);
        break;

     case WM_OVER: // Play game over sound
        pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
        if(pwd->psd->sound)
         PlaySound(SID_OVER);
        break;

     case WM_HIGH: // Play the high score sound
        pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
        if(pwd->psd->sound)
         PlaySound(SID_HIGH);
        break;

     case WM_DESTROY: // When destroyed just close the pop.wav file
         ClosePopFile();
        break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2)); // The rest goes to WinDefWindowProc
}

// ---------------------------------------------------------------------------
// Settings (WarpTris.cfg in the working directory)
// ---------------------------------------------------------------------------

VOID ReadSettings(PSETTINGSDATA psd)
 // Reads the settings saved on the WarpTris.cfg file. The file is a binary copy
 // of the SETTINGSDATA structure: saveonexit, detaillevel, current_lang come first.
 // A shorter (older) file leaves the missing fields at their defaults.
{
 FILE  *fp;
 size_t got;

 memset(psd, 0, sizeof(SETTINGSDATA));
 psd->saveonexit = 1;
 psd->detaillevel = 1;
 psd->current_lang = LANG_EN;
 psd->sound = 1;
 psd->high  = 1;
 psd->next  = 1;
 psd->score = 1;
 psd->game  = 1;
 psd->level = 1;
 psd->bgrun = 0;
 cfgLoaded = FALSE;

 fp = fopen("WarpTris.cfg", "rb");
 if(fp != NULL)
    {
     got = fread(psd, 1, sizeof(SETTINGSDATA), fp);
     fclose(fp);
     cfgLoaded = (got >= 9*sizeof(ULONG) + 5*sizeof(RECTL)); // positions were stored too
    }

 // validate what has been read
 if(psd->saveonexit > 1)  psd->saveonexit = 1;
 if(psd->detaillevel > 2) psd->detaillevel = 1;
 if(psd->current_lang >= LANG_COUNT) psd->current_lang = LANG_EN;
 if(psd->sound > 1)  psd->sound = 1;
 if(psd->high  > 1)  psd->high = 1;
 if(psd->next  > 1)  psd->next = 1;
 if(psd->score > 1)  psd->score = 1;
 if(psd->game  > 1)  psd->game = 1;
 if(psd->level < 1 || psd->level > 3) psd->level = 1;
 if(psd->bgrun > 1)  psd->bgrun = 0;

 if(cfgLoaded)
    if(psd->rclGame.xRight < 100*SCALE || psd->rclGame.yTop < 100*SCALE ||
       psd->rclScore.xRight < 50*SCALE || psd->rclScore.yTop < 30*SCALE ||
       psd->rclNext.xRight < 50*SCALE  || psd->rclNext.yTop < 30*SCALE ||
       psd->rclHigh.xRight < 50*SCALE  || psd->rclHigh.yTop < 30*SCALE)
       cfgLoaded = FALSE; // damaged positions: arrange the windows again
}

VOID SaveSettings(PSETTINGSDATA psd)
// Saves the settings on the WarpTris.cfg file
{
 SWP  swpWindowPos;
 HWND hwndAux, hwndParentFrame, hwndParentClient;
 FILE *fp;

 hwndParentFrame = WinWindowFromID(HWND_DESKTOP, WID_PARENT);
 WinQueryWindowPos(hwndParentFrame, &swpWindowPos);
 psd->rclParent.xRight = swpWindowPos.cx;
 psd->rclParent.yTop = swpWindowPos.cy;
 psd->rclParent.xLeft = swpWindowPos.x;
 psd->rclParent.yBottom = swpWindowPos.y;

 hwndParentClient = WinWindowFromID(hwndParentFrame, FID_CLIENT);
 hwndAux = WinWindowFromID(hwndParentClient, WID_MAIN);
 WinQueryWindowPos(hwndAux, &swpWindowPos);
 psd->rclGame.xRight = swpWindowPos.cx;
 psd->rclGame.xLeft = swpWindowPos.x;
 psd->rclGame.yTop = swpWindowPos.cy;
 psd->rclGame.yBottom = swpWindowPos.y;

 hwndAux = WinWindowFromID(hwndParentClient, WID_NEXT);
 WinQueryWindowPos(hwndAux, &swpWindowPos);
 psd->rclNext.xRight = swpWindowPos.cx;
 psd->rclNext.xLeft = swpWindowPos.x;
 psd->rclNext.yTop = swpWindowPos.cy;
 psd->rclNext.yBottom = swpWindowPos.y;

 hwndAux = WinWindowFromID(hwndParentClient, WID_SCORE);
 WinQueryWindowPos(hwndAux, &swpWindowPos);
 psd->rclScore.xRight = swpWindowPos.cx;
 psd->rclScore.xLeft = swpWindowPos.x;
 psd->rclScore.yTop = swpWindowPos.cy;
 psd->rclScore.yBottom = swpWindowPos.y;

 hwndAux = WinWindowFromID(hwndParentClient, WID_HIGH);
 WinQueryWindowPos(hwndAux, &swpWindowPos);
 psd->rclHigh.xRight = swpWindowPos.cx;
 psd->rclHigh.xLeft = swpWindowPos.x;
 psd->rclHigh.yTop = swpWindowPos.cy;
 psd->rclHigh.yBottom = swpWindowPos.y;

 fp = fopen("WarpTris.cfg", "wb");
 if(fp != NULL)
    {
     fwrite(psd, 1, sizeof(SETTINGSDATA), fp);
     fclose(fp);
    }
}

// ---------------------------------------------------------------------------
// Help: one library per language, WarpTris_en.hlp ... WarpTris_it.hlp
// ---------------------------------------------------------------------------

static const CHAR *szHelpFiles[LANG_COUNT] =
{
 "WarpTris_en.hlp",
 "WarpTris_es.hlp",
 "WarpTris_nl.hlp",
 "WarpTris_de.hlp",
 "WarpTris_fr.hlp",
 "WarpTris_it.hlp"
};

VOID SetHelpLanguage(HWND hwndFrame, INT lang)
// Destroys the help instance and creates a new one with the help library of
// the given language
{
 HELPINIT mainHelp;
 FILE    *fp;
 CHAR     szMsg[CCHMAXPATH+160];

 if(lang < 0 || lang >= LANG_COUNT)
    lang = LANG_EN;

 if(hwndHelpInst != NULLHANDLE)
    {
     WinAssociateHelpInstance(NULLHANDLE, hwndFrame);
     WinDestroyHelpInstance(hwndHelpInst);
     hwndHelpInst = NULLHANDLE;
    }

 // The help library is searched in the help folder next to the executable first
 strcpy(szHelpLib, szExeDir);
 strcat(szHelpLib, "help\\");
 strcat(szHelpLib, szHelpFiles[lang]);
 fp = fopen(szHelpLib, "rb");
 if(fp != NULL)
    fclose(fp);
 else
    strcpy(szHelpLib, szHelpFiles[lang]);

 memset(&mainHelp, 0, sizeof(mainHelp));
 mainHelp.cb = sizeof(HELPINIT);
 mainHelp.ulReturnCode = 0;
 mainHelp.pszTutorialName = NULL;
 mainHelp.phtHelpTable = (PHELPTABLE) MAKEULONG(HID_MAIN, 0xFFFF);
 mainHelp.hmodHelpTableModule = NULLHANDLE;
 mainHelp.hmodAccelActionBarModule = NULLHANDLE;
 mainHelp.idAccelTable = 0;
 mainHelp.idActionBar = 0;

 mainHelp.pszHelpWindowTitle = (PSZ) tr(STR_HELP_TITLE);
 mainHelp.fShowPanelId = CMIC_HIDE_PANEL_ID;
 mainHelp.pszHelpLibraryName = (PSZ) szHelpLib;

 hwndHelpInst = WinCreateHelpInstance(WinQueryAnchorBlock(hwndFrame), &mainHelp);
 if(hwndHelpInst != NULLHANDLE)
    WinAssociateHelpInstance(hwndHelpInst, hwndFrame);
 else if(mainHelp.ulReturnCode != 0)
    {
     sprintf(szMsg, tr(STR_HELP_MISSING), szHelpFiles[lang]);
     WinMessageBox(HWND_DESKTOP, hwndFrame, (PSZ) szMsg, (PSZ) "WarpTris", 0, MB_OK | MB_WARNING | MB_MOVEABLE);
    }
}

VOID ArrangeWindows(PSETTINGSDATA psd, LONG cxClient, LONG cyClient)
// Arranges the windows to their default position, in the middle of the client
// area of the WarpTris window. Game on the left, Score, Next and High Scores
// stacked on the right.
{
 INT  ulResOffset=0; // Offset because of the 768 pixel high resolution
 LONG dx, dy, blockW, blockH, gap=8, colX, top;
 LONG gameCx, gameCy, scoreCx, scoreCy, nextCx, nextCy, highCx, highCy;

 if(WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) > 700)
    ulResOffset=5;

 gameCx  = 320*SCALE + 8;     gameCy  = 320*SCALE + 26 + ulResOffset;
 scoreCx =  95*SCALE + 8;     scoreCy =  27*SCALE + 25 + ulResOffset;
 nextCx  = 150*SCALE + 8;     nextCy  = 100*SCALE + 25 + ulResOffset;
 highCx  = nextCx;            highCy  = 127*SCALE + ulResOffset;

 blockW = gameCx + 12 + nextCx;
 blockH = gameCy;
 dx = (cxClient - blockW)/2;
 dy = (cyClient - blockH)/2;
 if(dx < 0) dx = 0;
 if(dy < 0) dy = 0;

 colX = dx + gameCx + 12;
 top  = dy + gameCy;

 psd->rclGame.xLeft = dx;      psd->rclGame.yBottom = dy;
 psd->rclGame.xRight = gameCx; psd->rclGame.yTop = gameCy;

 psd->rclScore.xLeft = colX;   psd->rclScore.yBottom = top - scoreCy;
 psd->rclScore.xRight = scoreCx; psd->rclScore.yTop = scoreCy;

 psd->rclNext.xLeft = colX;    psd->rclNext.yBottom = psd->rclScore.yBottom - gap - nextCy;
 psd->rclNext.xRight = nextCx; psd->rclNext.yTop = nextCy;

 psd->rclHigh.xLeft = colX;    psd->rclHigh.yBottom = psd->rclNext.yBottom - gap - highCy;
 psd->rclHigh.xRight = highCx; psd->rclHigh.yTop = highCy;
}
// end of WarpTris source