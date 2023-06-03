#include "hexagon.h"
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    char *map[map_height];
    int mode;
    ifstream input_file("../layout.txt");

    if (!input_file) {
        cout << "Printing layout" << endl;
        createLayout(map);
    }
    else {
        cout << "Loading layout from file" << endl;
        loadLayout(map, input_file);
    }
    cout << "Play mode:\n	1 - Player VS Player\n	2 - Player VS Computer\n	3 - Computer VS Computer\n";
    cout << "Input play mode: ";
    cin >> mode;
    // Начинается игра
    gameLogic(map, mode);

    input_file.close();

    for (int i = 0; i < map_height; i++)
        delete[] map[i];
    return 0;
}
// Загрузка файла
void loadLayout(char **field, ifstream& file)
{
    for (int i = 0; i < map_height; i++)
    {
        field[i] = new char[map_width];
    }

    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            field[i][j] = file.get();
        }
        file.get();
    }
}

void createLayout(char **board) {
    board[0] = "....1....";
    board[1] = "...0.0...";
    board[2] = "..0.0.0..";
    board[3] = ".0.0.0.0.";
    board[4] = "2.0.0.0.2";
    board[5] = ".0.0.0.0.";
    board[6] = "0.0...0.0";
    board[7] = ".0.0.0.0.";
    board[8] = "0.0.0.0.0";
    board[9] = ".0.....0.";
    board[10] = "0.0.0.0.0";
    board[11] = ".0.0.0.0.";
    board[12] = "1.0.0.0.1";
    board[13] = ".0.0.0.0.";
    board[14] = "..0.0.0..";
    board[15] = "...0.0...";
    board[16] = "....2....";
}