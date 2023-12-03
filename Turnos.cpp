#include <random>
#include "Game.hpp"


void playerMove(Game* tablero) {
    int col;
    bool validMove = false;

    while (!validMove) {
        cout << "Player X, escoge columna (1-7): ";
        cin >> col;
        col--; // Adjust to array index

        if (tablero -> isValidMove(col)) {
            tablero -> dropFigura(col, 'X');
            tablero -> verTablero();
            validMove = true;
        } else {
            cout << "Movimiento invalido. Try again." << endl;
        }
    }
}

void IAmodeFacil(Game* tablero){
    int movimiento = 0;
    bool move = false;

    while(move == false){
        if(tablero -> isValidMove(movimiento)){
            tablero -> dropFigura(movimiento,'O');
            cout << "IA move: "<< movimiento + 1 << endl;
            tablero -> verTablero();
            move = true;
        }else{
            movimiento++;
        }
    }
}

int random(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 6);
    int random = dis(gen);
    return random;
}

void IAmodeNormal(Game* tablero){
    int movimiento = random();
    bool move = false;
    while(move == false){
        if(tablero -> isValidMove(movimiento)){
            tablero -> dropFigura(movimiento,'O');
            cout << "Movimiento IA: " << movimiento+1 << endl;
            tablero -> verTablero();
            move = true;
        }else{
            movimiento = random();
        }
    }
}


int evaluarTablero(Game* t, char figura) {
    char tablero[FILAS][COLUMNAS];
    t ->getTablero(tablero);
    // Función de evaluación simple: cuenta la cantidad de fichas en línea para la figura dada (X u O)
    int score = 0;

    // Evaluar horizontalmente
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            int count = 0;
            for (int k = 0; k < 4; ++k) {
                if (tablero[i][j + k] == figura) {
                    count++;
                }
            }
            if (count == 4) {
                score += figura == 'X' ? 100 : -100;
            } else if (count == 3 && j > 0 && j < COLUMNAS - 4) {
                if (tablero[i][j - 1] == ' ' && tablero[i][j + 3] == ' ') {
                    score += figura == 'X' ? 5 : -5;
                }
            }
        }
    }

    // Evaluar verticalmente
    for (int j = 0; j < COLUMNAS; ++j) {
        for (int i = 0; i <= FILAS - 4; ++i) {
            int count = 0;
            for (int k = 0; k < 4; ++k) {
                if (tablero[i + k][j] == figura) {
                    count++;
                }
            }
            if (count == 4) {
                score += figura == 'X' ? 100 : -100;
            }
        }
    }

    // Evaluar diagonales
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            int count = 0;
            for (int k = 0; k < 4; ++k) {
                if (tablero[i + k][j + k] == figura) {
                    count++;
                }
            }
            if (count == 4) {
                score += figura == 'X' ? 100 : -100;
            }
        }
    }

    return score;
}

int minimax(Game* tablero, int depth, bool maximizingPlayer, int alpha, int beta, char figura) {
    if (depth == 0 || tablero -> checkWin('X') || tablero -> checkWin('O') || tablero -> tableroFull()) {
        return evaluarTablero(tablero, figura);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int col = 0; col < COLUMNAS; ++col) {
            if (tablero -> isValidMove(col)) {
                Game* tempTablero = new Game(*tablero);
                tempTablero -> dropFigura(col, figura);
                int eval = minimax(tempTablero, depth - 1, false, alpha, beta, figura);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int col = 0; col < COLUMNAS; ++col) {
            if (tablero -> isValidMove(col)) {
                Game* tempTablero = new Game(*tablero);
                tempTablero -> dropFigura(col, figura);
                int eval = minimax(tempTablero, depth - 1, true, alpha, beta, figura);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}



void IAmodeDificil(Game* tablero) {
    cout<<"pensando la mejor jugada ..."<<endl;
    int bestScore = INT_MIN;
    int bestMove = -1;
    char tableroCopia [FILAS][COLUMNAS];
    tablero ->getTablero(tableroCopia); 

    // Verificar si el oponente ('X') está a punto de ganar y bloquear su jugada
    for (int col = 0; col < COLUMNAS; ++col) {
        if (tablero->isValidMove(col, tableroCopia)) {
            Game* tempTablero = new Game(*tablero);
            tempTablero->dropFigura(col, 'X'); // Simular movimiento del oponente ('X')
            if (tempTablero->checkWin('X')) { // Si el oponente tiene una jugada ganadora
                tablero->dropFigura(col, 'O'); // Bloquear el movimiento del oponente
                cout << "IA move: " << col + 1 << endl;
                tablero->verTablero();
                return; // Terminar la función después de bloquear
            }
            delete tempTablero;
        }
    } 

    for (int col = 0; col < COLUMNAS; ++col) {
        if (tablero -> isValidMove(col,tableroCopia)) {
            Game* tempTablero = new Game(*tablero);
            tempTablero -> dropFigura(col, 'A');// Usar tempTablero 
            int score = minimax(tempTablero, 6, false, INT_MIN, INT_MAX, 'O');
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    }

    if (bestMove != -1) {
        tablero -> dropFigura(bestMove, 'O'); // Actualizar el tablero original con el mejor movimiento
        cout << "IA move: " << bestMove + 1 << endl;
        tablero -> verTablero();
    }
}
