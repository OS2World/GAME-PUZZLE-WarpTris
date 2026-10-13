/* WarpTris - keyboard and joystick mapping (Options - Key Mapping...) */

#ifndef KEYMAP_H
#define KEYMAP_H

/* game actions */
#define KM_LEFT    0
#define KM_RIGHT   1
#define KM_UP      2
#define KM_DOWN    3
#define KM_ROTATE  4
#define KM_DROP    5
#define KM_PAUSE   6
#define KM_NACT    7

/* The mapping; it is part of the settings saved in WarpTris.cfg */
typedef struct {
                ULONG ver;             /* 1                                        */
                ULONG key1[KM_NACT];   /* key codes: 0x100+virtual key, or the     */
                ULONG key2[KM_NACT];   /* character in lower case; 0 = not set     */
                ULONG enabled;         /* joystick on / off                        */
                ULONG stick;           /* 1 = stick A, 2 = stick B                 */
                ULONG act[KM_NACT];    /* 0 none, 1-4 button, 5-8 axis L/R/U/D     */
               } KMCFG;

VOID KmDefaults(KMCFG *pcfg);
VOID KmInit(KMCFG *pcfg);       /* check the loaded mapping, open GAME$ */
VOID KmDone(VOID);
INT  KmKeyAction(ULONG fs, USHORT chr, USHORT vkey);   /* action of a WM_CHAR key, or -1 */
BOOL KmJoyEnabled(VOID);
VOID KmJoyTick(BOOL *fire);     /* every 40 ms: fire[KM_NACT] = actions to run now */
VOID KmDialog(HWND hwndOwner);  /* the dialog; changes the mapping on OK */

#endif /* KEYMAP_H */
