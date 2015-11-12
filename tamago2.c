#include<stdio.h>

#define B_SIZE 9
#define WIDTH (B_SIZE+2)
#define ALLBOARD (WIDTH * WIDTH)
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define WALL 3

int board[ALLBOARD] = {};
int dir4[4] = {};
int dir8[8] = {};   
int color,z;

int check_put(int x,int y);
int flip_color(int color);

void check_board()
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
}

int flip_color(int color)
{
  return 3 - color;
}

int check_put(int x,int y)
{
  z = (WIDTH*y) + x;
  if(z <= ALLBOARD){
    if(board[z] == EMPTY){
      board[z] = color;
    }else{
      printf("Put error\n");
      z=-1;
    }
  }else{
    printf("Put error\n");
    z=-1;
  }
  return z;
}


int main()
{
  int *inputx,*inputy;
  board_ini();

  while(1)
{
  color = BLACK;
  check_board();
  printf("BLACK TURN\nx->"); scanf("%d",&inputx);
  printf("y->"); scanf("%d",&inputy);
  check_put(inputx,inputy);
  if(z == -1){
    printf("end\n");
    break;
  }
  check_board();
  printf("z:%d %d-%d\n",color,inputx,inputy);
  color = flip_color(color);
  printf("WHITE TURN\nx->"); scanf("%d",&inputx);
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

      
