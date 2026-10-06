// This class handles everything that has to do with the High Scores:
//  o tests if the score is an high score
//  o shows the high score dialog
//  o sends the play message to the sound thread to play the HighScore.wav file
//  o saves the high scores on the ini file (which insn't really an ini file)
//  o and refreshes the High Scores listbox
//

//Class HighScore

class HighScore
{
 private:
  typedef struct {               // the structure of a register on the ini file
                  CHAR name[40];
                  ULONG score;
                 } REGISTER;

  REGISTER reg[10]; // the top ten register
  INT  number;
  HWND hwndLB, hwndOwner; // Handles of the listbox and owner windows
  PSHAREDDATA sd; // Pointer to the shared data between threads

 public:
  HighScore(HWND lB, HWND owner); // Constructor
  ~HighScore(); // Destructor
  VOID Save(); // Save the scores
  VOID Read(); // Read them from the ini file
  VOID Show(); // Show them on the listbox
  INT  New(ULONG score); // is it a new score ?, if yes initiate the correct procedure.
};

HighScore::HighScore(HWND lB, HWND owner)
{
 INT i;

 number = 10;
 hwndLB = lB;
 hwndOwner = owner;
 for(i=0;i<10;++i)
 {
  reg[i].name[0] = NULL;
  reg[i].score=0;
 }
 sd = (PSHAREDDATA) WinQueryWindowPtr(owner, 4);
 Read();
 Show();
}

HighScore::~HighScore()
{
 INT i;
 for(i=0;i<10;++i) ;
}




INT HighScore::New(ULONG score)
{
 INT i,pos,high=0;
 HWND hwndParent, hwndGame;
 REGISTER aux[10];
 POBJECTWINDOWDATA owd;

 for(i=0;i<number;++i)
 { aux[i].name[0] = NULL;
   aux[i].score=0;
 }
 for(i=0;i<number;++i)
  if(reg[i].score < score)
  { high=1;break;}
 pos=i;
 if(high==1)
 {
  for(i=0;i<number;++i)
  {
   if(i<pos){strcpy(aux[i].name,reg[i].name);aux[i].score=reg[i].score;}
   if(i>pos){strcpy(aux[i].name,reg[i-1].name);aux[i].score=reg[i-1].score;}
  }
  // dialog
  hwndParent = WinWindowFromID(WinWindowFromID(HWND_DESKTOP, WID_PARENT), FID_CLIENT);
  hwndGame = WinWindowFromID(WinWindowFromID(hwndParent, WID_MAIN), FID_CLIENT);
  owd = (POBJECTWINDOWDATA) WinQueryWindowPtr(hwndGame, 8);
  if(owd->threadRunning)
     WinPostMsg(owd->hwndObject, WM_HIGH, 0, 0);
  WinDlgBox(HWND_DESKTOP, hwndOwner, NameDlgProc, NULLHANDLE, DID_HIGHSCORE, sd);
  strcpy(aux[pos].name, sd->pszName);
  aux[pos].score=score;
  for(i=0;i<number;++i)
   {strcpy(reg[i].name,aux[i].name);reg[i].score=aux[i].score;}
  Save();
 }
 return(high);
}

VOID HighScore::Save()
{
 FILE *fp;
 INT i;

 fp=fopen("SCORES.INI","wb");
 fwrite(&reg, sizeof(REGISTER)*10, 1, fp);
 fclose(fp);
}

VOID HighScore::Show()
{
 INT i,j,k;
 PSZ pszScore, pszOrder;
 PSZ pszEntry[10];


 pszScore = (PSZ) malloc(20*sizeof(char));
 pszOrder = (PSZ) malloc(10*sizeof(char));

 for(i=0; i<10; ++i)
  pszEntry[i] = (PSZ) malloc(50*sizeof(char));

 WinSendMsg(hwndLB, LM_DELETEALL, 0, 0);
 for(i=0;i<number;++i)
  if(reg[i].score>0)
  {
   _ltoa(i+1, pszOrder, 10);                    // Ugly code, instn't it? :)
   for(j=0;j<strlen(pszOrder);++j)
      (pszEntry[i])[j] = pszOrder[j];
   (pszEntry[i])[strlen(pszOrder)] = '.';
   (pszEntry[i])[strlen(pszOrder)+1] = ' ';
   if(strlen(pszOrder)==1)
      (pszEntry[i])[strlen(pszOrder)+2] = ' ';

   _ltoa(reg[i].score, pszScore, 10);
   for(j=4;j<strlen(reg[i].name)+4;++j)
      (pszEntry[i])[j] = reg[i].name[j-4];
                                               // But works! Amazing....
    for(j=strlen(reg[i].name)+4; j<18; ++j)
       (pszEntry[i])[j] = ' ';

    for(j=18; j<28-strlen(pszScore); ++j)
       (pszEntry[i])[j] = ' ';

    for(k=0,j=27-strlen(pszScore); j<28 && k<7; ++k,++j)
       (pszEntry[i])[j] = pszScore[k];

   (pszEntry[i])[j+1] = '\0';
   WinSendMsg(hwndLB, LM_INSERTITEM, MPFROM2SHORT(i,0), MPFROMP(pszEntry[i]));
  }
 for(i=0; i<10; ++i)
  free(pszEntry[i]);
  free(pszScore);
  free(pszOrder);
}

VOID HighScore::Read()
{
 FILE *fp;

 fp=fopen("SCORES.INI","rb");
 if(fp!=NULL)
 {
  fseek(fp, SEEK_SET, 0);
  fread(&reg, sizeof(REGISTER)*10, 1, fp);
  fclose(fp);
 } else { fp=fopen("SCORES.INI","wb"); fclose(fp); }
}


