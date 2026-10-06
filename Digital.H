// This class implements a Digital Panel for displaying the Score.

// Digital Panel

class DigitalPanel
{
 private:
  HWND hwndOwner; // Handle of the window that owns the digital panel
  HBITMAP hbmp[11];// The handles of the bitmaps that represents the numbers
  INT digitCount; // The number of digits that the display has
  INT posX, posY; // Coordinates of the lower left corner
  ULONG value; // The value that it currently displays
  VOID LightDigit(HPS hps, INT digit, INT v); // Light a given digit with a given value(0..9)

 public:
  DigitalPanel(HWND hwnd, INT x, INT y, INT digitC, ULONG v=0); // Constructor
  ~DigitalPanel(); // Destructor
  VOID Draw(BOOL showValue=TRUE); // Draw the panel
  VOID ShowValue(VOID); // Show the value on it
  VOID SetValue(ULONG v) {value=v;}; // Set the value
  VOID AddToValue(ULONG v) {value += v; Draw();} // Add a number to the value
  ULONG GetValue(VOID) {return(value);} // Get the value
};

DigitalPanel::~DigitalPanel()
{
 INT i;

 for(i=0;i<11;++i)
    GpiDeleteBitmap(hbmp[i]);
}

DigitalPanel::DigitalPanel(HWND hwnd, INT x, INT y, INT digitC, ULONG v)
{
 INT i;
 HPS hps;

 hwndOwner = hwnd;
 digitCount = digitC;
 posX = x;
 posY = y;
 value = v;
 hps =  WinGetPS(hwnd);
 for(i=0; i<11; ++i)
  hbmp[i] = GpiLoadBitmap(hps, NULLHANDLE, i+10, 11, 21);
 WinReleasePS(hps);
}

VOID DigitalPanel::Draw(BOOL showValue)
{
 HPS hps;
 PPOINTL pt;
 POINTL p;
 RECTL rcl;
 INT i;

 hps = WinGetPS(hwndOwner);
 rcl.xLeft = posX+1;
 rcl.yBottom = posY+1;
 rcl.xRight = posX + 3 + digitCount*13;
 rcl.yTop = posY+26;
 WinFillRect(hps, &rcl, CLR_BLACK);

 pt = (PPOINTL) malloc(3*sizeof(POINTL));
 pt[0].x = posX;
 pt[0].y = posY+1;
 pt[1].x = posX;
 pt[1].y = posY+26;
 pt[2].x = posX+4+digitCount*13;
 pt[2].y = posY+26;
 GpiMove(hps, pt);
 GpiSetColor(hps,CLR_DARKGRAY);
 GpiPolyLine(hps, 2, pt+1);

 pt[0].x += 1;
 pt[0].y -= 1;
 pt[1].x = posX + 3 +digitCount*13;
 pt[1].y = posY;
 pt[2].x = posX + 3 +digitCount*13;
 pt[2].y = posY+25;
 GpiMove(hps, pt);
 GpiSetColor(hps, CLR_WHITE);
 GpiPolyLine(hps, 2, pt+1);
 free(pt);

 for(i=0; i<digitCount; ++i)
   {
    p.x = (posX+1)+2 + 13*i;
    p.y = (posY+1)+2;
    WinDrawBitmap(hps, hbmp[10], NULL, &p, 0, 0, DBM_NORMAL | DBM_IMAGEATTRS );
   }

 WinReleasePS(hps);
 if(showValue)
  ShowValue();
}


VOID DigitalPanel::LightDigit(HPS hps, INT digit, INT v)
{
 POINTL p;

 p.x=(posX + 3 + digitCount*13 - 13)-digit*13;
 p.y= posY+3;
 if(p.x>=posX+3)
  WinDrawBitmap(hps, hbmp[v-48], NULL, &p, 0, 0, DBM_NORMAL | DBM_IMAGEATTRS );
 return;
}

VOID DigitalPanel::ShowValue()
{
 PSZ pszNumber;
 INT i,k;
 HPS hps;

 hps = WinGetPS(hwndOwner);
 pszNumber = (PSZ) malloc(33*sizeof(SZ));
 _ltoa(value, pszNumber, 10);

 for(i=strlen(pszNumber)-1,k=0; i>=0; --i,++k)
  LightDigit(hps, k, (INT) pszNumber[i]);

 free(pszNumber);
 WinReleasePS(hps);
}

