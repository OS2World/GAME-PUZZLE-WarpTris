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
// pcamara@geocities.com
// dm03mi@antero.uac.pt


// defines
#define INCL_WIN // Include Win*  API functions
#define INCL_GPI // Include Gpi*  API functions
#define INCL_DOS // Include Dos*  API functions
#define INCL_OS2MM // Include multimedia functions, namely mci*
#define INCL_MMOS2
#define INCL_MCIOS2
#define INCL_MMIOOS2
// includes
#include <os2.h> // os2 API header file
#include <os2me.h> // os2 multimedia functions prototypes, defines and stuff...

#include <stdio.h> // standard C includes
#include <stdlib.h>
#include <string.h>

#include "WarpTris.h" // various defines for the program

// Forward classes definitions
class Board;
class Figure;
class DigitalPanel;
class HighScore;

// Structures that belong to windows

typedef struct {
                ULONG sound, high, game, next, score, level;
                RECTL rclParent, rclGame, rclScore, rclNext, rclHigh;
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
                     hwndPopGame;
                PSETTINGSDATA psd;
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
MRESULT EXPENTRY       PInfoDlgProc(HWND, ULONG, MPARAM, MPARAM); // Product Information Dialog
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
VOID        ReadSettings(HAB, PSETTINGSDATA); // Reads the settings saved on WarpTris.INI
VOID        SaveSettings(HAB, PSETTINGSDATA); // Saves the settings on WarpTris.INI
VOID      ArrangeWindows(PSETTINGSDATA); // Restores the default window positions
VOID           SetupHelp(HAB, HWND); // Sets up the help manager
INT               Random(INT); // Gives a random number in the range [0..argument]
DIR         NewDirection(VOID);// Gives a new direction randomly

// Include the objects that were defined on top
#include "Board.h"
#include "Figure.h"
#include "Digital.h"
#include "HighScore.h"

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

 PSZ   pszTitle = "Game"; // Titles and class names
 PSZ   pszClassName = "WarpTris for OS/2";
 PSZ   pszParentTitle = "WarpTris 1.0";
 PSZ   pszParentClassName = "Parent Class";
 PSZ   pszScoreTitle = "Score";
 PSZ   pszScoreClassName= "Score Window Class";
 PSZ   pszNextTitle = "Next";
 PSZ   pszNextClassName = "Next Window Class";
 PSZ   pszHighTitle = "High Scores";
 PSZ   pszHighClassName = "High Window Class";
 PSZ   pszNoteTitle = "WarpTris Properties";
 PSZ   pszNoteClassName = "Properties Window Class";
  // Various windows creation flags
 ULONG ulParentCreateFlags = FCF_SYSMENU       |   FCF_TITLEBAR     |
                             FCF_SIZEBORDER    |   FCF_TASKLIST     |
                             FCF_SHELLPOSITION |   FCF_MINBUTTON    |
                             FCF_MAXBUTTON     |   FCF_MENU         |
                             FCF_ICON          |   FCF_ACCELTABLE;
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

 LogoWindow(); //Display Logotype

 hab = WinInitialize(0); // Initialize PM and get an HAB
 hmq = WinCreateMsgQueue(hab, 25); // Create the Msg Queue
  // Register the main thread window classes
 WinRegisterClass(hab,
                  pszParentClassName,
                  ParentWindowProc,
                  CS_SIZEREDRAW,
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
   // The Warptris client window is the parent off all the other frame windows
 hwndParentFrame = WinCreateStdWindow(HWND_DESKTOP,
                                      WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                                      &ulParentCreateFlags,
                                      pszParentClassName,
                                      pszParentTitle,
                                      NULL,
                                      NULLHANDLE,
                                      WID_PARENT,
                                      &hwndParentClient);

 hwndFrame = WinCreateStdWindow(hwndParentClient,
                                WS_VISIBLE,
                                &ulCreateFlags,
                                pszClassName,
                                pszTitle,
                                NULL,
                                NULLHANDLE,
                                WID_MAIN,
                                &hwndClient);

 hwndScoreFrame = WinCreateStdWindow(hwndParentClient,
                                     WS_VISIBLE,
                                     &ulScoreCreateFlags,
                                     pszScoreClassName,
                                     pszScoreTitle,
                                     NULL,
                                     NULLHANDLE,
                                     WID_SCORE,
                                     &hwndScoreClient);

 hwndNextFrame = WinCreateStdWindow(hwndParentClient,
                                    WS_VISIBLE,
                                    &ulNextCreateFlags,
                                    pszNextClassName,
                                    pszNextTitle,
                                    NULL,
                                    NULLHANDLE,
                                    WID_NEXT,
                                    &hwndNextClient);

 hwndHighFrame = WinCreateStdWindow(hwndParentClient,
                                    WS_VISIBLE,
                                    &ulHighCreateFlags,
                                    pszHighClassName,
                                    pszHighTitle,
                                    NULL,
                                    NULLHANDLE,
                                    WID_HIGH,
                                    &hwndHighClient);

 hwndNoteFrame = WinCreateStdWindow(hwndParentClient,
                                    0,
                                    &ulNoteCreateFlags,
                                    pszNoteClassName,
                                    pszNoteTitle,
                                    NULL,
                                    NULLHANDLE,
                                    WID_NOTE,
                                    &hwndNoteClient);
   // initialize the warptris window data structures
 pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParentClient, 0);
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

 SetupHelp(hab, hwndParentFrame); // Call the function that initializes the help manager

 while(appState == APPNORMAL) // external while loop (see the comment on the appState var)
 {
  while(WinGetMsg(hab, &qmsg, 0, 0, 0)) // main application loop
     WinDispatchMsg(hab, &qmsg);

  if((INT) WinSendMsg(hwndParentClient, WM_VERIFY, 0, 0) == DID_OK) // Verify exit
     appState = USERQUIT;
  else
     WinPostMsg(hwndClient, WM_RESUMEGAME, 0, 0);
 }
 // Destroy all windows
 // (When a window is destroyed, all her child windows are also destroyed)
 WinDestroyWindow(hwndParentFrame);
 WinDestroyMsgQueue(hmq); // Destroy the message queue
 WinTerminate(hab); // Release the PM resources used by WarpTris

 free(sd->pszName); // free memory used by the string pszName
 free(sd); // free memory used by the shared data structure

 return(0);
}

