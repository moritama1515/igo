/* tamago.c */
#include<stdio.h>
#include<stdlib.h>
#include"display.h"

#define B_SIZE 19                  //BOARDSIZE
#define WIDTH (B_SIZE+2)          //BOARDSIZE+WALL
#define ALLBOARD (WIDTH * WIDTH)  //盤外を含めたBOARDSIZE

#define EMPTY 0   //空点
#define BLACK 1   //黒石
#define WHITE 2   //白石
#define WALL 3    //盤外
#define MARK 1    //マーク
#define PLAYER 1  //プレイヤーの色
#define COM 2     //COMの色


//------------------------------------------------------
// 変数                                                 
//------------------------------------------------------

/* 碁盤 */
int board[ALLBOARD] = {};
/* MARK用の碁盤 */
int check_board[ALLBOARD] = {};
/* 着手場所の周りを調べる(右から時計回り) */
int dir4[4] = {+1,+WIDTH,-1,-WIDTH};
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
/* エラー処理 */
int error;

//------------------------------------------------------
// 関数
//------------------------------------------------------ 
void TamagoMove(int *x,int *y);
int GenerateZ(void);

void TamagoMove(int *x,int *y)
{
  if(error == 1) return;

  color = COM;

  z = GenerateZ();
  *y = z / WIDTH;
  *x = z % WIDTH;

  error = CheckPut(*x,*y);

}

int GenerateZ(){
  while(1){
    z = rand() % ( ALLBOARD + WIDTH);
    if(board[z] == EMPTY){
      return z;
    }
  }
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
    
    error = CheckPut(x,y);
    
    printf("z:%d %d-%d\nmove:%d\n",z,x,y,move);

    TamagoMove(&x,&y);
  }

  return 0;  
}
  
