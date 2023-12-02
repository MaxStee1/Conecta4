#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;
char tablero[FILAS][COLUMNAS];
fstream MyFile;


class Nodo{
    char tablero[FILAS][COLUMNAS];
    int moveColumn;
    Nodo* hijo[COLUMNAS];
};

void crearTablero(){
    for(int i =0; i< FILAS; ++i){
        for(int j=0; j<COLUMNAS; ++j){
            tablero[i][j] = ' ';
        }
    }
}

void verTablero(){
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


void dropFigura(int col, char figura){
    for(int i = FILAS - 1; i >= 0; --i ){
        if(tablero[i][col] == ' '){
            tablero[i][col] = figura;
            break;
        }
    }
}

bool isValidMove(int col) {
    return col >= 0 && col < COLUMNAS && tablero[0][col] == ' ';
}

bool isValidMove(int col, char tablero[FILAS][COLUMNAS]) {
    return tablero[0][col] == ' '; // Verifica si la fila superior de la columna está vacía
}

void copiarTablero(char origen[FILAS][COLUMNAS], char destino[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            destino[i][j] = origen[i][j];
        }
    }
}

bool checkWin(char figura) {
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

bool tableroFull() {
    for (int i = 0; i < COLUMNAS; ++i) {
        if (isValidMove(i)) {
            return false;
        }
    }
    return true;
}

void playerMove() {
    int col;
    bool validMove = false;

    while (!validMove) {
        cout << "Player X, choose a column (1-7): ";
        cin >> col;
        col--; // Adjust to array index

        if (isValidMove(col)) {
            dropFigura(col, 'X');
            verTablero();
            validMove = true;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

void IAmodeFacil(){
    int movimiento = 0;
    bool move = false;

    while(move == false){
        if(isValidMove(movimiento)){
            dropFigura(movimiento,'O');
            cout << "IA move: "<< movimiento + 1 << endl;
            verTablero();
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

void IAmodeNormal(){
    int movimiento = random();
    bool move = false;
    while(move == false){
        if(isValidMove(movimiento)){
            dropFigura(movimiento,'O');
            cout << "Movimiento IA: " << movimiento+1 << endl;
            verTablero();
            move = true;
        }else{
            movimiento = random();
        }
    }
}

bool dropFicha(int col, char figura, char tablero[FILAS][COLUMNAS]) {
    for (int i = FILAS - 1; i >= 0; --i) {
        if (tablero[i][col] == ' ') {
            tablero[i][col] = figura;
            return true; // Indica que se pudo colocar la ficha en la columna
        }
    }
    return false; // Si la columna está llena y no se pudo colocar la ficha
}


int evaluarTablero(char tablero[FILAS][COLUMNAS], char figura) {
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

int minimax(char tablero[FILAS][COLUMNAS], int depth, bool maximizingPlayer, int alpha, int beta, char figura) {
    if (depth == 0 || checkWin('X') || checkWin('O') || tableroFull()) {
        return evaluarTablero(tablero, figura);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int col = 0; col < COLUMNAS; ++col) {
            if (isValidMove(col)) {
                char tempTablero[FILAS][COLUMNAS];
                copiarTablero(tablero, tempTablero);
                dropFicha(col, figura, tempTablero);
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
            if (isValidMove(col)) {
                char tempTablero[FILAS][COLUMNAS];
                copiarTablero(tablero, tempTablero);
                dropFicha(col, figura, tempTablero);
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

void IAmodeDificil() {
    int bestScore = INT_MIN;
    int bestMove = -1;

    for (int col = 0; col < COLUMNAS; ++col) {
        if (isValidMove(col, tablero)) {
            char tempTablero[FILAS][COLUMNAS];
            copiarTablero(tablero, tempTablero);
            dropFicha(col, 'O', tempTablero); // Usa tempTablero aquí
            int score = minimax(tempTablero, 6, false, INT_MIN, INT_MAX, 'O');
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    }

    if (bestMove != -1) {
        dropFicha(bestMove, 'O', tablero); // Actualiza el tablero original con el mejor movimiento
        cout << "IA move: " << bestMove + 1 << endl;
        verTablero();
    }
}

void IAmove(int dificultad){
    switch (dificultad)
    {
    case 1:
        IAmodeFacil();
        break;
    
    case 2:
        IAmodeNormal();
        break;

    case 3:
        IAmodeDificil();
        break;
    
    default:
        cout << "La dificultad seleccionada no existe";
        break;
    }
}

struct GameResult {
    string winner;
    int playerScore;
    int computerScore;
    string finalBoardState;
};

void guardarPartida(GameResult resultado) {
    ofstream archivo("partidas.csv", ios::app); // Abre el archivo en modo de escritura al final del archivo

    archivo << resultado.winner << "," << resultado.playerScore << "," << resultado.computerScore << endl;

    // Almacena el estado final del tablero en un formato legible en el archivo CSV
    archivo << "|";
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            archivo << tablero[i][j] << "|";
        }
        archivo << endl << "|";
    }
    archivo << endl;

    archivo.close();
}

void consultarPuntuacion() {
    ifstream archivo("partidas.csv");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de partidas." << endl;
        return;
    }

    int jugadorScore = 0;
    int maquinaScore = 0;
    string linea;
    string jugadorTag = "Jugador";
    string maquinaTag = "Maquina";

    // Lee cada línea del archivo CSV
    while (getline(archivo, linea)) {
        if (linea.find(jugadorTag) != string::npos) {
            jugadorScore++;
        } else if (linea.find(maquinaTag) != string::npos) {
            maquinaScore++;
        }
    }

    archivo.close();

    // Muestra la puntuación acumulada del jugador y la máquina
    cout << "Puntuacion acumulada - Jugador: " << jugadorScore << " | Maquina: " << maquinaScore << endl;
}



void juego(int dificultad){
    int playerScore = 0;
    int computerScore = 0;
    bool gameOver = false;
    bool playerTurn = true;

    crearTablero();
    verTablero();

    GameResult resultado;
    resultado.finalBoardState = ""; // Inicializa el estado final del tablero como una cadena vacía

    while(!gameOver){
        
        //turno del jugador
        playerMove();
        if (checkWin('X')) {
            cout << "Player X wins!" << endl;
            gameOver = true;
            playerScore++;
            resultado.winner = "Jugador";
            break;
        }

        if (tableroFull()) {
            cout << "Es un empate!" << endl;
            gameOver = true;
            break;
        }
    
        //turno del sistema
        IAmove(dificultad);

        if(checkWin('O')){
            cout<<"IA wins!" << endl;
            gameOver = true;
            computerScore++;
            resultado.winner = "Maquina";
            break;
        }
        if (tableroFull()) {
            cout << "Es un empate!" << endl;
            gameOver = true;
            break;
        }
        
        playerTurn = !playerTurn;
    }

    cout << "Puntuacion: Jugador - " << playerScore << " | Maquina - " << computerScore << endl;

    resultado.playerScore = playerScore;
    resultado.computerScore = computerScore;
    // Guardar el resultado del juego en el archivo CSV
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            resultado.finalBoardState += tablero[i][j];
        }
    }
    guardarPartida(resultado);
    cout << "juegoFinalizado" << endl;
}

int main() {
    int dificultad;
    int opcion;
    cout<<" ** CONECTA 4 ** " << endl;
    cout<<"[1] jugar"<<endl;
    cout<<"[2] Ver Puntuacion"<<endl;
    cout<<" -> ";
    cin >> opcion;

    if(opcion == 1){

    cout<<"seleciona un modo de juego: "<<endl;
    cout<<"[1] Facil"<<endl;
    cout<<"[2] Normal"<<endl;
    cout<<"[3] Dificil"<<endl; 
    cout <<" -> ";
    cin >> dificultad;

    bool game = true;
    string again;
    while(game){
        juego(dificultad);
        cout << "Desea jugar nuevamente?"<<endl;
        cout << "[si]"<< "[no]" << endl;
        cin >> again;
        if(again == "no"){
            game = false;
        }else{
            cout<<"seleciona un modo de juego: "<<endl;
            cout<<"[1] Facil"<<endl;
            cout<<"[2] Normal"<<endl;
            cout<<"[3] Dificil"<<endl; 
            cout <<" -> ";
            cin >> dificultad;
        }
    }
    
    }else if (opcion == 2){
        consultarPuntuacion();
    }
    

    return 0;
}