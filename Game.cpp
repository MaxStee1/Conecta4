#include "Game.hpp"

void Game::generarTablero(){
    for(int i =0; i< FILAS; ++i){
        for(int j=0; j<COLUMNAS; ++j){
            this -> tablero[i][j] = ' ';
        }
    }
}

void Game::verTablero(){
    cout << " 1 2 3 4 5 6 7 " << endl;
    for(int i=0; i<FILAS; ++i){
        cout << "|";
        for(int j=0; j < COLUMNAS; j++){
            cout << tablero[i][j] << "|";
        }
        cout << endl;
    }
    cout << "___________________" << endl;
}

void Game::dropFigura(int col, char figura){
    for(int i = FILAS - 1; i >= 0; --i ){
        if(tablero[i][col] == ' '){
            tablero[i][col] = figura;
            break;
        }
    }
}

bool Game::isValidMove(int col){
    return col >= 0 && col < COLUMNAS && tablero[0][col] == ' ';
}


bool Game::checkWin(char figura){
    // Check horizontal
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == figura &&
                tablero[i][j + 1] == figura &&
                tablero[i][j + 2] == figura &&
                tablero[i][j + 3] == figura) {
                return true;
            }
        }
    }

    // Check vertical
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero[i][j] == figura &&
                tablero[i + 1][j] == figura &&
                tablero[i + 2][j] == figura &&
                tablero[i + 3][j] == figura) {
                return true;
            }
        }
    }

    // Check diagonal (from bottom-left to top-right)
    for (int i = 3; i < FILAS; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == figura &&
                tablero[i - 1][j + 1] == figura &&
                tablero[i - 2][j + 2] == figura &&
                tablero[i - 3][j + 3] == figura) {
                return true;
            }
        }
    }

    // Check diagonal (from top-left to bottom-right)
    for (int i = 0; i <= FILAS - 4; ++i) {
        for (int j = 0; j <= COLUMNAS - 4; ++j) {
            if (tablero[i][j] == figura &&
                tablero[i + 1][j + 1] == figura &&
                tablero[i + 2][j + 2] == figura &&
                tablero[i + 3][j + 3] == figura) {
                return true;
            }
        }
    }
    return false;
}

bool Game::tableroFull(){
    for (int i = 0; i < COLUMNAS; ++i) {
        if (isValidMove(i)) {
            return false;
        }
    }
    return true;
}

bool Game::isGameFinished() {
    // Verifica si algún jugador ha ganado
        if (checkWin('O') || checkWin('X')) {
            return true;
        }

    // Verifica si el tablero está lleno, lo que resulta en un empate
        return tableroFull();
}

void Game::undoMove(int col) {
    // Encuentra la fila en la que se colocó la última ficha en la columna 'col'
    int fila = -1;
    for (int i = 0; i < FILAS; ++i) {
        if (tablero[i][col] != ' ') {
            fila = i;
            break;
        }
    }

    // Si la columna no estaba vacía, deshacer el movimiento
    if (fila != -1) {
        tablero[fila][col] = ' ';
    }
}