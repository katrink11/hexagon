#include "hexagon.h"
//Uncomment line below for Windows OS
//#include<windows.h>
#include <cstdio>
#include <cmath>
using namespace std;

//Uncomment line below for Windows OS
//HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Максимальное количество ходов фишки
const int x[18] = { -1, 1, 2, 1, -1, -2, -4, -3, -2, 0, 2, 3, 4, 3, 2, 0, -2, -3 };
const int y[18] = { 1, 1, 0, -1, -1, 0, 0, 1, 2, 2, 2, 1, 0, -1, -2, -2, -2, -1 };

const int player1 = 1;
const int player2 = 2;

string getOSName()
{
#ifdef _WIN32
    return "Windows";
#elif _WIN64
    return "Windows";
#elif __APPLE__ || __MACH__ || __linux__ || __unix || __unix__
    return "Mac/Linux/Unix";
#endif
}

void winnerCheck(char** board, int mode)
{
    if (getScore(board, 1) > getScore(board, 2))
    {
        if (mode == 1)
            cout << "The Winner is Player 1!\n" << "Score : " << getScore(board, 1) << endl;
        if (mode == 2)
            cout << "The Winner is Player!\n" << "Score : " << getScore(board, 1) << endl;
        if (mode == 3)
            cout << "The Winner is Computer 1!\n" << "Score : " << getScore(board, 1) << endl;
    }
    else if (getScore(board, 1) < getScore(board, 2))
    {
        if (mode == 1)
            cout << "The Winner is Player 2!\n" << "Score : " << getScore(board, 2) << endl;
        if (mode == 2)
            cout << "The Winner is Computer!\n" << "Score : " << getScore(board, 2) << endl;
        if (mode == 3)
            cout << "The Winner is Computer 2 !\n" << "Score : " << getScore(board, 2) << endl;
    }
    else
    {
        cout << "DRAW\n" << getScore(board, 1) << " : " << getScore(board, 1) << endl;
    }
}

void gameLogic(char** board, int mode)
{
    // уровень сложности по умолчанию
    int compLevel_1 = 1;
    int compLevel_2 = 1;

    if (mode == 2)
    {
        cout << "Enter difficulty level: ";
        cin >> compLevel_2;
    }
    else if (mode == 3)
    {
        cout << "Enter difficulty level for Computer 1: ";
        cin >> compLevel_1;
        cout << "Enter difficulty level for Computer 2: ";
        cin >> compLevel_2;
    }

    // печать доски
    printBoard(board);

    while (true)
    {
        if (mode == 1 || mode == 2)
        {
            if (generateMoves(board, player1))
            {
                playerMove(board, player1);
            }

            else
            {
                break;
            }
        }
        else if (generateMoves(board, player1) && mode == 3)
        {
            //computerMove(board, 1, compLevel_1, 1, player1, -infinity, infinity);
            minimax(board, 1, compLevel_1, 1, player1);
            cout << "Результат оценочной функции для Player 1 = " << moveEvaluation(board,player1) << endl;
        }
        else
        {
            break;
        }
        if (mode == 1) {
            if (generateMoves(board, player2))
            {
                playerMove(board, player2);
            }
            else
            {
                break;
            }
        }
        else if (generateMoves(board, player2))
        {
            //computerMove(board, 1, compLevel_2, 2, player2, -infinity, infinity);
            minimax(board, 1, compLevel_2, 2, player2);
            cout << "Результат оценочной функции для Player 2 = " << moveEvaluation(board,player2) << endl;
        }

        else
        {
            break;
        }
    }
    winnerCheck(board, mode);
}

void colorField(char** field, int& i, int& j)
{
    if (field[i][j] == '1')
    {
        if(getOSName() == "Mac/Linux/Unix")
        {
            cout << "\033[31m" << '<' << field[i][j] << '>' << "\033[0m";
        }
        else
        {
            //Uncomment line below for Windows OS
            //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << '<' << field[i][j] << '>';
        }
    }
    if (field[i][j] == '2')
    {
        if(getOSName() == "Mac/Linux/Unix")
        {
            cout << "\033[34m" << '<' << field[i][j] << '>' << "\033[0m";
        }
        else {
            //Uncomment line below for Windows OS
            //SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            cout << '<' << field[i][j] << '>';
        }
    }
    //Uncomment line below for Windows OS
    //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    if (field[i][j] == '0')
    {
        cout << '<' << field[i][j] << '>';
    }

    if (field[i][j] == '.')
    {
        cout << "   ";
    }
}