MRESULT EXPENTRY NoteBookWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 static ULONG color = CLR_PALEGRAY;
 RECTL rcl;
 HWND hwndAux;
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
                                            0, -30, 350, 300,
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

         WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage1ID, MPFROMP("Page 1 of 1"));
         WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage2ID, MPFROMP("Page 1 of 1"));
         WinSendMsg(wd->hwndNoteBook, BKM_SETSTATUSLINETEXT, (MPARAM)wd->ulPage3ID, MPFROMP("Page 1 of 1"));

         WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage1ID), MPFROMP("Sound"));
         WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage2ID), MPFROMP("Windows"));
         WinSendMsg(wd->hwndNoteBook, BKM_SETTABTEXT, MPFROMLONG(wd->ulPage3ID), MPFROMP("Impulse"));

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

         WinSendMsg(wd->hwndNoteBook, BKM_SETDIMENSIONS, MPFROM2SHORT(83, 25), MPFROMSHORT(BKA_MAJORTAB));

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

     case WM_CLOSE: // if the window is closed, then don't destroy it, just hide it
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinShowWindow(wd->hwndFrame, FALSE);
        return((MRESULT) FALSE);

     case WM_SHOW: // When window is shown, set its position
         wd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinSetWindowPos(wd->hwndFrame, HWND_TOP, 100, 50, 355, 296, SWP_SIZE | SWP_MOVE);
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
         WinSendMsg(hwndEntryField, EM_SETTEXTLIMIT, (MPARAM) 15, 0);
         WinSetPresParam(hwndEntryField, PP_FONTNAMESIZE, 14, "10.System VIO");
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
                WinQueryWindowText(hwndEntryField, 15, sd->pszName);
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

MRESULT EXPENTRY PInfoDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch (msg)
    {
     default: // Nothing to do here, just show it, and wait for the user to press
              // the OK button to dismiss it
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2)); // Here the default dialog procedure
                                             // handles everything
}



MRESULT EXPENTRY HighWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 HPS hps;
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
         sd->highScore = new HighScore(wd->hwndListBox, hwnd); // create the highscore object
         sd->highScore->Read();// Tell the highscore object to read the high scores from the SCORES.INI file
         sd->highScore->Show();// Tell him also to put those scores in the listbox
         WinSetPresParam(wd->hwndListBox, PP_FONTNAMESIZE, 14, "10.System VIO");
         WinShowWindow(wd->hwndListBox, TRUE); // Finally, show it!
        break;

     case WM_FOCUSCHANGE: // This is a way of changing the check status  of the
                          // menuitem High Score on the menu Windows when the window
                          // is hidden from the hide button. It must exist
                          // a better way of doing this, but I haven't found it,
                          // so... anyway it works!
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->high && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_HIGHWINDOW, 0), 0);
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
          wd->hbmp[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+1, 16, 16);
           // Load the bitmaps of the pieces
         for(i=0; i<4; ++i)
          wd->hbmpDirection[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+30, 32, 32);
           // Load the bitmaps of the direction arrows
         wd->hbmpBackground = GpiLoadBitmap(wd->hps, NULLHANDLE, BID_NEXTBACKGROUND, 150, 100);
           // Load the background bitmap
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
          p.x = 100;
          p.y = 34;
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->next && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_NEXTWINDOW, 0), 0);
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
 HWND hwndFrame, hwndAux;
 PSHAREDDATA sd;
 PPARENTWINDOWDATA pwd;

 switch(msg)
    {
     case WM_CREATE: // Allocate and initialize private data structure
         wd = (PSCOREWINDOWDATA) malloc(sizeof(SCOREWINDOWDATA));
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hwndParent = WinQueryWindow(wd->hwndFrame, QW_PARENT);
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->score && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_SCOREWINDOW, 0), 0);
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_SOUNDON, 0), 0);
               }
              return 0;

            case DRB_OFF:
               if(SHORT2FROMMP(mp1)==BN_CLICKED && !first)
                 {
                  pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                  WinCheckButton(hwnd, DRB_ON, 0);
                  WinCheckButton(hwnd, DRB_OFF, 1);
                  pwd->psd->sound = 0;
                  WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_SOUNDOFF, 0), 0);
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
         hwndParent = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
                WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(CMD_HIGHWINDOW,0),0);
              return(0);

            case DCB_NEXT:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->next = WinQueryButtonCheckstate(hwnd, DCB_NEXT);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(CMD_NEXTWINDOW,0),0);
              return(0);

            case DCB_SCORE:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->score = WinQueryButtonCheckstate(hwnd, DCB_SCORE);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(CMD_SCOREWINDOW,0),0);
              return(0);

            case DCB_GAME:
               WinDefDlgProc(hwnd, msg, mp1, mp2);
               pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndParent, 0);
               pwd->psd->game = WinQueryButtonCheckstate(hwnd, DCB_GAME);
               WinPostMsg(hwndParent, WM_COMMAND, MPFROM2SHORT(CMD_GAMEWINDOW,0),0);
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         switch(pwd->psd->level)
            {
             case 1:
                WinCheckButton(hwnd, DRB_DONKEY, 1);
                WinCheckButton(hwnd, DRB_FORMULA1, 0);
                WinCheckButton(hwnd, DRB_WARP, 0);
               break;

             case 2:
                WinCheckButton(hwnd, DRB_DONKEY, 0);
                WinCheckButton(hwnd, DRB_FORMULA1, 1);
                WinCheckButton(hwnd, DRB_WARP, 0);
               break;

             case 3:
                WinCheckButton(hwnd, DRB_DONKEY, 0);
                WinCheckButton(hwnd, DRB_FORMULA1, 0);
                WinCheckButton(hwnd, DRB_WARP, 1);
               break;
            }
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
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_BEGINNER,0),0);
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
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_INTERMEDIATE,0),0);
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
                WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_EXPERT,0),0);
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
     case WM_INITDLG: // Nothing to initialize here
        break;

     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_OK: // If the OK button has been pressed, dismiss and return DID_OK
                WinDismissDlg(hwnd, DID_OK);
               break;

            case DID_CANCEL:
                WinDismissDlg(hwnd, DID_CANCEL); //If canceled, dismiss and return DID_CANCEL
               break;
           }

     default:
        break;
    }
 return(WinDefDlgProc(hwnd, msg, mp1, mp2));//The default dialog procedure will handle the rest
}


