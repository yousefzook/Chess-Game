#include <stdio.h>
#include <stdlib.h>

char board[8][8],capturedpiece[8][4],garbage,color,pormot;
char undoredo[500][8][8];
//"garbage" for the \n which entered while pressing ENTER after any input,,,, color --> the color which player1 had choosen
//undoredo[][][] --> A three dimension array 2 dimension for the board and for every move we save the board in the 3rd dimension
//capturedpiece --> an array to store the captured pieces
//pormot--> a global variable to check the promotion
int inrow,outrow,incol,outcol,count1=0,count2=0,count3=7,count4=0,gamecounter=0,playercount=0;
int krow,kcol,Krow,Kcol,STALEMATE=0,CHECKMATE=0,stalemate=0,checkmate=0,kingcolorcheck;
//krow-->row of white kinng,,,Krow--> row of black KING,,the same to the columns
//kingcolorcheck-->if we check the threating on the sqaures around white king ,so kingcolorcheck=0,,,if the black king so ,kingcolorcheck=1
// inrow --> row whice wanted to move from,,,outrow --> row which wanted to move to , the same in columns,,,
//gameconter --> to count every move,,,playercount --> to count the turns for player
int inPieceAscii,outPieceAscii;
//inPieceAscii --> the ASCII code for the entered piece,, the same for the out
//-----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
int controlcheck()
{
    inPieceAscii=(int)board[inrow][incol];
    outPieceAscii=(int)board[outrow][outcol];
    if(playercount%2==0)//that mean that the player one is playing
    {
        if(color=='B'&&(inPieceAscii<'Z'&&inPieceAscii>'A'))
        {
            return 1;
        }
        else if (color=='W'&&(inPieceAscii<'z'&&inPieceAscii>'a'))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else//that mean that player 2 is playing
    {
        if(color=='B'&&(inPieceAscii<'z'&&inPieceAscii>'a'))
        {
            return 1;
        }
        else if(color=='W'&&(inPieceAscii<'Z'&&inPieceAscii>'A'))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    }

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void kingplace()//it is a function to get the two kings place
{
    int i,j;//counters
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(board[i][j]=='k')
            {
                krow=i;//white king row
                kcol=j;//white kin col
            }
            if(board[i][j]=='K')
            {
                Krow=i;//black king row
                Kcol=j;//black king col
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------
int threatening(int krow,int kcol)//it is a function take the coordinates of a square and check if it is threaten or not
{
    int threaten=0,x;//x--> counter
    //if threaten==0---> that mesn the square isn't threaten;;;;else if threaten==1--->the square is threaten
    if(krow<0||krow>7||kcol>7||kcol<0)//any square out of the board is considerd as threaten
    {
        threaten=1;
    }
    else if ((board[krow][kcol]=='k'||board[krow][kcol]=='.'||board[krow][kcol]=='-'||board[krow][kcol]=='R'||board[krow][kcol]=='B'||board[krow][kcol]=='N'||board[krow][kcol]=='Q'||board[krow][kcol]=='P')&&kingcolorcheck==0)
    {
        //checking diagonally
        for (x=1; (krow+x<8)&&(kcol+x<8); x++)
        {
            if (board[krow+x][kcol+x]=='Q'||board[krow+x][kcol+x]=='B')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; (krow-x>=0)&&(kcol+x<8); x++)
        {
            if (board[krow-x][kcol+x]=='Q'||board[krow-x][kcol+x]=='B')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; (krow+x<8)&&(kcol-x>=0); x++)
        {
            if (board[krow+x][kcol-x]=='Q'||board[krow+x][kcol-x]=='B')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol-x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; (krow-x>=0)&&(kcol-x>=0); x++)
        {
            if (board[krow-x][kcol-x]=='Q'||board[krow-x][kcol-x]=='B')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol-x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }
        //checking vertically and horizontally
        for (x=1; kcol+x<8; x++)
        {
            if (board[krow][kcol+x]=='Q'||board[krow][kcol+x]=='R')
            {
                threaten=1;
                break;
            }
            else if (board[krow][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; kcol-x>=0; x++)
        {
            if (board[krow][kcol-x]=='Q'||board[krow][kcol-x]=='R')
            {
                threaten=1;
                break;
            }
            else if (board[krow][kcol-x]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; krow+x<8; x++)
        {
            if (board[krow+x][kcol]=='Q'||board[krow+x][kcol]=='R')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }

        for (x=1; krow-x>=0; x++)
        {
            if (board[krow-x][kcol]=='Q'||board[krow-x][kcol]=='R')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol]>'A')
            {
                if(board[krow+x][kcol]=='k')
                break;
            }
        }
        //checking the knights
        if (board[krow+1][kcol+2]=='N'||board[krow+2][kcol+1]=='N'||board[krow-1][kcol+2]=='N'||board[krow-2][kcol+1]=='N'||board[krow+1][kcol-2]=='N'||board[krow+2][kcol-1]=='N'||board[krow-1][kcol-2]=='N'||board[krow-2][kcol-1]=='N')
        {
            threaten=1;
        }

        //checking the pawns
        if (board[krow-1][kcol+1]=='P'||board[krow-1][kcol-1]=='P')
        {
            threaten=1;
        }

    }
    //THE SAME AS THE WHITE KING
    else if ((board[krow][kcol]=='K'||board[krow][kcol]=='.'||board[krow][kcol]=='-'||board[krow][kcol]=='r'||board[krow][kcol]=='b'||board[krow][kcol]=='n'||board[krow][kcol]=='q'||board[krow][kcol]=='p')&&kingcolorcheck==1)
    {
        for (x=1; (krow+x<8)&&(kcol+x<8); x++)
        {
            if (board[krow+x][kcol+x]=='q'||board[krow+x][kcol+x]=='b')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; (krow-x>=0)&&(kcol+x<8); x++)
        {
            if (board[krow-x][kcol+x]=='q'||board[krow-x][kcol+x]=='b')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; (krow+x<8)&&(kcol-x>=0); x++)
        {
            if (board[krow+x][kcol-x]=='q'||board[krow+x][kcol-x]=='b')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol-x]>'A')
            {
            if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; (krow-x>=0)&&(kcol-x>=0); x++)
        {
            if (board[krow-x][kcol-x]=='q'||board[krow-x][kcol-x]=='b')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol-x]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; kcol+x<8; x++)
        {
            if (board[krow][kcol+x]=='q'||board[krow][kcol+x]=='r')
            {
                threaten=1;
                break;
            }
            else if (board[krow][kcol+x]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; kcol-x>=0; x++)
        {
            if (board[krow][kcol-x]=='q'||board[krow][kcol-x]=='r')
            {
                threaten=1;
                break;
            }
            else if (board[krow][kcol-x]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        for (x=1; krow+x<8; x++)
        {
            if (board[krow+x][kcol]=='q'||board[krow+x][kcol]=='r')
            {
                threaten=1;
                break;
            }
            else if (board[krow+x][kcol]>'A')
            {
                if(board[krow+x][kcol]=='K')
                 break;
            }
        }

        for (x=1; krow-x>=0; x++)
        {
            if (board[krow-x][kcol]=='q'||board[krow-x][kcol]=='r')
            {
                threaten=1;
                break;
            }
            else if (board[krow-x][kcol]>'A')
            {
                if(board[krow+x][kcol]=='K')
                break;
            }
        }

        if (board[krow+1][kcol+2]=='n'||board[krow+2][kcol+1]=='n'||board[krow-1][kcol+2]=='n'||board[krow-2][kcol+1]=='n'||board[krow+1][kcol-2]=='n'||board[krow+2][kcol-1]=='n'||board[krow-1][kcol-2]=='n'||board[krow-2][kcol-1]=='n')
        {
            threaten=1;
        }

        if (board[krow+1][kcol+1]=='p'||board[krow+1][kcol-1]=='p')
        {
            threaten=1;
        }

    }

//    else if(kingcolorcheck==0&&board[krow][kcol]>'Z')
//    {
//        threaten=1;
//    }
//    else if(kingcolorcheck==1&&(board[krow][kcol]>'A'&&board[krow][kcol]<'Z'))
//    {
//        threaten=1;
//    }
    else
        threaten=0;
    return threaten;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//To check if the player want to undo or redo the last movement or not
char UndoRedo(char char1)
{
    int i,j,undocounter=0;
    //i,j --> are local counters
    //undocounter --> to count the undo's number
    while (char1=='u'||char1=='r')
    {

        if(char1=='u')//u --> to UNDO
        {
            if (gamecounter==0)//that mean we have been backed to the initial board
            {
                printf("It's the first move! \n");
            }
            else
            {
                for(i=0; i<8; i++)
                {
                    for(j=0; j<8; j++)
                    {
                        board[i][j]=undoredo[gamecounter-1][i][j];
                        //while undo --> we return the board for it's previous condition

                    }
                }
                gamecounter--;
                playercount--;
                printf("Undo DONE!\n");
                undocounter++;
                //After every UNDO the undoconter increases by 1
                print();
            }
            //The function to print the board and the captured pieces
            printf("\n");
            garbage=getchar();
            while(garbage!='\n')
                garbage=getchar();
//This command because of that the ENTER is got as a character so to prevent that the \n character be input in the next scan
            if(playercount%2==0)
                printf("Player1 movment : ");
            else
                printf("Player2 movment : ");
            char1=getchar();
            //To get the first character again and return its value

        }

        else if(char1=='r')//r --> to REDO
        {
            if (undocounter==0)//if true --> that mean that there is no more possible REDO
            {
                print();
                printf("\n");
                printf("ERROR,There is no more REDO.Try again\n");
            }
            else
            {
                for(i=0; i<8; i++)
                {
                    for(j=0; j<8; j++)
                    {
                        board[i][j]=undoredo[gamecounter+1][i][j];
                    }
                }
                gamecounter++;
                playercount++;
                printf("REDO DONE!\n");
                undocounter--;
                //because every REDO cancel one of the UNDO
                print();
                printf("\n");
            }
            garbage=getchar();
            while(garbage!='\n')
                garbage=getchar();
            //To store the \0 character in an unused variable called "garbage"
            if(playercount%2==0)
                printf("Player1 movment : ");
            else
                printf("Player2 movment : ");
            char1=getchar();
            //To get the first character again and return its value

        }

    }

    return char1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//This function check if the player want to save or load the game or not
char SaveLoadCheck(char char1)
{
    FILE *boardsave,*capturedsave,*playerturn,*player1color;
    //The pointer which point to the save file
    int i,j;
    while(char1=='s'||char1=='l')
    {
        if(char1=='s')//mean the player want to SAVE
        {
            boardsave=fopen("save.txt","w");
            //The board saved in a text file named "save.txt"
            fputs(board,boardsave);
            //the board had been put as a string in the file
            fclose(boardsave);

//            for(i=0; i<8; i++)
//            {
//                for(j=0; j<4; j++)
//                {
//                    array[i][j]=capturedpiece[i][j];//??????
//                }
//            }

            capturedsave=fopen("savecaptured.txt","w");//To save the capturepiece array ,,as we did for the board
            fputs(capturedpiece,capturedsave);
            fclose(capturedsave);

            playerturn=fopen("saveplayer.txt","w");//To save the capturepiece array ,,as we did for the board
            fputc((int)playercount,playerturn);
            fclose(playerturn);

            player1color=fopen("saveplayer1color.txt","w");//To save the capturepiece array ,,as we did for the board
            fputc(color,player1color);
            fclose(player1color);

            garbage=getchar();
            while(garbage!='\n')
                garbage=getchar();
            printf("Save DONE!\n");
            if (gamecounter%2==0)
                printf("Player1 movment : ");
            else
                printf("Player2 movment : ");
            char1=getchar();
            //To get the first character again and return its value

        }
        else if(char1=='l')//To LOAD
        {
            boardsave=fopen("save.txt","r");//to read (LOAD) From the saved file

            if(boardsave==NULL)//if true --> that mean that there is no file has been saved for the board and capturedpiece
            {
                printf("ERROR,There is no saved file!,try again : ");
                garbage=getchar();
                while(garbage!='\n')
                    garbage=getchar();
                char1=getchar();
            }
            else
            {
                while(!feof(boardsave))//that will loop till the end of file
                {
                    fgets(board,70,boardsave);//that get the characters from file and put it into the board
                }
                fclose(boardsave);
                capturedsave=fopen("savecaptured.txt","r");//The same as the board
                while(!feof(capturedsave))
                {
                    fgets(capturedpiece,40,capturedsave);
                }
                fclose(capturedsave);

                playerturn=fopen("saveplayer.txt","r");//The same as the board
                while(!feof(playerturn))
                {
                    playercount=fgetc(playerturn);
                    break;
                }
                fclose(playerturn);

                player1color=fopen("saveplayer1color.txt","r");//The same as the board
                while(!feof(player1color))
                {
                    color=fgetc(player1color);
                    break;
                }
                fclose(player1color);

                printf("Load DONE!\n");
                print();
                printf("\n");
                garbage=getchar();
                while(garbage!='\n')
                    garbage=getchar();
                if (playercount%2==0)
                    printf("Player1 movment : ");
                else
                    printf("Player2 movment : ");
                char1=getchar();
            }

        }
    }
    return char1;

}
//----------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------

//function to get the move from user
void getmovment()
{
    char char1,char2;
    //char1-->the inrow input
    //char2-->the outrow input
    if (color=='l')//that mean that the user want to load in the first move
    {
        char1='l';
    }
    else
    {
        char1=getchar();
    }
    char1=UndoRedo(char1);//check the undoredo function
    char1=SaveLoadCheck(char1);//check the SaveLoad function

    while(char1=='\n')
    {
        printf("You Entered nothing , try again : ");
        char1=getchar();
        char1=SaveLoadCheck(char1);
    }

    scanf("%d",&inrow);
    //we should reverse the inrow the user returned
    if(inrow==1)
    {
        inrow=7;
    }
    else if(inrow==2)
    {
        inrow=6;
    }
    else if(inrow==3)
    {
        inrow=5;
    }
    else if(inrow==4)
    {
        inrow=4;
    }
    else if(inrow==5)
    {
        inrow=3;
    }
    else if(inrow==6)
    {
        inrow=2;
    }
    else if(inrow==7)
    {
        inrow=1;
    }
    else if(inrow==8)
    {
        inrow=0;
    }

    char2=getchar();

    while(char2=='\n')
    {
        printf("You Entered the move-from location only,now Enter the move-to location  : ");
        char2=getchar();
    }

    scanf("%d",&outrow);
    if (outrow==1||outrow==8)
    {
        pormot=getchar();
    }

    //any other unnecessary input will be put in garbage
    garbage=getchar();
    while(garbage!='\n')
        garbage=getchar();
    if(outrow==1)
    {
        outrow=7;
    }
    else if(outrow==2)
    {
        outrow=6;
    }
    else if(outrow==3)
    {
        outrow=5;
    }
    else if(outrow==4)
    {
        outrow=4;
    }
    else if(outrow==5)
    {
        outrow=3;
    }
    else if(outrow==6)
    {
        outrow=2;
    }
    else if(outrow==7)
    {
        outrow=1;
    }
    else if(outrow==8)
    {
        outrow=0;
    }
    incol=char1;
    outcol=char2;
    //because the input is a character so we want to turn it to asciicode and -65
    incol=incol-65;
    outcol=outcol-65;

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

int capturecheck()//a function to check the out place if it is has a piece of the same army or not
{
    //if the returned value==1-->that mean that is a valid move ,,, else if 0-->not valid
    inPieceAscii=(int)board[inrow][incol];
    outPieceAscii=(int)board[outrow][outcol];

    //if there is a promotion it will return 1
    if(pormot=='q'||pormot=='r'||pormot=='n'||pormot=='b'||pormot=='B'||pormot=='N'||pormot=='R'||pormot=='Q')
    {
        return 1;
    }

    //if the moved piece will eat a piece of its army then return 0
    else if(((inPieceAscii>90)&&(outPieceAscii>90))||(((inPieceAscii<90&&inPieceAscii>64)&&(outPieceAscii<90&&outPieceAscii>64))))
    {
        return 0;
    }

    else
    {
        if (outPieceAscii<90&&outPieceAscii>64)
        {
            //else if valid --> put the captured piece in the array capturedpiece

            if(count2==4)
            {
                count1++;
                count2=0;
                capturedpiece[count1][count2]=board[outrow][outcol];
                count2++;
            }
            else
            {
                capturedpiece[count1][count2]=board[outrow][outcol];
                count2++;
            }
        }
        else if(outPieceAscii>90)
        {
            if(count4==4)
            {
                count3--;
                count4=0;
                capturedpiece[count3][count4]=board[outrow][outcol];
                count4++;
            }
            else
            {
                capturedpiece[count3][count4]=board[outrow][outcol];
                count4++;
            }
        }
        return 1;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
int  queencheck()//function check that (if the queen is moving, is it a valid move or not),if valid return 1 else return 0
{

    int i,j,flag=0,x,n=1,m;
    //flag--> a variable=0 , and if there are a piece between the movefrom and moveto places ,,flag=1
    //if flag=1 then it's NOT avalid move

    i=outrow-inrow;//i-->the difference between the rows
    j=outcol-incol;//j-->the difference between the columns
    if(i==j||i==-j)
    {
        if(i>0&&j>0)
        {
            for(m=1; m<i; m++)
            {
                if ((int)board[inrow+m][incol+n]>64)
                {
                    flag=1;
                    break;
                }
                n++;
            }
        }
        else if(i<0&&j>0)
        {
            for(m=-1; m>i; m--)
            {
                if ((int)board[inrow+m][incol+n]>64)
                {
                    flag=1;
                    break;
                }
                n++;
            }
        }
        else if(i<0&&j<0)
        {
            n=-1;
            for(m=-1; m>i; m--)
            {
                if ((int)board[inrow+m][incol+n]>64)
                {
                    flag=1;
                    break;
                }
                n--;
            }
        }
        else if(i>0&&j<0)
        {
            n=-1;
            for(m=1; m<i; m++)
            {
                if ((int)board[inrow+m][incol+n]>64)
                {
                    flag=1;
                    break;
                }
                n--;
            }
        }
    }
    else
    {
        if(outcol>incol)
        {
            for(x=incol+1; x<outcol; x++)
            {
                if ((int)board[inrow][x]>64)
                {
                    flag=1;
                    break;
                }
            }
        }
        else if(outcol<incol)
        {
            for(x=outcol+1; x<incol; x++)
            {
                if ((int)board[inrow][x]>64)
                {
                    flag=1;
                    break;
                }
            }
        }
        else if(outrow>inrow)
        {
            for(x=inrow+1; x<outrow; x++)
            {
                if ((int)board[x][incol]>64)
                {
                    flag=1;
                    break;
                }
            }
        }
        else if(outrow<inrow)
        {
            for(x=outrow+1; x<inrow; x++)
            {
                if ((int)board[x][incol]>64)
                {
                    flag=1;
                    break;
                }
            }
        }
    }
    if((i==j||i==-j)&&(flag==0))
    {
        return 1;
    }
    else if(((outcol!=incol&&outrow==inrow)||(outcol==incol&&outrow!=inrow))&&flag==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
int knightcheck()//function check that (if the knight is moving, is it a valid move or not),if valid return 1 else return 0
{
    int i,j;
    i=outrow-inrow;
    j=outcol-incol;
    if(((i==-2||i==2)&&(j==-1||j==1))||(((j==-2||j==2)&&(i==-1||i==1))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------
int kingcheck()//function check that (if the queen is moving, is it a valid move or not),if valid return 1 else return 0
{
    int i,j;
    i=outrow-inrow;
    j=outcol-incol;
    if((i<=1&&i>=-1)&&(j<=1&&j>=-1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
int bishopcheck()//function check that (if the bishop is moving, is it a valid move or not),if valid return 1 else return 0
{
    int i,j,m,n=1,flag=0;
    //flag--> [as in queen]
    i=outrow-inrow;
    j=outcol-incol;
    if(i>0&&j>0)
    {
        for(m=1; m<i; m++)
        {
            if ((int)board[inrow+m][incol+n]>64)
            {
                flag=1;
                break;
            }
            n++;
        }
    }
    else if(i<0&&j>0)
    {
        for(m=-1; m>i; m--)
        {
            if ((int)board[inrow+m][incol+n]>64)
            {
                flag=1;
                break;
            }
            n++;
        }
    }
    else if(i<0&&j<0)
    {
        n=-1;
        for(m=-1; m>i; m--)
        {
            if ((int)board[inrow+m][incol+n]>64)
            {
                flag=1;
                break;
            }
            n--;
        }
    }
    else if(i>0&&j<0)
    {
        n=-1;
        for(m=1; m<i; m++)
        {
            if ((int)board[inrow+m][incol+n]>64)
            {
                flag=1;
                break;
            }
            n--;
        }
    }
    if((i==j||i==-j)&&flag==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------
int rookcheck()//function check that (if the rook is moving, is it a valid move or not),if valid return 1 else return 0
{
    int flag=0,x;
    //flag--> [as in queen]
    if(outcol>incol)
    {
        for(x=incol+1; x<outcol; x++)
        {
            if ((int)board[inrow][x]>64)
            {
                flag=1;
                break;
            }
        }
    }
    else if(outcol<incol)
    {
        for(x=outcol+1; x<incol; x++)
        {
            if ((int)board[inrow][x]>64)
            {
                flag=1;
                break;
            }
        }
    }
    else if(outrow>inrow)
    {
        for(x=inrow+1; x<outrow; x++)
        {
            if (board[x][incol]!='.'&&board[x][incol]!='-')
            {
                flag=1;
                break;
            }
        }
    }
    else if(outrow<inrow)
    {
        for(x=outrow+1; x<inrow; x++)
        {
            if ((int)board[x][incol]>64)
            {
                flag=1;
                break;
            }
        }
    }
    if(((outcol!=incol&&outrow==inrow)||(outcol==incol&&outrow!=inrow))&&(flag==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------//
int pawncheck()//function check that (if the pawn is moving, is it a valid move or not),if valid return 1 else return 0
{
    inPieceAscii=(int)board[inrow][incol];
    outPieceAscii=(int)board[outrow][outcol];
    switch(board[inrow][incol])
    {
    case 'p':
        if(outrow==0)//then it is a promotion
        {

            while(pormot!='q'&&pormot!='b'&&pormot!='n'&&pormot!='r')
            {
                printf("Invalid piece choose (q,r,n,b) only : ");
                pormot=getchar();
                while(garbage!='\n')
                    garbage=getchar();
            }

            switch (pormot)//while pormot is valid then do the promotion
            {
            case 'q':
                board[outrow][outcol]='q';
                break;
            case 'r':
                board[outrow][outcol]='r';
                break;
            case 'n':
                board[outrow][outcol]='n';
                break;
            case 'b':
                board[outrow][outcol]='b';
                break;
            default :
                break;
            }


        }
        if (((outcol==incol&&((inrow==6&&(outrow==5||outrow==4))||outrow==inrow-1))&&outPieceAscii<64)||((outrow==inrow-1&&(outcol==incol+1||outcol==incol-1))&&(outPieceAscii<90&&outPieceAscii>64)))
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 'P':
        if(outrow==7)//then it is a promotion
        {
            while(pormot!='Q'&&pormot!='B'&&pormot!='N'&&pormot!='R')
            {
                printf("Invalid piece choose (q,r,n,b) only : ");
                pormot=getchar();
                while(garbage!='\n')
                    garbage=getchar();
            }

            switch (pormot)//while pormot is valid then do the promotion
            {
            case 'Q':
                board[outrow][outcol]='Q';
                break;
            case 'R':
                board[outrow][outcol]='R';
                break;
            case 'N':
                board[outrow][outcol]='N';
                break;
            case 'B':
                board[outrow][outcol]='B';
                break;
            default :
                break;
            }


        }
        if (((incol==outcol&&((inrow==1&&(outrow==3||outrow==2))||outrow==inrow+1))&&outPieceAscii<64)||(outrow==inrow+1&&(outcol==incol+1||outcol==incol-1))&&outPieceAscii>90)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
void initialize()//A function to initialize any array in the game
{

    int i=0,j=0;
    for (i=0; i<8; i++)
    {
        for (j=0; j<8; j+=2)
        {
            if(i%2==0)
            {
                board[i][j]='-';
                board[i][j+1]='.';
            }
            else
            {
                board[i][j]='.';
                board[i][j+1]='-';
            }
        }
    }
    board[0][0]=board[0][7]='R';
    board[0][1]=board[0][6]='N';
    board[0][2]=board[0][5]='B';
    board[0][3]='Q';
    board[0][4]='K';
    for(j=0; j<8; j++)
    {
        board[1][j]='P';
    }


    board[7][0]=board[7][7]='r';
    board[7][1]=board[7][6]='n';
    board[7][2]=board[7][5]='b';
    board[7][3]='q';
    board[7][4]='k';
    for(j=0; j<8; j++)
    {
        board[6][j]='p';
    }

    for(i=0; i<8; i++)
    {
        for(j=0; j<4; j++)
        {
            capturedpiece[i][j]='.';
        }
    }

    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            undoredo[0][i][j]=board[i][j];
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void print()//A function to print the board and the captured piece array
{
    int i,j,c=8,m=0;
    printf("     A  B  C  D  E  F  G  H");
    for (i=0; i<8; i++)
    {
        printf("\n\n%d   ",c);
        for(j=0; j<8; j++)
        {
            printf(" %c ",board[i][j]);
        }
        printf("   %d   ",c);
        c--;
        for (m=0; m<4; m++)
        {
            printf(" %c ",capturedpiece[i][m]);
        }
        if(i<4)
            printf("\t   <<--Captured BLACK pieces");
        else
            printf("\t<<--Captured WHITE pieces");
    }
    printf("\n\n     A  B  C  D  E  F  G  H");
    return;

}
//---------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------//
void domovement()//the function witch do the movement and call another functions
{

    int retofcheck,i,j,checkflag;
    //retofcheck--> "return of check"--a variable which = the returned values of the moved piece checking functions
    //checkflag--> to prevent the player from keep his king threaten---if =1 then it's a valid move
    int stale1,stale2,stale3,stale4,stale5,stale6,stale7,stale8;
    //They are variables which will be = the returned valued of the threating check for every square around the white king
    int STALE1,STALE2,STALE3,STALE4,STALE5,STALE6,STALE7,STALE8;
    //They are variables which will be = the returned valued of the threating check for every square around the black king
    getmovment();//calling the function to getmovment

    kingplace();//to know the two kings place

    if(threatening(krow,kcol)==1&&board[inrow][outrow]!='k')//if the white king is threaten the white player should only move the king
    {
        checkflag=0;
    }
    else if(threatening(Krow,Kcol)==1&&board[inrow][outrow]!='K')//if the white king is threaten the black player should only move the king
    {
        checkflag=0;
    }
    else
    {
        checkflag=1;
    }

    if (board[inrow][incol]=='p'||board[inrow][incol]=='P')
    {
        retofcheck=pawncheck();
    }
    else if (board[inrow][incol]=='r'||board[inrow][incol]=='R')
    {
        retofcheck=rookcheck();
    }
    else if (board[inrow][incol]=='b'||board[inrow][incol]=='B')
    {
        retofcheck=bishopcheck();
    }
    else if (board[inrow][incol]=='k'||board[inrow][incol]=='K')
    {
        retofcheck=kingcheck();
    }
    else if (board[inrow][incol]=='n'||board[inrow][incol]=='N')
    {
        retofcheck=knightcheck();
    }
    else if (board[inrow][incol]=='q'||board[inrow][incol]=='Q')
    {
        retofcheck=queencheck();
    }
    else retofcheck=0;


    while(checkflag==0||0>incol||incol>7||0>outcol||outcol>7||0>inrow||inrow>7||0>outrow||outrow>7||retofcheck==0||capturecheck()==0||controlcheck()==0)
    {
        //while the player want to go to out of the board or move a piece wrongly or want to eat himself..will print errpr

        if(controlcheck()==0)
        {
            printf("\nYou can move ONLY your pieces!,\n");
        }
        else if(capturecheck()==0)
        {
            printf("\nYou can not capture your piece!,\n");
        }
        printf("Error:Invalid move please try again : ");
        getmovment();
        if(threatening(krow,kcol)==1&&board[inrow][incol]!='k')
        {
            checkflag=0;
        }
        else if(threatening(Krow,Kcol)==1&&board[inrow][incol]!='K')
        {
            checkflag=0;
        }
        else
        {
            checkflag=1;
        }
        if (board[inrow][incol]=='p'||board[inrow][incol]=='P')
        {
            retofcheck=pawncheck();
        }
        if (board[inrow][incol]=='r'||board[inrow][incol]=='R')
        {
            retofcheck=rookcheck();
        }
        if (board[inrow][incol]=='b'||board[inrow][incol]=='B')
        {
            retofcheck=bishopcheck();
        }
        if (board[inrow][incol]=='k'||board[inrow][incol]=='K')
        {
            retofcheck=kingcheck();
        }
        if (board[inrow][incol]=='n'||board[inrow][incol]=='N')
        {
            retofcheck=knightcheck();
        }
        if (board[inrow][incol]=='q'||board[inrow][incol]=='Q')
        {
            retofcheck=queencheck();
        }
        printf("\n");
    }


    if(pormot!='q'&&pormot!='b'&&pormot!='r'&&pormot!='n'&&pormot!='N'&&pormot!='R'&&pormot!='B'&&pormot!='Q')
        //if it isn's a promotion then do the movement
        //note that if it a peomotion the movment will be done in the pawn function
        board[outrow][outcol]=board[inrow][incol];


    //after moving the piece return the inplace to the '.' or '-'
    if((incol+inrow)%2==0)
    {
        board[inrow][incol]='-';
    }
    else
    {
        board[inrow][incol]='.';
    }
    pormot='M';


    for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            undoredo[gamecounter+1][i][j]=board[i][j];
        }
    }
    gamecounter++;
    kingplace();

//    if(board[krow-1][kcol-1]>'Z'&&board[krow-1][kcol]>'Z'&&board[krow-1][kcol+1]>'Z'&&board[krow][kcol-1]>'Z'&&board[krow][kcol+1]>'Z')
//    {
//        if(krow==7)
//            stalemate=0;
//        else if(board[krow+1][kcol-1]>'Z'&&board[krow+1][kcol]>'Z'&&board[krow+1][kcol+1]>'Z')
//            stalemate=0;
//    }
//    if(board[Krow][Kcol-1]>'A'&&board[Krow][Kcol+1]>'A'&&board[Krow+1][Kcol-1]>'A'&&board[Krow+1][Kcol]>'A'&&board[Krow+1][Kcol+1]>'A')
//    {
//        if(krow==0)
//            STALEMATE=0;
//        else if(board[Krow-1][Kcol-1]>'A'&&board[Krow-1][Kcol]>'A'&&board[Krow-1][Kcol+1]>'A')
//            STALEMATE=0;
//    }
//    else
    {

        kingcolorcheck=0;
        stale1=threatening(krow-1,kcol-1);
        if(stale1==0&&threatening(krow,kcol)==1)
        {
            if(board[krow-1][kcol-1]>'a'&&board[krow-1][kcol-1]<'z')
                stale1=1;
        }
        stale2=threatening(krow-1,kcol);
        if(stale2==0&&threatening(krow,kcol)==1)
        {
            if(board[krow-1][kcol]>'a'&&board[krow-1][kcol]<'z')
                stale2=1;
        }
        stale3=threatening(krow-1,kcol+1);
        if(stale3==0&&threatening(krow,kcol)==1)
        {
            if(board[krow-1][kcol+1]>'a'&&board[krow-1][kcol+1]<'z')
                stale3=1;
        }
        stale4=threatening(krow,kcol-1);
        if(stale4==0&&threatening(krow,kcol)==1)
        {
            if(board[krow][kcol-1]>'a'&&board[krow][kcol-1]<'z')
                stale4=1;
        }
        stale5=threatening(krow,kcol+1);
        if(stale5==0&&threatening(krow,kcol)==1)
        {
            if(board[krow][kcol+1]>'a'&&board[krow][kcol+1]<'z')
                stale5=1;
        }
        stale6=threatening(krow+1,kcol-1);
        if(stale6==0&&threatening(krow,kcol)==1)
        {
            if(board[krow+1][kcol]>'a'&&board[krow+1][kcol]<'z')
                stale6=1;
        }

        stale7=threatening(krow+1,kcol);
        if(stale7==0&&threatening(krow,kcol)==1)
        {
            if(board[krow+1][kcol]>'a'&&board[krow+1][kcol]<'z')
                stale7=1;
        }
        stale8=threatening(krow+1,kcol+1);
        if(stale8==0&&threatening(krow,kcol)==1)
        {
            if(board[krow+1][kcol]>'a'&&board[krow+1][kcol]<'z')
                stale8=1;
        }

        kingcolorcheck=1;
        STALE1=threatening(Krow-1,Kcol-1);
        if(STALE1==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow-1][Kcol-1]>'A'&&board[Krow-1][Kcol-1]<'Z')
                STALE1=1;
        }
        STALE2=threatening(Krow-1,Kcol);
        if(STALE2==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow-1][Kcol]>'A'&&board[Krow-1][Kcol]<'Z')
                STALE2=1;
        }

        STALE3=threatening(Krow-1,Kcol+1);
        if(STALE3==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow-1][Kcol+1]>'A'&&board[Krow-1][Kcol+1]<'Z')
                STALE3=1;
        }
        STALE4=threatening(Krow,Kcol-1);
        if(STALE4==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow][Kcol-1]>'A'&&board[Krow][Kcol-1]<'Z')
                STALE4=1;
        }
        STALE5=threatening(Krow,Kcol+1);
        if(STALE5==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow][Kcol-1]>'A'&&board[Krow][Kcol-1]<'Z')
                STALE5=1;
        }
        STALE6=threatening(Krow+1,Kcol-1);
        if(STALE6==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow+1][Kcol-1]>'A'&&board[Krow+1][Kcol-1]<'Z')
                STALE6=1;
        }
        STALE7=threatening(Krow+1,Kcol);
        if(STALE7==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow+1][Kcol]>'A'&&board[Krow+1][Kcol]<'Z')
                STALE7=1;
        }
        STALE8=threatening(Krow+1,Kcol+1);
        if(STALE8==0&&threatening(Krow,Kcol)==1)
        {
            if(board[Krow+1][Kcol+1]>'A'&&board[Krow+1][Kcol+1]<'Z')
                STALE8=1;
        }
    }

    kingcolorcheck=0;
    if(stale1==1&&stale2==1&&stale3==1&&stale4==1&&stale5==1&&stale6==1&&stale7==1&&stale8==1&&threatening(krow,kcol)==1)
    {
        checkmate=1;
    }
    else if(stale1==1&&stale2==1&&stale3==1&&stale4==1&&stale5==1&&stale6==1&&stale7==1&&stale8==1)
    {
        stalemate=1;
    }

    else if(threatening(krow,kcol)==1)
    {
        printf("White king Check ! \n");
    }
    kingcolorcheck=1;
    if(STALE1==1&&STALE2==1&&STALE3==1&&STALE4==1&&STALE5==1&&STALE6==1&&STALE7==1&&STALE8==1&&threatening(Krow,Kcol)==1)
    {
        CHECKMATE=1;
    }
    else if (STALE1==1&&STALE2==1&&STALE3==1&&STALE4==1&&STALE5==1&&STALE6==1&&STALE7==1&&STALE8==1)
    {
        STALEMATE=1;
    }
    else if(threatening(Krow,Kcol)==1)
    {
        printf("Black king Check ! \n");
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------//
int main()
{

    int i=2;
    printf("\t\t\t WELCOME TO CHESS\n \
The input options:\n\
\"A1A2\":Example To enter the move from A1 to A2\n\
\"u\":To UNDO\n\
\"r\":To REDO\n\
\"W\":To choose the white color pieces\n\
\"B\":To choose the black color pieces\n\
\"s\":To SAVE the game\n\
\"l\":To LOAD the game\n!-->PLEASE NOTE THAT ANY INCREMENT THAN THE REQUIRED WILL BE NEGLEGTED<--!\n\n");
    initialize();
    print();
    printf("\nChoose player1 color! (W/B) or \"l\" to load: ");
    scanf("%c",&color);
    if(color!='l')
    {
        garbage=getchar();
        while(garbage!='\n')
            garbage=getchar();
    }
    while(color!='W'&&color!='B'&&color!='l')
    {
        printf("\nERROR,only input \"W\" or \"B\" Choose player1 color! (W/B) or \"l\" to load : ");
        scanf("%c",&color);
        if(color!='l')
        {
            garbage=getchar();
            while(garbage!='\n')
                garbage=getchar();
        }
    }

    if(color!='l')
        printf("\nPlayer1 movment : ");
    while(STALEMATE!=1&&CHECKMATE!=1&&stalemate!=1&&checkmate!=1)
    {
        domovement();
        printf("\n\n");
        print();
        if(playercount%2==0)
        {
            i=2;
        }
        else
        {
            i=1;
        }
        printf("\n\n\nPlayer%d momvment : ",i);
        playercount++;

    }

    if(STALEMATE==1)
    {
        printf("Game Over!\n\t\t DRAW;;black Player stalmate");
    }
    else if(CHECKMATE==1)
    {
        printf("Game Over!\n\t\t White Player Won");
    }
    else if(stalemate==1)
    {
        printf("Game Over!\n\t\t DRAW;;white Player stalmate");
    }
    else if(checkmate==1)
    {
        printf("Game Over!\n\t\t Black Player Won");
    }
    return 0;
}
