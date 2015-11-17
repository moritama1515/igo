#include<stdio.h>

#define B_SIZE 9
#define WIDTH (B_SIZE+2)
#define ALLBOARD (WIDTH * WIDTH)
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define WALL 3
#define MARK 1


int board[ALLBOARD] = {};
int check_board[ALLBOARD] = {};
int dir4[4] = {+1,+WIDTH,-1,-WIDTH};
int dir8[8] = {};   
int color,z,prisoner_b,prisoner_w;

void CheckBoard(void);
void CheckBoard_check(void);
void BoardIni(void);
void ClearCheckBoard(void);
int CheckPut(int x,int y);
int FlipColor(int color);
int CheckWarning(int z);
int TakeStone(int z);
int RemoveStone(int z);
int RemoveCount(int z);

void CheckBoard(void)
{
  int i = 0;
  int mapy = 0;

  printf("    ");
  while(1){
    if(i != WIDTH){
      printf("%02d ",i);
      i++;
    }else{
      printf("\n");
      break;
    }
  }

  printf("%02d ",mapy);
  mapy++;
  for (i = 0; i < ALLBOARD; i++){
      if((i+1) % WIDTH != 0){
	printf("%3d",board[i]);
      }else if(mapy < WIDTH){
	  printf("%3d\n%02d ",board[i],mapy);
	  mapy++;
	  
      }else{
	printf("%3d\n",board[i]);
      }
    }
  printf("BLACK:%d,WHITE:%d\n",prisoner_b,prisoner_w);
}

void CheckBoard_check(void)
{
  int i = 0;
  int mapy = 0;

  printf("check_board\n");
  printf("    ");
  while(1){
    if(i != WIDTH){
      printf("%02d ",i);
      i++;
    }else{
      printf("\n");
      break;
    }
  }

  printf("%02d ",mapy);
  mapy++;
  for (i = 0; i < ALLBOARD; i++){
    if((i+1) % WIDTH != 0){
      printf("%3d",check_board[i]);
    }else if(mapy < WIDTH){
      printf("%3d\n%02d ",check_board[i],mapy);
      mapy++;

    }else{
      printf("%3d\n",check_board[i]);
    }
  }
}

void BoardIni()
{
  int i;

  for(i = 0; i < ALLBOARD-WIDTH; i++)
    {
      if( i < WIDTH){
	board[i] = WALL;
	check_board[i] = WALL;
      }else if((i+1) % WIDTH == 0 || i % WIDTH == 0){
	board[i] = WALL;
	check_board[i] = WALL;
      }else{
	board[i] = EMPTY;
	check_board[i] = EMPTY;
      }
    }

  for(i = (ALLBOARD-WIDTH);i < ALLBOARD;i++){
    board[i] = WALL;
    check_board[i] = WALL;
  }
}

void ClearCheckBoard()
{
  int i;
  for(i = 0; i < ALLBOARD-WIDTH; i++)
    {
      if( i < WIDTH){
	check_board[i] = WALL;
      }else if((i+1) % WIDTH == 0 || i % WIDTH == 0){
	check_board[i] = WALL;
      }else{
	check_board[i] = EMPTY;
      }
    }

  for(i = (ALLBOARD-WIDTH);i < ALLBOARD;i++){
    check_board[i] = WALL;
  }
}

int FlipColor(int color)
{
  return 3 - color;
}

int CheckPut(int x,int y)
{
  int i,check;

  z = (WIDTH*y) + x;
  if(z <= ALLBOARD && board[z] == EMPTY && CheckWarning(z) != -1){
    board[z] = color;
  }else{
    printf("Put error.\n");
    return -1;
  }
  
    if(color == BLACK){
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	printf("put[%d];%d\n",i,check);
	if(TakeStone(check) == 0){
	  prisoner_b = RemoveStone(check);
	}else{
	  ClearCheckBoard;
	}
      }
    }else{
      for(i = 0; i < 4; i++){
	CheckBoard_check();
	check = z + dir4[i];
	printf("put[%d];%d\n",i,check);
	if(TakeStone(check) == 0){
	  prisoner_w = RemoveStone(check);
	}else{
	   ClearCheckBoard;
	} 
      }
    }   
    return z;
}

int CheckWarning(int z)
{
  int check,flag,i;

  check = 0;
  flag = 0;

  //printf("color;%d\n",color);
  //printf("z;%d\n",z);

  if(color == BLACK){
    for(i = 0; i < 4; i++){
      check = z + dir4[i];
      if(board[check] == BLACK){;
      }else if(board[check] != EMPTY ){
	flag += 1;
      }
    }
  }else{
    for(i = 0; i < 4; i++){
      check = z + dir4[i];
  //printf("check[%d];%d\n",i,check);
      if(board[check] == WHITE){;
      }else if(board[check] != EMPTY ){
	flag += 1;
      }
    }
  }

  //printf("flag;%d\n",flag);

  if(flag == 4){
    printf("Here is ban position.\n");
    return -1;
      }
  
  return 0;
}

int TakeStone(int z)
{
  int i,check,rtn;
  
    if(check_board[z] == MARK ){
      return -1;
    }
    
    check_board[z] = MARK;
      
    if(board[z] == EMPTY){
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	if(TakeStone(check) == -1){
	  return -1;
	}
      }
    }
    return 0;   
}
  
int RemoveStone(int z)
{
  int prisoner;
  
  if(board[z] == color){
    return 0;
  }

  if(board[z] == EMPTY){
    return 0;
  }

  if(board[z] == WALL){
    return 0;
  }

  ClearCheckBoard();

  if(TakeStone(z) == 0){
   prisoner = RemoveCount(z);
   return prisoner;  
  }
  return 0;
}

int RemoveCount(int z)
{
  int i,check,prisoner;
  
    if(board[z] == color){
      prisoner += 1;
      board[z] = EMPTY;
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	RemoveCount(check);
      }
    }
    return prisoner;
}

int main()
{  
  
  int *inputx,*inputy;
  
  /*碁盤の初期化*/
  BoardIni();
  
  printf("Program Start\n");

  /*アゲハマ*/
  prisoner_b = 0;
  prisoner_w = 0;

  color = WHITE;
 
  while(1)
    {
      CheckBoard();
      color = FlipColor(color);
      if(color == 1){
      printf("BLACK TURN\nx->");
      }else{
	printf("WHITE TURN\nx->");
      }
      scanf("%d",&inputx);
      printf("y->"); scanf("%d",&inputy);
      CheckPut(inputx,inputy);
      if(z == -1){
	printf("end\n");
	break;
      }
      printf("z:%d %d-%d\n",z,inputx,inputy);
    }
  
  return 0;
}

      
