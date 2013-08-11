/*
Project: Cross & Nuts game implementation using simple console graphics. //Done :D
Author: Nishad Dawkhar
Objectives:
1) Layout ----> Done.
2) Movement ---> Done.
3) Storage of data.----> Done.
4) Opponents turn.-----> Done.
5) Condition check. ---> done.

*/

#include <stdio.h>
#include <stdlib.h>
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

//Global variables
int flg = 1,p = 1,plyr1loc, plyr2loc; //location of end letters of player1,2... //for flags, 1 is off(false), 0 is on(true).
char a[11][70], t = ' '; //main array used for layout

//Function declarations
void makelayout();
void printlayout();
int storename(int j);
int usr_input();
void make_change();
void place(char c);
void reset();
void check_status(char c);

struct pos_info //structure storing position coordinates.
{
    int last_x;
    int last_y;
    int current_x;
    int current_y;
} pos = {0,0,1,3};


int main()
{
    int FLAG = 1,temp = 1;
    char crossnut;
    makelayout();
    system("clear");
    for(;FLAG == 1;)
    {
        if(p == 1)
        crossnut = '*';
        else
        crossnut = 'o';
        if(temp == 0)
        {
        place(crossnut);
        check_status(crossnut);
        reset();
        }
        printlayout();
        temp = usr_input();
        system("clear");
        if(temp == 1)
        make_change(crossnut);

    }

    return 0;
}

void makelayout() //Creates default layout of the game
{
    int i,j;
    for(i = 0; i < 11; i++)
    {
        for(j = 0; j < 70; j++)
        a[i][j] = ' ';
    }
    printf("Enter your name: ");
    plyr1loc = storename(0);
    flg = 0;
    printf("Enter opponent's name: ");
    plyr2loc = storename((plyr1loc + 3));

    for(j = 2; j <= 4; j = j + 2)
    {
        for(i = 2; i<=8; i++)
        a[i][j] = '|';
    }
    for(i = 4; i <= 6; i = i + 2)
    {
        for(j = 0; j <= 6; j++)
        a[i][j] = '-';
    }
    a[3][1] = '_';
}

int storename(int j) //Stores player names and returns position of the array where the score is gonna be displayed
{
    int score;
    char c;
    do
    {
        c = getchar();
        if(c != '\n')
        {
            a[0][j] = c;
            j++;
        }
    } while(c != '\n');
    a[0][j] = ':';
    j++;
    if(flg == 1)
    a[0][j] = 'o';
    else
    a[0][j] = '*';
    score = j;
    return score;
}

void printlayout() //prints current layout
{
    int i,j;
    for(i = 0; i < 11; i++)
    {
        for(j = 0; j < 70; j++)
        printf("%c",a[i][j]);
        printf("\n");
    }
    printf("//Press w,s,a,d to move , z to save and x to exit.\n");
}

int usr_input() //takes in user input.
{
    char c;
    c = getchar();
    switch(c)
    {
        case UP:
        if(pos.current_y == 3)
        usr_input();
        else
        {
            pos.last_y = pos.current_y;
            pos.last_x = pos.current_x;
            pos.current_y -= 2;
        }
        return 1;
        break;

        case DOWN:
        if(pos.current_y == 7)
        usr_input();
        else
        {
            pos.last_y = pos.current_y;
            pos.last_x = pos.current_x;
            pos.current_y += 2;
        }
        return 1;
        break;

        case LEFT:
        if(pos.current_x == 1)
        usr_input();
        else
        {
            pos.last_y = pos.current_y;
            pos.last_x = pos.current_x;
            pos.current_x -= 2;
        }
        return 1;
        break;

        case RIGHT:
        if(pos.current_x == 5)
        usr_input();
        else
        {
            pos.last_y = pos.current_y;
            pos.last_x = pos.current_x;
            pos.current_x += 2;
        }
        return 1;
        break;

        case 'z':
        p *= -1;
        return 0;
        break;

        case 'x':
        exit(EXIT_SUCCESS);
        break;

        default:
        usr_input();
    }
}

void check_status(char c) //checks status of game based on users input.
{
    int i;
    if(
       (a[3][1] == c && a[3][5] == c && a[3][7] == c) ||
       (a[3][1] == c && a[5][1] == c && a[7][1] == c) ||
       (a[3][1] == c && a[5][3] == c && a[7][5] == c) ||
       (a[3][3] == c && a[5][3] == c && a[7][3] == c) ||
       (a[3][5] == c && a[5][5] == c && a[7][5] == c) ||
       (a[5][1] == c && a[5][3] == c && a[5][5] == c) ||
       (a[7][1] == c && a[7][3] == c && a[7][5] == c) ||
       (a[3][5] == c && a[5][3] == c && a[7][1] == c)
       )

    {
        system("clear");
        printf("Congrats ");
        if(c == 'o')
        {
        for(i = 0; i < (plyr1loc - 1); i++)
        printf("%c", a[0][i]);
        printf(", you won !!!!!\n");
        }
        else
        {
        for(i = (plyr1loc + 3); i < (plyr2loc - 1); i++)
        printf("%c", a[0][i]);
        printf(", you won !!!!!\n");
        }
        exit(EXIT_SUCCESS);

    }



}

void make_change() //makes changes according to user input.
{
    a[pos.last_y][pos.last_x] = t;
    t = a[pos.current_y][pos.current_x];
    if(t == ' ')
    a[pos.current_y][pos.current_x] = '_';
    else
    a[pos.current_y][pos.current_x] = '!';
    flg = 0;
}

void reset() //resets the coordinates of position after every turn
{
    pos.current_x = 1;
    pos.current_y = 3;
    pos.last_x = 0;
    pos.last_y = 0;
    t = a[pos.current_y][pos.current_x];
    if(t == ' ')
    a[pos.current_y][pos.current_x] = '_';
    else
    a[pos.current_y][pos.current_x] = '!';
}

void place(char c) //places character on the initial point
{
    if(a[pos.current_y][pos.current_x] == '_')
    a[pos.current_y][pos.current_x] = c;
    else
    {
       a[pos.current_y][pos.current_x] = t;
       p *= -1;
    }
}
