// This is the object that handles the logical operations
// of putting and removing pieces on the board, it also
// evaluates the board and removes lines if that's the case.

// Board object definition

class Board
{
 private:
  INT board[COLUMNS][LINES]; // The logical board
  HWND hwndClient;           // Handle of the game client window
  VOID EraseLine(INT line);  // Removes a line
  VOID EraseColumn(INT column); // Removes a Column
  INT  Limit(DIR side, INT definition[5][5]); // Gives the limit of a given side of a piece
  VOID DrawSquare(INT x, INT y); // Draws a square on the board
  INT  SingleEvaluate(DIR side); // Searches one side of the board for full lines

 public:
  Board(HWND hwnd); // Constructor
  VOID DrawArea(DIR side); // Draws a given area of the board, for performance reasons
  INT  Evaluate(DIR side); // Searches the board for full lines on a way that depends
                           // on the side the piece is falling, it returns the number
                           // of lines removed.
  BOOL PutFigure(INT x, INT y, INT definition[5][5]); // Puts a figure on the board (logical)
                                                      // Returns TRUE if possible on (x,y)
  VOID RemoveFigure(INT x, INT y, INT definition[5][5]); // Removes a figure from the board
  BOOL Finished(); // Is the game over ?
};


Board::Board(HWND hwnd)
{
 INT x, y;

 hwndClient = hwnd;
 for(y=0; y < LINES; ++y)
    for(x=0; x < COLUMNS; ++x)
       board[x][y] = EMPTY;
}

BOOL Board::Finished()
{
 INT x, y;

 for(y=8; y<=11; ++y)
    for(x=8; x<=11; ++x)
       if(board[x][y] != EMPTY) return(TRUE);

 return(FALSE);
}

VOID Board::DrawArea(DIR side)
{
 INT limX=0, limY=0,
     limCX=19, limCY=19;
 INT x,y;

 switch(side)
    {
     case UP:
         limCY = 7;
        break;

     case DOWN:
         limY = 12;
        break;

     case RIGHT:
         limX = 12;
        break;

     case LEFT:
         limCX = 7;
        break;

     default:
        break;
    }
 for(y=limY; y<=limCY; ++y)
    for(x=limX; x<=limCX; ++x)
       DrawSquare(x,y);
 return;
}

VOID Board::DrawSquare(INT x, INT y)
{
 PWINDOWDATA wd;

 wd = (PWINDOWDATA) WinQueryWindowPtr(hwndClient, 0);
 if(board[x][y] != EMPTY)
  DrawSquareOnGame(hwndClient, x, y, board[x][y]);
 else
  ClearSquare(hwndClient, x, y);

 return;
}

VOID Board::EraseColumn(INT column)
{
 INT x,y;

 if((column >= 0) && (column <= 7))
    {
     for(x=column; x<=7; ++x)
       for(y=0; y<LINES; ++y)
         board[x][y] = board[x+1][y];

     for(y=0; y<LINES; ++y)
         board[7][y] = EMPTY;
    }

 if((column >= 12) && (column <= 19))
    {
     for(x=column; x>=12; --x)
        for(y=0; y<LINES; ++y)
            board[x][y] = board[x-1][y];

     for(y=0; y<LINES; ++y)
        board[12][y] = EMPTY;
    }
}



VOID Board::EraseLine(INT line)
{
 INT x, y;

 if((line >= 0) && (line <= 7))
    {
     for(x=0; x<COLUMNS; ++x)
        for(y=line; y<=7; ++y)
           board[x][y] = board[x][y+1];

     for(x=0; x<COLUMNS; ++x)
        board[x][7] = EMPTY;
    }

 if((line >= 12) && (line <= 19))
    {
     for(x=0; x<COLUMNS; ++x)
        for(y=line; y>=12; --y)
           board[x][y] = board[x][y-1];

     for(x=0; x<COLUMNS; ++x)
        board[x][12] = EMPTY;
    }
}

INT Board::Evaluate(DIR side)
{
 INT ret=0;

 switch(side)
    {
     case UP:
        ret += SingleEvaluate(UP);
        ret += SingleEvaluate(LEFT);
        ret += SingleEvaluate(RIGHT);
       return(ret);

    case DOWN:
        ret += SingleEvaluate(DOWN);
        ret += SingleEvaluate(LEFT);
        ret += SingleEvaluate(RIGHT);
       return(ret);


    case RIGHT:
        ret += SingleEvaluate(UP);
        ret += SingleEvaluate(DOWN);
        ret += SingleEvaluate(RIGHT);
       return(ret);

    case LEFT:
        ret += SingleEvaluate(UP);
        ret += SingleEvaluate(DOWN);
        ret += SingleEvaluate(LEFT);
       return(ret);

    default:
       break;
    }
 return(0);
}


