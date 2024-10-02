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

void MakeScreen(int r, int c, char screen[30][60]) {
    if (r < 30) { // Caso base: cuando ya hemos procesado todas las filas (r >= 30), la recursión termina.
        if (c < 60) { // Caso recursivo para las columnas: recorre cada columna dentro de la fila actual.
            screen[r][c] = 46; // Llena la posición actual de la pantalla con un punto (ASCII 46).
            int corner = rand() % 20; // Genera un número aleatorio entre 0 y 19.
            if (!corner) { // Si el número aleatorio es 0, coloca una "o" (ASCII 111) en esa posición.
                screen[r][c] = 111;
            }
            printf("%c", screen[r][c]); // Imprime el caracter actual en la consola.
            // Llama a la función recursivamente para la siguiente columna en la misma fila.
            MakeScreen(r, c + 1, screen);
        } else { // si hemos llegado al final de una fila, imprimimos un salto de línea y pasamos a la siguiente fila.
            printf("\n");
            MakeScreen(r + 1, 0, screen); // Llama recursivamente para la siguiente fila y reinicia la columna.
        }
    }
}

// Función recursiva que rellena el interior de los rectángulos con 'x'
void MakeRectangle(int x1, int x2, int y1, int y2, int i, int j, char screen[30][60]) {
    if (i <= y2) { // Asegura que no hemos excedido la última fila del rectángulo.
        if (j <= x2) { // Asegura que no hemos excedido la última columna del rectángulo.
            // Si el caracter actual es un punto, lo reemplaza por una 'x'.
            if (screen[i][j] == 46) {
                screen[i][j] = 120;
            }
            // Llamada recursiva para procesar la siguiente columna en la misma fila.
            MakeRectangle(x1, x2, y1, y2, i, j + 1, screen);
        } else {
            // Cuando se alcanza el final de una fila, se pasa a la siguiente fila y reinicia las columnas.
            MakeRectangle(x1, x2, y1, y2, i + 1, x1, screen);
        }
    }
}

// Función recursiva para encontrar la posición de la próxima 'o' en la fila
int FindNextOInRow(char screen[30][60], int y, int i) {
    if (i >= 59) { // Caso base: Si alcanzamos el límite derecho de la pantalla, devolvemos el índice actual (límite).
        return i;
    } else if (screen[y][i] == 111) { // Caso base: Si encontramos una 'o', devolvemos el índice actual.
        return i;
    } else {
        return FindNextOInRow(screen, y, i + 1); // Llamada recursiva para la siguiente columna.
    }
}

// Función recursiva para encontrar la posición de la próxima 'o' en la columna
int FindNextOInColumn(char screen[30][60], int j, int i) {
    if (j >= 29) { // Caso base: Si alcanzamos el límite inferior de la pantalla, devolvemos el índice actual (límite).
        return j;
    } else if (screen[j][i] == 111) { // Caso base: Si encontramos una 'o', devolvemos el índice actual.
        return j;
    } else {
        return FindNextOInColumn(screen, j + 1, i); // Llamada recursiva para la siguiente fila.
    }
}

// Función que va a determinar cuando hay un rectángulo con el punto mandado como parametro y en donde
// Devuelve 1 o 0 dependiendo de si hay o no un rectángulo asociado al punto
int FindRectangle(char screen[30][60], int x, int y, int rectangle[3][2]) {
    int i = x + 1; // Iniciamos la variable i con el valor de x + 1 para iterar sobre la fila y revisar cada punto
    int j = y + 1; // Inciiamos la variable j con el valor de y + 1 para iterar en cada posición de la fila

    // Cambiamos el valor de i hasta que se encuentra otro caracter 111(o) o hasta que llegue al borde de la pantalla
    i = FindNextOInRow(screen, y, i);
    // revisamos si hay un caracter en ese punto, ya que i toma el valor del límite de la pantalla cuando no encuentra otra "o"
    if (screen[y][i] == 111) {
        // Cambia el valor de j hasta que encuentre otro caracter 111(o) o hasta que llegue al borde de la pantalla
        j = FindNextOInColumn(screen, j, i);
        // revisamos si hay un caracter en ese punto, ya que j toma el valor del límite de la pantalla cuando no encuentra otra "o"
        // Además se pregunta si en el punto i j hay un 111(o) ya que eso significaría que hay un cuadrado
        if (screen[j][i] == 111 && screen[j][x] == 111) {
            MakeRectangle(x, i, y, j, x, y, screen); // Llamada a la función MakeRectangle para rellenar el cuadrado encontrado
            // Revisamos si el área del rectángulo encontrado es menor al área del último cuadrado encontrado 
            if ((i - x) * (j - y) < (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1])) {
                // Guardamos Las coordenadas de las esquinas 1, 2 y 3 del nuevo rectangulo
                rectangle[0][0] = x;
                rectangle[0][1] = y;
                rectangle[1][0] = i;
                rectangle[1][1] = y;
                rectangle[2][0] = i;
                rectangle[2][1] = j;
                return 1;
            }
        }
    }
    return 0;
} // fin función FindRectangle

