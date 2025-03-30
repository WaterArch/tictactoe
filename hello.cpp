#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdlib>

std::string ans;
char roles[2] = {'x', 'o'};
char playerRole;
char botRole;
int roleIndex;
bool bot = true;
bool checkWin(char player, char board[3][3]);
int score;
bool isDraw;
char turn;
int row;
int col;
char lett;
double bestScore = 0;

char x[3][3] = {{' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}};

char botBoard[3][3];

struct Move {
    int row;
    int col;
    double score;
};
std::vector<Move> possibleMoves;
std::vector<Move> bestMoves;
Move botMove;

void checkPossibleMoves();
void chooseMove();

int main(){

    srand(time(NULL));

    roleIndex = rand() % 2;
    playerRole = roles[roleIndex];
    botRole = roles[!(roleIndex)];
    std::cout << playerRole << botRole << '\n';
    roleIndex = 0;
    while (true) {

        // Board Layout
        std::cout << "****************************\n";
        std::cout << "         |         |        \n";
        std::cout << "    " << x[0][0] << "    |    " << x[0][1] << "    |    " << x[0][2] << std::endl;
        std::cout << "         |         |        \n";
        std::cout << "----------------------------\n";
        std::cout << "         |         |        \n";
        std::cout << "    " << x[1][0] << "    |    " << x[1][1] << "    |    " << x[1][2] << std::endl;
        std::cout << "         |         |        \n";
        std::cout << "----------------------------\n";
        std::cout << "         |         |        \n";
        std::cout << "    " << x[2][0] << "    |    " << x[2][1] << "    |    " << x[2][2] << std::endl;
        std::cout << "         |         |        \n";
        std::cout << "****************************\n";

        checkPossibleMoves();

        turn = roles[roleIndex];

        //Check for 3 in a rows
        if (checkWin('x', x)){
            std::cout << "Player X won!";
            break;
        } 
        else if (checkWin('o', x)){
            std::cout << "Player O won!";
            break;
        }else {
            isDraw = true;
            for (int r = 0; r < 3; r++){
                for (int c = 0; c < 3; c++){
                    if (x[r][c] == ' '){
                        isDraw = false;
                        break;
                    }
                }
            }

            if (isDraw){
                std::cout << "It's a draw!";
                break;
            }
        }


        //Place Turn
        if (turn == playerRole) {
            std::cin >> ans;
            if (ans == "end"){
                break;
            }
            row = (stoi(ans) / 10);
            col = (stoi(ans) % 10);
            if (x[row][col] == ' '){
                x[row][col] = turn;
                roleIndex = !roleIndex;
            }else {
                std::cout << "Invalid Move" << "\n";
                break;
            }
            
                 
        }
        else if (turn == botRole){
            std::cout << "Size: " << possibleMoves.size() << '\n';
            chooseMove();
            row = botMove.row;
            col = botMove.col;
            std::cout << row << " " << col << '\n';

            x[row][col] = turn;
            roleIndex = !roleIndex;
        }
    }

    return 0;
}

bool checkWin(char player, char board[3][3]){

    for (int r = 0; r < 3; r++){
        if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2] && board[r][2] == player){
            return true;
        }
        if (board[0][r] != ' ' && board[0][r] == board[1][r] && board[1][r] == board[2][r] && board[2][r] == player){
            return true;
        }
    };  

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == player ||
        board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] == player){
            return true;
    }
    return false;
}

void checkPossibleMoves(){
    possibleMoves = {};
    memcpy(botBoard, x, sizeof(x));
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (x[i][j] == ' '){
                possibleMoves.push_back({i, j});
            }
        }

    }
}

void chooseMove() {
    bestMoves = {};
    bestScore = 0;
    for (auto &move : possibleMoves){
        botBoard[move.row][move.col] = botRole;
        if (checkWin(botRole, botBoard)){
            move.score += 100;
        }
        if (move.row == 1 && move.col == 1 ){
            move.score += 5;
        }
        if ((move.row == 0 || move.row == 2) && (move.col == 0 || move.col == 2)){
            if (botBoard[1][1] == playerRole){
                move.score += 1;
            }
            move.score += 1;
        }else if (!(move.row == 1 && move.col == 11)){
            move.score += 1;
        }
        memcpy(botBoard, x, sizeof(x));

        botBoard[move.row][move.col] = playerRole;
        if (checkWin(playerRole, botBoard)){
            move.score += 50;
        }

        memcpy(botBoard, x, sizeof(x));
    }

    for (auto &move : possibleMoves){
        if (move.score > bestScore){
            bestScore = move.score;
            bestMoves = {move};
        }else if (move.score == bestScore){
            bestMoves.push_back(move);
        }
    }

    botMove = bestMoves[rand() % bestMoves.size()];
}
