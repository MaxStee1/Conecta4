#include "Turnos.cpp"
#include <fstream>

struct GameResult {
    string winner;
    int playerScore;
    int computerScore;
    string finalBoardState;
};

void guardarPartida(GameResult resultado, char tablero[FILAS][COLUMNAS]) {
    ofstream archivo("partidas.csv", ios::app); // Abre el archivo en modo de escritura al final del archivo

    archivo << resultado.winner <<endl;

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

void IAmove(int dificultad, Game* partida){
    switch (dificultad)
    {
    case 1:
        IAmodeFacil(partida);
        break;
    
    case 2:
        IAmodeNormal(partida);
        break;

    case 3:
        IAmodeDificil(partida);
        break;
    
    default:
        cout << "La dificultad seleccionada no existe";
        break;
    }
}

void juego(int dificultad,Game* partida, int& playerScore, int& computerScore){
    bool gameOver = false;
    bool playerTurn = true;
    partida -> generarTablero();
    partida -> verTablero();
    //crearTablero();
    //verTablero();

    GameResult resultado;
    resultado.finalBoardState = ""; // Inicializa el estado final del tablero como una cadena vacía

    while(!gameOver){
        
        //turno del jugador
        playerMove(partida);
        if (partida -> checkWin('X')) {
            cout << "Player X wins!" << endl;
            gameOver = true;
            playerScore++;
            resultado.winner = "Jugador";
            break;
        }

        if (partida -> tableroFull()) {
            cout << "Es un empate!" << endl;
            gameOver = true;
            break;
        }
    
        //turno del sistema
        IAmove(dificultad,partida);

        if(partida -> checkWin('O')){
            cout<<"IA wins!" << endl;
            gameOver = true;
            computerScore++;
            resultado.winner = "Maquina";
            break;
        }
        if (partida -> tableroFull()) {
            cout << "Es un empate!" << endl;
            gameOver = true;
            break;
        }
        
        playerTurn = !playerTurn;
    }

    cout << "Puntuacion: Jugador - " << playerScore << " | Maquina - " << computerScore << endl;

    char tablero[FILAS][COLUMNAS]; 
    partida -> getTablero(tablero);
    //resultado.playerScore = playerScore;
    //resultado.computerScore = computerScore;
    // Guardar el resultado del juego en el archivo CSV
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            resultado.finalBoardState += tablero[i][j];
        }
    }
    guardarPartida(resultado,tablero);
    cout << "juegoFinalizado" << endl;
}

int main(){
    int playerScore = 0;
    int computerScore = 0;

    Game* partida = new Game();
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
    int again;
    while(game){
        juego(dificultad, partida, playerScore,computerScore);
        cout << "\nQue desea hacer: "<<endl;
        cout << "[1] Jugar nuevamente"<< endl <<"[2] Ver puntuacion" << endl << "[3] Salir"<<endl<<" -> ";
        cin >> again;
        if(again == 3){
            game = false;
        }else if(again == 1){
            cout<<"seleciona un modo de juego: "<<endl;
            cout<<"[1] Facil"<<endl;
            cout<<"[2] Normal"<<endl;
            cout<<"[3] Dificil"<<endl; 
            cout <<" -> ";
            cin >> dificultad;
        }else if(again == 2){
            consultarPuntuacion();    
            game = false;
        }else{
            cout<<"opcion invalida"<<endl;
            break;
        }
    }
    
    }else if (opcion == 2){
        consultarPuntuacion();
    }
    

    return 0;
}
