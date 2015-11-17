#include<stdio.h>

#define B_SIZE 9                  //BOARDSIZE
#define WIDTH (B_SIZE+2)          //BOARDSIZE+WALL
#define ALLBOARD (WIDTH * WIDTH)  //盤外を含めたBOARDSIZE

#define EMPTY 0 //空点
#define BLACK 1 //黒石
#define WHITE 2 //白石
#define WALL 3  //盤外
#define MARK 1  //マーク

/*------------------------------------------------------*/
/* 変数                                                 */
/*------------------------------------------------------*/

/* 碁盤 */
int board[ALLBOARD] = {};
/* MARK用の碁盤 */
int check_board[ALLBOARD] = {};
/* 着手場所の周りを調べる(右から時計回り) */
int dir4[4] = {+1,+WIDTH,-1,-WIDTH};
int dir8[8] = {+1,+1+WIDTH,+WIDTH,-1+WIDTH,-1,-1-WIDTH,-WIDTH,+1-WIDTH};   
/* 手盤 */
int color;
/* 着手場所 */
int z;
/* アゲハマ */
int prisoner_b,prisoner_w;

/*-------------------------------------------------------*/
/* 関数                                                  */
/*-------------------------------------------------------*/

/* 盤面(board)の表示 */
void CheckBoard(void);
/* check_boardの表示 */
void CheckBoard_check(void);
/* 盤面(board)の初期化 */
void BoardIni(void);
/* check_boardの初期化 */
void ClearCheckBoard(void);
/* 石を置く */
int CheckPut(int x,int y);
/* 色(手番)の反転 */
int FlipColor(int color);
/* 自殺手かどうか調べる */
int CheckWarning(int z);
/* zの石が囲まれているか調べる */
int TakeStone(int z);
/* TakeStoneがTRUEならばRemoveCountを呼び出す */
int RemoveStone(int z);
/* 囲まれた石を取り除きアゲハマ(prisoner)を返す */
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
	prisoner_b = RemoveStone(check);
      }
    }else{
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	prisoner_w = RemoveStone(check);
      }
    }   
    return z;
}

int CheckWarning(int z)
{
  int check,flag,i;

  check = 0;
  flag = 0;

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
      if(board[check] == WHITE){;
      }else if(board[check] != EMPTY ){
	flag += 1;
      }
    }
  }

  if(flag == 4){
    printf("Here is ban position.\n");
    return -1;
      }
  
  return 0;
}

int TakeStone(int z)
{
  int i,check,rtn,uncolor;
  
  uncolor = FlipColor(color);
  printf("uncolor=%d\n",uncolor);


    if(check_board[z] == MARK ){
      return -1;
    }
    
    check_board[z] = MARK;
      
    if(board[z] == EMPTY){
      return -1;
    }
    
    if(board[z] == uncolor){
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

  printf("RemoveStone;%d\n",prisoner);  
  if(board[z] == color){
    return 0;
  }

  if(board[z] == EMPTY){
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
  int i,check,prisoner,uncolor;

  uncolor = FlipColor(color);

  printf("removecount\n");
    if(board[z] == uncolor){
      prisoner++;
      printf("RemoveCount;%d\n",prisoner);
      board[z] = EMPTY;
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	prisoner = RemoveCount(check);
	printf("RemoveCount[%d];%d\n",i,prisoner);
      }
    }

    printf("RemoveCountend;%d\n",prisoner);
    return prisoner;
}

/*-------------------------------------------------------*/
/* main関数                                              */
/*-------------------------------------------------------*/
int main()
{  
  
  int *inputx,*inputy;
  
  /*碁盤の初期化*/
  BoardIni();
  
  printf("Program Start\n");

  /*アゲハマ*/
  prisoner_b = 0;
  prisoner_w = 0;

  color = WHITE; //初手を黒にするために白を代入
 
  while(1)
    {
      /*碁盤を表示*/
      CheckBoard();
      /*手盤の反転*/
      color = FlipColor(color);
      if(color == 1){
      printf("BLACK TURN\nx->");
      }else{
	printf("WHITE TURN\nx->");
      }
      /*手の入力*/
      scanf("%d",&inputx);
      printf("y->"); scanf("%d",&inputy);
      /*着手*/
      CheckPut(inputx,inputy);
      if(z == -1){
	printf("end\n");
	break;
      }
      printf("z:%d %d-%d\n",z,inputx,inputy);
    }
  
  return 0;
}

      