MRESULT EXPENTRY ParentWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 RECTL rcl, desktopRcl;
 ULONG usResponse;
 POINTL ptl;
 HPS   hps;
 HWND  hwndAux, hwndHelp;
 BOOL  newStatus;
 PPARENTWINDOWDATA wd;
 PPROPERTIESWINDOWDATA pwd;

 switch(msg)
    {
     case WM_CREATE: //Initialize data structures and menus
         WinDefWindowProc(hwnd, msg, mp1, mp2);
         wd = (PPARENTWINDOWDATA) malloc(sizeof(PARENTWINDOWDATA));
         wd->psd = (PSETTINGSDATA) malloc(sizeof(SETTINGSDATA));
         ReadSettings(WinQueryAnchorBlock(hwnd), wd->psd);
         wd->hwndFrame = WinQueryWindow(hwnd, QW_PARENT);
         wd->hwndMenu = WinWindowFromID(wd->hwndFrame, FID_MENU);
         wd->hwndPop = WinLoadMenu(hwnd, 0, MNU_PARENT);
         wd->hwndPopGame = WinLoadMenu(hwnd, 0, MNU_GAME);
         WinCheckMenuItem(wd->hwndMenu, CMD_SCOREWINDOW, wd->psd->score);
         WinCheckMenuItem(wd->hwndMenu, CMD_HIGHWINDOW, wd->psd->high);
         WinCheckMenuItem(wd->hwndMenu, CMD_GAMEWINDOW, wd->psd->game);
         WinCheckMenuItem(wd->hwndMenu, CMD_NEXTWINDOW, wd->psd->next);
         WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDON, wd->psd->sound);
         WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDOFF, !wd->psd->sound);
         WinCheckMenuItem(wd->hwndPop, CMD_SCOREWINDOW, wd->psd->score);
         WinCheckMenuItem(wd->hwndPop, CMD_HIGHWINDOW, wd->psd->high);
         WinCheckMenuItem(wd->hwndPop, CMD_GAMEWINDOW, wd->psd->game);
         WinCheckMenuItem(wd->hwndPop, CMD_NEXTWINDOW, wd->psd->next);
         WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDON, wd->psd->sound);
         WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDOFF, !wd->psd->sound);
         switch(wd->psd->level)
            {
             case 1:
                WinCheckMenuItem(wd->hwndMenu, CMD_BEGINNER, 1);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, 1);
               break;
             case 2:
                WinCheckMenuItem(wd->hwndMenu, CMD_INTERMEDIATE, 1);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, 1);
               break;
             case 3:
                WinCheckMenuItem(wd->hwndMenu, CMD_EXPERT, 1);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, 1);
               break;
            }
         WinSetWindowPtr(hwnd, 0, wd);
         WinPostMsg(hwnd, WM_SHOW, 0, 0);
        return(0);

     case WM_CONTEXTMENU: // a context menu needs to be shown
         wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         if(SHORT2FROMMP(mp2))
            WinQueryPointerPos(hwnd, &ptl); //Where's the mouse pointer?
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
        WinSendMsg(hwnd, WM_PAUSEGAME, 0, 0);
        wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
        usResponse = WinDlgBox(HWND_DESKTOP,
                               hwnd,
                               ExitDlgProc,
                               NULLHANDLE,
                               DID_EXIT,
                               NULL);
        if(usResponse == DID_OK)
          SaveSettings(WinQueryAnchorBlock(hwnd), wd->psd);
        return((MRESULT) usResponse);

     case WM_SHOW: //Window is about to show, so set its size and position
         wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         WinSetWindowPos(wd->hwndFrame, HWND_TOP, wd->psd->rclParent.xLeft, wd->psd->rclParent.yBottom,
                         wd->psd->rclParent.xRight, wd->psd->rclParent.yTop, SWP_SIZE | SWP_MOVE);
        break;

     case WM_PAINT: // Window needs repainting
        hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
        WinFillRect(hps, &rcl, CLR_DARKGREEN);//Just give it a nice green colour
        WinEndPaint(hps);
        break;

     case WM_COMMAND://Handle menu events
        switch(SHORT1FROMMP(mp1))
           {
            case CMD_PROPERTIES:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinShowWindow(wd->hwndNote, TRUE);
                WinSetFocus(HWND_DESKTOP, wd->hwndNote);
               break;

            case CMD_EXIT:
               WinPostMsg(hwnd, WM_CLOSE, 0, 0);
               break;

            case CMD_NEWGAME:
               wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
               WinFocusChange(HWND_DESKTOP,
                              wd->hwndGame,
                              0);
               WinPostMsg(wd->hwndNext, WM_NEXT, 0, 0);
               WinPostMsg(wd->hwndGame, WM_NEWGAME, 0, 0);
               break;

            case CMD_GAMEWINDOW:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                if(WinIsMenuItemChecked(wd->hwndMenu, CMD_GAMEWINDOW))
                  {
                   newStatus = 0;
                   hwndAux = WinQueryWindow(wd->hwndGame, QW_PARENT);
                   WinShowWindow(hwndAux, FALSE);
                  }
                else
                  {
                   newStatus = MIA_CHECKED;
                   hwndAux = WinQueryWindow(wd->hwndGame, QW_PARENT);
                   WinShowWindow(hwndAux, TRUE);
                  }
                WinCheckMenuItem(wd->hwndMenu, CMD_GAMEWINDOW, newStatus);
                WinCheckMenuItem(wd->hwndPop, CMD_GAMEWINDOW, newStatus);
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                if(newStatus) wd->psd->game = 1;
                   else wd->psd->game = 0;
                WinPostMsg(pwd->hwndDlg2, WM_INITDLG, 0, 0);
               break;

            case CMD_SCOREWINDOW:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                if(WinIsMenuItemChecked(wd->hwndMenu, CMD_SCOREWINDOW))
                  {
                   newStatus = 0;
                   hwndAux = WinQueryWindow(wd->hwndScore, QW_PARENT);
                   WinShowWindow(hwndAux, FALSE);
                  }
                else
                  {
                   newStatus = MIA_CHECKED;
                   hwndAux = WinQueryWindow(wd->hwndScore, QW_PARENT);
                   WinShowWindow(hwndAux, TRUE);
                  }
                WinCheckMenuItem(wd->hwndMenu, CMD_SCOREWINDOW, newStatus);
                WinCheckMenuItem(wd->hwndPop, CMD_SCOREWINDOW, newStatus);
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                if(newStatus) wd->psd->score = 1;
                   else wd->psd->score = 0;
                WinPostMsg(pwd->hwndDlg2, WM_INITDLG, 0, 0);
               break;

            case CMD_NEXTWINDOW:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                if(WinIsMenuItemChecked(wd->hwndMenu, CMD_NEXTWINDOW))
                  {
                   newStatus = 0;
                   hwndAux = WinQueryWindow(wd->hwndNext, QW_PARENT);
                   WinShowWindow(hwndAux, FALSE);
                  }
                else
                  {
                   newStatus = MIA_CHECKED;
                   hwndAux = WinQueryWindow(wd->hwndNext, QW_PARENT);
                   WinShowWindow(hwndAux, TRUE);
                  }
                WinCheckMenuItem(wd->hwndMenu, CMD_NEXTWINDOW, newStatus);
                WinCheckMenuItem(wd->hwndPop, CMD_NEXTWINDOW, newStatus);
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                if(newStatus) wd->psd->next = 1;
                   else wd->psd->next = 0;
                WinPostMsg(pwd->hwndDlg2, WM_INITDLG, 0, 0);
               break;

            case CMD_HIGHWINDOW:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                if(WinIsMenuItemChecked(wd->hwndMenu, CMD_HIGHWINDOW))
                  {
                   newStatus = 0;
                   hwndAux = WinQueryWindow(wd->hwndHigh, QW_PARENT);
                   WinShowWindow(hwndAux, FALSE);
                  }
                else
                  {
                   newStatus = MIA_CHECKED;
                   hwndAux = WinQueryWindow(wd->hwndHigh, QW_PARENT);
                   WinShowWindow(hwndAux, TRUE);
                  }
                WinCheckMenuItem(wd->hwndMenu, CMD_HIGHWINDOW, newStatus);
                WinCheckMenuItem(wd->hwndPop, CMD_HIGHWINDOW, newStatus);
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                if(newStatus) wd->psd->high = 1;
                   else wd->psd->high = 0;
                 WinPostMsg(pwd->hwndDlg2, WM_INITDLG, 0, 0);
                break;

            case CMD_BEGINNER:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinPostMsg(wd->hwndGame, WM_CHANGELEVEL, MPFROMLONG(LV_BEGINNER),0);
                WinCheckMenuItem(wd->hwndMenu, CMD_BEGINNER, TRUE);
                WinCheckMenuItem(wd->hwndMenu, CMD_INTERMEDIATE, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_EXPERT, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, TRUE);
                WinCheckMenuItem(wd->hwndPopGame, CMD_INTERMEDIATE, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_EXPERT, 0);
                wd->psd->level = 1;
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinPostMsg(pwd->hwndDlg3, WM_INITDLG, 0, 0);
               break;

            case CMD_INTERMEDIATE:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinPostMsg(wd->hwndGame, WM_CHANGELEVEL, MPFROMLONG(LV_INTERMEDIATE),0);
                WinCheckMenuItem(wd->hwndMenu, CMD_BEGINNER, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_INTERMEDIATE, TRUE);
                WinCheckMenuItem(wd->hwndMenu, CMD_EXPERT, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_INTERMEDIATE, TRUE);
                WinCheckMenuItem(wd->hwndPopGame, CMD_EXPERT, 0);
                wd->psd->level = 2;
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinPostMsg(pwd->hwndDlg3, WM_INITDLG, 0, 0);
               break;

            case CMD_EXPERT:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinPostMsg(wd->hwndGame, WM_CHANGELEVEL, MPFROMLONG(LV_EXPERT),0);
                WinCheckMenuItem(wd->hwndMenu, CMD_BEGINNER, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_INTERMEDIATE, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_EXPERT, TRUE);
                WinCheckMenuItem(wd->hwndPopGame, CMD_BEGINNER, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_INTERMEDIATE, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_EXPERT, TRUE);
                wd->psd->level = 3;
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinPostMsg(pwd->hwndDlg3, WM_INITDLG, 0, 0);
               break;

            case CMD_SOUNDON:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDON, 1);
                WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDOFF, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDON, 1);
                WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDOFF, 0);
                wd->psd->sound = 1;
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinPostMsg(pwd->hwndDlg1, WM_INITDLG, 0, 0);
               break;

            case CMD_SOUNDOFF:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDON, 0);
                WinCheckMenuItem(wd->hwndMenu, CMD_SOUNDOFF, 1);
                WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDON, 0);
                WinCheckMenuItem(wd->hwndPopGame, CMD_SOUNDOFF, 1);
                wd->psd->sound = 0;
                hwndAux = WinWindowFromID(wd->hwndNote, FID_CLIENT);
                pwd = (PPROPERTIESWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
                WinPostMsg(pwd->hwndDlg1, WM_INITDLG, 0, 0);
               break;

            case CMD_PINFO:
                WinDlgBox(HWND_DESKTOP, hwnd, PInfoDlgProc, NULLHANDLE, DID_PINFO, NULL);
               break;

            case CMD_ARRANGE:
                wd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                ArrangeWindows(wd->psd);
                WinPostMsg(wd->hwndGame, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndScore, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndNext, WM_SHOW, 0, 0);
                WinPostMsg(wd->hwndHigh, WM_SHOW, 0, 0);
               break;

            case CMD_GENERALHELP:
                hwndHelp = WinQueryHelpInstance(hwnd);
                WinSendMsg (hwndHelp,
                            HM_DISPLAY_HELP,
                            MPFROMSHORT(HID_GENERAL),
                            MPFROMSHORT(HM_RESOURCEID));
               break;

            case CMD_HELPINDEX:
                hwndHelp = WinQueryHelpInstance(hwnd);
                WinSendMsg(hwndHelp, HM_HELP_INDEX, 0, 0);
               break;

            case CMD_HELPONHELP:
                hwndHelp = WinQueryHelpInstance(hwnd);
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
     case WM_COMMAND:
        switch(SHORT1FROMMP(mp1))
           {
            case DID_CANCEL:
                WinDismissDlg(hwnd, DID_CANCEL);// If canceled, dismiss and return DID_CANCEL
               break;

            case DID_OK:
                WinDismissDlg(hwnd, DID_OK);// If OK pressed, dismiss and return DID_OK
               break;
           }
    }
 return((MRESULT) WinDefDlgProc(hwnd, msg, mp1, mp2));// The rest is up to the default dialog procedure
}

