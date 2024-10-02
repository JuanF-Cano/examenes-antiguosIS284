/* 
- Fecha de publicación: 24/09/2024
- Hora de publicación: 3:00 pm
- Versión de su código: 1.0
- Autor. Ing(c): Juan Fernando Cano Duque
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Nombre y versión del Sistema Operativo(S.O) sobre el que compiló y probó los ejecutables: windows 10.0.22631
- Versión del compilador utilizado: Compilado con GCC 6.3.0 (MinGW.org GCC-6.3.0-1)
- Presentado a: Doctor Ricardo Moreno Laverde
- Universidad Tecnológica de Pereira
- Programa de Ingeniería de Sistemas y Computación
- Asignatura IS284 Programación II

- Descripción del programa: Este programa genera una pantalla de caracteres de 60 X 30 (60 de ancho y 30 de alto). Imprime la pantalla 
    de puntos y con circulos generado aleatoriamente.

    Luego se evalua cuales de esos circulos son esquinas de rectangulos imprimiendo de nuevo la pantalla pero con los rectángulos 
    rellenos por "x", sin rellenar los lugares en los que se encuntran otras esquinas, notadas por la letra "o". 
    Finalmente imprime por pantalla cuales son las dimensiones del cuadrado más pequeño y cual es su área.
    Todo el programa se basa en que los puntos de los rectángulos se toman con la siguiente enumeración:
                                                        1 - - - - 2
                                                        |         |
                                                        |         |
                                                        4 - - - - 3

    Se usa el ASCII 46(.) para representar el fondo de la pantalla, el ASCII 111(o) para las esquinas de los rectángulos y
    el ASCII 120(x) para rellenar los rectángulos.
*/

#include <stdio.h>   // Librería estándar de entrada/salida.
#include <stdlib.h>  // Librería estándar de utilidades.
#include <time.h>    // Librería para manejar el tiempo.

void fillScreen(int row, int col, char screen[30][60]) {
    // Caso base: cuando se ha completado la última fila
    if (row == 30) {
        return;
    }

    // Llena la pantalla con puntos (.) y coloca una 'o' aleatoriamente
    screen[row][col] = '.';
    if (rand() % 22 == 0) {
        screen[row][col] = 'o';
    }
    printf("%c", screen[row][col]);

    // Caso base: cuando se ha completado la última columna de una fila
    if (col == 59) {
        printf("\n");
        fillScreen(row + 1, 0, screen); // Avanzamos a la siguiente fila
    } else {
        fillScreen(row, col + 1, screen); // Avanzamos a la siguiente columna
    }
}

void makeRectangle(int x1, int x2, int y1, int y2, char screen[30][60], int i, int j) {
    // Caso base: hemos terminado la fila actual
    if (i > y2) {
        return;
    }

    // Cambia los puntos por 'x', si no es una esquina 'o'
    if (j <= x2) {
        if (screen[i][j] == '.') {
            screen[i][j] = 'x';
        }
        makeRectangle(x1, x2, y1, y2, screen, i, j + 1); // Avanzamos a la siguiente columna
    } else {
        makeRectangle(x1, x2, y1, y2, screen, i + 1, x1); // Avanzamos a la siguiente fila
    }
}

int findRectangle(char screen[30][60], int x, int y, int rectangle[3][2], int i, int j) {
    // Caso base: hemos llegado al límite de la pantalla
    if (i >= 60 || j >= 30) {
        return 0;
    }

    // Caso base: encontramos una esquina
    if (screen[y][i] == 'o' && screen[j][i] == 'o' && screen[j][x] == 'o') {
        makeRectangle(x, i, y, j, screen, y, x); // Rellenamos el rectángulo
        // Calcula el área y comprueba si es el rectángulo más pequeño
        if ((i - x) * (j - y) < (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1])) {
            rectangle[0][0] = x;
            rectangle[0][1] = y;
            rectangle[1][0] = i;
            rectangle[1][1] = y;
            rectangle[2][0] = i;
            rectangle[2][1] = j;
            return 1;
        }
    }

    // Avanza a la siguiente columna
    if (i < 59) {
        return findRectangle(screen, x, y, rectangle, i + 1, j);
    }

    // Avanza a la siguiente fila
    return findRectangle(screen, x, y, rectangle, x + 1, j + 1);
}

int checkScreen(int r, int c, char screen[30][60], int rectangle[3][2], int *area) {
    // Caso base: si terminamos de recorrer todas las filas
    if (r == 30) {
        return *area;
    }

    // Si encontramos una esquina 'o', buscamos un rectángulo
    if (screen[r][c] == 'o') {
        if (findRectangle(screen, c, r, rectangle, c + 1, r + 1)) {
            *area = (rectangle[1][0] - rectangle[0][0] + 1) * (rectangle[2][1] - rectangle[1][1] + 1);
        }
    }

    // Continuar con la siguiente columna
    if (c < 59) {
        return checkScreen(r, c + 1, screen, rectangle, area);
    }

    // Avanza a la siguiente fila
    return checkScreen(r + 1, 0, screen, rectangle, area);
}

void printScreen(int r, int c, char screen[30][60]) {
    // Caso base: si terminamos de recorrer todas las filas
    if (r == 30) {
        return;
    }

    printf("%c", screen[r][c]); // Imprime el carácter actual

    // Continuar con la siguiente columna
    if (c < 59) {
        printScreen(r, c + 1, screen); // Avanzamos a la siguiente columna
    } else {
        printf("\n");
        printScreen(r + 1, 0, screen); // Avanzamos a la siguiente fila
    }
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para números aleatorios
    char screen[30][60]; // Pantalla de 60 columnas y 30 filas
    int rectangle[3][2] = {{0, 0}, {59, 0}, {59, 29}}; // Coordenadas de las esquinas del rectángulo más pequeño
    int area = 0; // Inicializa el área en 0

    fillScreen(0, 0, screen); // Llenar e imprimir la pantalla con puntos y esquinas 'o'
    printf("\n");

    // Revisa la pantalla para buscar rectángulos
    checkScreen(0, 0, screen, rectangle, &area);

    // Si se ha encontrado algún rectángulo, imprime la pantalla actualizada y el área del más pequeño
    if (area) {
        printScreen(0, 0, screen); // Imprimir la pantalla actualizada
        printf("\nEl %crea del m%cs peque%co seria %i x %i\nArea = %i\n", 160, 160, 164, 
        rectangle[1][0] - rectangle[0][0] + 1, rectangle[2][1] - rectangle[1][1] + 1, area);
    } else {
        printf("No se ha encontrado ningun rectangulo.\n");
    }

    return 0;
}