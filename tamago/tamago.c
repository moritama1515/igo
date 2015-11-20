#include<stdio.h>
#include<stdlib.h>
#include"display.h"

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


/*-------------------------------------------------------*/
/* main関数                                              */
/*-------------------------------------------------------*/
int main()
{  
  
  int x,y;
  
  /*碁盤の初期化*/
  BoardIni();
  
  printf("Program Start\n");

  move = 0;
  ko_z = 0;
  ko_num = 0;

  /*アゲハマ*/
  prisoner_b = 0;
  prisoner_w = 0;

  color = WHITE; //初手を黒にするために白を代入

  while(1){ 
    /*着手場所の入力*/
    InputMap(&x,&y);
    
    if(x == 0 && y == 0){
      printf("Program End\n");
      break;
    }
    CheckPut(x,y);
    printf("z:%d %d-%d\nmove:%d\n",z,x,y,move);
    printf("ko_num:%d ko_z:%d\n",ko_num,ko_z);
  }
  
  return 0;
}

      
