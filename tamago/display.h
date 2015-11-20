/* display.h */
#ifndef DISPLAY_H
#define DISPLAY_H

#define B_SIZE 19                 //BOARDSIZE                                   
#define WIDTH (B_SIZE+2)          //BOARDSIZE+WALL                              
#define ALLBOARD (WIDTH * WIDTH)  //盤外を含めたBOARDSIZE                       

#define EMPTY 0 //空点                                                          
#define BLACK 1 //黒石                                                          
#define WHITE 2 //白石                                                          
#define WALL 3  //盤外                                                          
#define MARK 1  //マーク

/* 碁盤 */
extern int board[ALLBOARD];
/* MARK用の碁盤 */
extern int check_board[ALLBOARD];
/* 着手場所の周りを調べる(右から時計回り) */
extern int dir4[4];
/* 手盤 */
extern int color;
/* 着手場所 */
extern int x,y,z;
/* コウの位置 */
extern int ko_z;
/* アゲハマ */
extern int prisoner_b,prisoner_w;
/* 手数 */
extern int move;
/* コウの発生手数 */
extern int ko_num;

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


#endif
