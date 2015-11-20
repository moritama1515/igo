/* board.c */
#include<stdio.h>
#include<stdlib.h>

#define B_SIZE 19                  //BOARDSIZE
#define WIDTH (B_SIZE+2)          //BOARDSIZE+WALL
#define ALLBOARD (WIDTH * WIDTH)  //盤外を含めたBOARDSIZE

#define EMPTY 0 //空点
#define BLACK 1 //黒石
#define WHITE 2 //白石
#define WALL 3  //盤外
#define MARK 1  //マーク

//------------------------------------------------------
// 変数                                                 
//------------------------------------------------------

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
int x,y,z;
/* コウの位置 */
int ko_z;
/* アゲハマ */
int prisoner_b,prisoner_w;
/* 手数 */
int move;
/* コウの発生手数 */
int ko_num;

//-------------------------------------------------------
// 関数                                                  
//-------------------------------------------------------

/* 盤面(board)の表示 */
void CheckBoard(void);
/* check_boardの表示 */
void CheckBoard_check(void);
/* 盤面(board)の初期化 */
void BoardIni(void);
/* check_boardの初期化 */
void ClearCheckBoard(void);
/* 着手場所の入力 */
void InputMap(int *x,int *y);
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
int RemoveCount(int z,int prisoner);



/* 盤面(board)の表示 */
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
  printf("\nBLACK:%d,WHITE:%d\n",prisoner_b,prisoner_w);
}

/* check_boardの表示 */
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

/* 盤面(board)の初期化 */
void BoardIni()
{
  
  move = 0;
  ko_z = 0;
  ko_num = 0;

  /*アゲハマ*/
  prisoner_b = 0;
  prisoner_w = 0;

  color = WHITE; //初手を黒にするために白を代入     

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

/* check_boardの初期化 */
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

/* 着手場所の入力 */
void InputMap(int *x,int*y)
{
  int inputX,inputY;
  char inpx[5],inpy[5];

    /*手盤の反転*/
    color = FlipColor(color);
    CheckBoard();
    while(1){
      if(color == 1){
	printf("BLACK TURN    Pass -> 20\n");
      }else{
	printf("WHITE TURN    Pass -> 20\n");
      }
  
      /*手の入力*/
      printf("x -> ");
      fgets(inpx,5,stdin);
      inputX = atoi(inpx);
      
      /* Pass */
      if(inputX == 20){
	move++;
        printf("Pass\n");
	break;
      }
     
      printf("y -> ");
      fgets(inpy,5,stdin);
      inputY = atoi(inpy);

      if(inputX != 0 && inputY != 0 && inputX < 20 && inputY < 20){
	break;
      }     

      printf("Try Again! Input is 1 ~ 19.\n");
      printf("If you want to exit,please enter 20 twice.\n");

    }
 
    if(inputX == 20 && color == 1){
      *x = 0;
    }else if(inputX == 20 && color == 2){
      *y = 0;
    }else{
      *x = inputX;
      *y = inputY;
    }
}
/* 色(手番)の反転 */
int FlipColor(int color)
{
  return 3 - color;
}

/* 石を置く */
int CheckPut(int x,int y)
{
  int i,check,remove,koflag;

  if(x == 0 | y == 0){
    return -1;
  }

  z = (WIDTH * y) + x;
  remove = 0;
  koflag = 1;

  ClearCheckBoard();

  /* コウの処理 */  
  if(z == ko_z && move == ko_num){
    color = FlipColor(color);
    printf("Ko has occurred.Here is ban position.\n");
    return z;
  }

  if(z <= ALLBOARD && board[z] == EMPTY){
    board[z] = color;
  }else{
    color = FlipColor(color);
    printf("Put error.\n");
    return z;
  }  

  for(i = 0; i < 4; i++){
    check = z + dir4[i];
    if(board[check] == color){
      koflag = 0;
    }
  }

  for(i = 0; i < 4; i++){
    check = z + dir4[i];
    remove = RemoveStone(check);
    
    if(koflag == 1 && remove == 1){
      ko_num = (move + 1);
      for(i = 0; i < 4; i++){
	check = z + dir4[i];
	if(board[check] == EMPTY){
	  ko_z = check;
	}
      }
    }
    
    if(remove != 0){
      if(color == BLACK){
	prisoner_b += remove;
      }else{
	prisoner_w += remove;
      }
    }

  }

  board[z] = EMPTY;
  
  if(CheckWarning(z) != -1){
    board[z] = color;
    move++;
  }else{
    color = FlipColor(color);
    printf("Put error.\n");
  }

    return z;
}

/* 自殺手かどうか調べる */
int CheckWarning(int z)
{
  int uncolor,check,i;

  board[z] = color;

  ClearCheckBoard();


  color = FlipColor(color);
  check = TakeStone(z);
  color = FlipColor(color);

  if(check == 0){
    board[z] = EMPTY;
    return -1;
  }

  return 0;
}

/* zの石が囲まれているか調べる */
int TakeStone(int z)
{
  int i,check,rtn,uncolor;
  
  uncolor = FlipColor(color);

    if(check_board[z] == MARK ){
      return 0;
    }
    
    check_board[z] = MARK;
      
    if(board[z] == EMPTY ){
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

/* TakeStoneがTRUEならばRemoveCountを呼び出す */  
int RemoveStone(int z)
{
  int prisoner = 0;

  if(board[z] == color || board[z] == EMPTY){
    return 0;
  }
  
  ClearCheckBoard();
  
  if(TakeStone(z) == 0){
    prisoner = RemoveCount(z,prisoner);
    return prisoner;  
  }

  return 0;
}

/* 囲まれた石を取り除きアゲハマ(prisoner)を返す */
int RemoveCount(int z,int prisoner)
{
  int i,check,uncolor;
  
  uncolor = FlipColor(color);
  
  if(board[z] == uncolor){
    prisoner += 1;
    board[z] = EMPTY;
    for(i = 0; i < 4; i++){
      check = z + dir4[i];
      prisoner = RemoveCount(check,prisoner);
    }
  }
  return prisoner;
}

//-------------------------------------------------------
// main関数                                              
//-------------------------------------------------------
int main()
{  
  
  int x,y;
  printf("Program Start\n");
  BoardIni();
  
  while(1){ 

    InputMap(&x,&y);
    
    if(x == 0 && y == 0){
      printf("Program End\n");
      break;
    }
    CheckPut(x,y);
    printf("z:%d %d-%d\nmove:%d\n",z,x,y,move);
  }
  
  return 0;
}

      
