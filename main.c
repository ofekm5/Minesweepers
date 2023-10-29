#include "game.h"

int main(){
    int measurements[2]={0,0}, numofbombs;//measurements: cell 0 is num of rows, cell 1 is nums of cols
    char board[maxboardsize][maxboardsize];

    Mainmenu(measurements);

    if(measurements[1]!=0 && measurements[0]!=0){//If the player has not chosen 0
        boardSetting(board, measurements);//initialize a new board with X's and show it
        numofbombs=(int)sqrt((double)(measurements[0]*measurements[1]));
        bombseeder(board,measurements,numofbombs);//inserting bombs
        playingTime(board,measurements,numofbombs);
    }

    return 0;
}