MRESULT EXPENTRY MainWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 INT i, linesRemoved = 0;
 ULONG ulTimerDelay;
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
          wd->hbmp[i] = GpiLoadBitmap(wd->hps, NULLHANDLE, i+1, 16, 16);
         wd->direction = NewDirection();
         wd->hasFocus = TRUE;
         wd->gamePaused = TRUE;
         wd->gamePlaying = FALSE;
         wd->board = NULL;
         wd->figure = NULL;
         wd->hwndParent = WinQueryWindow(WinQueryWindow(wd->hwndFrame, QW_PARENT), QW_PARENT);
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         wd->hwndPop = pwd->hwndPopGame;
         wd->psd = pwd->psd;
         switch(wd->psd->level)
            {
             case 1:
                 ulTimerDelay = LV_BEGINNER;
                break;
             case 2:
                 ulTimerDelay = LV_INTERMEDIATE;
                break;
             case 3:
                 ulTimerDelay = LV_EXPERT;
                break;
            }
         wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, ulTimerDelay);
         WinSetWindowPtr(hwnd, 0, wd);
         owd = (POBJECTWINDOWDATA) malloc(sizeof(OBJECTWINDOWDATA));
         owd->hwndGame = hwnd;
         owd->threadRunning = FALSE;
         owd->tid = 2;
         owd->pfThread = &SoundThread;
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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
       if((SHORT1FROMMP(mp2) == 'p' || SHORT1FROMMP(mp2)=='P') && wd->gamePaused && wd->gamePlaying)
          WinPostMsg(hwnd, WM_RESUMEGAME, 0, 0);// P was pressed and the game was paused, in this case: resume the game
       else if((SHORT1FROMMP(mp2) == 'p' || SHORT1FROMMP(mp2)=='P') && wd->gamePlaying)
          WinPostMsg(hwnd, WM_PAUSEGAME, 0, 0); // else pause the game
       if(wd->hasFocus && !wd->gamePaused && wd->gamePlaying)
           switch(SHORT1FROMMP(mp2)) // handle the game keys
              {
               case '5':
                   wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                   wd->figure->Rotate(*(wd->board));
                  break;

               case '4':
                   wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                   if(wd->direction == UP || wd->direction == DOWN)
                     wd->figure->Move(LEFT, *(wd->board));
                  break;

               case '6':
                   wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                   if(wd->direction == UP || wd->direction == DOWN)
                     wd->figure->Move(RIGHT, *(wd->board));
                  break;

               case '8':
                    wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                    if(wd->direction == LEFT || wd->direction == RIGHT)
                      wd->figure->Move(UP, *(wd->board));
                  break;

               case '2':
                  wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                  if(wd->direction == LEFT || wd->direction == RIGHT)
                    wd->figure->Move(DOWN, *(wd->board));
                  break;

               case ' ':
                   wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                   wd->figure->Fall(wd->direction, *(wd->board));
                   WinPostMsg(hwnd, WM_DROPED, 0, 0);
                  break;

               default:
                  break;
              }
       break;

    case WM_CHANGELEVEL: // Change the level to the value stored in mp1
        switch(LONGFROMMP(mp1))
           {
            case LV_BEGINNER:
                wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, wd->ulTimerID);
                wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, LV_BEGINNER);
               break;

            case LV_INTERMEDIATE:
                wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, wd->ulTimerID);
                wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, LV_INTERMEDIATE);
               break;

            case LV_EXPERT:
                wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
                WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, wd->ulTimerID);
                wd->ulTimerID = WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_TIMER, LV_EXPERT);
               break;

            default:
               break;
           }
       break;

    case WM_DROPED: // A piece as droped, it's time to see if there are lines to remove
        owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwnd, 8);
        wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
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
         sd->digitalPanel->AddToValue(SC_PIECESCORE*wd->psd->level); //mark here ********************************
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
        wd->gamePlaying = FALSE; // the game is no longer being played
        sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
        if(!sd->highScore->New(sd->digitalPanel->GetValue()))
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
           if(wd->hasFocus && !wd->gamePaused && wd->gamePlaying)
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
         if(owd->threadRunning)
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
         wd->board->DrawArea(ALL);
         *(wd->figure) = *(sd->figure);
         wd->figure->Draw();
         wd->gamePlaying = TRUE;
         WinPostMsg(sd->hwndNext, WM_NEXT, 0, 0);
         sd = (PSHAREDDATA) WinQueryWindowPtr(hwnd, 4);
         sd->digitalPanel->AddToValue(SC_PIECESCORE*wd->psd->level);
        break;

     case WM_PAUSEGAME: // Pause the game
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         wd->gamePaused = TRUE;
         WinSetWindowText(wd->hwndFrame, "Game Paused! - Press P to Resume -");
        break;

     case WM_RESUMEGAME: // Resume game
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         wd->gamePaused = FALSE;
         WinSetWindowText(wd->hwndFrame, "Game");
        break;

     case WM_FOCUSCHANGE:// again a trick to intercept the hide button message
         wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
         wd->hasFocus = (BOOL) SHORT1FROMMP(mp2);
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
         pwd = (PPARENTWINDOWDATA) WinQueryWindowPtr(hwndAux, 0);
         if(!WinIsWindowVisible(hwnd) && SHORT1FROMMP(mp2) == FALSE && pwd->psd->game && WinIsWindowVisible(hwndAux))
             WinPostMsg(hwndAux, WM_COMMAND, MPFROM2SHORT(CMD_GAMEWINDOW, 0), 0);
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
         WinPostMsg(owd->hwndObject, WM_QUIT, 0, 0);// quit the object window
         DosKillThread(owd->tid); // Kill the sound thread
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
 p.x = (x)*16;
 p.y = (y)*16;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinDrawBitmap(wd->hps, wd->hbmp[bitmapID-1], NULL, &p, 0, 0, DBM_NORMAL);
 return;
}

