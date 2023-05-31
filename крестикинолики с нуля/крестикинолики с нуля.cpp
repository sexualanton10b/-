#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;
void boardDrawing(string Name1, string Name2, char boardData[10]) {
    system("cls"); // очищаем консоль
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n\n\tКрестики-Нолики\n";
    cout << Name1 << " (X)  ||  " << Name2 << " (О)" << endl;
    cout << endl;
    cout << "__________________ " << endl;
    cout << "|     |     |     |" << endl;
    cout << "|  ";
    if (boardData[1] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[1] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[1]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[2] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[2] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[2]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[3] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[3] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[3]; SetConsoleTextAttribute(hConsole, 7); cout << "  |" << endl;
    cout << "|_____|_____|_____|" << endl;
    cout << "|     |     |     |" << endl;
    cout << "|  ";
    if (boardData[4] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[4] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[4]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[5] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[5] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[5]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[6] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[6] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[6]; SetConsoleTextAttribute(hConsole, 7); cout << "  |" << endl;
    cout << "|_____|_____|_____|" << endl;
    cout << "|     |     |     |" << endl;
    cout << "|  ";
    if (boardData[7] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[7] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[7]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[8] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[8] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[8]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (boardData[9] == 'X') SetConsoleTextAttribute(hConsole, 4); if (boardData[9] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << boardData[9]; SetConsoleTextAttribute(hConsole, 7); cout << "  |" << endl;
    cout << "|_____|_____|_____|" << endl << endl;
}
int checkWin(char board[10]) {
    if (board[1] == board[2] && board[2] == board[3])
        return 1;
    else if (board[4] == board[5] && board[5] == board[6])
        return 1;
    else if (board[7] == board[8] && board[8] == board[9])
        return 1;
    else if (board[1] == board[4] && board[4] == board[7])
        return 1;
    else if (board[2] == board[5] && board[5] == board[8])
        return 1;
    else if (board[3] == board[6] && board[6] == board[9])
        return 1;
    else if (board[1] == board[5] && board[5] == board[9])
        return 1;
    else if (board[3] == board[5] && board[5] == board[7])
        return 1;
    else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
        board[4] != '4' && board[5] != '5' && board[6] != '6' &&
        board[7] != '7' && board[8] != '8' && board[9] != '9')
        return 0;
    else
        return -1;
}
int choiceNum(int start, int end) {
    char i;
    cin >> i;
    while ((int)i < start || (int)i>end) {
        cout << "Введите корректное значение\n";
        cin >> i;
    }
    return (int)i - 48;
}
int minimax(int count, char board[10]) {
    bool isX = (count % 2 == 0) ? false : true;
    int win; int sum = 0;
    char boardnew[10];
    int max = -100; int min = 100;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            boardnew[j] = board[j];
        }
        if (boardnew[i] != 'X' && boardnew[i] != 'O') {
            boardnew[i] = (isX) ? 'X' : 'O';
            win = checkWin(boardnew);
            if (win == 1) {
                if (isX)
                    return  10;
                else return -10;
            }
            if (win == 0)  return 0;
            if (win == -1) sum = minimax(count++, boardnew);
            if (min > sum) min = sum;
            if (max < sum) max = sum;
        }
    }
    if (isX)
        return min;
    else return max;
    delete[] boardnew;
}
bool isAvailable(char board[10], int choice) {
    if (choice < 1 || choice>9) return false;
    if (board[choice] != 'X' && board[choice] != 'O')
        return true;
    return false;
}
int AImove(int count, char gameBoard[10]) {
    int bestChoiceO = -100;
    int bestChoiceX = -100;
    char board[10];
    int minsum = 1000; int maxsum = -1000;
    if (count == 1) return 5;
    for (int k = 1; k < 10; k++) {
        for (int j = 1; j < 10; j++) {
            board[j] = gameBoard[j];
        }
        if (isAvailable(board, k)) {
            board[k] = (count % 2) ? 'X' : 'O';
            int grade;
            if (checkWin(board) == 1 || checkWin(board) == 0) {
                return k;
            }
            grade = minimax(count + 1, board);
            if (minsum > grade) {
                minsum = grade;
                bestChoiceO = k;
            }
            if (maxsum < grade) {
                maxsum = grade;
                bestChoiceX = k;
            }
        }
    }
    if (count % 2) return bestChoiceX;
    return bestChoiceO;
}
int UserMove(char board[10], string Name) {
    cout << "\n";
    cout << Name << ", выберите число \n";
    int choice = choiceNum(49, 57);
    while (isAvailable(board, choice) == false) {
        cout << "Невозможно совершить ход, повторите \n";
        choice = choiceNum(49, 57);
    }
    return choice;
}
void result(int win, int count, pair<string, int>& Player1, pair<string, int>& Player2, char board[10]) {
    boardDrawing(Player1.first, Player2.first, board);
    if (win == 1) {
        if (count % 2) {
            cout << "*** " << Player1.first << " победил(-а) ***\n";
            Player1.second++;
        }
        else {
            cout << "*** " << Player2.first << " победил(-а) ***\n";
            Player2.second++;
        }
    }
    else cout << "*** Ничья ***\n";
    cout << "   ***Общий счет***\n";
    cout << Player1.first << " - " << Player1.second << "    ||    " << Player2.first << " - " << Player2.second << "\n";
}
int oneGameWithAI(int UserTurn, pair<string, int>& PlayerForX, pair<string, int>& PlayerForO) {
    system("cls");
    int choice; int win = -1;
    int count = 0;
    char mark = (UserTurn == 1) ? 'X' : 'O';
    char AImark = (UserTurn == 1) ? 'O' : 'X';
    char boardData[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    do {
        ++count;
        if (count % 2 == UserTurn) {
            boardDrawing(PlayerForX.first, PlayerForO.first, boardData);
            choice = UserMove(boardData, "Игрок");
            boardData[choice] = mark;
        }
        else {
            int bestChoice = AImove(count, boardData);
            boardData[bestChoice] = AImark;
        }
        win = checkWin(boardData);
    } while (win == -1);
    result(win, count, PlayerForX, PlayerForO, boardData);
    if (count % 2 != UserTurn) cout << "Проиграл ботику? боже, чел, ты кринж" << endl;
    return 1;
}
void swap(pair<string, int>& Player1, pair<string, int>& Player2) {
    pair<string, int> Temp = Player1;
    Player1 = Player2;
    Player2 = Temp;
}
void oneGame2Users(pair<string, int>& PlayerForX, pair<string, int>& PlayerForO) {
    system("cls");
    char boardData[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int win = -1; int choice;
    int count = 0;
    do {
        ++count;
        if (count % 2) {
            boardDrawing(PlayerForX.first, PlayerForO.first, boardData);
            choice = UserMove(boardData, PlayerForX.first);
            boardData[choice] = 'X';
        }
        else {
            boardDrawing(PlayerForX.first, PlayerForO.first, boardData);
            choice = UserMove(boardData, PlayerForO.first);
            boardData[choice] = 'O';
        }
        win = checkWin(boardData);
    } while (win == -1);
    result(win, count, PlayerForX, PlayerForO, boardData);
    delete[] boardData;
}
void boardDrawing5(string Name1, string Name2, char board[26]) {
    system("cls"); // очищаем консоль
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n\n\t  Крестики-Нолики\n";
    cout << "****   " << Name1 << " (X)  ||  " << Name2 << " (О)   ****" << endl;
    cout << endl;
    cout << "     1     2     3     4     5     " << endl;
    cout << "  _______________________________" << endl;
    cout << "  |     |     |     |     |     |" << endl;
    cout << "1 |  "; if (board[1] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[1] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[1]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[2] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[2] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[2]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[3] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[3] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[3]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[4] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[4] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[4]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[5] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[5] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[5]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |" << endl;
    cout << "2 |  "; if (board[6] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[6] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[6]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[7] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[7] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[7]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[8] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[8] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[8]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[9] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[9] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[9]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[10] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[10] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[10]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |" << endl;
    cout << "3 |  "; if (board[11] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[11] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[11]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[12] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[12] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[12]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[13] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[13] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[13]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[14] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[14] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[14]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[15] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[15] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[15]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |" << endl;
    cout << "4 |  "; if (board[16] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[16] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[16]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[17] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[17] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[17]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[18] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[18] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[18]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[19] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[19] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[19]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[20] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[20] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[20]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |" << endl;
    cout << "5 |  "; if (board[21] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[21] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[21]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[22] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[22] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[22]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[23] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[23] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[23]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[24] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[24] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[24]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  ";
    if (board[25] == 'X') SetConsoleTextAttribute(hConsole, 4); if (board[25] == 'O') SetConsoleTextAttribute(hConsole, 1);
    cout << board[25]; SetConsoleTextAttribute(hConsole, 7); cout << "  |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|" << endl;
}
bool isAvailable5(char board[26], int choice) {
    if (choice > 25 || choice < 1) {
        return false;
    }
    if (board[choice] != 'X' && board[choice] != 'O')
        return true;
    return false;
}
int UserMove5(char board[26], string Name) {
    int choice = 0;
    cout << "\n";
    cout << Name << ", выберите клетку (сначала номер ряда, потом номер столбца) \n";
    int i = choiceNum(49, 53);
    int j = choiceNum(49, 53);
    choice = (i - 1) * 5 + j;
    while (isAvailable5(board, choice) == false) {
        cout << "Невозможно совершить ход, повторите \n";
        i = choiceNum(49, 53);
        j = choiceNum(49, 53);
        choice = (i - 1) * 5 + j;
    }
    return choice;
}
int checkWin5(char board[26], int count) {
    char mark = (count % 2) ? 'X' : 'O';
    int num = 0;
    for (int i = 1; i < 3; i++) {// проверка по горизонтали
        for (int j = 0; j < 5; j++) {
            num = i + j * 5;
            if (board[num] == mark) {
                if (board[num] == board[num + 1] && board[num + 1] == board[num + 2] && board[num + 2] == board[num + 3]) return 1;
            }
        }
    }
    for (int j = 0; j < 2; j++) { // проверка по вертикали
        for (int i = 1; i < 6; i++) {
            num = i + j * 5;
            if (board[num] == mark) {
                if (board[num] == board[num + 5] && board[num + 5] == board[num + 10] && board[num + 10] == board[num + 15]) return 1;
            }
        }
    }
    for (int i = 1; i < 3; i++) { //проверка по диагоналям
        for (int j = 0; j < 2; j++) {
            num = i + j * 5;
            if (board[num] == mark)
                if (board[num] == board[num + 6] && board[num + 6] == board[num + 12] && board[num + 12] == board[num + 18]) return 1;
            if (board[num + 3] == mark)
                if (board[num + 3] == board[num + 7] && board[num + 7] == board[num + 11] && board[num + 11] == board[num + 15]) return 1;
        }
    }
    for (int i = 1; i < 26; i++) {
        if (board[i] == ' ') return -1;
    }
    return 0;
}
void result5(int win, int count, pair<string, int>& Player1, pair<string, int>& Player2, char board[26]) {
    boardDrawing5(Player1.first, Player2.first, board);
    if (win == 1) {
        if (count % 2) {
            cout << "*** " << Player1.first << " победил(-а) ***\n";
            Player1.second++;
        }
        else {
            cout << "*** " << Player2.first << " победил(-а) ***\n";
            Player2.second++;
        }
    }
    else cout << "*** Ничья ***\n";
    cout << "   ***Общий счет***\n";
    cout << Player1.first << " - " << Player1.second << "    ||    " << Player2.first << " - " << Player2.second << "\n";
}
void oneGame2Users5(pair<string, int>& PlayerForX, pair<string, int>& PlayerForO) {
    system("cls");
    char boardData[26];
    for (int i = 0; i < 26; i++) {
        boardData[i] = ' ';
    }
    int win = -1; int choice;
    int count = 0;
    do {
        ++count;
        if (count % 2) {
            boardDrawing5(PlayerForX.first, PlayerForO.first, boardData);
            choice = UserMove5(boardData, PlayerForX.first);
            boardData[choice] = 'X';
        }
        else {
            boardDrawing5(PlayerForX.first, PlayerForO.first, boardData);
            choice = UserMove5(boardData, PlayerForO.first);
            boardData[choice] = 'O';
        }
        win = checkWin5(boardData, count);
    } while (win == -1);
    result5(win, count, PlayerForX, PlayerForO, boardData);
}
void Game2Users() {
    system("cls");
    pair<string, int> NameForX = pair<string, int>(".", 0);
    pair<string, int> NameForO = pair<string, int>(".", 0);
    cout << "Введите имя первого игрока: " << endl;
    cin >> NameForX.first;
    cout << "Введите имя второго игрока: " << endl;
    cin >> NameForO.first;
    char play = '1'; char size = '0';
    cout << "Выберите размер поля " << endl;
    cout << "1) 3x3 " << endl;
    cout << "2) 5x5 " << endl;
    do {
        cin >> size;
    } while (size != '1' && size != '2');
    while (play == '1') {
        if (size == '1')
            oneGame2Users(NameForX, NameForO);
        else oneGame2Users5(NameForX, NameForO);
        cout << "\n\n1. Продолжить игру\n2.Поменяться сторонами\nДругой символ - Выйти в главное меню" << endl;
        cin >> play;
        if (play == '2') {
            swap(NameForX, NameForO);
            play = '1';
        }
    }
}
void GameWithAI() {
    system("cls");
    pair<string, int> NameForX = pair<string, int>("Игрок", 0);
    pair<string, int>NameForO = pair<string, int>("Ботик", 0);
    cout << "Выберите сторону\n";
    cout << "[1] - X                 [2] - O\n";
    int turn = choiceNum(49, 50);
    turn = turn % 2;
    char play = '1';
    if (turn == 0) swap(NameForX, NameForO);
    while (play == '1') {
        oneGameWithAI(turn, NameForX, NameForO);
        cout << "\n\n1. Продолжить игру\n2.Поменяться сторонами\nДругой символ - Выйти в главное меню" << endl;
        cin >> play;
        if (play == '2') {
            swap(NameForX, NameForO);
            play = '1';
            turn = (turn + 1) % 2;
        }
    }
}
void cat() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "                                                                        /%%%%%%%                    \n";
    cout << "                                                /%%%%%%%%%%%%%        /%......%%                    \n";
    cout << "                                          /%%%%%,,,,,,,,,,,,,,%%%%%%%%........%%                    \n";
    cout << "                      /%%%%%%%        /%%%,,,,,,,,,,,,,,,,,,,,,,,,**......  ..%%                    \n";
    cout << "                      /%..............****,,,,,,,,,,,,,,,,,,,,,,......      ..%%                    \n";
    cout << "                        /%..        ....,,,,,,,,,,,,,,,,,,,,,,,,....        ..%%                    \n";
    cout << "                        /%....        ..,,,,,,,,,,,,,,,,,,,,,,........      ..%%                    \n";
    cout << "                          /%..      ........,,,,..,,,,,,,,,,..................%%                    \n";
    cout << "                            /%................,,....,,....................,,**..%%          **  **  \n";
    cout << "                            /%**..............,,................................%%            **    \n";
    cout << "                            /%..................................................%%                  \n";
    cout << "                            /%..................................................%%                  \n";
    cout << "                            /%,,....  @@@@@@@@@@  ............  @@@@@@@@  ....,,%%                  \n";
    cout << "                            /%,,......  @@  @@@@  ..........  @@@@  @@  ....,,,,%%      **          \n";
    cout << "                              /%......  @@@@@@@@  ..........  @@@@@@@@  ..,,,,..%%                  \n";
    cout << "                  ,,******    /%,,,,,,..  @@@@@@  ..........  @@@@@@  ,,,,,,..%%                    \n";
    cout << "                ******..  **    /%................        ............,,,,,,,,%%//*///              \n";
    cout << "      ,,******  ******....**    /%,,,,,,........    %%..%%  ................%%  /%////%%            \n";
    cout << "    ,,**********************      /%,,........      ..%%..      ............%%%%((////**%%          \n";
    cout << "    ,,**********************      /%......**        ..%%..        **......%%%%%%((//////((          \n";
    cout << "      ,***//////////////**        /%........,,,,****      ****,,%%  **//((%%**((%%%%**%%            \n";
    cout << "        ,*****////////****      /%..............,,,,******,,,,,,%%****//((((%%%%%%((//**%%          \n";
    cout << "            ******////**,,      /%..................,,,,,,....,,,,%%//////%%((%%,,%%((//**%%        \n";
    cout << "                ,,******        /%..............................,,,,%%////%%((%%,,,,%%((//**((      \n";
    cout << "                              /%..........    ......................,,,,%%//((%%....,,,,%%%%        \n";
    cout << "                              /%,,,,,,................................,,%%//((%%......,,,,,,%%      \n";
    cout << "                              /%,,,,,,,,..............................,,%%//((%%............%%      \n";
    cout << "            ,*                /%......................................,,%%%%%%%%........,,..%%      \n";
    cout << "            ,*        ,,      /%,,,,,,,,............................**..................,,......//  \n";
    cout << "                              /%,,,,,,,,,,,,......**................**................**........%%  \n";
    cout << "                                /%........,,,,....**..............**,,,,,,,,..........**..........%%\n";
    cout << "                                /(..................**  ..........**,,,,,,,,,,,,....**............%%\n";
    cout << "                                    /%,,,,,,..........**        **................**..............%%\n";
    cout << "                                    /%................**        **......,,,,,,,,**................%%\n";
    cout << "                                      /%..........,,,,**//      **..........,,,,**................%%\n";
    cout << "                                      /%..............**..//////..............**................%% \n";
    cout << "                                    //..............**........//..........******..........**..%% \n";
    cout << "                                  /%          ......**........//..              **  **    **%%   \n";
    cout << "                                  /%              ..**..//....//..              **  **    %%        \n";
    cout << "                                  /(  **  **      ((((((((((((((..  **  **  **  ((((((((((          \n";
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Введите любой символ для выхода" << endl;
    cin.ignore();
    cin.get();
}
void heart() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "@@@@@******@@@@@@@******@@@@@@\n";
    cout << "@@*,,,,,,,,,**@**,,,... ,,*@@@\n";
    cout << "@@*,,,,,,,,,,,*,,,,,,,,...*@@@\n";
    cout << "@@*,,,,СПАСИБО ЗА ИГРУ,,,,*@@@\n";
    cout << "@@@**,,,,,,,,,,,,,,,,,,,,,*@@@\n";
    cout << "@@@**,,,,,,,,,,,,,,,,,,,,*@@@@\n";
    cout << "@@@@@*,,,,,,,,,,,,,,,,,*@@@@@@\n";
    cout << "@@@@@@@@*,,,,,,,,,,,*@@@@@@@@@\n";
    cout << "@@@@@@@@@***,,,,,***@@@@@@@@@@\n";
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    SetConsoleTextAttribute(hConsole, 7);
}
void menu() {
    char choice = 'b';
    do
    {
        system("cls"); // очищаем консоль
        cout << "\n\n\tМеню игры Крестики-Нолики\n";
        cout << "1. Режим игры с другом" << endl;
        cout << "2. Режим игры с компьютером" << endl;
        cout << "3. Котик" << endl;
        cout << "4. Выход из игры" << endl;
        cin >> choice;
        if (choice == '1') Game2Users();
        if (choice == '2') GameWithAI();
        if (choice == '3') cat();
        if (choice == '4') heart();
    } while (choice != '4');
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    menu();
    return 0;
}
