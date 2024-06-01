#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include <math.h>
using namespace std;
char mohavate[100][100];
int locpacx = 1, locpacy = 1;
char pacman = 'X';
char ghost = 'O';
char jahat = 'f';
char tjahat;
int jooon=3;
int energy1 = 16 , energy2 = 16 , energy3 = 16;
int recovery1 = 12 , recovery2 = 12 , recovery3 = 12;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void SetCursorPosition(int x, int y)
{
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = {x, y};
  SetConsoleCursorPosition(output, pos);
}
void zamin(int row, int column)
{
  int i, j;
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      if (i == 0 || i == row - 1 || j == 0 || j == column - 1)
      {
        mohavate[i][j] = '#';
      }
      else
      {
        mohavate[i][j] = '.';
      }
    }
  }
}
void mane(int row, int column)
{
  int m, n, mane = 0;
  while (mane < (row * column / 10))
  {
    m = rand() % row;
    n = rand() % column;
    if (mohavate[m][n] != '#')
    {
      mohavate[m][n] = '#';
      mane++;
    }
  }
}
int noghte(int row, int column)
{
  int i, j, noghte = 0;
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      if (mohavate[i][j] == '.')
      {
        noghte++;
      }
    }
  }
  return noghte;
}
// fasele= fasele pacman ta ghost
int fasele(int locgx, int locgy)
{
  int fasele;
  fasele = sqrt(pow((locgx - locpacx), 2) + pow((locgy - locpacy), 2));
  return fasele;
}
void Taghib(int row, int column, int &locgx, int &locgy, char &plocg)
{
    if (locpacy < locgy && mohavate[locgy - 1][locgx] != '#'&&mohavate[locgy - 1][locgx] != 'O')
    {
      mohavate[locgy][locgx] = plocg;
      if (mohavate[locgy - 1][locgx]!='O')
      {
      	plocg = mohavate[locgy - 1][locgx];
	  }
      locgy--;
      mohavate[locgy][locgx] = ghost;
    }
    else if (locpacy > locgy && mohavate[locgy + 1][locgx] != '#'&&mohavate[locgy + 1][locgx] != 'O')
    {
      mohavate[locgy][locgx] = plocg;
      if(mohavate[locgy + 1][locgx]!='O')
      {
      	plocg = mohavate[locgy + 1][locgx];
	  }
      locgy++;
      mohavate[locgy][locgx] = ghost;
    }
    else if (locpacx > locgx && mohavate[locgy][locgx + 1] != '#'&&mohavate[locgy][locgx + 1] != 'O' &&(locgy!=row / 2||locgx + 1!=column - 1))
    {
      mohavate[locgy][locgx] = plocg;
      if (mohavate[locgy][locgx + 1]!='O')
      {
      	plocg = mohavate[locgy][locgx + 1];
	  }
      locgx++;
      mohavate[locgy][locgx] = ghost;
    }
    else if (locpacx < locgx && mohavate[locgy][locgx - 1] != '#'&&mohavate[locgy][locgx - 1] != 'O' &&(locgy!=row / 2||locgx - 1!=0))
    {
      mohavate[locgy][locgx] = plocg;
      if(mohavate[locgy][locgx - 1]!='O')
      {
      	plocg = mohavate[locgy][locgx - 1];
	  }
      locgx--;
      mohavate[locgy][locgx] = ghost;
    }
}
void Random(int row, int column, int &locgx, int &locgy, char &plocg){
  int jahatG , tjahatG;
  bool jahatdorost = 0;
  while (jahatdorost == 0){
    tjahatG = rand()%4;
      if ((tjahatG == 0 && mohavate[locgy - 1][locgx] != '#') || (tjahatG == 1 && mohavate[locgy + 1][locgx] != '#') || (tjahatG == 2 && mohavate[locgy][locgx - 1] != '#') || (tjahatG == 3 && mohavate[locgy][locgx + 1] != '#'))
      {
        jahatG = tjahatG;
        jahatdorost = 1;
      }
  }
    if (jahatG == 0 && mohavate[locgy - 1][locgx] != '#'&&mohavate[locgy - 1][locgx] != 'O')
    {
      mohavate[locgy][locgx] = plocg;
      locgy--;
      if(mohavate[locgy][locgx]!='O')
      {
      	plocg = mohavate[locgy][locgx]; 
	  }
      mohavate[locgy][locgx] = ghost;
    }
    else if (jahatG == 1 && mohavate[locgy + 1][locgx] != '#'&&mohavate[locgy + 1][locgx] != 'O')
    {
      mohavate[locgy][locgx] = plocg;
      locgy++;
      if(mohavate[locgy][locgx]!='O')
      {
      	plocg = mohavate[locgy][locgx];
	  }
      mohavate[locgy][locgx] = ghost;
    }
    else if (jahatG == 2 && mohavate[locgy][locgx - 1] != '#'&&mohavate[locgy][locgx - 1] != 'O' &&(locgy!=row / 2||locgx - 1!=0))
    {
      mohavate[locgy][locgx] = plocg;
      locgx--;
      if(mohavate[locgy][locgx]!='O')
      {
      	plocg = mohavate[locgy][locgx];
	  }
      mohavate[locgy][locgx] = ghost;
    }
    else if (jahatG == 3 && mohavate[locgy][locgx + 1] != '#'&&mohavate[locgy][locgx + 1] != 'O' &&(locgy!=row / 2||locgx + 1!=column - 1))
    {
      mohavate[locgy][locgx] = plocg;
      locgx++;
      if(mohavate[locgy][locgx]!='O')
      {
      	plocg = mohavate[locgy][locgx];
	  }
      mohavate[locgy][locgx] = ghost;
    }
}
void chap(int row, int column)
{
  int i, j;
  cout<<"jooooon: "<<jooon<<"      "<<"tedad ghazaii ke baas bokhori: "<<noghte(row,column)<<endl<<endl;
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < column; j++)
    {
      switch(mohavate[i][j])
  {
  	case '#':
  		SetConsoleTextAttribute(h, 0xFF);
  		break;
  	case 'X':
  		SetConsoleTextAttribute(h, 0x66);
  		break;
  	case 'O':
  		SetConsoleTextAttribute(h, 0xCC);
  		break;
  	case '.':
  		SetConsoleTextAttribute(h, 0x0F);
  		break;
  	case ' ':
  		SetConsoleTextAttribute(h, 0x0F);
  		break;
  	default:
  		SetConsoleTextAttribute(h, 0x0F);
  }
    cout << mohavate[i][j] << " ";
    }
    cout << endl;
  }
  SetConsoleTextAttribute(h, 0x0F);
  SetCursorPosition(0, 0); 
}
void bakht(int row, int column, int &locg1x, int &locg1y,char &plocg1, int &locg2x, int &locg2y,char &plocg2, int &locg3x, int &locg3y,char &plocg3)
{
	if(locpacx==locg1x&&locpacy==locg1y||locpacx==locg2x&&locpacy==locg2y||locpacx==locg3x&&locpacy==locg3y)
	{
		int i,j;
		mohavate[locpacy][locpacx]='O';
		locg1x = column - 2; 
		locg1y = row - 2;
        locg2x = 1; 
		locg2y = row - 2;
        locg3x = column - 2; 
		locg3y = 1;
        jahat = 'f';
        plocg1 = ' ';
        plocg2 = ' ';
        plocg3 = ' ';
        for (i = 0; i < row; i++)
         {
          for (j = 0; j < column; j++)
           {
           	 if (mohavate[i][j]==pacman||mohavate[i][j]==ghost)
           	   {
           	     mohavate[i][j]=' ';
			   }
		   }
	    }
        locpacx = 1;
        locpacy = 1;
        jahat = 'f';
        energy1 = 16;
        energy2 = 16;
        energy3 = 16;
        recovery1 = 12;
        recovery2 = 12;
        recovery3 = 12;
        jooon--;
        chap(row,column);
        usleep(300000);
        if(jooon==3||jooon==2)
        {
          system("cls");
		  cout<<"ye jooonet raft :(";
		  usleep(900000);
		  usleep(900000);
		  usleep(900000);
		  system("cls");
		}
		if(jooon==1)
		{
		  system("cls");
		  cout<<"ye joon moonde, bepppaaa!!!!";
		  usleep(900000);
		  usleep(900000);
		  usleep(900000);
		  system("cls");
		}
		mohavate[1][1]=pacman;
	}
}
void ghostmove(int AMT , int &locgx , int &locgy , int &recovery , bool &tekrar , int &energy , char &plocg , int row , int column){
  bool ghostmode = 0;
  if ((AMT - fasele(locgx, locgy) > -2 && AMT - fasele(locgx, locgy) < 2 ) && recovery <= 0 && tekrar == 1){
      ghostmode = 1;
      energy = 16;
      tekrar = 0;
    }
    if (AMT >= fasele(locgx, locgy) && recovery <= 0){
      ghostmode = 1;
      energy --;
      if (energy == 0){
        ghostmode = 0;
        recovery = 12;
        tekrar = 1;
      }
    }
    if (ghostmode == 0){
      recovery--;
    }
    if (ghostmode == 1){
      Taghib(row, column, locgx, locgy, plocg);
    }
    if (ghostmode == 0){
      Random(row, column, locgx, locgy, plocg);
    }
}
int main()
{
  srand(time(0));
  int row, column;
  cout << "pacmanet chan dar chan bashe? " << endl;
  cin >> row >> column;
  int i, j;
  // AMT = andaze mojaze taghib
  int AMT = sqrt(pow((column) / 3, 2) + pow((row) / 3, 2));
  int locg1x = column - 2, locg1y = row - 2;
  int locg2x = 1, locg2y = row - 2;
  int locg3x = column - 2, locg3y = 1;
  // plocg1 = previous location of ghost1
  char plocg1 = ' ';
  char plocg2 = ' ';
  char plocg3 = ' ';
  zamin(row, column);
  mane(row, column);
  mohavate[1][1] = pacman;
  mohavate[row - 2][column - 2] = ghost;
  mohavate[row - 2][1] = ghost;
  mohavate[1][column - 2] = ghost;
  mohavate[row / 2][0] = ' ';
  mohavate[row / 2][column - 1] = ' ';
  mohavate[row / 2][1] = ' ';
  mohavate[row / 2][column - 2] = ' ';
  mohavate[2][1] = '.';
  mohavate[row-3][column - 3] = '.';
  mohavate[row - 3][1] = '.';
  system("cls");
  bool tekrar1=1 , tekrar2=1 , tekrar3=1;
  while (noghte(row, column) != 0&&jooon>0)
  {
    ghostmove(AMT , locg1x , locg1y , recovery1 , tekrar1 , energy1 , plocg1 , row , column);
    ghostmove(AMT , locg2x , locg2y , recovery2 , tekrar2 , energy2 , plocg2 , row , column);
    ghostmove(AMT , locg3x , locg3y , recovery3 , tekrar3 , energy3 , plocg3 , row , column);
    bakht(row,column,locg1x,locg1y,plocg1,locg2x,locg2y,plocg2,locg3x,locg3y,plocg3);
    chap(row, column);
    if (mohavate[row / 2][0] == pacman)
    {
      mohavate[row / 2][0] = ' ';
      usleep(300000);
      chap(row, column);
      usleep(300000);
      mohavate[row / 2][column - 1] = pacman;
      chap(row, column);
      tjahat = 'a';
      locpacy = row / 2;
      locpacx = column - 1;
    }
    else if (mohavate[row / 2][column - 1] == pacman)
    {
      mohavate[row / 2][column - 1] = ' ';
      usleep(300000);
      chap(row, column);
      usleep(300000);
      mohavate[row / 2][0] = pacman;
      chap(row, column);
      jahat = 'd';
      locpacy = row / 2;
      locpacx = 0;
    }
    usleep(300000);
    if (kbhit())
    {
      tjahat = getch();
    }
    if ((tjahat == 'w' && mohavate[locpacy - 1][locpacx] != '#') || (tjahat == 's' && mohavate[locpacy + 1][locpacx] != '#') || (tjahat == 'a' && mohavate[locpacy][locpacx - 1] != '#') || (tjahat == 'd' && mohavate[locpacy][locpacx + 1] != '#'))
    {
      jahat = tjahat;
    }
    if (jahat == 'w' && mohavate[locpacy - 1][locpacx] != '#')
    {
      mohavate[locpacy][locpacx] = ' ';
      locpacy--;
      mohavate[locpacy][locpacx] = pacman;
    }
    else if (jahat == 's' && mohavate[locpacy + 1][locpacx] != '#')
    {
      mohavate[locpacy][locpacx] = ' ';
      locpacy++;
      mohavate[locpacy][locpacx] = pacman;
    }
    else if (jahat == 'a' && mohavate[locpacy][locpacx - 1] != '#')
    {
      mohavate[locpacy][locpacx] = ' ';
      locpacx--;
      mohavate[locpacy][locpacx] = pacman;
    }
    else if (jahat == 'd' && mohavate[locpacy][locpacx + 1] != '#')
    {
      mohavate[locpacy][locpacx] = ' ';
      locpacx++;
      mohavate[locpacy][locpacx] = pacman;
    }
  }
  if (noghte(row, column) == 0)
  {
  	system("cls");
    cout << "Borrrrrrdiiiiiiii!!!!";
  }
  if (jooon==0)
  {
  	system("cls");
  	cout<<"Ei baaaaba bakhti ke :(((((";
	usleep(900000);
	usleep(900000);
	usleep(900000);
  }
}
