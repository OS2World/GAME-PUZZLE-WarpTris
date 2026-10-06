// This is the object that represents the figure that is currently moving

// Object Figure Definition

class Figure
{
 private:
  INT  posX, posY; // The current position of the figure
  INT  definition[MAX_FIGURE_X][MAX_FIGURE_Y]; // The logical representation of the figure
  INT  bitmapID; // Which bitmap used to draw the figure
  BOOL pairFigure; // Is it a pair figure (has to do with the rotation of the figure)
  HWND hwndClient; // Handle of the game client window

 public:
  Figure(HWND hwnd, INT bitmap, INT def[MAX_FIGURE_X][MAX_FIGURE_Y], INT px=0, INT py=0, BOOL animated=TRUE, BOOL draw=TRUE);
   // Constructor
  VOID Rotate(Board &board); // Rotate the figure on the board (if possible...)
  VOID ClearLastFigure(INT x=0, INT y=0); // Erase last figure from the game window
  VOID Draw(INT x=0, INT y=0); // Draw the figure
  VOID DrawNext(INT x=0, INT y=0); // Draw the figure on the next window
  INT  Move(DIR d, Board &board); // Move it on a given direction (if possible...)
  VOID Fall(DIR d, Board &board); // Let it fall to a given side
  VOID operator=(Figure &figure); // To assign a figure to another (has to do with the next figure...)
  INT  GetBitmapID() {return(bitmapID);}// Get method of the private var, bitmapID
};


VOID Figure::operator=(Figure &figure)
{
 INT i,j;

 bitmapID = figure.bitmapID;
 pairFigure = figure.pairFigure;
 posX=figure.posX;
 posY=figure.posY;
 for(i=0;i<MAX_FIGURE_Y;++i)
  for(j=0;j<MAX_FIGURE_X;++j)
   definition[i][j] = figure.definition[i][j];
}




Figure::Figure(HWND hwnd, INT bitmap, INT def[MAX_FIGURE_X][MAX_FIGURE_Y], INT px, INT py, BOOL animated, BOOL draw)
{
 INT x, y;

 hwndClient = hwnd;
 bitmapID = bitmap;
 pairFigure = FALSE;
 posX=px;
 posY=py;
 for(y=0; y<MAX_FIGURE_Y; ++y)
    for(x=0; x<MAX_FIGURE_X; ++x)
      {
       if(def[x][y] == 9) {pairFigure = TRUE;}
       definition[x][y] = def[x][y];
      }
 if(animated) Animation(hwnd);
 if(draw)
  Draw(px, py);
}

VOID Figure::Rotate(Board &board)
{
 INT i,j,k,l;
 INT aux[5];
 INT def[MAX_FIGURE_X][MAX_FIGURE_Y];

 board.RemoveFigure(posX, posY, definition);
 ClearLastFigure();

 for(i=0; i<5; ++i)
    for(j=0; j<5; ++j)
       def[i][j] = 0;

 if(!pairFigure)
 {
  for(i=4,k=0;k<5;--i,++k)
    for(j=0;j<5;++j)
      def[j][k] = definition[i][j];
 }
 else
 {
  for(i=3,k=0;k<4;--i,++k)
    for(j=0;j<4;++j)
      def[j][k] = definition[i][j];
 }

 if(board.PutFigure(posX,posY,def))
 {
  for(i=0;i<5;++i)
   for(j=0;j<5;++j)
    definition[i][j] = def[i][j];
  Draw();
 }
 else
 board.PutFigure(posX, posY, definition);
 Draw();
}

VOID Figure::ClearLastFigure(INT x, INT y)
{
 INT i,j;

 if((x==0) && (y==0))
 {
  for(i=0;i<MAX_FIGURE_Y;++i)
   for(j=0;j<MAX_FIGURE_X;++j)
    if(definition[i][j] == FULL)
      ClearSquare(hwndClient, posX+j, posY+i);
 }
 else
 {
  for(i=0;i<MAX_FIGURE_Y;++i)
   for(j=0;j<MAX_FIGURE_X;++j)
    if(definition[i][j] == FULL)
       ClearSquare(hwndClient, x+j, y+i);
 }
 return;
}


VOID Figure::Draw(INT x, INT y)
{
 INT i,j;

 if((x==0) && (y==0))
 {
  for(i=0;i<5;++i)
   for(j=0;j<5;++j)
    if(definition[i][j] == FULL)
      DrawSquareOnGame(hwndClient, posX+j, posY+i, bitmapID);
 }
 else
 {
  for(i=0;i<5;++i)
   for(j=0;j<5;++j)
    if(definition[i][j] == FULL)
       DrawSquareOnGame(hwndClient, x+j, y+i, bitmapID);
 }
}

VOID Figure::DrawNext(INT x, INT y)
{
 INT i,j;

  for(i=0;i<5;++i)
   for(j=0;j<5;++j)
    if(definition[i][j] == FULL)
       DrawSquareOnNext(hwndClient, x+j, y+i, bitmapID);
}

INT Figure::Move(DIR d, Board &board)
{
 INT ret=0;

 board.RemoveFigure(posX, posY, definition);
 switch (d)
 {
  case UP:
    ret=board.PutFigure(posX,posY-1, definition);
    if(ret)
       {
        ClearLastFigure();
        --posY;
       }
    else
     board.PutFigure(posX,posY, definition);
   break;

  case DOWN:
    ret=board.PutFigure(posX,posY+1, definition);
    if(ret)
       {
        ClearLastFigure();
        ++posY;
       }
    else
     board.PutFigure(posX,posY,definition);
   break;

  case RIGHT:
    ret=board.PutFigure(posX+1,posY, definition);
    if(ret)
       {
        ClearLastFigure();
        ++posX;
       }
    else
     board.PutFigure(posX,posY, definition);
   break;

  case LEFT:
    ret=board.PutFigure(posX-1,posY, definition);
    if(ret)
       {
        ClearLastFigure();
        --posX;
       }
    else
     board.PutFigure(posX,posY, definition);
   break;

  default:
     break;
 }
 if(ret) Draw();
 return ret;
}

VOID Figure::Fall(DIR d, Board &board)
{
 while(Move(d, board)) ;
}
