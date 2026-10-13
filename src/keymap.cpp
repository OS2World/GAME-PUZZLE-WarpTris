/* WarpTris - keyboard and joystick mapping and the "Key Mapping..." dialog
   (notebook with a Keyboard and a Joystick page).

   Keyboard: every action has two keys (the second one is an alternative key).
             A key code is 0x100 + virtual key (cursor keys, Shift, Home, End,
             PgUp, PgDn) or the character in lower case (letters, digits, Space,
             punctuation).
   Joystick: through the GAME$ driver, stick A or B. Every action is a joystick
             button or a stick direction. */

#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_WINSTDBOOK
#define INCL_WINENTRYFIELDS

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warptris.h"
#include "lang.h"
#include "keymap.h"
#include "joyos2.h"

/* ------------------------------------------------------------------ texts */

enum {
   KMS_TITLE = 0, KMS_TAB_KBD, KMS_TAB_JOY, KMS_JOY_EN, KMS_JOY_A, KMS_JOY_B,
   KMS_CAL_A, KMS_CAL_B, KMS_OK, KMS_CANCEL, KMS_CAL_MSG, KMS_CAL_TITLE,
   KMS_NONE, KMS_AXL, KMS_AXR, KMS_AXU, KMS_AXD, KMS_BTN,
   KMS_A_LEFT, KMS_A_RIGHT, KMS_A_UP, KMS_A_DOWN, KMS_A_ROTATE, KMS_A_DROP, KMS_A_PAUSE,
   KMS_KBD_H, KMS_JOY_H1, KMS_JOY_H2, KMS_DEFAULT, KMS_UNSET, KMS_COL1, KMS_COL2,
   KMS_COUNT
};

static const char *km_txt[LANG_COUNT][KMS_COUNT] = {
   /* EN */ {
      "Key Mapping", "Keyboard", "Joystick", "Enable Joystick",
      "Joystick A", "Joystick B", "Calibrate A", "Calibrate B",
      "OK", "Cancel", "Center Joystick %c, then click OK.", "Calibrate Joystick %c",
      "None", "Axis L", "Axis R", "Axis Up",
      "Axis Down", "Btn %d",
      "Move left", "Move right", "Move up", "Move down", "Rotate", "Drop", "Pause",
      "Click a box, then press the key (Delete clears).", "Click a box, then press a joystick button", "or move the stick (Delete clears).", "Default", "<unset>", "Key", "Alternate"
   },
   /* ES */ {
      "Asignacion de teclas", "Teclado", "Joystick", "Activar joystick",
      "Joystick A", "Joystick B", "Calibrar A", "Calibrar B",
      "Aceptar", "Cancelar", "Centre el joystick %c y pulse Aceptar.", "Calibrar joystick %c",
      "Ninguno", "Eje izq.", "Eje der.", "Eje arriba",
      "Eje abajo", "Boton %d",
      "Mover a la izquierda", "Mover a la derecha", "Mover arriba", "Mover abajo", "Girar", "Soltar", "Pausa",
      "Haga clic en un cuadro y pulse la tecla (Supr borra).", "Haga clic en un cuadro y pulse un boton", "del joystick o mueva la palanca (Supr borra).", "Por defecto", "<sin asignar>", "Tecla", "Alternativa"
   },
   /* NL */ {
      "Toetsen toewijzen", "Toetsenbord", "Joystick", "Joystick gebruiken",
      "Joystick A", "Joystick B", "Kalibreer A", "Kalibreer B",
      "OK", "Annuleren", "Centreer joystick %c en klik op OK.", "Joystick %c kalibreren",
      "Geen", "As links", "As rechts", "As omhoog",
      "As omlaag", "Knop %d",
      "Naar links", "Naar rechts", "Omhoog", "Omlaag", "Draaien", "Laten vallen", "Pauze",
      "Klik op een vak en druk op de toets (Delete wist).", "Klik op een vak en druk op een joystickknop", "of beweeg de stick (Delete wist).", "Standaard", "<leeg>", "Toets", "Alternatief"
   },
   /* DE */ {
      "Tastenzuordnung", "Tastatur", "Joystick", "Joystick aktivieren",
      "Joystick A", "Joystick B", "A kalibrieren", "B kalibrieren",
      "OK", "Abbrechen", "Joystick %c zentrieren, dann OK klicken.", "Joystick %c kalibrieren",
      "Keine", "Achse links", "Achse rechts", "Achse oben",
      "Achse unten", "Taste %d",
      "Nach links", "Nach rechts", "Nach oben", "Nach unten", "Drehen", "Fallen lassen", "Pause",
      "Klicke auf ein Feld und druecke die Taste (Entf loescht).", "Klicke auf ein Feld und druecke eine Joystick-Taste", "oder bewege den Stick (Entf loescht).", "Standard", "<leer>", "Taste", "Alternative"
   },
   /* FR */ {
      "Affectation des touches", "Clavier", "Joystick", "Activer le joystick",
      "Joystick A", "Joystick B", "Calibrer A", "Calibrer B",
      "OK", "Annuler", "Centrez le joystick %c puis cliquez sur OK.", "Calibrer le joystick %c",
      "Aucun", "Axe gauche", "Axe droite", "Axe haut",
      "Axe bas", "Bouton %d",
      "Aller a gauche", "Aller a droite", "Aller en haut", "Aller en bas", "Tourner", "Faire tomber", "Pause",
      "Cliquez sur une case puis appuyez sur la touche (Suppr efface).", "Cliquez sur une case puis appuyez sur un bouton", "du joystick ou bougez le manche (Suppr efface).", "Defaut", "<vide>", "Touche", "Alternative"
   },
   /* IT */ {
      "Assegnazione tasti", "Tastiera", "Joystick", "Attiva joystick",
      "Joystick A", "Joystick B", "Calibra A", "Calibra B",
      "OK", "Annulla", "Centra il joystick %c e fai clic su OK.", "Calibra joystick %c",
      "Nessuno", "Asse sinistra", "Asse destra", "Asse su",
      "Asse giu", "Pulsante %d",
      "Sposta a sinistra", "Sposta a destra", "Sposta su", "Sposta giu", "Ruota", "Fai cadere", "Pausa",
      "Fai clic su una casella e premi il tasto (Canc cancella).", "Fai clic su una casella e premi un pulsante", "del joystick o muovi la leva (Canc cancella).", "Predefinito", "<vuoto>", "Tasto", "Alternativo"
   },
};

