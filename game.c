#include "game.h"

void Mainmenu(int measurements[]){
    int choice;

    //Getting player's choice regarding board size
    do{
        printf("Welcome to Minesweepers!\nChoose board size:\n0. Exit\n1. 8X8\n2. 12X12\n3. 15X15\n4. Custom\n");
        scanf("%d", &choice);
        if(choice<0 || choice>4)
            printf("Illegal number, try again.\n");
    }
    while(choice<0 || choice>4);

    //Setting the board's measurements according the player's choice
    if(choice==0)
        printf("Goodbye!\n");
    else if(choice>=1 && choice<=3){
        measurements[0] = Boardsize[choice];
        measurements[1] = Boardsize[choice];
    }
    else if(choice==4){
      do{
          printf("Enter amount of rows\n");
          scanf("%d", &measurements[0]);
          if(measurements[0]<1||measurements[0]>22)
              printf("Illegal number, enter a number between 1 and 22.\n");

      }
      while(measurements[0]<1||measurements[0]>22);//won't stop until a legal number is inserted

      do{
          printf("Enter amount of columns\n");
          scanf("%d", &measurements[1]);
          if(measurements[1]<1||measurements[1]>22)
              printf("Illegal number, enter a number between 1 and 22.\n");
      }
      while(measurements[1]<1||measurements[1]>22);//won't stop until a legal number is inserted
    }
}


void boardSetting(char board[][maxboardsize], int measurements[]){//Initialize board and print it
    int i,y;

    //Filling the board with X's
    for(i=0;i<measurements[0];i++){
        for(y=0;y<measurements[1];y++)
            board[i][y]='X';
    }
    boardprinting(measurements,board, true);
}


void boardprinting(int measurements[], char board[][maxboardsize], bool coverbombs){
    int i;

    printcolumn(measurements);

    //Adding underline to column's numbers
    printf("   ");
    for(i=0;i<measurements[1];i++){
        if(i<measurements[1]-1)
            printf("_  ");
        else
            printf("_\n");
    }

    printrow(measurements, board, coverbombs);
}


void printcolumn(int measurements[]){
    int i;
    printf("\n   ");//seperates the matrix from the input
    if(measurements[1]<=9){//if num of cols is below 9
        for(i=0;i<measurements[1];i++){//Setting cols numbers, two digit nums require extra space
            if(i<measurements[1]-1)
                printf("%d  ", i);
            else//last column number
                printf("%d\n", i);
        }
    }
    else if(measurements[1]>9){//if num of cols is over 9
        for(i=0;i<measurements[1];i++){//Setting cols numbers, two digit nums require extra space
            if(i<measurements[1]-1)
                if(i>=10)//two digit nums require less space
                    printf("%d ", i);
                else
                    printf("%d  ", i);
            else//last column number
                printf("%d\n", i);
        }
    }
}


void printrow(int measurements[], char board[][maxboardsize], bool coverbombs){
    int i,y;
    for(i=0;i<measurements[0];i++){
        if(measurements[0]<10){//Setting rows numbers, two digit nums require extra space
            if(i<10)
                printf("%d| ", i);
            else
                printf("%d| ", i);
        }
        else if(measurements[0]>=10){
            //Setting rows numbers, one digit numbers got 1 space ahead to keep up with two-digit-nums
            if(i<10)
                printf(" %d|", i);
            else
                printf("%d|", i);
        }
        for(y=0;y<measurements[1];y++){//printing the cells
            if(y!=measurements[1]-1){
                if(coverbombs==true && board[i][y]=='B')
                    printf("X  ");
                else if(coverbombs==true && board[i][y]=='C')
                    printf("F  ");
                else if(coverbombs==false && board[i][y]=='C')
                    printf("B  ");
                else
                    printf("%c  ", board[i][y]);
            }
            else{//last cell in a row
                if(coverbombs==true && board[i][y]=='B')
                    printf("X\n");
                else if(coverbombs==true && board[i][y]=='C')
                    printf("F\n");
                else if(coverbombs==false && board[i][y]=='C')
                    printf("B\n");
                else
                    printf("%c\n", board[i][y]);
            }
        }
    }
}