INT Board::SingleEvaluate(DIR side)
{
 INT  x, y;
 INT  line, column;
 BOOL hole=FALSE;
 INT taken=0;

 switch(side)
 {
  case UP:
     for(line=7; line >=0; --line)
        {
         for(x=0; x<COLUMNS; ++x)
            if(board[x][line] == EMPTY) {hole=TRUE;break;}
         if(!hole) {EraseLine(line); ++taken;}
         else hole=FALSE;
        }
     break;

   case DOWN:
      for(line=12; line<LINES; ++line)
         {
          for(x=0; x<COLUMNS; ++x)
             if(board[x][line] == EMPTY) {hole=TRUE; break;}
          if(!hole) {EraseLine(line); ++taken;}
          else hole=FALSE;
         }
      break;

   case RIGHT:
      for(column=12; column<COLUMNS; ++column)
         {
          for(y=0; y<LINES; ++y)
             if(board[column][y] == EMPTY) {hole=TRUE; break;}
          if(!hole) {EraseColumn(column); ++taken;}
          else hole=FALSE;
         }
      break;

   case LEFT:
      for(column=7; column>=0; --column)
         {
          for(y=0; y<LINES; ++y)
             if(board[column][y] == EMPTY) {hole=TRUE; break;}
          if(!hole) {EraseColumn(column); ++taken;}
          else hole=FALSE;
         }
      break;

   default:
      break;
 }
 if(taken)
   {
    DrawArea(side);
   }
 return(taken);
}


VOID Board::RemoveFigure(INT x, INT y, INT definition[5][5])
{
 INT px, py;

 for(py=0; py<MAX_FIGURE_Y; ++py)
    for(px=0; px<MAX_FIGURE_X; ++px)
       if(definition[py][px] == FULL)
           board[px+x][py+y] = EMPTY;
}

BOOL Board::PutFigure(INT x, INT y, INT definition[5][5])
{
 INT  px, py;
 BOOL possible=TRUE;
 PWINDOWDATA wd;

 if(Limit(LEFT, definition)+x<0) possible=FALSE;
 if(Limit(RIGHT, definition)+x>19) possible=FALSE;
 if(Limit(UP, definition)+y<0) possible=FALSE;
 if(Limit(DOWN, definition)+y>19) possible=FALSE;

 for(py=0; py<MAX_FIGURE_Y; ++py)
    for(px=0; px<MAX_FIGURE_X; ++px)
      if(definition[py][px] == FULL)
          if(board[px+x][py+y] != EMPTY)
             {possible=FALSE; break;}

 if(possible)
    for(py=0; py<MAX_FIGURE_Y; ++py)
       for(px=0; px<MAX_FIGURE_X; ++px)
        {
         if(definition[py][px] == FULL)
          {
           wd = (PWINDOWDATA) WinQueryWindowPtr(hwndClient, 0);
           board[px+x][py+y] = wd->currentBitmapID;
          }
        }
return(possible);
}


INT  Board::Limit(DIR side, INT definition[5][5])
{
 INT x, y, ret=-1;

 switch(side)
    {
     case UP:
         for(y=0;(y<MAX_FIGURE_Y && ret==-1); ++y)
            for(x=0; x<MAX_FIGURE_X; ++x)
               if(definition[y][x] == FULL) {ret=y; break;}
        break;

     case DOWN:
        for(y=3; (y>=0 && ret==-1); --y)
           for(x=0; x<MAX_FIGURE_X; ++x)
              if(definition[y][x] == FULL) {ret=y; break;}
        break;

     case LEFT:
        for(x=0;(x<MAX_FIGURE_X && ret==-1); ++x)
           for(y=0; y<MAX_FIGURE_Y; ++y)
              if(definition[y][x] == FULL) {ret=x; break;}
        break;

     case RIGHT:
         for(x=3; (x>=0 && ret==-1); --x)
            for(y=0; y<MAX_FIGURE_Y; ++y)
               if(definition[y][x] == FULL) {ret=x; break;}
        break;

     default:
        break;
    }
 return(ret);
}