static const char *kmText(int id)
{
   int l = current_lang;

   if(l < 0 || l >= LANG_COUNT)
      l = LANG_EN;
   return km_txt[l][id];
}

/* ------------------------------------------------------------------- data */

#define JOY_AXIS_L  5
#define JOY_AXIS_R  6
#define JOY_AXIS_U  7
#define JOY_AXIS_D  8

#define REPEAT_DELAY 7      /* joystick: ticks before a held move repeats */
#define REPEAT_RATE  3      /* ... and ticks between the repeats          */

#define WM_KM_INPUT  (WM_USER + 40)

static KMCFG              *pcfg = NULL;
static HFILE              hGame = 0;
static GAME_2DPOS_STRUCT  joyCal[3];                  /* centre of stick A (1) and B (2) */
static BOOL               bJoyAvail[2];
static GAME_STATUS_STRUCT joyNow;
static BOOL               bJoyNow = FALSE;
static BOOL               bDialogOpen = FALSE;
static BOOL               bWasDown[KM_NACT];
static INT                iHold[KM_NACT];

static const USHORT usButBit[4] = { JOY_BUT1_BIT, JOY_BUT2_BIT, JOY_BUT3_BIT, JOY_BUT4_BIT };

static const ULONG ulDefKey1[KM_NACT] = { 0x100|VK_LEFT, 0x100|VK_RIGHT, 0x100|VK_UP, 0x100|VK_DOWN,
                                          0x100|VK_SHIFT, ' ', 'p' };
static const ULONG ulDefKey2[KM_NACT] = { '4', '6', '8', '2', '5', 0, 0 };
static const ULONG ulDefJoy[KM_NACT]  = { JOY_AXIS_L, JOY_AXIS_R, JOY_AXIS_U, JOY_AXIS_D, 1, 2, 3 };

/* ------------------------------------------------------------------- keys */

static BOOL VirtualAllowed(USHORT vk)
{
   return vk == VK_LEFT || vk == VK_RIGHT || vk == VK_UP || vk == VK_DOWN ||
          vk == VK_SHIFT || vk == VK_HOME || vk == VK_END || vk == VK_PAGEUP || vk == VK_PAGEDOWN;
}

/* key code of a WM_CHAR message (0 = not usable) */
static ULONG KeyCode(ULONG fs, USHORT chr, USHORT vkey)
{
   if(fs & (KC_CTRL | KC_ALT))
      return 0;
   if((fs & KC_VIRTUALKEY) && VirtualAllowed(vkey))
      return 0x100 | vkey;
   if(fs & KC_CHAR)
   {
      if(chr >= 'A' && chr <= 'Z')
         chr += 'a' - 'A';
      if(chr == ' ' || (chr > ' ' && chr < 127))
         return chr;
   }
   return 0;
}