void EvaluateScreen(int r, int c, char screen[30][60], int rectangle[3][2], int *area) {
    if (r < 30) { // Caso base para las filas: si hemos procesado todas las filas, termina la recursión
        if (c < 60) { // Caso recursivo para las columnas
            if (screen[r][c] == 111) { // Si encontramos una 'o', evaluamos si hay un rectángulo
                if (FindRectangle(screen, c, r, rectangle)) { 
                    // Si se encuentra un rectángulo más pequeño, se calcula y guarda el área
                    area = (rectangle[1][0] - rectangle[0][0] + 1) * (rectangle[2][1] - rectangle[1][1] + 1);
                }
            }
            // Llamada recursiva para la siguiente columna en la misma fila
            FindRectanglesRec(r, c + 1, screen, rectangle, area);
        } else { 
            // Si llegamos al final de una fila, pasamos a la siguiente fila y reiniciamos la columna
            FindRectanglesRec(r + 1, 0, screen, rectangle, area);
        }
    }
}

void printScreenRec(int r, int c, char screen[30][60]) {
    if (r < 30) { // Caso base para las filas: cuando hemos procesado todas las filas, termina la recursión
        if (c < 60) { // Caso recursivo para las columnas: recorre cada columna dentro de la fila actual
            printf("%c", screen[r][c]); // Imprime el caracter actual
            // Llamada recursiva para la siguiente columna en la misma fila
            printScreenRec(r, c + 1, screen);
        } else { 
            // Si llegamos al final de la fila, imprimimos un salto de línea y pasamos a la siguiente fila
            printf("\n");
            // Llamada recursiva para la siguiente fila y reinicia la columna
            printScreenRec(r + 1, 0, screen);
        }
    }
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para la generación aleatoria
    char screen[30][60]; // Iniciamos la matriz 60 x 30 en la que se va a guardar la pantalla con los cuadrados
    int rectangle[3][2] = {{0, 0}, {59, 0}, {59, 59}};// La variable rectangle guarda 3 coordenadas, correspondientes a las esquinas 
    // 1, 2 y 3 de toda la pantalla, para que el área siempre sea mayor al área del primer rectángulo encontrado
    int area = 0; // Se inicializa la variable área con 0, que será en la que se guarde el valor del área calculada de rectángulo menor

    // Se llena e imprime la matriz con caracteres (.) y (o)
    MakeScreen(0, 0, screen);

    printf("\n"); // Salto de línea para el orden en la consola

    // Se recorre la matriz para evaluar si con los puntos se generan rectángulos
    EvaluateScreen(0, 0, screen, rectangle, &area);

    // Si se encontró un rectángulo, se imprime la pantalla y el mensaje del menor rectángulo encontrado
    if (area) {
        // Vuelve a imprimir la pantalla con los rectángulos econtrados rellendaso
        printScreenRec(0, 0, screen);
        // Se imprime el mensaje con las dimensiones del rectangulo más pequeño encontrado y su área
        printf("\nEl %crea del m%cs peque%co seria %i x %i %i\n", 160, 160, 164, 
        rectangle[1][0] - rectangle[0][0] + 1, rectangle[2][1] - rectangle[1][1] + 1, area);
    } else {
        printf("\nNo se ha encontrado ningun rectangulo.");
    }
    return 0;
}