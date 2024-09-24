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

#include <stdio.h>   // Librería estándar de entrada/salida, se usa para imprimir en consola.
#include <stdlib.h>  // Librería estándar de utilidades, se usa para las funciones rand() y srand() para generar números aleatorios.
#include <time.h>    // Librería para manejar el tiempo, se utiliza para obtener la hora actual y como semilla en srand()

// Función que cambia los caracteres internos de los rectángulos por x para luego imprimirlo
void MakeRectangle(int x1, int x2, int y1, int y2, char screen[30][60]) {
    for (int i = y1; i <= y2; i++) { // Iteramos desde la fila más arriba hasta la más abajo
        for (int j = x1; j <= x2; j++) { // Iteramos desde la columna más a la izquierda hasta la más a la derecha
            // Si el caracter es unn punto lo cambia por una x, sino lo deja con la letra "o"
            if (screen[i][j] == 46) { 
                screen[i][j] = 120;
            }
        }
    }
} // Fin función MakeRectangle

// Función que va a determinar cuando hay un rectángulo con el punto mandado como parametro y en donde
// Devuelve 1 o 0 dependiendo de si hay o no un rectángulo asociado al punto
int FindRectangle(char screen[30][60], int x, int y, int rectangle[3][2]) {
    int i = x + 1; // Iniciamos la variable i con el valor de x + 1 para iterar sobre la fila y revisar cada punto
    int j = y + 1; // Inciiamos la variable j con el valor de y + 1 para iterar en cada posición de la fila

    // Cambiamos el valor de i hasta que se encuentra otro caracter 111(o) o hasta que llegue al borde de la pantalla
    while (screen[y][i] != 111 && i < 59) i++; 
    // revisamos si hay un caracter en ese punto, ya que i toma el valor del límite de la pantalla cuando no encuentra otra "o"
    if (screen[y][i] == 111) {
        // Cambia el valor de j hasta que encuentre otro caracter 111(o) o hasta que llegue al borde de la pantalla
        while (screen[j][i] != 111 && j < 29) j++;
        // revisamos si hay un caracter en ese punto, ya que j toma el valor del límite de la pantalla cuando no encuentra otra "o"
        // Además se pregunta si en el punto i j hay un 111(o) ya que eso significaría que hay un cuadrado
        if (screen[j][i] == 111 && screen[j][x] == 111) {
            MakeRectangle(x, i, y, j, screen); // Llamada a la función MakeRectangle para rellenar el cuadrado encontrado
            // Revisamos si el área del rectángulo encontrado es menor al área del último cuadrado encontrado 
            if ((i - x) * (j - y) < (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1])) {
                // Guardamos Las coordenadas de las esquinas 1, 2 y 3 del nuevo rectangulo
                rectangle[0][0] = x;
                rectangle[0][1] = y;
                rectangle[1][0] = i;
                rectangle[1][1] = y;
                rectangle[2][0] = j;
                rectangle[2][1] = i;
                return 1;
            }
        }
    }
    return 0;
} // fin función FindRectangle

int main() {
    srand(time(NULL)); // Inicializa la semilla para la generación aleatoria
    char screen[30][60]; // Iniciamos la matriz 60 x 30 en la que se va a guardar la pantalla con los cuadrados
    int rectangle[3][2] = {{0, 0}, {59, 0}, {59, 59}};// La variable rectangle guarda 3 coordenadas, correspondientes a las esquinas 
    // 1, 2 y 3 de toda la pantalla, para que el área siempre sea mayor al área del primer rectángulo encontrado
    int area = 0; // Se inicializa la variable área con 0, que será en la que se guarde el valor del área calculada de rectángulo menor

    // Se llena e imprime la matriz con caracteres (.) y (o)
    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 60; c++) {
            screen[r][c] = 46; // Llena de puntos toda la pantalla
            int corner = rand() % 20; // Genera un número aleatorio entre 0 y 19 para poner una "o" cuando sea 0
            if (!corner) {
                screen[r][c] = 111;
            }
            printf("%c", screen[r][c]); // Imprimimos en pantalla el caracter en la posición actual
        }
        printf("\n"); // Salto de linea cada 30 caracteres
    }

    printf("\n"); // Salto de línea para el orden en la consola

    // Se recorre la matriz para evaluar si con los puntos se generan rectángulos
    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 60; c++) {
            if (screen[r][c] == 111) { // Cuando encuentre una letra "o" evalúa si hay un rectángulo
                if (FindRectangle(screen, c, r, rectangle)) { 
                    // Si se encuentra un rectángulo y este es menor a al anterior encontrado se calcula y guarda el área en la variable area
                    area = (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1]);
                }
            }
        }
    }

    // Si se encontró un rectángulo, se imprime la pantalla y el mensaje del menor rectángulo encontrado
    if (area) {
        // Vuelve a imprimir la pantalla con los rectángulos econtrados rellendaso
        for (int r = 0; r < 30; r++) {
            for (int c = 0; c < 60; c++) {
                printf("%c", screen[r][c]);
            }
            printf("\n"); // Salto de linea cada 30 caracteres
        }
        // Se imprime el mensaje con las dimensiones del rectangulo más pequeño encontrado y su área
        printf("\nEl %crea del m%cs peque%co seria %i x %i %i\n", 160, 160, 164, 
        rectangle[1][0] - rectangle[0][0], rectangle[2][1] - rectangle[1][1], area);
    } else {
        printf("\nNo se ha encontrado ningun rectangulo.");
    }
    return 0;
}