static BOOL CodeValid(ULONG code)
{
   if(code == 0)
      return TRUE;
   if(code >> 8 == 1)
      return VirtualAllowed((USHORT)(code & 0xFF));
   return code == ' ' || (code > ' ' && code < 127);
}

INT KmKeyAction(ULONG fs, USHORT chr, USHORT vkey)
{
   ULONG code = KeyCode(fs, chr, vkey);
   INT   i;

   if(code == 0 || pcfg == NULL)
      return -1;
   for(i = 0; i < KM_NACT; i++)
      if(pcfg->key1[i] == code || pcfg->key2[i] == code)
         return i;
   return -1;
}

static VOID KeyName(ULONG code, char *buf)
{
   buf[0] = 0;
   if(code == 0)
      strcpy(buf, kmText(KMS_UNSET));
   else if(code >> 8 == 1)
      switch(code & 0xFF)
      {
         case VK_LEFT:     strcpy(buf, "Cursor Left");  break;
         case VK_RIGHT:    strcpy(buf, "Cursor Right"); break;
         case VK_UP:       strcpy(buf, "Cursor Up");    break;
         case VK_DOWN:     strcpy(buf, "Cursor Down");  break;
         case VK_SHIFT:    strcpy(buf, "Shift");        break;
         case VK_HOME:     strcpy(buf, "Home");         break;
         case VK_END:      strcpy(buf, "End");          break;
         case VK_PAGEUP:   strcpy(buf, "PgUp");         break;
         case VK_PAGEDOWN: strcpy(buf, "PgDn");         break;
         default:          sprintf(buf, "0x%02X", (unsigned)(code & 0xFF));
      }
   else if(code == ' ')
      strcpy(buf, "Space");
   else if(code >= 'a' && code <= 'z')
      sprintf(buf, "%c", (char)(code - 'a' + 'A'));
   else
      sprintf(buf, "%c", (char) code);
}

static const char *JoyLabel(ULONG n)
{
   static char b[100];

   if(n == 0) return kmText(KMS_NONE);
   if(n >= 1 && n <= 4) { sprintf(b, kmText(KMS_BTN), (int) n); return b; }
   if(n == JOY_AXIS_L) return kmText(KMS_AXL);
   if(n == JOY_AXIS_R) return kmText(KMS_AXR);
   if(n == JOY_AXIS_U) return kmText(KMS_AXU);
   if(n == JOY_AXIS_D) return kmText(KMS_AXD);
   return "?";
}

/* --------------------------------------------------------------- joystick */

VOID KmDefaults(KMCFG *p)
{
   INT i;

   memset(p, 0, sizeof(KMCFG));
   p->ver = 1;
   p->stick = 1;
   for(i = 0; i < KM_NACT; i++)
   {
      p->key1[i] = ulDefKey1[i];
      p->key2[i] = ulDefKey2[i];
      p->act[i]  = ulDefJoy[i];
   }
}

VOID KmInit(KMCFG *p)
{
   ULONG             action, dataLen;
   GAME_PARM_STRUCT  parms;
   GAME_CALIB_STRUCT calib;
   INT               i;
   BOOL              ok = TRUE;

   pcfg = p;

   /* a missing or damaged mapping (older WarpTris.cfg) is replaced by the default */
   if(p->ver != 1 || p->enabled > 1 || p->stick < 1 || p->stick > 2)
      ok = FALSE;
   for(i = 0; i < KM_NACT; i++)
      if(p->act[i] > 8 || !CodeValid(p->key1[i]) || !CodeValid(p->key2[i]))
         ok = FALSE;
   if(!ok)
      KmDefaults(p);

   if(DosOpen((PSZ) GAMEPDDNAME, &hGame, &action, 0, FILE_READONLY, FILE_OPEN,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL) != NO_ERROR)
      hGame = 0;
   else
   {
      dataLen = sizeof(parms);
      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_PARMS, NULL, 0, NULL, &parms, dataLen, &dataLen) != NO_ERROR)
      {
         DosClose(hGame);
         hGame = 0;
      }
   }
   if(hGame != 0)
   {
      bJoyAvail[0] = (parms.useA & GAME_USE_BOTH_NEWMASK) != 0;
      bJoyAvail[1] = (parms.useB & GAME_USE_BOTH_NEWMASK) != 0;
      dataLen = sizeof(calib);
      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_CALIB, NULL, 0, NULL, &calib, dataLen, &dataLen) == NO_ERROR)
      {
         joyCal[1].x = calib.Ax.centre;  joyCal[1].y = calib.Ay.centre;
         joyCal[2].x = calib.Bx.centre;  joyCal[2].y = calib.By.centre;
      }
   }
   else
      p->enabled = 0;
}

