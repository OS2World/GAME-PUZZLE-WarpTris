// This class handles everything that has to do with the High Scores:
//  o tests if the score is a high score
//  o shows the high score dialog
//  o sends the play message to the sound thread to play the High.wav file
//  o saves the high scores on Hiscore.bin (in the working directory)
//  o and refreshes the High Scores listbox
//
// 2026: file renamed to Hiscore.bin, entries hold name[10], score and level
//       (standardization plan, section 10).

#define HS_NAMELEN   10
#define HS_ENTRIES   10

class HighScore
{
 private:
  typedef struct {               // the structure of one entry in Hiscore.bin
                  CHAR  name[HS_NAMELEN];
                  ULONG score;
                  ULONG level;
                 } HSENTRY;

  HSENTRY reg[HS_ENTRIES]; // the top ten entries
  INT  number;
  HWND hwndLB, hwndOwner; // Handles of the listbox and owner windows
  PSHAREDDATA sd; // Pointer to the shared data between threads
  VOID Defaults(); // Fill the table with empty entries

 public:
  HighScore(HWND lB, HWND owner); // Constructor
  ~HighScore(); // Destructor
  VOID Save(); // Save the scores
  VOID Read(); // Read them from Hiscore.bin
  VOID Show(); // Show them on the listbox
  INT  New(ULONG score, ULONG level); // is it a new score ?, if yes initiate the correct procedure.
};

VOID HighScore::Defaults()
{
 INT i;

 for(i=0; i<HS_ENTRIES; ++i)
 {
  strcpy(reg[i].name, "Anon");
  reg[i].score = 0;
  reg[i].level = 0;
 }
}

HighScore::HighScore(HWND lB, HWND owner)
{
 number = HS_ENTRIES;
 hwndLB = lB;
 hwndOwner = owner;
 Defaults();
 sd = (PSHAREDDATA) WinQueryWindowPtr(owner, 4);
 Read();
 Show();
}

HighScore::~HighScore()
{
}

INT HighScore::New(ULONG score, ULONG level)
{
 INT i, pos, high=0;
 HWND hwndParent, hwndGame;
 POBJECTWINDOWDATA owd;

 if(score == 0)
    return(0);

 pos = number;
 for(i=0; i<number; ++i)
  if(reg[i].score < score)
  {
   high = 1;
   pos = i;
   break;
  }

 if(high==1)
 {
  hwndParent = ParentClient();
  hwndGame = WinWindowFromID(WinWindowFromID(hwndParent, WID_MAIN), FID_CLIENT);
  owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwndGame, 8);
  if(owd->threadRunning)
     WinPostMsg(owd->hwndObject, WM_HIGH, 0, 0);

  sd->pszName[0] = '\0';
  WinDlgBox(HWND_DESKTOP, hwndOwner, NameDlgProc, NULLHANDLE, DID_HIGHSCORE, sd);
  if(sd->pszName[0] == '\0')
     strcpy(sd->pszName, tr(STR_ANON));

  for(i=number-1; i>pos; --i)
     reg[i] = reg[i-1];

  memset(reg[pos].name, 0, HS_NAMELEN);
  strncpy(reg[pos].name, sd->pszName, HS_NAMELEN-1);
  reg[pos].score = score;
  reg[pos].level = level;
  Save();
 }
 return(high);
}

VOID HighScore::Save()
{
 FILE *fp;

 fp = fopen("Hiscore.bin", "wb");
 if(fp != NULL)
 {
  fwrite(reg, sizeof(HSENTRY), HS_ENTRIES, fp);
  fclose(fp);
 }
}

VOID HighScore::Show()
{
 INT  i;
 CHAR line[48];

 WinSendMsg(hwndLB, LM_DELETEALL, 0, 0);
 for(i=0; i<number; ++i)
  if(reg[i].score > 0)
  {
   sprintf(line, "%2d. %-9s %8lu", i+1, reg[i].name, reg[i].score);
   WinSendMsg(hwndLB, LM_INSERTITEM, MPFROM2SHORT(LIT_END, 0), MPFROMP(line));
  }
}

VOID HighScore::Read()
{
 FILE  *fp;
 size_t got = 0;

 fp = fopen("Hiscore.bin", "rb");
 if(fp != NULL)
 {
  got = fread(reg, sizeof(HSENTRY), HS_ENTRIES, fp);
  fclose(fp);
 }

 if(got != HS_ENTRIES)   // missing or damaged file: start with a fresh table
 {
  Defaults();
  Save();
 }
 else
 {
  for(INT i=0; i<number; ++i)
     reg[i].name[HS_NAMELEN-1] = '\0';
 }
}
