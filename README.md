# Conecta 4
### En este codigo se dearrolla el juego conecta 4 en el cual puedes seleccionar la dificultad de la IA

Para compilar este codigo escribo el siguiente comando
g++ -o main.exe main.cpp Game.cpp

Para ejecutarlo
.\main.exe


<p>
En este codigo simpre comienza el jugador, luego va la maquina
</p>

- El jugador es representado por('X') dentro del tablero
- La maquina es representada por('O')


<p>
Puedes elegir entre tres modos de dificultad de la IA:
</p>

- Modo facil: la maquina solo va llenando las columnas
- Modo Normal: la maquina elige columnas al azar, lo que te puede complicar
- Modo Dificl: En este caso, la IA primero ve si el jugador esta a punto de ganar, si no es asi, utiliza minimax para escoger la mejor jugada


** Función evaluarTablero(Game* t, char figura) **

Evalua el estado actual del tablero y calcula una puntuación basada en la cantidad de fichas en línea para una figura dada ('X' o 'O') en filas, columnas y diagonales.


** Función minimax(Game* tablero, int depth, bool maximizingPlayer, int alpha, int beta, char figura) **

Analiza posibles movimientos de jugadores en profundidad limitada y evalúa el tablero resultante.
Utiliza la función evaluarTablero() para asignar una puntuación a cada estado del tablero.
Implementa la poda alfa-beta para reducir la cantidad de nodos evaluados y mejorar la eficiencia del algoritmo minimax.


** Función IAmodeDificil(Game* tablero) **

Es la lógica de la inteligencia artificial para el modo de dificultad difícil.
Primero verifica si el oponente ('X') tiene una jugada ganadora y trata de bloquearla si es posible.
Utiliza el algoritmo minimax para determinar el mejor movimiento posible para la IA ('O') con una profundidad de búsqueda de 6 niveles (este número puede variar dependiendo de la complejidad deseada).
Selecciona el mejor movimiento posible para la IA y actualiza el tablero con esta jugada.



------------

El resultado se guarda dentro del archivo "partidas.csv" de la siguiente manera

GANADOR(JUGADOR / MAQUINA)
matriz resultante
|
GANADOR(JUGADOR / MAQUINA)
matriz resultante
|