VOID KmDone(VOID)
{
   if(hGame)
   {
      HFILE h = hGame;
      hGame = 0;
      DosClose(h);
   }
}

BOOL KmJoyEnabled(VOID)
{
   return hGame && pcfg && pcfg->enabled;
}

/* Is the action held on the joystick (status in joyNow)? */
static BOOL JoyDown(const KMCFG *p, INT iAct)
{
   INT   c, dX, dY, tolX, tolY;
   GAME_2DPOS_STRUCT *jd, *cal;

   c = (INT) p->act[iAct];
   if(c == 0)
      return FALSE;
   if(c >= 1 && c <= 4)
      return (joyNow.curdata.butMask & usButBit[c - 1]) == 0;

   jd  = (p->stick == 1) ? &joyNow.curdata.A : &joyNow.curdata.B;
   cal = &joyCal[p->stick];
   tolX = abs((int) cal->x) / 10 + 1;
   tolY = abs((int) cal->y) / 10 + 1;
   if(tolX < 16) tolX = 16;
   if(tolY < 16) tolY = 16;
   dX = (int) jd->x - (int) cal->x;
   dY = (int) jd->y - (int) cal->y;
   switch(c)
   {
      case JOY_AXIS_L: return dX < -tolX;
      case JOY_AXIS_R: return dX >  tolX;
      case JOY_AXIS_U: return dY < -tolY;
      case JOY_AXIS_D: return dY >  tolY;
   }
   return FALSE;
}

VOID KmJoyTick(BOOL *fire)
{
   ULONG len = sizeof(joyNow);
   INT   i;

   for(i = 0; i < KM_NACT; i++)
      fire[i] = FALSE;

   if(!KmJoyEnabled() || bDialogOpen)
   {
      bJoyNow = FALSE;
      for(i = 0; i < KM_NACT; i++)
      {
         bWasDown[i] = FALSE;
         iHold[i] = 0;
      }
      return;
   }

   bJoyNow = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &joyNow, len, &len) == NO_ERROR;
   if(!bJoyNow)
      return;

   for(i = 0; i < KM_NACT; i++)
   {
      BOOL down = JoyDown(pcfg, i);

      if(down)
      {
         if(!bWasDown[i])
         {
            iHold[i] = 0;
            fire[i] = TRUE;
         }
         else
         {
            iHold[i]++;
            if(i <= KM_DOWN && iHold[i] >= REPEAT_DELAY && ((iHold[i] - REPEAT_DELAY) % REPEAT_RATE) == 0)
               fire[i] = TRUE;
         }
      }
      bWasDown[i] = down;
   }
}

/* ============================================================== dialogs */

typedef struct {
   KMCFG cfg;                    /* working copy */
   HWND  hwndKbd, hwndJoy, hwndNB;
   ULONG ulKbdPage, ulJoyPage;
} KMDATA, *PKMDATA;

static PFNWP pfnEntryOrig;

static VOID EnableChildren(HWND hwnd, USHORT idExcept, BOOL en)
{
   HENUM he = WinBeginEnumWindows(hwnd);
   HWND  hc;

   while((hc = WinGetNextWindow(he)) != NULLHANDLE)
      if(WinQueryWindowUShort(hc, QWS_ID) != idExcept)
         WinEnableWindow(hc, en);
   WinEndEnumWindows(he);
}

/* Keys pressed in a mapping box go to the owning page as a key code (0xFFFF = clear) */
static MRESULT EXPENTRY KmEntryProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HWND   hwndOwner = WinQueryWindow(hwnd, QW_OWNER);
   USHORT id        = WinQueryWindowUShort(hwnd, QWS_ID);

   if(msg == WM_CHAR)
   {
      USHORT fs = SHORT1FROMMP(mp1);
      USHORT vk = SHORT2FROMMP(mp2);

      if(fs & KC_ALT)
         return pfnEntryOrig(hwnd, msg, mp1, mp2);
      if((fs & KC_VIRTUALKEY) && (vk == VK_TAB || vk == VK_BACKTAB || vk == VK_ESC || vk == VK_F1))
         return pfnEntryOrig(hwnd, msg, mp1, mp2);
      if(!(fs & KC_KEYUP))
      {
         ULONG code;

         if((fs & KC_VIRTUALKEY) && (vk == VK_BACKSPACE || vk == VK_DELETE))
            code = 0xFFFF;
         else
            code = KeyCode(fs, SHORT1FROMMP(mp2), vk);
         WinSendMsg(hwndOwner, WM_KM_INPUT, MPFROMSHORT(id), MPFROMLONG(code));
      }
      return (MRESULT) TRUE;
   }
   return pfnEntryOrig(hwnd, msg, mp1, mp2);
}