void printBoard(char** board)
{
    cout << "\n       0  1  2  3  4  5  6  7  8 " << endl;
    for (int i = 0; i < map_height; i++)
    {
        //Uncomment line below for Windows OS
        //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (i < 10)
        {
            cout << "  " << i << "   ";
        }
        else
        {
            cout << " " << i << "   ";
        }
        for (int j = 0; j < map_width; j++)
        {
            colorField(board, i, j);
        }

        cout << endl;
    }
    cout << endl;
}

void highlightCellSelection(char** board, int x, int y)
{

    cout << "\n       0  1  2  3  4  5  6  7  8 " << endl;
    for (int i = 0; i < map_height; i++)
    {
        //Uncomment line below for Windows OS
        //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        if (i < 10)
        {
            cout << "  " << i << "   ";
        }
        else
        {
            cout <<" "<< i << "   ";
        }
        for (int j = 0; j < map_width; j++) {
            if (i == x && j == y) {
                if(getOSName() == "Mac/Linux/Unix") {
                    cout << "\033[1m\033[32m" << '<' << board[i][j] << '>' << "\033[0m";
                }
                else {
                    //Uncomment line below for Windows OS
                    //SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
                    cout << '<' << board[i][j] << '>';
                }
                //Uncomment line below for Windows OS
                //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else
            {
                colorField(board, i, j);
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isValidSelection(char** board, int x, int y, int player)
{
    if (x >= 0 && y >= 0 && x < map_height && y < map_width && board[x][y] == 48 + player)
    {
        highlightCellSelection(board, x, y);
        return true;
    }
    return false;
}

bool isValidMove(char** board, int x1, int y1, int x2, int y2)
{
    if (x2 >= 0 && y2 >= 0 && x2 < map_height && y2 < map_width && board[x2][y2] == '0' && abs(x1 - x2) <= 4 && abs(y1 - y2) <= 2 && abs(x1 - x2) + abs(y1 - y2) <= 4)
    {
        return true;
    }
    return false;
}

void moveChip(char** board, int x1, int y1, int x2, int y2, int player)
{
    // (48 + player) returns ASCII char value 48 = 0
    board[x2][y2] = 48 + player;

    if (abs(x2 - x1) + abs(y2 - y1) > 2 || abs(x2 - x1) + abs(y2 - y1) == 2 && abs(y2 - y1) == 2)
    {
        board[x1][y1] = 48;
    }
    if (x2 - 2 >= 0)
    {
        if (board[x2 - 2][y2] != '0' && board[x2 - 2][y2] != '.')
            board[x2 - 2][y2] = 48 + player;
    }

    if (x2 - 1 >= 0 && y2 + 1 < map_width)
    {
        if (board[x2 - 1][y2 + 1] != '0' && board[x2 - 1][y2 + 1] != '.')
        {
            board[x2 - 1][y2 + 1] = 48 + player;
        }
    }

    if (x2 + 1 < map_height && y2 + 1 < map_width)
    {
        if (board[x2 + 1][y2 + 1] != '0' && board[x2 + 1][y2 + 1] != '.')
        {
            board[x2 + 1][y2 + 1] = 48 + player;
        }
    }

    if (x2 + 2 < map_height)
    {
        if (board[x2 + 2][y2] != '0' && board[x2 + 2][y2] != '.')
        {
            board[x2 + 2][y2] = 48 + player;
        }
    }

    if (y2 - 1 >= 0 && x2 + 1 < map_height)
    {
        if (board[x2 + 1][y2 - 1] != '0' && board[x2 + 1][y2 - 1] != '.')
        {
            board[x2 + 1][y2 - 1] = 48 + player;
        }
    }

    if (x2 - 1 >= 0 && y2 - 1 >= 0)
    {
        if (board[x2 - 1][y2 - 1] != '0' && board[x2 - 1][y2 - 1] != '.')
        {
            board[x2 - 1][y2 - 1] = 48 + player;
        }
    }
}

void playerMove(char** board, int current_player) {
    int x1 = 0 , y1 = 0;
    int x2 = 0, y2 = 0;

    while (true)
    {
        cout << "\tPlayer " << (current_player == 1 ? " 1:" : " 2:") << endl;
        puts("\tSelect existing chip coordinates: ");
        cout << "x = ";
        cin >> x1;
        cout << "y = ";
        cin >> y1;
        if (isValidSelection(board, x1, y1, current_player))
        {
            cout << "\tPlayer " << (current_player == 1 ? " 1:" : " 2:") << endl;
            puts("\tSelect coordinates where to move");
            cout<<"x = ";
            cin >> x2;
            cout<<"y = ";
            cin >> y2;
            if (isValidMove(board, x1, y1, x2, y2))
            {
                moveChip(board, x1, y1, x2, y2, current_player);
                printBoard(board);
                break;
            }
            else
            {
                printBoard(board);
                if(getOSName() == "Mac/Linux/Unix")
                {
                    puts( "\033[31m\tInvalid coordinates! Try again.\033[0m");
                }
                else
                {
                    //Uncomment line below for Windows OS
                    //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
                    puts( "\tInvalid coordinates! Try again.");
                }
                //Uncomment line below for Windows OS
                //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
        }
        else
        {
            printBoard(board);
            if(getOSName() == "Mac/Linux/Unix")
            {
                puts( "\033[31m\tInvalid coordinates! Try again.\033[0m");
            }
            else
            {
                //Uncomment line below for Windows OS
                //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
                puts( "\tInvalid coordinates! Try again.");
            }
            //Uncomment line below for Windows OS
            //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
    }
}

bool generateMoves(char** board, int player)
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            // (48 + player) returns ASCII char value
            if (board[i][j] == 48 + player)
            {
                for (int k = 0; k < 18; k++)
                {
                    if (isValidMove(board, i, j, i + x[k], j + y[k]))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;

}

int getScore(char** board, int player)
{
    int score = 0;

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            // (48 + player) returns ASCII char value
            if (board[i][j] == 48 + player)
                score++;
        }
    }
    return score;
}

int moveEvaluation(char** board, int current_player)
{
    return getScore(board, current_player) - getScore(board, (current_player * 2) % 3);
}

int minimax(char* map[], int level, int depth, int player,
        int current_player) {

    char copy[map_height][map_width];

    const int all_move = 1100;

    const int amount_move = 18;

    int begin_x[all_move];

    int begin_y[all_move];

    int end_x[all_move];

    int end_y[all_move];

    int value[all_move];

    int counter_move = 0, i, j, bestMove;
    if (level % 2 == 0)
    {
        // выбор max
        bestMove = infinity;
    }
    else
    {
        // выбор min
        bestMove = -infinity;
    }
    for (i = 0; i < map_height; i++)
    {
        for (j = 0; j < map_width; j++)
        {
            copy[i][j] = map[i][j];
        }
    }

    if (level > depth)
    {
        return moveEvaluation(map, current_player);
    }

    else
    {
        for (i = 0; i < map_height; i++)
        {
            for (j = 0; j < map_width; j++)
            {
                if (isValidSelection(map, i, j, player))
                {
                    for (int k = 0; k < amount_move; k++)
                    {
                        if (isValidMove(map, i, j, i + x[k], j + y[k]))
                        {
                            begin_x[counter_move] = i;

                            begin_y[counter_move] = j;

                            end_x[counter_move] = i + x[k];

                            end_y[counter_move] = j + y[k];

                            moveChip(map, begin_x[counter_move], begin_y[counter_move], end_x[counter_move],
                                     end_y[counter_move], player);

                            if (level % 2 == 0)
                            {
                                value[counter_move] = minimax(map, level + 1, depth, (player * 2) % 3,
                                                                   current_player);

                                bestMove = ((bestMove < value[counter_move]) ? bestMove : value[counter_move]);

                                value[counter_move] = bestMove;
                            }

                            else
                            {
                                value[counter_move] = minimax(map, level + 1, depth, (player * 2) % 3,
                                                                   current_player);

                                bestMove = ((bestMove > value[counter_move]) ? bestMove : value[counter_move]);

                                value[counter_move] = bestMove;

                            }
                            for (int t1 = 0; t1 < map_height; t1++)
                            {
                                for (int t2 = 0; t2 < map_width; t2++)
                                {
                                    map[t1][t2] = copy[t1][t2];
                                }
                            }
                            counter_move++;
                        }
                    }
                }
            }
        }

        if (level != 1)
        {
            return bestMove;
        }

        if (i == map_height)
        {
            int max_value = value[0], max_index = 0;
            for (int k = 1; k < counter_move; k++)
            {
                if (max_value < value[k])
                {
                    max_value = value[k];
                    max_index = k;
                }
            }
            moveChip(map, begin_x[max_index], begin_y[max_index], end_x[max_index], end_y[max_index], player);
            printBoard(map);
        }
    }
}



int computerMove(char* map[], int level, int depth, int player,
                 int current_player, int alpha, int beta) {

    char copy[map_height][map_width];

    const int all_move = 1100;

    const int amount_move = 18;

    int begin_x[all_move];

    int begin_y[all_move];

    int end_x[all_move];

    int end_y[all_move];

    int value[all_move];

    int counter_move = 0, i, j, optimal;

    if (level % 2 == 0)
    {
        optimal = infinity;
    }
    else
    {
        optimal = -infinity;
    }

    for (i = 0; i < map_height; i++)
    {
        for (j = 0; j < map_width; j++)
        {
            copy[i][j] = map[i][j];
        }
    }

    if (level > depth)
    {
        return moveEvaluation(map, current_player);
    }

    else
    {
        for (i = 0; i < map_height; i++)
        {
            for (j = 0; j < map_width; j++)
            {
                if (isValidSelection(map, i, j, player))
                {
                    for (int k = 0; k < amount_move; k++)
                    {
                        if (alpha > beta)
                            return optimal;
                        if (isValidMove(map, i, j, i + x[k], j + y[k]))
                        {
                            begin_x[counter_move] = i;

                            begin_y[counter_move] = j;

                            end_x[counter_move] = i + x[k];

                            end_y[counter_move] = j + y[k];

                            moveChip(map, begin_x[counter_move], begin_y[counter_move], end_x[counter_move],
                                     end_y[counter_move], player);

                            if (level % 2 == 0)
                            {
                                value[counter_move] = computerMove(map, level + 1, depth, (player * 2) % 3,
                                                                   current_player, alpha, beta);

                                optimal = ((optimal < value[counter_move]) ? optimal : value[counter_move]);

                                value[counter_move] = optimal;

                                beta = ((beta < optimal) ? beta : optimal);
                            }

                            else
                            {
                                value[counter_move] = computerMove(map, level + 1, depth, (player * 2) % 3,
                                                                   current_player, alpha, beta);

                                optimal = ((optimal > value[counter_move]) ? optimal : value[counter_move]);

                                value[counter_move] = optimal;

                                alpha = ((alpha > optimal) ? alpha : optimal);

                            }
                            for (int t1 = 0; t1 < map_height; t1++)
                            {
                                for (int t2 = 0; t2 < map_width; t2++)
                                {
                                    map[t1][t2] = copy[t1][t2];
                                }
                            }
                            counter_move++;
                        }
                    }
                }
            }
        }

        if (level != 1)
        {
            return optimal;
        }

        if (i == map_height)
        {
            int max_value = value[0], max_index = 0;
            for (int k = 1; k < counter_move; k++)
            {
                if (max_value < value[k])
                {
                    max_value = value[k];
                    max_index = k;
                }
            }
            moveChip(map, begin_x[max_index], begin_y[max_index], end_x[max_index], end_y[max_index], player);
            printBoard(map);
        }
    }
}
