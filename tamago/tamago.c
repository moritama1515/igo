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

#define FIRSTMAX 72
#define SECONDMAX 64
#define THIRDMAX 56
#define FORTHMAX 48

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

int node[100];
double eval[100];
int first_line[FIRSTMAX];
int second_line[SECONDMAX];
int third_line[THIRDMAX];
int forth_line[FORTHMAX];

//------------------------------------------------------
// 関数
//------------------------------------------------------
void LineIni(void); 
void TamagoMove(int *x,int *y);
void GenerateZ(void);
void BonusEval(void);
int MaxEval(void);

void LineIni(void)
{
  int i;
  int side = 18;
  /* first_line */
  for(i = 0; i < FIRSTMAX; i++){
    if(i <= side){
      first_line[i] = WIDTH+2 + i;
    }else if(side < i && i <= side*2){
      first_line[i] = first_line[i-1] + WIDTH;
    }else if(side*2 < i && i <= side*3){
      first_line[i] = first_line[i-1] - 1;
    }else if(side*3 < i && i < side*4){
      first_line[i] = first_line[i-1] - WIDTH;
    }
    //    printf("[%d]%d\n",i,first_line[i]);
  }
  /* second_line */
  side = 16;
  for(i = 0; i < SECONDMAX; i++){
    if(i <= side){
      second_line[i] = WIDTH*2+3 + i;
    }else if(side < i && i <= side*2){
      second_line[i] = second_line[i-1] + WIDTH;
    }else if(side*2 < i && i <= side*3){
      second_line[i] = second_line[i-1] - 1;
    }else if(side*3 < i && i < side*4){
      second_line[i] = second_line[i-1] - WIDTH;
    }
    //    printf("[%d]%d\n",i,second_line[i]);                                                  
  }
  /* third_line */
  side = 14;
  for(i = 0; i < THIRDMAX; i++){
    if(i <= side){
      third_line[i] = WIDTH*3+4 + i;
    }else if(side < i && i <= side*2){
      third_line[i] = third_line[i-1] + WIDTH;
    }else if(side*2 < i && i <= side*3){
      third_line[i] = third_line[i-1] - 1;
    }else if(side*3 < i && i < side*4){
      third_line[i] = third_line[i-1] - WIDTH;
    }
    //     printf("[%d]%d\n",i,third_line[i]);
  }
  /* forth_line */
  side = 12;
  for(i = 0; i < FORTHMAX; i++){
    if(i <= side){
      forth_line[i] = WIDTH*4+5 + i;
    }else if(side < i && i <= side*2){
      forth_line[i] = forth_line[i-1] + WIDTH;
    }else if(side*2 < i && i <= side*3){
      forth_line[i] = forth_line[i-1] - 1;
    }else if(side*3 < i && i < side*4){
      forth_line[i] = forth_line[i-1] - WIDTH;
    }
    //    printf("[%d]%d\n",i,forth_line[i]);
  }
}

void TamagoMove(int *x,int *y)
{
  int i,max;
  color = COM;
  
  GenerateZ();

  BonusEval();
  max = MaxEval();
  z = node[max];
  printf("z;%d",z);

  *y = z / WIDTH;
  *x = z % WIDTH - 1;
  
  error = CheckPut(*x,*y);
  for(i = 0; i < 100; i++){
    printf("[%d]%f\n",node[i],eval[i]);
  }
}

void GenerateZ()
{
  int i;
  for(i = 0;i < 100; i++){
    while(1){
      z = rand() % ( ALLBOARD + WIDTH);
      if(board[z] == EMPTY){
	break;
      }
    }
    node[i] = z;
    eval[i] = 1;
  }
}

void BonusEval(void)
{
  int i,j;

  for(i = 0;i < 100; i++){
    for(j = 0; j < FIRSTMAX; j++){
      if(node[i] == first_line[j]){
	eval[i] *= 0.2;
      }
    }
    for(j = 0; j < SECONDMAX; j++){
      if(node[i] == second_line[j]){
	eval[i] *= 0.4;
      }
    }    
    for(j = 0; j < THIRDMAX; j++){
      if(node[i] == third_line[j]){
        eval[i] *= 1.2;
      }
    }
    for(j = 0; j < FORTHMAX; j++){
      if(node[i] == forth_line[j]){
        eval[i] *= 1.3;
      }
    }
  }
}

int MaxEval(void)
{
  int i;
  int max = 0;
  for(i = 1;i <= 100; i++){
    if(eval[max] < eval[i]){
      max = i;    
    }
  }

  printf("max;%d\n",max);
  return max;
}
//-------------------------------------------------------
// main関数                                              
//-------------------------------------------------------
int main()
{  
  
  int x,y;
  printf("Program Start\n");
  BoardIni();  
  LineIni();

  while(1){ 

    InputMap(&x,&y);
        
    if(x == 0 && y == 0){
      printf("Program End\n");
      break;
    }
    
    CheckPut(x,y);

    printf("Player error;%d",error);    
    printf("z:%d %d-%d\nmove:%d\n",z,x,y,move);

    TamagoMove(&x,&y);
    CheckPut(x,y);
    printf("Tamago error;%d",error);
  }

  return 0;  
}
  