static VOID Subclass(HWND hwndBox)
{
   PFNWP p = WinSubclassWindow(hwndBox, KmEntryProc);

   if(pfnEntryOrig == NULL)
      pfnEntryOrig = p;
}

/* ------------------------------------------------------------ keyboard page */

static VOID KbdShowAll(HWND hwnd, PKMDATA wd)
{
   char buf[40];
   INT  i;

   for(i = 0; i < KM_NACT; i++)
   {
      KeyName(wd->cfg.key1[i], buf);
      WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_K1BOX + i), (PSZ) buf);
      KeyName(wd->cfg.key2[i], buf);
      WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_K2BOX + i), (PSZ) buf);
   }
}

static MRESULT EXPENTRY KbdPageProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA) WinQueryWindowULong(hwnd, QWL_USER);
   INT i;

   switch(msg)
   {
      case WM_INITDLG:
         wd = (PKMDATA) PVOIDFROMMP(mp2);
         WinSetWindowULong(hwnd, QWL_USER, (ULONG) wd);
         WinSetDlgItemText(hwnd, IDC_KM_KH, (PSZ) kmText(KMS_KBD_H));
         WinSetDlgItemText(hwnd, IDC_KM_KC1, (PSZ) kmText(KMS_COL1));
         WinSetDlgItemText(hwnd, IDC_KM_KC2, (PSZ) kmText(KMS_COL2));
         for(i = 0; i < KM_NACT; i++)
         {
            WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_KLBL + i), (PSZ) kmText(KMS_A_LEFT + i));
            Subclass(WinWindowFromID(hwnd, (USHORT)(IDC_KM_K1BOX + i)));
            Subclass(WinWindowFromID(hwnd, (USHORT)(IDC_KM_K2BOX + i)));
         }
         KbdShowAll(hwnd, wd);
         return (MRESULT) FALSE;

      case WM_KM_INPUT:
         {
            INT   id = (INT) SHORT1FROMMP(mp1);
            ULONG code = LONGFROMMP(mp2);
            BOOL  second = id >= IDC_KM_K2BOX;
            INT   r = id - (second ? IDC_KM_K2BOX : IDC_KM_K1BOX);
            ULONG *slot;

            if(r >= 0 && r < KM_NACT)
            {
               slot = second ? &wd->cfg.key2[r] : &wd->cfg.key1[r];
               if(code == 0xFFFF)
                  *slot = 0;
               else if(code != 0)
               {
                  INT j;

                  for(j = 0; j < KM_NACT; j++)      /* a key in use goes to this slot's old key */
                  {
                     if(wd->cfg.key1[j] == code && !(j == r && !second))
                        wd->cfg.key1[j] = *slot;
                     if(wd->cfg.key2[j] == code && !(j == r && second))
                        wd->cfg.key2[j] = *slot;
                  }
                  *slot = code;
               }
               else
                  WinAlarm(HWND_DESKTOP, WA_WARNING);
               KbdShowAll(hwnd, wd);
            }
         }
         return (MRESULT) TRUE;

      case WM_COMMAND:
         if(SHORT1FROMMP(mp1) == BN_KM_DEFAULTS)
         {
            for(i = 0; i < KM_NACT; i++)
            {
               wd->cfg.key1[i] = ulDefKey1[i];
               wd->cfg.key2[i] = ulDefKey2[i];
            }
            KbdShowAll(hwnd, wd);
         }
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* ------------------------------------------------------------ joystick page */

static VOID JoyShowAll(HWND hwnd, PKMDATA wd)
{
   INT i;

   for(i = 0; i < KM_NACT; i++)
      WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + i), (PSZ) JoyLabel(wd->cfg.act[i]));
}

