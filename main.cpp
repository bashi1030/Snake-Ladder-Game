#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>
#include <stdlib.h>
#include<ctime>  // for srand and time

void gotoRowCol(int rpos, int cpos, char a) {
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
    cout << a;
}

void gotoRowColl(int rpos, int cpos) {
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}

void sleep(int m)
{
    for (int j = 0; j < m * 21000; j++) {}
}

void winScreen(const string& playerName, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");
    SetConsoleTextAttribute(hConsole, color);
    gotoRowColl(10, 40);
    cout << "=============================";
    gotoRowColl(11, 40);
    cout << "     " << playerName << " WINS!";
    gotoRowColl(12, 40);
    cout << "=============================";
    SetConsoleTextAttribute(hConsole, 7);
    getch();
    return 0;
}

void board() {
    int contt =1;
    int Pr =3;
    int Pc =5;

    for (int i=0; i<=50;i++) {
        for (int j=0; j<=100; j++) {
            if (i==0|| i==50 || j==0 || j==100) {
                gotoRowCol(i, j, 219);
            }
            else  if ( j==0 || j==100) {
                gotoRowCol(i, j, 219);
            }
            if (i%5==0 || j%10==0) {
                gotoRowCol(i,j,219);
            }
        }
    }

    for (int q=1;q<=100;q++) {
        gotoRowColl(Pr,Pc);
        cout<<contt;
        contt++;
        Pc += 10;

        if (Pc>=105) {
            Pr+=5;
            Pc=5;
        }
    }
}

void condition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    gotoRowColl(5,125);
    cout<<"LADDERS"<<endl;
    gotoRowColl(6,122);
    cout<<"12---------38"<<endl;
    gotoRowColl(7,122);
    cout<<"32---------54"<<endl;
    gotoRowColl(8,122);
    cout<<"10---------65"<<endl;
    gotoRowColl(9,122);
    cout<<"62---------90"<<endl;

    SetConsoleTextAttribute(hConsole, 12);
    gotoRowColl(12,125);
    cout<<"SNAKES"<<endl;
    gotoRowColl(13,122);
    cout<<"28---------8"<<endl;
    gotoRowColl(14,122);
    cout<<"48---------18"<<endl;
    gotoRowColl(15,122);
    cout<<"82---------44"<<endl;
    gotoRowColl(16,122);
    cout<<"99---------5"<<endl;
    SetConsoleTextAttribute(hConsole, 7);
}

int dice() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    gotoRowColl(18,112);
    cout<<"DICE IS MOVING PRESS ANY BUTTON : "<<endl;
    getch();
    while (1) {
        srand(time(NULL));
        int diceRoll = rand() % 6 + 1;
        if(kbhit()) {
            gotoRowColl(18,150);
            cout<<diceRoll;
            SetConsoleTextAttribute(hConsole, 7);
            return diceRoll;
        }
    }
}

int getPos(int row, int col) {
    return row * 10 + col + 1;
}

void getCoordsFromPos(int pos, int &row, int &col) {
    row = (pos - 1) / 10;
    col = (pos - 1) % 10;
}

void position1(int &row,int &col,int contt1,int &turn) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int pt=dice();
    int r,c;
    int R=row;
    int C=col;
    int sum=0;

    if (row >= 0 && col >= 0) {
        int prev_r = 1 + row * 5;
        int prev_c = 3 + col * 10;
        gotoRowCol(prev_r, prev_c, ' ');
    }

    gotoRowColl(20,120);
    SetConsoleTextAttribute(hConsole, 10);
    cout << "Turn of Player ONE (@) ";
    SetConsoleTextAttribute(hConsole, 7);

    if (row==-1 && col==-2 && pt==6) {
        gotoRowColl(26,125);
        cout<<"You Enter a Board (@)";
        row=0;
        col=-1;
        pt=0;
        pt=dice();
        if (pt==6) {
            sum+=pt;
            pt=dice();
            if (pt==6) {
                sum=0;
                turn=1;
            }
        }
    }

    if (row==-1 && col==-2 && pt!=6) {
        turn=1;
    }

    if(row>-1 && col>-2) {
        if (pt>0) {
            sum+=pt;
            if (pt==6) {
                contt1++;
            }
        }
        if (pt!=6) {
            turn=1;
        }
        while (pt==6) {
            pt=dice();
            if (pt==6 && contt1==1) {
                sum+=pt;
                contt1++;
            }
            if (pt==6 && contt1==2) {
                pt=0;
                contt1=0;
                sum=0;
            }
            if(pt!=6) {
                sum+=pt;
                turn=1;
                break;
            }
        }

        int currentPos = getPos(row, col);
        int targetPos = currentPos + sum;

        if (targetPos > 100) {
            row = R;
            col = C;
        } else {
            getCoordsFromPos(targetPos, row, col);
        }

        if (row==2 && col==7)  { row=0; col=8; }
        if (row==4 && col==7)  { row=1; col=7; }
        if (row==8 && col==1)  { row=4; col=3; }
        if (row==9 && col==8)  { row=0; col=4; }
        if (row==1 && col==1)  { row=3; col=7; }
        if (row==3 && col==1)  { row=5; col=3; }
        if (row==0 && col==9)  { row=6; col=4; }
        if (row==6 && col==1)  { row=8; col=9; }
    }

    r = 1 + row * 5;
    c = 3 + col * 10;
    SetConsoleTextAttribute(hConsole, 10);
    gotoRowCol(r,c,'@');
    SetConsoleTextAttribute(hConsole, 7);
    gotoRowColl(19,120);
    sleep(100);

    if (row==9 && col==9) {
        winScreen("Player @", 112);
    }
}