void bombseeder(char board[][maxboardsize], int measurements[], int numofbombs){//Inserting bombs in random cells
    int i, bombsrow, bombscol;

    srand((int)time(NULL));

    for(i=0;i<numofbombs;i++){//creating numofbombs bombs
        do{
            bombsrow = rand() % (measurements[0]-1);//random row location
            bombscol = rand() % (measurements[1]-1);//random column location
        }
        while(board[bombsrow][bombscol]=='B');//Avoiding insert two bombs in the same cell
        board[bombsrow][bombscol]='B';
    }
}


void playingTime(char board[][maxboardsize], int measurements[], int numofbombs){
    int  column=0, row, cellslefttoopen;
    bool isgameover=false;

    cellslefttoopen=((measurements[0]*measurements[1])-numofbombs);


    while(!isgameover){
        //Player's turn
        do{
            do{
                printf("Your move!\nEnter row:\n");
                scanf("%d",&row);
                if(row<-1 || row >(measurements[0]-1))
                   printf("Illegal number, try again\n");
            }
            while(row<-1 || row >(measurements[0]-1));

            if(row!=-1){//not cheat mode
                do{
                    printf("Enter column:\n");
                    scanf("%d",&column);
                    if(column<0 || column >(measurements[1]-1))
                       printf("Illegal number, try again\n");
                }
                while(column<0 || column >(measurements[1]-1));

                if((board[row][column])!='X' && (board[row][column])!='B' && (board[row][column])!='C' && board[row][column]!='F'){
                    printf("Cell is already revealed, try again\n");
                }
            }
        }
        while(((board[row][column])!='X' && (board[row][column])!='B' && (board[row][column])!='C' && (board[row][column])!='F') & (row!=-1));
        if(row!=-1)
            isgameover=playersturn(board, measurements, row, column, &cellslefttoopen);
        else//cheat mode
            isgameover=cheatmode(board, measurements, numofbombs, &cellslefttoopen);
    }
    if(cellslefttoopen==0)//If the game ended and the player opened up all cells that are not bombs
        printf("You won! Great job\n");
}


bool playersturn(char board[][maxboardsize], int measurements[], int row, int column, int *cellslefttoopen){
    int i,y;
    bool isgameover=false;
    char Flagoropen;

    do{
        printf("enter O to open selected cell, F to flag it.\n");
        scanf(" %c", &Flagoropen);
        if(Flagoropen!='F' && Flagoropen!='O' && Flagoropen!='f' && Flagoropen!='o')
            printf("Ilegal move, try again\n");
    }
    while(Flagoropen!='F' && Flagoropen!='O' && Flagoropen!='f' && Flagoropen!='o');

    if(Flagoropen=='O' || Flagoropen=='o'){
        //Checking for bombs
        if(board[row][column]=='B' || board[row][column]=='C'){//C is for bombs that have benn flagged
            printf("You have hit a bomb!\nGame over!");
            for(i=0;i<measurements[0];i++){//Unveiling cells
                for(y=0;y<measurements[1];y++){
                    if(board[i][y]=='X' || board[i][y]=='F')
                        calculatebombsnear(board, measurements, i, y, true);
                }
            }
            boardprinting(measurements,board, false);//print board without covering bombs
            isgameover=true;
        }

        else{
            if(board[row][column]=='F')//if chosen cell is flagged, unflag it
                board[row][column]='X';
            if((*cellslefttoopen)!=1){//if the game is not over
                revealemptycells(board, measurements, row, column, cellslefttoopen);
                boardprinting(measurements,board, true);
            }
            else
                isgameover=true;
        }
    }
    else if(Flagoropen=='F' || Flagoropen=='f'){
        //If the player chose to flag a bomb, insert the letter C to the matrix to distinguish it from ordinary cells
        if(board[row][column]=='B')
            board[row][column]='C';
        else
            board[row][column]='F';
        boardprinting(measurements,board, true);
    }
    return isgameover;
}