static VOID JoyEnableState(HWND hwnd, PKMDATA wd)
{
   BOOL en = wd->cfg.enabled != 0;

   EnableChildren(hwnd, IDC_KM_JEN, en);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JCALA), en && hGame && bJoyAvail[0]);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JCALB), en && hGame && bJoyAvail[1]);
   if(!hGame)
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JEN), FALSE);
   if(!bJoyAvail[0])
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JPA), FALSE);
   if(!bJoyAvail[1])
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JPB), FALSE);
}

static VOID JoyCalibrate(HWND hwnd, INT stick)
{
   char szMsg[160], szTitle[160];
   char ch = (stick == 1) ? 'A' : 'B';

   if(!hGame)
      return;
   sprintf(szMsg,   kmText(KMS_CAL_MSG),   ch);
   sprintf(szTitle, kmText(KMS_CAL_TITLE), ch);
   if(WinMessageBox(HWND_DESKTOP, hwnd, (PSZ) szMsg, (PSZ) szTitle, 0, MB_OKCANCEL | MB_INFORMATION) == MBID_OK)
   {
      GAME_STATUS_STRUCT s;
      ULONG len = sizeof(s);

      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &s, len, &len) == NO_ERROR)
      {
         if(stick == 1) { joyCal[1].x = s.curdata.A.x; joyCal[1].y = s.curdata.A.y; }
         else           { joyCal[2].x = s.curdata.B.x; joyCal[2].y = s.curdata.B.y; }
      }
   }
}