void position2(int &roww,int &coll,int &contt2,int &turn) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int pt=dice();
    int rr,cc;
    int RR=roww;
    int CC=coll;
    int ssum=0;

    if (roww >= 0 && coll >= 0) {
        int prev_rr = 1 + roww * 5;
        int prev_cc = 3 + coll * 10;
        gotoRowCol(prev_rr, prev_cc, ' ');
    }

    gotoRowColl(20,120);
    SetConsoleTextAttribute(hConsole, 12);
    cout<<"Turn of Player TWO ($) ";
    SetConsoleTextAttribute(hConsole, 7);

    if (roww==-2 && coll==-3 && pt==6) {
        gotoRowColl(25,125);
        cout<<"You Enter A Board ($)";
        roww=0;
        coll=-1;
        pt=0;
        pt=dice();
        if (pt==6) {
            ssum+=pt;
            pt=dice();
            if (pt==6) {
                ssum=0;
                turn=0;
            }
        }
    }

    if (roww==-2 && coll==-3 && pt!=6) {
        turn=0;
        ssum=0;
    }

    if (roww>-2 && coll>-3) {
        if (pt>0) {
            ssum+=pt;
            if (pt==6) {
                contt2++;
            }
        }
        if (pt!=6) {
            turn=0;
        }
        while (pt==6) {
            pt=dice();
            if (pt==6 && contt2==1) {
                ssum+=pt;
                contt2++;
            }
            if (pt==6 && contt2==2) {
                pt=0;
                contt2=0;
                ssum=0;
            }
            if (pt!=6) {
                ssum+=pt;
                turn=0;
                break;
            }
        }

        int currentPos = getPos(roww, coll);
        int targetPos = currentPos + ssum;

        if (targetPos > 100) {
            roww = RR;
            coll = CC;
        } else {
            getCoordsFromPos(targetPos, roww, coll);
        }

        if (roww==2 && coll==7)  { roww=0; coll=8; }
        if (roww==4 && coll==7)  { roww=1; coll=7; }
        if (roww==8 && coll==1)  { roww=4; coll=3; }
        if (roww==9 && coll==8)  { roww=0; coll=4; }
        if (roww==1 && coll==1)  { roww=3; coll=7; }
        if (roww==3 && coll==1)  { roww=5; coll=3; }
        if (roww==0 && coll==9)  { roww=6; coll=4; }
        if (roww==6 && coll==1)  { roww=8; coll=9; }
    }

    rr = 1 + roww * 5;
    cc = 3 + coll * 10;
    SetConsoleTextAttribute(hConsole, 12);
    gotoRowCol(rr,cc,'$');
    SetConsoleTextAttribute(hConsole, 7);
    gotoRowColl(19,120);
    sleep(100);

    if (roww==9 && coll==9) {
        winScreen("Player $", 112);
    }
}

int main() {

    board();
    condition();
    int row1=-1,col1=-2;
    int row2=-2,col2=-3;
    int turn=0,contt2=0,contt1=0;

    while(1) {
        if (turn==0) {
            position1(row1,col1,contt1,turn);
        }
        else {
            position2(row2,col2,contt2,turn);
        }
    }
    getch();
    return 0;
}