VOID DrawSquareOnNext(HWND hwnd, LONG x, LONG y, INT bitmapID)
//Draws a square at a given position on the next window
{
 POINTL p;
 PNEXTWINDOWDATA wd;

 p.x = (x)*16;
 p.y = (y)*16;

 wd = (PNEXTWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinDrawBitmap(wd->hps, wd->hbmp[bitmapID-1], NULL, &p, 0, 0, DBM_NORMAL);
 return;
}


VOID ClearSquare(HWND hwnd, LONG x, LONG y)
//Clears a square
{
 PWINDOWDATA wd;
 RECTL rcl;
 ULONG color = CLR_BLACK;
 PPOINTL pt;


 if((x >= 8) && (y >=8) && (x <= 11) && (y <= 11)) // if the position is on the gray square
     color = CLR_PALEGRAY;

 y = 19-y;
 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 rcl.xLeft =   (x)*16;
 rcl.yBottom = (y)*16;
 rcl.xRight =  (x)*16+16;
 rcl.yTop =    (y)*16+16;
 WinFillRect(wd->hps, &rcl, color);

 pt = (PPOINTL) malloc(3*sizeof(POINTL));
 pt[0].x = 8*16;
 pt[0].y = 8*16;
 pt[1].x = 8*16;
 pt[1].y = 12*16;
 pt[2].x = 12*16;
 pt[2].y = 12*16;
 GpiMove(wd->hps, &pt[0]);
 GpiSetColor(wd->hps, CLR_DARKGRAY);
 GpiPolyLine(wd->hps, 2, pt+1);

 pt[1].x = 12*16;
 pt[1].y = 8*16;
 pt[2].x = 12*16;
 pt[2].y = 12*16;
 GpiMove(wd->hps, &pt[0]);
 GpiSetColor(wd->hps, CLR_WHITE);
 GpiPolyLine(wd->hps, 2, pt+1);
 free(pt);

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
 PPOINTL pt;
 PWINDOWDATA wd;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 WinQueryWindowRect(hwnd, &rcl);
 WinFillRect(wd->hps, &rcl, CLR_BLACK);
 rcl.xLeft =   128;
 rcl.yBottom = 128;
 rcl.xRight =  128+64;
 rcl.yTop =    128+64;
 WinFillRect(wd->hps, &rcl, CLR_PALEGRAY);

 pt = (PPOINTL) malloc(3*sizeof(POINTL));
 pt[0].x = 8*16;
 pt[0].y = 8*16;
 pt[1].x = 8*16;
 pt[1].y = 12*16;
 pt[2].x = 12*16;
 pt[2].y = 12*16;
 GpiMove(wd->hps, &pt[0]);
 GpiSetColor(wd->hps, CLR_DARKGRAY);
 GpiPolyLine(wd->hps, 2, pt+1);

 pt[1].x = 12*16;
 pt[1].y = 8*16;
 pt[2].x = 12*16;
 pt[2].y = 12*16;
 GpiMove(wd->hps, &pt[0]);
 GpiSetColor(wd->hps, CLR_WHITE);
 GpiPolyLine(wd->hps, 2, pt+1);
 free(pt);

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
// Animates the gray square
{
 POINTL p1, p2;
 INT    x, y, cx, cy;
 PWINDOWDATA wd;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwnd, 0);
 for(y=150,x=150,cx=170, cy=170 ; x>8*16 && y>8*16 && cx<200 && cy<200; x-=10, y-=10, cx+=10, cy+=10)
    {
     p1.x = x;
     p1.y = y;
     p2.x = cx;
     p2.y = cy;
     GpiMove(wd->hps, &p1);
     GpiSetColor(wd->hps, CLR_BLUE);
     GpiBox(wd->hps, DRO_OUTLINE, &p2, 0, 0);
     DosSleep(30);
     GpiSetColor(wd->hps, CLR_PALEGRAY);
     GpiBox(wd->hps, DRO_OUTLINE, &p2, 0, 0);
    }
    WinPostMsg(hwnd, WM_PLAYSOUND, 0, 0);
}


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
 HBITMAP hbmp;
 HPS     hps;
 RECTL   rcl,desktopRcl;
 POINTL  ptl;
 HWND    hwndFrame;

 switch(msg)
    {
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
          WinQueryWindowRect(hwnd, &rcl);
          hps = WinGetPS(hwnd);
          hbmp = GpiLoadBitmap(hps, NULLHANDLE, BID_LOGO, 400, 200);
          ptl.x=0;
          ptl.y=0;
          WinDrawBitmap(hps, hbmp, NULL, &ptl, 0, 0, DBM_NORMAL);
        break;

     case WM_TIMER: // At timer event, just quit
         WinPostMsg(hwnd, WM_QUIT, 0, 0);
        break;

     case WM_BUTTON1CLICK: // At button click, quit
         WinPostMsg(hwnd, WM_QUIT, 0, 0);
        break;

     case WM_DESTROY: // When Destroyed release the Presentation space, and delete the bitmap
            WinReleasePS(hps);
            GpiDeleteBitmap(hbmp);
           break;

     default:
        break;
    }
 return(WinDefWindowProc(hwnd, msg, mp1, mp2));
  // The rest is handled by the default window procedure
}

