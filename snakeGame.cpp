#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define UP 72
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define SNAKE_LENGTH 17
typedef struct _body
{
    int x;
    int y;
}Body;
Body body[18][18];
Body Temp[18][18];
typedef struct _food
{
    int x;
    int y;
}Food;
Food heart;
int i, j;
typedef struct _logic
{
    bool Up;
    bool Down;
    bool Right;
    bool Left;
}Logic;
Logic l;
int snake[18][18];
int map[20][20] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void Map();
void Init();
void TempToBody();
void MoveCoor();
void BodyToTemp();
void Delete();
void Output();
void Move();
void FoodOutput();
void Eatheart();
void BodyPlus();
void Score();
void Clear();
void GameOver();
void GameExplain();
void gotoxy(int x, int y);
void CursorView(char show);
void Map()
{
    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j] == 1)
                printf("■");
            else
                printf("  ");
        }
        printf("\n");
    }
}
void Init()
{
    l.Up = false;
    l.Down = false;
    l.Right = false;
    l.Left = false;
    body[17][17].x = 14;
    body[17][17].y = 14;
    body[17][16].x = 12;
    body[17][16].y = 14;
    body[17][15].x = 10;
    body[17][15].y = 14;
}
void TempToBody()
{
    bool ExitOutLoop = false;

    for (i = 17; i >= 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (snake[i][j] == 1)
            {
                Temp[i][j].x = body[i][j].x;
                Temp[i][j].y = body[i][j].y;
            }
            if (snake[i][j] == 0)
            {
                ExitOutLoop = true;
                break;
            }
        }
        if (ExitOutLoop == true)
        {
            ExitOutLoop = false;
            break;
        }
    }
}
void MoveCoor()
{
    if (l.Up == true)
    {
        TempToBody();
        body[17][17].y--;
        BodyToTemp();
    }

    if (l.Down == true)
    {
        TempToBody();
        body[17][17].y++;
        BodyToTemp();
    }

    if (l.Right == true)
    {
        TempToBody();
        body[17][17].x += 2;
        BodyToTemp();
    }

    if (l.Left == true)
    {
        TempToBody();
        body[17][17].x -= 2;
        BodyToTemp();
    }
}
void BodyToTemp()
{
    bool ExitOutLoop = false;
    for (i = 17; i > 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (snake[i][j] == 0 && j == 0)
            {
                body[i - 1][17].x = Temp[i][j].x;
                body[i - 1][17].y = Temp[i][j].y;
                ExitOutLoop = true;
                break;
            }
            body[i][j - 1].x = Temp[i][j].x;
            body[i][j - 1].y = Temp[i][j].y;
        }

        if (ExitOutLoop == true)
        {
            ExitOutLoop = false;
            break;
        }
    }
}
void Delete()
{
    bool ExitOutLoop = false;

    for (i = 17; i >= 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (snake[i][j] == 1)
            {
                gotoxy(body[i][j].x, body[i][j].y);
                printf("  ");
            }
            else
            {
                ExitOutLoop = true;
                break;
            }
        }
        if (ExitOutLoop == true)
        {
            ExitOutLoop = false;
            break;
        }
    }
}
void Output()
{
    bool ExitOutLoop = false;
    for (i = 17; i >= 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (snake[i][j] == 1)
            {
                gotoxy(body[i][j].x, body[i][j].y);
                printf("◎");
            }
            else
            {
                ExitOutLoop = true;
                break;
            }
        }
        if (ExitOutLoop == true)
        {
            ExitOutLoop = false;
            break;
        }
    }
}
void Move()
{
    int Time = 150;
    while (1)
    {
        Sleep(Time);
        Delete();
        MoveCoor();
        Output();
        Eatheart();
        GameOver();
        if (_kbhit())
            break;
    }
}
void FoodOutput()
{
    bool ExitOutLoop = false;
    srand(time(NULL));
    heart.x = (rand() % 18 + 1) * 2;
    heart.y = rand() % 18 + 1;
    for (i = 17; i >= 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (body[i][j].x == heart.x && body[i][j].y == heart.y)
            {
                heart.x = (rand() % 18 + 1) * 2;
                heart.y = rand() % 18 + 1;
            }
        }
    }
    gotoxy(heart.x, heart.y);
    printf("♥");
}
void Eatheart()
{
    if (body[17][17].x == heart.x && body[17][17].y == heart.y)
    {
        Score();
        BodyPlus();
        FoodOutput();
    }
}
void BodyPlus()
{
    bool ExitOutLoop = false;

    for (i = 17; i >= 0; i--)
    {
        for (j = 17; j >= 0; j--)
        {
            if (snake[i][j] == 0)
            {
                snake[i][j] = 1;
                ExitOutLoop = true;
                break;
            }
        }
        if (ExitOutLoop == true)
        {
            ExitOutLoop = false;
            break;
        }
    }
}
void Score()
{
    static int score = 0;
    score += 1000;
    gotoxy(13, 20);
    printf("점수 : %d", score);
    if (score == 30000)
        Clear();
}
void GameOver()
{
    if (body[17][17].x >= 38 || body[17][17].x <= 0)
    {
        system("cls");
        printf("게임 오버");
        exit(0);
    }
    if (body[17][17].y >= 19 || body[17][17].y <= 0)
    {
        system("cls");
        printf("게임 오버");
        exit(0);
    }
    for (i = 17; i >= 0; i--)
    {
        for (j = 16; j >= 0; j--)
        {
            if (body[17][17].x == body[i][j].x &&
                body[17][17].y == body[i][j].y)
            {
                system("cls");
                printf("게임 오버");
                exit(0);
            }
        }
    }
}
void GameExplain()
{
    gotoxy(2, 30);
    puts("맨 처음에는 상하우로만 이동 가능");
    gotoxy(2, 31);
    puts("방향키 상하좌우");
    gotoxy(2, 32);
    puts("몸통, 벽에 머리가 닿으면 게임 오버");
    gotoxy(2, 33);
    puts("1000 score / 하트");
    gotoxy(2, 34);
    puts("q: 게임 종료");
}
void Clear()
{
    system("cls");
    printf("클리어");
    exit(0);
}
int main()
{

    system("color 70");
    system("mode con cols=40 lines=40");
    int key;
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 18; j++) {
            snake[i][j] = 0;
        }
    }
    snake[17][15] = 1;
    snake[17][16] = 1;
    snake[17][17] = 1;

    Map();
    CursorView(0);
    Init();
    Output();
    FoodOutput();
    while (1)
    {
        GameExplain();
        if (_kbhit())
        {
            key = _getch();

            if (key == 'q')
                break;

            switch (key)
            {
            case UP:
                if (l.Down == true)
                    l.Up = false;
                else
                {
                    l.Up = true;
                    l.Down = false;
                    l.Right = false;
                    l.Left = false;
                }
                Move();
                break;
            case DOWN:
                if (l.Up == true)
                    l.Down = false;
                else
                {
                    l.Down = true;
                    l.Up = false;
                    l.Right = false;
                    l.Left = false;
                }
                Move();
                break;
            case LEFT:
                if (body[17][17].x == 14 && body[17][17].y == 14)
                    l.Left = false;
                else if (l.Right == true)
                    l.Left = false;
                else
                {
                    l.Left = true;
                    l.Down = false;
                    l.Right = false;
                    l.Up = false;
                }
                Move();
                break;
            case RIGHT:
                if (l.Left == true)
                    l.Right = false;
                else
                {
                    l.Right = true;
                    l.Down = false;
                    l.Up = false;
                    l.Left = false;
                }
                Move();
                break;
            default:
                break;
            }
        }
    }
    return 0;
}
void gotoxy(int x, int y)
{
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