bool cheatmode(char board[][maxboardsize], int measurements[], int numofbombs, int *cellslefttoopen){
    int cellsrevealed=0, cellstoreveale, revealerow=0, revealecolumn=0, cellsuncovered=0;
    bool isgameover=false;

    do{
        printf("Cheat mode activated;)\nhow many cells do you want to open up?\n");
        scanf("%d",&cellstoreveale);
        if(cellstoreveale<=0 || cellstoreveale > (measurements[0]*measurements[1]-numofbombs))//max cells minus bombs
           printf("Illegal number, try again\n");
    }
    while(cellstoreveale<=0 || cellstoreveale > (measurements[0]*measurements[1]-numofbombs));

    while(cellsrevealed<cellstoreveale){
        if(board[revealerow][revealecolumn]=='X' || (board[revealerow][revealecolumn]>=49 && board[revealerow][revealecolumn]<=56) || board[revealerow][revealecolumn]=='F' || board[revealerow][revealecolumn]==' '){//if cell is everything but a bomb
            if((board[revealerow][revealecolumn])=='X' || (board[revealerow][revealecolumn])=='F'){//if cell is covered, reveal it
                calculatebombsnear(board, measurements,revealerow, revealecolumn, true);
                cellsuncovered++;
            }
            cellsrevealed++;
        }
        if(revealecolumn==measurements[1]){//if it is the end of the line, go to a new one
            revealerow++;
            revealecolumn=0;
        }
        else//if it is not the end of the line, continue
            revealecolumn++;
    }
    (*cellslefttoopen)-=cellsuncovered;//deducting only cells that uncovered in this section, not cells that uncovered beforehand
    if((*cellslefttoopen)<=0)
        isgameover=true;

    //resetting for further use if neccesary
    cellsrevealed=0;
    revealerow=0;
    revealecolumn=0;
    cellsuncovered=0;

    boardprinting(measurements,board, true);
    return isgameover;
}


void calculatebombsnear(char board[][maxboardsize], int measurements[], int row, int column, bool revealflags){//calculates how many bombs are near a cell
    int Bombsnear=0;

    //checking if there are bombs is the 8 cells nearby
    if((board[row-1][column]=='B' || board[row-1][column]=='C') && (row>0))
            Bombsnear++;
    if((board[row-1][column-1]=='B' || board[row-1][column-1]=='C') && (row>0) && (column>0))
            Bombsnear++;
    if((board[row][column-1]=='B' || board[row][column-1]=='C') && (column>0))
            Bombsnear++;
    if((board[row+1][column-1]=='B' || board[row+1][column-1]=='C') && (column>0))
            Bombsnear++;
    if(board[row+1][column]=='B' || board[row+1][column]=='C')
            Bombsnear++;
    if(board[row][column+1]=='B' || board[row][column+1]=='C')
            Bombsnear++;
    if(board[row+1][column+1]=='B' || board[row+1][column+1]=='C')
            Bombsnear++;
    if((board[row-1][column+1]=='B' || board[row-1][column+1]=='C') && (row>0))
            Bombsnear++;

    if(Bombsnear==0)
        board[row][column]=' ';
    else if(board[row][column]=='F' && revealflags==true)
        board[row][column]=Bombsnear+48;
    else if(board[row][column]!='F')
        board[row][column]=Bombsnear+48;//48 is neccesary for converting the int to char
}


void revealemptycells(char board[][maxboardsize], int measurements[], int row, int column, int *cellslefttoopen){//A

    if(board[row][column]=='X' || board[row][column]=='F'){//if the cell is not revealed
        calculatebombsnear(board, measurements, row, column, false);
        if(board[row][column]!='F')//if a cell is not a flag and therefore is revealed
            (*cellslefttoopen)--;
        if(board[row][column]==' '){//if the cell contains space, keep running all over the matrix until all spaces are bounded by nums or flags
            if(row<measurements[0]-1)
                revealemptycells(board, measurements, row+1, column, cellslefttoopen);
            if(column<measurements[1]-1)
                revealemptycells(board, measurements, row, column+1, cellslefttoopen);
            if(row>0)
                revealemptycells(board, measurements, row-1, column, cellslefttoopen);
            if(column>0)
                revealemptycells(board, measurements, row, column-1, cellslefttoopen);
        }
    }
}
