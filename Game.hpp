#ifndef GAME_HPP
#define GANE_HPP

#include <iostream>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;


class Game{
private:
    char tablero[FILAS][COLUMNAS];

public:
    void generarTablero();
    void verTablero();
    void dropFigura(int,char);
    bool checkWin(char);
    bool isValidMove(int);
    bool isValidMove(int col, char tablero[FILAS][COLUMNAS]) {
    return tablero[0][col] == ' '; // Verifica si la fila superior de la columna está vacía
    }
    bool tableroFull();

    void getTablero(char destino[FILAS][COLUMNAS]) {
        for (int i = 0; i < FILAS; ++i) {
            for (int j = 0; j < COLUMNAS; ++j) {
                destino[i][j] = tablero[i][j];
            }
        }
    }

    bool isGameFinished();

    void undoMove(int);



};


#endif // GAME_HPP