static MRESULT EXPENTRY JoyPageProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA) WinQueryWindowULong(hwnd, QWL_USER);
   static INT    iSelRow;
   static USHORT usPrevButs;
   static BOOL   bPAxL, bPAxR, bPAxU, bPAxD;
   INT i;

   switch(msg)
   {
      case WM_INITDLG:
         wd = (PKMDATA) PVOIDFROMMP(mp2);
         WinSetWindowULong(hwnd, QWL_USER, (ULONG) wd);
         iSelRow = -1;
         usPrevButs = 0xFFFF;
         bPAxL = bPAxR = bPAxU = bPAxD = FALSE;

         WinSetDlgItemText(hwnd, IDC_KM_JEN,   (PSZ) kmText(KMS_JOY_EN));
         WinSetDlgItemText(hwnd, IDC_KM_JH1,   (PSZ) kmText(KMS_JOY_H1));
         WinSetDlgItemText(hwnd, IDC_KM_JH2,   (PSZ) kmText(KMS_JOY_H2));
         WinSetDlgItemText(hwnd, IDC_KM_JP,    (PSZ) kmText(KMS_TAB_JOY));
         WinSetDlgItemText(hwnd, IDC_KM_JPA,   (PSZ) kmText(KMS_JOY_A));
         WinSetDlgItemText(hwnd, IDC_KM_JPB,   (PSZ) kmText(KMS_JOY_B));
         WinSetDlgItemText(hwnd, IDC_KM_JCALA, (PSZ) kmText(KMS_CAL_A));
         WinSetDlgItemText(hwnd, IDC_KM_JCALB, (PSZ) kmText(KMS_CAL_B));
         for(i = 0; i < KM_NACT; i++)
         {
            WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JLBL + i), (PSZ) kmText(KMS_A_LEFT + i));
            Subclass(WinWindowFromID(hwnd, (USHORT)(IDC_KM_JBOX + i)));
         }
         WinSendDlgItemMsg(hwnd, IDC_KM_JEN, BM_SETCHECK, MPFROMSHORT(wd->cfg.enabled != 0), MPVOID);
         WinSendDlgItemMsg(hwnd, wd->cfg.stick == 2 ? IDC_KM_JPB : IDC_KM_JPA, BM_SETCHECK, MPFROMSHORT(1), MPVOID);
         JoyShowAll(hwnd, wd);
         JoyEnableState(hwnd, wd);
         WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, 1, 50);
         return (MRESULT) FALSE;

      case WM_TIMER:
         /* a new button press or stick direction goes to the focused box */
         if(hGame && wd->cfg.enabled && iSelRow >= 0)
         {
            GAME_STATUS_STRUCT s;
            ULONG len = sizeof(s);

            if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &s, len, &len) == NO_ERROR)
            {
               GAME_2DPOS_STRUCT *jd  = (wd->cfg.stick == 1) ? &s.curdata.A : &s.curdata.B;
               GAME_2DPOS_STRUCT *cal = &joyCal[wd->cfg.stick];
               INT    tolX = abs((int) cal->x) / 10 + 1, tolY = abs((int) cal->y) / 10 + 1;
               INT    dX, dY;
               USHORT curButs = s.curdata.butMask;
               USHORT pressed = usPrevButs & ~curButs;
               BOOL   axL, axR, axU, axD;
               INT    newAct = 0;

               if(tolX < 16) tolX = 16;
               if(tolY < 16) tolY = 16;
               dX = (int) jd->x - (int) cal->x;
               dY = (int) jd->y - (int) cal->y;
               axL = dX < -tolX;  axR = dX > tolX;  axU = dY < -tolY;  axD = dY > tolY;

               if(pressed)
                  for(i = 0; i < 4; i++)
                     if(pressed & usButBit[i]) { newAct = i + 1; break; }
               if(!newAct)
               {
                  if(axL && !bPAxL) newAct = JOY_AXIS_L;
                  else if(axR && !bPAxR) newAct = JOY_AXIS_R;
                  else if(axU && !bPAxU) newAct = JOY_AXIS_U;
                  else if(axD && !bPAxD) newAct = JOY_AXIS_D;
               }
               if(newAct)
               {
                  wd->cfg.act[iSelRow] = newAct;
                  WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + iSelRow), (PSZ) JoyLabel(newAct));
               }
               usPrevButs = curButs;
               bPAxL = axL; bPAxR = axR; bPAxU = axU; bPAxD = axD;
            }
         }
         return 0;

      case WM_KM_INPUT:
         {
            INT r = (INT) SHORT1FROMMP(mp1) - IDC_KM_JBOX;

            if(r >= 0 && r < KM_NACT && LONGFROMMP(mp2) == 0xFFFF)
            {
               wd->cfg.act[r] = 0;
               WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + r), (PSZ) JoyLabel(0));
            }
         }
         return (MRESULT) TRUE;

      case WM_CONTROL:
         if(SHORT1FROMMP(mp1) >= IDC_KM_JBOX && SHORT1FROMMP(mp1) < IDC_KM_JBOX + KM_NACT)
         {
            if(SHORT2FROMMP(mp1) == EN_SETFOCUS)
               iSelRow = SHORT1FROMMP(mp1) - IDC_KM_JBOX;
            else if(SHORT2FROMMP(mp1) == EN_KILLFOCUS)
               iSelRow = -1;
            return 0;
         }
         if(SHORT2FROMMP(mp1) == BN_CLICKED)
         {
            switch(SHORT1FROMMP(mp1))
            {
               case IDC_KM_JEN:
                  wd->cfg.enabled = ((SHORT)(ULONG) WinSendDlgItemMsg(hwnd, IDC_KM_JEN, BM_QUERYCHECK, MPVOID, MPVOID)) != 0;
                  JoyEnableState(hwnd, wd);
                  break;
               case IDC_KM_JPA: wd->cfg.stick = 1; break;
               case IDC_KM_JPB: wd->cfg.stick = 2; break;
            }
         }
         return 0;

      case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
            case IDC_KM_JCALA: JoyCalibrate(hwnd, 1); break;
            case IDC_KM_JCALB: JoyCalibrate(hwnd, 2); break;
            case BN_KM_DEFAULTS:
               for(i = 0; i < KM_NACT; i++)
                  wd->cfg.act[i] = ulDefJoy[i];
               wd->cfg.stick = 1;
               WinSendDlgItemMsg(hwnd, IDC_KM_JPA, BM_SETCHECK, MPFROMSHORT(1), MPVOID);
               WinSendDlgItemMsg(hwnd, IDC_KM_JPB, BM_SETCHECK, MPFROMSHORT(0), MPVOID);
               JoyShowAll(hwnd, wd);
               break;
         }
         return 0;

      case WM_DESTROY:
         WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, 1);
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* -------------------------------------------------------------- main dialog */

static VOID SizeNotebook(HWND hwnd, PKMDATA wd)
{
   SWP swpBtn, swpDlg;

   WinQueryWindowPos(hwnd, &swpDlg);
   WinQueryWindowPos(WinWindowFromID(hwnd, DID_OK), &swpBtn);
   WinSetWindowPos(wd->hwndNB, HWND_TOP,
      4, swpBtn.y + swpBtn.cy + 4,
      swpDlg.cx - 8,
      swpDlg.cy - (swpBtn.y + swpBtn.cy + 4) - 4 - WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR),
      SWP_MOVE | SWP_SIZE);
}