VOID OpenPopFile() // opens the pop.wav file, using the mci string interpreter
{
 CHAR szBuffer[128];

 strcpy (szBuffer, "open pop.wav alias pop wait");
 mciSendString ((PSZ)szBuffer,
                      NULL,
                      0,
                      0,
                      0);
}

VOID ClosePopFile() // closes the pop.wav file
{
 CHAR szBuffer[128];

 strcpy (szBuffer, "close pop wait");
 mciSendString ((PSZ)szBuffer,
                     NULL,
                      0,
                      0,
                      0);
}

VOID PlaySound(ULONG ulSoundID)
// Note: The pop.wav file must always be open when the game is playing, in order
//        not to show disk activity everytime the pop sound is heard.
//       That's why the code below, isn't very effective.
//       I still have to learn how to work with play lists.:)
{
 CHAR szBuffer[128];

 switch(ulSoundID)
    {
     case SID_POP: // Pop sound is to be played
       strcpy (szBuffer, "play pop wait");
       mciSendString ((PSZ)szBuffer,
                       NULL,
                       0,
                       0,
                       0);
       strcpy(szBuffer, "seek pop to 0 wait");
       mciSendString((PSZ) szBuffer, NULL, 0, 0, 0);
       break;

     case SID_OVER: // Game over sound is to be played
       ClosePopFile();
       strcpy (szBuffer, "open over.wav alias over wait");
       mciSendString ((PSZ)szBuffer,
                      NULL,
                      0,
                      0,
                      0);
       strcpy (szBuffer, "play over wait");
       mciSendString ((PSZ)szBuffer,
                       NULL,
                       0,
                       0,
                       0);
      strcpy (szBuffer, "close over wait");

      mciSendString ((PSZ)szBuffer,
                      NULL,
                      0,
                      0,
                      0);
       OpenPopFile();
        break;

     case SID_HIGH: // Highscore sound is to be played
       ClosePopFile();
       strcpy (szBuffer, "open high.wav alias high wait");
       mciSendString ((PSZ)szBuffer,
                      NULL,
                      0,
                      0,
                      0);
       strcpy (szBuffer, "play high wait");
       mciSendString ((PSZ)szBuffer,
                       NULL,
                       0,
                       0,
                       0);
      strcpy (szBuffer, "close high wait");
      mciSendString ((PSZ)szBuffer,
                      NULL,
                      0,
                      0,
                      0);
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
         hwndAux = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
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

VOID ReadSettings(HAB hab, PSETTINGSDATA psd)
 // Reads the settings saved on the WarpTris.INI file
{
 HINI  hini;
 ULONG value;
 BOOL  blFileExists = TRUE;
 CHAR  szFilename[20];
 RECTL desktopRcl;
 FILE  *fp;

 strcpy(szFilename, "WarpTris.ini");
 fp = fopen("WarpTris.INI", "r");
 if(fp == NULL)
    blFileExists = FALSE;
   else
    fclose(fp);

 hini = PrfOpenProfile(hab, szFilename);

 if(!blFileExists)
    {
     psd->sound = 1;
     psd->high  = 1;
     psd->next  = 1;
     psd->score = 1;
     psd->game  = 1;
     psd->level = 1;
     ArrangeWindows(psd);
     PrfWriteProfileData(hini, "WarpTris", "Settings", (PVOID)psd, sizeof(SETTINGSDATA));
    }
 else
    {
     value = sizeof(SETTINGSDATA);
     PrfQueryProfileData(hini, "WarpTris", "Settings", (PVOID)psd, &value);
     WinQueryWindowRect(HWND_DESKTOP, &desktopRcl);
     if(psd->rclScore.yTop == 57 &&  desktopRcl.yTop < 700)
        {
          psd->rclScore.yTop -= 5;
          psd->rclNext.yTop -= 5;
          psd->rclGame.yTop -= 5;
          psd->rclHigh.yTop -= 5;
        }

     if(psd->rclScore.yTop == 52 &&  desktopRcl.yTop > 700)
        {
          psd->rclScore.yTop += 5;
          psd->rclNext.yTop += 5;
          psd->rclGame.yTop += 5;
          psd->rclHigh.yTop += 5;
        }
    }
 PrfCloseProfile(hini);
}

VOID SaveSettings(HAB hab, PSETTINGSDATA psd)
// Saves the settings on the WarpTris.INI file
{
 HINI hini;
 CHAR szFilename[20];
 SWP  swpWindowPos;
 HWND hwndAux, hwndParentFrame, hwndParentClient;

 strcpy(szFilename, "WarpTris.ini");
 hini = PrfOpenProfile(hab, szFilename);

 if(hini != NULL)
    {
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

     PrfWriteProfileData(hini, "WarpTris", "Settings",(PVOID) psd, sizeof(SETTINGSDATA));
     PrfCloseProfile(hini);
    }
}

VOID SetupHelp(HAB hab, HWND hwnd)
// Sets up the help manager
{
 HWND     hwndHelp;
 HELPINIT mainHelp;

 mainHelp.cb = sizeof(HELPINIT);
 mainHelp.ulReturnCode = 0;
 mainHelp.pszTutorialName = NULL;
 mainHelp.phtHelpTable = (PHELPTABLE) MAKEULONG(HID_MAIN, 0xFFFF);
 mainHelp.hmodHelpTableModule = NULLHANDLE;
 mainHelp.hmodAccelActionBarModule = NULLHANDLE;
 mainHelp.idAccelTable = 0;
 mainHelp.idActionBar = 0;

 mainHelp.pszHelpWindowTitle = "WarpTris Help";
 mainHelp.fShowPanelId = CMIC_HIDE_PANEL_ID;
 mainHelp.pszHelpLibraryName = "WarpTris.HLP";

 hwndHelp = WinCreateHelpInstance(hab, &mainHelp);
 WinAssociateHelpInstance(hwndHelp, hwnd);
}

VOID ArrangeWindows(PSETTINGSDATA psd)
// Arranges the windows to their default position
{
 RECTL desktopRcl;
 INT ulResOffset=0; // Offset because of the 1024x768 resolution

 WinQueryWindowRect(HWND_DESKTOP, &desktopRcl);
 psd->rclParent.xRight = 635;
 psd->rclParent.yTop = 430;
 psd->rclParent.xLeft = (desktopRcl.xRight - psd->rclParent.xRight)/2;
 psd->rclParent.yBottom = (desktopRcl.yTop - psd->rclParent.yTop)/2;
 if(desktopRcl.yTop > 700)
    ulResOffset=5;

 psd->rclGame.xRight = 328;
 psd->rclGame.xLeft = 0;
 psd->rclGame.yTop = 346+ulResOffset;
 psd->rclGame.yBottom = 10;

 psd->rclScore.xRight = 103;
 psd->rclScore.xLeft = 360;
 psd->rclScore.yTop = 52+ulResOffset;
 psd->rclScore.yBottom = 303;

 psd->rclNext.xRight = 158;
 psd->rclNext.xLeft = 360;
 psd->rclNext.yTop = 125+ulResOffset;
 psd->rclNext.yBottom = 171;

 psd->rclHigh.xRight = 250;
 psd->rclHigh.xLeft = 360;
 psd->rclHigh.yTop = 155+ulResOffset;
 psd->rclHigh.yBottom = 9;
}
// end of WarpTris source
