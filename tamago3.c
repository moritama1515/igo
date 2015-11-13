#include<stdio.h>

#define B_SIZE 9
#define WIDTH (B_SIZE+2)
#define ALLBOARD (WIDTH * WIDTH)
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define WALL 3

int board[ALLBOARD] = {};
int dir4[4] = {+1,+WIDTH,-1,-WIDTH};
int dir8[8] = {};   
int color,z,black_a,white_a;

void check_board(void);
void board_ini(void);
int check_put(int x,int y);
int flip_color(int color);
int check_warning(int z);
int take_stone(int z);
void remove_stone(void);

void check_board(void)
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
  printf("BLACK:%d,WHITE:%d\n",black_a,white_a);
}

void board_ini()
{
  int i;

  for(i = 0; i < ALLBOARD-WIDTH; i++)
    {
      if( i < WIDTH){
	board[i] = WALL;
      }else if((i+1) % WIDTH == 0 || i % WIDTH == 0){
	board[i] = WALL;
      }else{
	board[i] = EMPTY;
      }
    }

  for(i = (ALLBOARD-WIDTH);i < ALLBOARD;i++)
    board[i] = WALL;

  black_a = 0;
  white_a = 0;
}

int flip_color(int color)
{
  return 3 - color;
}

int check_put(int x,int y)
{
  z = (WIDTH*y) + x;
  if(z <= ALLBOARD && board[z] == EMPTY && check_warning(z) == 0){
    board[z] = color;
  }else{
    printf("Put error.\n");
    z=-1;
  }
  return z;
}

int check_warning(int z)
{
  int check,flag,i;

  check = 0;
  flag = 0;

  //printf("color;%d\n",color);
  //printf("z;%d\n",z);

  if(color == BLACK){
    for(i=0;i<4;i++){
      check = z + dir4[i];
      if(board[check] == BLACK){;
      }else if(board[check] != EMPTY ){
	flag += 1;
      }
    }
  }else{
    for(i=0;i<4;i++){
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

int take_stone(int z)
{

}
  
void remove_stone()
{

}
    int main()
    {  
  
  int *inputx,*inputy;
  board_ini();

  color = BLACK;
  check_board();
  printf("BLACK TURN\nx->"); scanf("%d",&inputx);
  printf("y->"); scanf("%d",&inputy);
  check_put(inputx,inputy);
  if(z == -1){
    printf("end\n");
  }
  check_board();
  printf("z:%d %d-%d\n",color,inputx,inputy);
  
  while(1)
    {
      color = flip_color(color);
      if(color == 1){
      printf("BLACK TURN\nx->");
      }else{
	printf("WHITE TURN\nx->");
      }
      scanf("%d",&inputx);
      printf("y->"); scanf("%d",&inputy);
      check_put(inputx,inputy);
      if(z == -1){
	printf("end\n");
	break;
      }
      check_board();
      printf("z:%d %d-%d\n",color,inputx,inputy);
    }
  
  return 0;
}

      