static MRESULT EXPENTRY KeyMapDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA) WinQueryWindowULong(hwnd, QWL_USER);

   switch(msg)
   {
      case WM_INITDLG:
         {
            SWP swpFr;

            wd = (PKMDATA) PVOIDFROMMP(mp2);
            WinSetWindowULong(hwnd, QWL_USER, (ULONG) wd);

            WinSetWindowText(hwnd, (PSZ) kmText(KMS_TITLE));
            WinSetDlgItemText(hwnd, DID_OK,         (PSZ) kmText(KMS_OK));
            WinSetDlgItemText(hwnd, DID_CANCEL,     (PSZ) kmText(KMS_CANCEL));
            WinSetDlgItemText(hwnd, BN_KM_DEFAULTS, (PSZ) kmText(KMS_DEFAULT));
            WinQueryWindowPos(hwnd, &swpFr);
            WinSetWindowPos(hwnd, HWND_TOP,
               (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) - swpFr.cx) / 2,
               (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) - swpFr.cy) / 2,
               0, 0, SWP_MOVE | SWP_ACTIVATE);

            wd->hwndNB = WinCreateWindow(hwnd, WC_NOTEBOOK, (PSZ) "",
                           BKS_TABBEDDIALOG | BKS_BACKPAGESBR | WS_VISIBLE | WS_TABSTOP,
                           0, 0, 1, 1, hwnd, HWND_TOP, IDC_KM_NB, NULL, NULL);
            if(wd->hwndNB == NULLHANDLE)
            {
               WinDismissDlg(hwnd, DID_CANCEL);
               return (MRESULT) FALSE;
            }
            SizeNotebook(hwnd, wd);
            WinSendMsg(wd->hwndNB, BKM_SETNOTEBOOKCOLORS,
                       MPFROMLONG(WinQuerySysColor(HWND_DESKTOP, SYSCLR_DIALOGBACKGROUND, 0)),
                       MPFROMSHORT(BKA_BACKGROUNDPAGECOLOR));

            wd->ulKbdPage = (ULONG) WinSendMsg(wd->hwndNB, BKM_INSERTPAGE, NULL, MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
            WinSendMsg(wd->hwndNB, BKM_SETTABTEXT, MPFROMLONG(wd->ulKbdPage), MPFROMP(kmText(KMS_TAB_KBD)));
            wd->ulJoyPage = (ULONG) WinSendMsg(wd->hwndNB, BKM_INSERTPAGE, NULL, MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
            WinSendMsg(wd->hwndNB, BKM_SETTABTEXT, MPFROMLONG(wd->ulJoyPage), MPFROMP(kmText(KMS_TAB_JOY)));

            wd->hwndKbd = WinLoadDlg(wd->hwndNB, wd->hwndNB, KbdPageProc, NULLHANDLE, DLG_KM_KBD, wd);
            WinSendMsg(wd->hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(wd->ulKbdPage), MPFROMHWND(wd->hwndKbd));
            wd->hwndJoy = WinLoadDlg(wd->hwndNB, wd->hwndNB, JoyPageProc, NULLHANDLE, DLG_KM_JOY, wd);
            WinSendMsg(wd->hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(wd->ulJoyPage), MPFROMHWND(wd->hwndJoy));

            WinSendMsg(wd->hwndNB, BKM_TURNTOPAGE, MPFROMLONG(wd->ulKbdPage), MPVOID);
         }
         return (MRESULT) FALSE;

      case WM_SIZE:
         if(wd && wd->hwndNB)
            SizeNotebook(hwnd, wd);
         break;

      case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
            case DID_OK:
               WinDismissDlg(hwnd, DID_OK);
               return 0;
            case DID_CANCEL:
               WinDismissDlg(hwnd, DID_CANCEL);
               return 0;
            case BN_KM_DEFAULTS:
               WinSendMsg(wd->hwndKbd, WM_COMMAND, MPFROMSHORT(BN_KM_DEFAULTS), MPVOID);
               WinSendMsg(wd->hwndJoy, WM_COMMAND, MPFROMSHORT(BN_KM_DEFAULTS), MPVOID);
               return 0;
         }
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

VOID KmDialog(HWND hwndOwner)
{
   KMDATA wd;

   if(pcfg == NULL)
      return;
   memset(&wd, 0, sizeof(wd));
   wd.cfg = *pcfg;
   pfnEntryOrig = NULL;

   bDialogOpen = TRUE;
   if(WinDlgBox(HWND_DESKTOP, hwndOwner, KeyMapDlgProc, NULLHANDLE, IDD_KEYMAP, &wd) == DID_OK)
   {
      *pcfg = wd.cfg;
      if(!hGame)
         pcfg->enabled = 0;
   }
   bDialogOpen = FALSE;
}
