#ifndef H_HEXAGON
#define H_HEXAGON

#include <iostream>
#include <fstream>

using namespace std;

const int map_width = 9;
const int map_height = 17;
const int infinity = 100;

/**
* Load board layout from file - Загружает игровое поле из файла
* @param **board - game board (map[])
* @param file - file pinter that contains layout
*/
void loadLayout(char **board, ifstream& file);

/**
* Create game board layout - Создает игровое поле
* @param **board - game board (map[])
*/
void createLayout(char **board);

/**
* Get user's operating system - Выдает имя пользовательской операционной системы
*/
string getOSName();

/**
* Check game winner - Проверяет есть ли победитель в игре
* @param **board - game board (map[])
* @param mode - game mode
*/
void winnerCheck(char **board, int mode);

/**
* Initial game logic - Игровая логика
* @param **board - game board (map[])
* @param mode - game mode
*/
void gameLogic(char **board, int mode);

/**
* Print game board - выводит игровое поле на консоль
* @param **board - game board (map[])
*/
void printBoard(char **board);

/**
* Highlight selected cell - Выделяет выбранную фишку
* @param **board - game board (map[])
* @param x - X coordinate of the cell
* @param y - Y coordinate of the cell
*/
void highlightCellSelection(char **board, int x, int y);

/**
* Check if the cell selection is valid - Проверяет возможно ли выбрать клетку
* @param **board - game board (map[])
* @param x - X coordinate of the cell
* @param y - Y coordinate of the cell
* @param player - current player
* @return true - if selected cell is valid player's cell, 0 - if selected cell is not player's cell
*/
bool isValidSelection(char **board, int x, int y, int player);

/**
* Check if the move is valid - Проверяет возможно ли сходить в клетку
* @param **board - game board (map[])
* @param x2 - end X coordinate of the cell
* @param y2 - end Y coordinate of the cell
* @param x1 - initial X coordinate of the cell
* @param y1 - initial Y coordinate of the cell
* @return true - if valid move, false - if invalid move
*/
bool isValidMove(char **board, int x1, int y1, int x2, int y2);

/**
* Perform chip move of specified player - Передвигает фишку
* @param **board - game board (map[])
* @param x2 - end X coordinate of the cell
* @param y2 - end Y coordinate of the cell
* @param x1 - initial X coordinate of the cell
* @param y1 - initial Y coordinate of the cell
* @param player - current player
*/
void moveChip(char **board, int x1, int y1, int x2, int y2, int player);

/**
* Perform player's move - Осуществляет ход игрока
* @param **board - game board (map[])
 * @param current_player - player with current turn
*/
void playerMove(char **board, int current_player);

/**
* Check if there are possible moves for specified player - Проверяет есть ли возможные ходы у игрока
* @param **board - game board (map[])
* @param player - current player
* @return true - if there are moves that can be performed by player, false - if there are no moves that can be performed by the player
*/
bool generateMoves(char **board, int player);

/**
* Get specific player's score - Выдает очки игрока (количество фишек)
* @param **board - game board (map[])
* @param player - specific player
* @return score of the player
*/
int getScore(char **board, int player);

/**
* Get score difference - Выдает разницу между количеством фишек двух игроков (оценочная функция)
* @param **board - game board (map[])
* @param current_player - player with current turn
* @return score of the player
*/
int moveEvaluation(char** board, int current_player);

/**
* Move computer chip - Осуществляет ход компьютера (оптимизированная функция минимакса)
* @param **board - game board (map[])
* @param level - current level in the tree
* @param depth - search depth
* @param player - the one who's turn
* @param current_player - current player
* @param alpha - current maximum "alpha"
* @param beta - current minimum "beta"
* @return evaluation function of the current move
*/
int computerMove(char *map[], int level, int depth, int player,
                 int current_player, int alpha, int beta);

/**
* Move computer chip - Осуществляет ход компьютера (функция минимакса)
* @param **board - game board (map[])
* @param level - current level in the tree
* @param depth - search depth
* @param player - the one who's turn
* @param current_player - current player
* @return evaluation function of the current move
*/
int minimax(char *map[], int level, int depth, int player,
                 int current_player);

#endif
