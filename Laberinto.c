/* 
- Fecha de publicación: 23/09/2024
- Hora de publicación: 2:36 am
- Versión de su código: 2cd ..0
- Autor. Ing(c): Juan Fernando Cano Duque
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Nombre y versión del Sistema Operativo(S.O) sobre el que compiló y probó los ejecutables: windows 10.0.22631
- Versión del compilador utilizado: Compilado con GCC 6.3.0 (MinGW.org GCC-6.3.0-1)
- Presentado a: Doctor Ricardo Moreno Laverde
- Universidad Tecnológica de Pereira
- Programa de Ingeniería de Sistemas y Computación
- Asignatura IS284 Programación II

- Descripción del programa: Este programa genera una matriz de caracteres de 30 x 30 que contiene un laberinto. Se cuenta con la 
    entrada al laberinto en la parte superior izquierda del mismo y la salida se genera de manera aleatoria en el muro izquierdo
    
    Luego, con una función, busca el camino de solución usando la técnica de la recursividad y los ciclos for, en caso de que no
    tenga solución imprime que no la tiene y en caso de que si tenga solución imprime de nuevo el laberinto con el camino encontrado.
    
    Se usa el ASCII 219(█) para representar los muros y el ASCII 184(©) para el camino de solución.
*/

#include <stdio.h>   // Librería estándar de entrada/salida, se usa para imprimir en consola.
#include <stdlib.h>  // Librería estándar de utilidades, se usa para las funciones rand() y srand() para generar números aleatorios.
#include <time.h>    // Librería para manejar el tiempo, se utiliza para obtener la hora actual y como semilla en srand().

// Función que explora el laberinto en busca de un camino hacia la salida
int ExplorePath(char maze[30][30], int x, int y, int exit, int mov[4][2], int actualMov, int count) {
    // Verifica si se ha alcanzado la salida
    if (y == exit && x == 28) {
        maze[y][x] = 184; // Marca la posición de la salida
        maze[y][x + 1] = 184; // Marca la posición adyacente a la salida
        return 1; // Se encontró un camino
    }

    // Calcula las nuevas coordenadas basadas en el movimiento actual
    int movX = x + mov[actualMov][0];
    int movY = y + mov[actualMov][1];

    // Limita la cantidad de movimientos para evitar recursión infinita
    if (count < 780) {
        // Verifica si la nueva posición es un espacio vacío
        if (maze[movY][movX] == 32) {
            maze[y][x] = 184; // Marca la posición actual
            // Llama recursivamente para explorar la nueva posición
            if (ExplorePath(maze, movX, movY, exit, mov, actualMov, count + 1)) {
                return 1; // Se encontró un camino
            }
        }

        // Intenta otros movimientos (giro en el laberinto)
        for (int j = 1; j < 4; j++) {
            actualMov = (actualMov + 1) % 4; // Cambia el movimiento
            movX = x + mov[actualMov][0];
            movY = y + mov[actualMov][1];

            // Verifica si la nueva posición es un espacio vacío
            if (maze[movY][movX] == 32) {
                maze[y][x] = 184; // Marca la posición actual
                // Llama recursivamente para explorar la nueva posición
                if (ExplorePath(maze, movX, movY, exit, mov, actualMov, count + 1)) {
                    return 1; // Se encontró un camino
                }
            }
        }
        // Desmarca la posición si no se encontró un camino
        maze[y][x] = '0';
        count--;
    }
    return 0; // No se encontró un camino
} // Fin función ExplorePath

int main() {
    srand(time(NULL)); // Inicializa la semilla para la generación aleatoria
    int exit = (rand() % 28) + 1; // Genera una posición de salida aleatoria
    char maze[30][30]; // Inicializamos la matriz que va a contener el laberinto
    // Inicializa el laberinto
    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 30; c++) { 
            maze[r][c] = 219; // Rellena el laberinto con bloques
            int espacio = rand() % 5; // Decide si colocar un espacio vacío
            if (c != 0 && c != 29 && r != 0 && r != 29 && espacio) {
                maze[r][c] = 32; // Coloca un espacio vacío
            }
            // Crea un camino inicial en la esquina superior izquierda
            if ((c == 0 && r == 0) || (c == 1 && r == 1) || (c == 0 && r == 1) || (c == 1 && r == 0)) {
                maze[r][c] = 32;
            }
            maze[exit][28] = 32; // Coloca la salida
            maze[exit][29] = 32; // Coloca el espacio adyacente a la salida
            printf("%c", maze[r][c]); // Imprime la fila del laberinto
        }
        printf("\n"); // Nueva línea al final de la fila
    } 
    printf("\n"); // Imprime nueva línea para el orden en consola
    
    int mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Definición de los movimientos: derecha, abajo, izquierda, arriba

    // Inicia la exploración del laberinto desde la posición (0, 0)
    if (ExplorePath(maze, 0, 0, exit, mov, 0, 0)) {
        // Si se encontró un camino, imprime el laberinto modificado
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                if (maze[i][j] == 48) {
                    maze[i][j] = 32; // Convierte marcas a espacios vacíos
                }
                printf("%c", maze[i][j]); // Imprime cada posición del laberinto
            }
            printf("\n"); // Nueva línea al final de cada fila
        }
    } else {
        printf("No tiene soluci%cn", 162); // Mensaje si no hay solución
    }
    return 0; // Fin del programa
}