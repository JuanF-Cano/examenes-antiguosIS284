/* 
- Fecha de publicación: 23/09/2024
- Hora de publicación: 5:20 pm
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

- Descripción del programa: Este programa genera una matriz de caracteres de 30 x 30 que contiene un QR con bordes siempre en blanco.
    Se imprime por consola el QR en forma tabular y con separaciones dadas por " | ".

    Luego se evalua si el QR generado cumple con las codiciones requeridas por una empresa, siendo estas:
    a) Los píxeles de la periferia están siempre en blanco.
    b) El código tiene reservados un cuadrado de 7x7 píxeles encajado en la parte más externa superior derecha(sin incluir la periferia,
    esto es no incluir fila 0 ni la columna 29), que debe estar formado por al menos 25 píxeles negros, con cualquier disposición.
    c) En la séptima fila(subíndice 6 de la figura), las columnas de la figura con subíndices 2, 4, y 25 son píxeles de color negro.
    Cualquier producto que no cumpla los tres requisitos anteriores se considera falsificado. El número de errores se calculará teniendo
    en cuenta solo el último requisito (c), asignando un punto por cada píxel de los citados que no sea negro.

    Se usa el ASCII 219(█) para representar las partes negras del QR y el ASCII 32( ) para mostrar las partes blancas del QR.

*/

#include <stdio.h>   // Librería estándar de entrada/salida, se usa para imprimir en consola.
#include <stdlib.h>  // Librería estándar de utilidades, se usa para las funciones rand() y srand() para generar números aleatorios.
#include <time.h>    // Librería para manejar el tiempo, se utiliza para obtener la hora actual y como semilla en srand().
#include <string.h>  // Librería para el manejo de strings, se usa para la función strcpy

// Función que imprime y genera la matriz QR en un formato de tabla, con encabezado y bordes enumerando las filas y columnas.
void PrintTable1(char QR[30][30]) {
    // Imprimir el encabezado de las columnas
    printf("\n         012345678901234567890123456789\n        +------------------------------+\n");
    // Bucle para recorrer las filas
    for (int r = 0; r < 30; r++) {
        // Imprimir el número de la fila al inicio de cada línea
        printf("%i\t|", r);
        // Bucle para recorrer las columnas
        for (int c = 0; c < 30; c++) {
            // Inicializar cada celda con el carácter negro (ASCII 219)
            QR[r][c] = 219;
            // Generar aleatoriamente un valor para decidir si se cambia a un espacio
            int espacio = rand() % 2;
            // Si estamos en los bordes o el valor aleatorio lo decide, se pone un espacio (ASCII 32)
            if (c == 0 || c == 29 || r == 0 || r == 29 || espacio) {
                QR[r][c] = 32;
            }            
            // Imprimir el valor de la celda
            printf("%c", QR[r][c]);
        }
        // Imprimir el número de fila al final de la línea
        printf("|%i\n", r);
    }
    // Imprimir la línea inferior de la tabla
    printf("        +------------------------------+\n");
} // Fin función PrintTable1

// Función que imprime la matriz QR en un formato de tabla con cada celda delimitada por "|".
void PrintTable2(char QR[30][30]) {
    // Imprimir el encabezado de las columnas
    printf("\n        |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|\n        +-----------------------------------------------------------+\n");
    // Bucle para recorrer las filas
    for (int r = 0; r < 30; r++) {
        // Imprimir el número de la fila al inicio de cada línea
        printf("%i\t|", r);
        // Bucle para recorrer las columnas
        for (int c = 0; c < 30; c++) {
            // Imprimir el valor de la celda seguido de "|"
            printf("%c|", QR[r][c]);
        }
        // Imprimir el número de fila al final de la línea y una línea divisoria
        printf("%i\n        +-----------------------------------------------------------+\n", r);
    }
} // Fin función PrintTable2

// Función que verifica la "Condición B", que revisa si un área específica de la matriz 
int ConditionB(char conditionB[15], char QR[30][30]) {
    int count = 0; // Iniciamos la variable count con 0, que será la que va a contar la cantidad de caracteres que encuentre    
    // Bucle para contar los píxeles negros en un área 7x7 de la matriz, entre las filas 22-28 y las columnas 1-7
    for (int i = 22; i <= 28; i++) {
        for (int j = 1; j <= 7; j++) {
            if (QR[i][j] == -37) { // Verifica si el valor es igual al ASCII de un píxel negro (-37 ya que es con signo)
                count++;
            }
        }
    }    
    // Si hay al menos 25 píxeles negros, se cumple la condición B
    if (count >= 25) {
        strcpy(conditionB, "Se cumple"); // Cambiamos el mensaje del estado de la condicio de B por Se cumple
    } else {
        strcpy(conditionB, "NO se cumple"); // Cambiamos el mensaje del estado de la condicio de B por NO se cumple
    }    
    return count;
} // Fin función ConditionB

// Función que verifica la "Condición C", que requiere que tres celdas específicas en la fila 6
// (columnas 2, 4 y 25) sean píxeles negros (ASCII 32 para espacio).
int ConditionC(char conditionC[15], char QR[30][30]) {
    int count = 0; // Iniciamos la variable count = 0 para guardar la cantidad de errores que hay (Que son la cantidad de espacios que hay en dichas posiciones)
    // Verificar si en la fila 6 columnas 2, 4, 25 hay un caracter negro
    if (QR[6][2] == 32) {
        count++;
    }
    if (QR[6][4] == 32) {
        count++;    
    } 
    if (QR[6][25] == 32) {
        count++;
    }
    // Si ninguna de las posiciones contiene un espacio, la condición C se cumple
    if (count == 0) {
        strcpy(conditionC, "Se cumple"); // Cambiamos el mensaje del estado de la condicio de B por Se cumple
    } else {
        strcpy(conditionC, "NO se cumple"); // Cambiamos el mensaje del estado de la condicio de B por NO se cumple
    }    
    return count;
} // Fin función ConditionC

int main() { // Inicio función prinipal
    srand(time(NULL)); // Inicializar la semilla para la generación de números aleatorios
    
    char QR[30][30];      // Matriz QR de 30x30
    char conditionB[15];  // Cadena para almacenar el estado de la condición B
    char conditionC[15];  // Cadena para almacenar el estado de la condición C
    char errors[15];      // Cadena para almacenar si el QR es original o no

    // Llamar a las funciones para imprimir la matriz en dos formatos diferentes
    PrintTable1(QR);
    PrintTable2(QR);
    
    // Verificar las condiciones B y C
    int nBlackPixels = ConditionB(conditionB, QR);
    int nErrors = ConditionC(conditionC, QR);

    // Si hay errores (fallos en la condición C), se considera que el QR no es original
    if (nErrors) {
        strcpy(errors, "No es original"); // Cambiamos el mensaje del estado de la condicio de B por NO es original
    } else {
        strcpy(errors, "Es original"); // Cambiamos el mensaje del estado de la condicio de B por Es original
    }

    // Imprimir los requisitos y resultados
    printf("\nRequisitos:\na) Los p%cxeles de la periferia est%cn siempre en blanco\nb) El c%cdigo tiene reservados un cuadrado de 7x7 p%cxeles encajado en la parte más externa superior derecha (sin incluir la periferia), que debe estar formado por al menos 25 p%cxeles negros, con cualquier disposici%Cn\n", 161, 160, 162, 161, 161, 162);
    printf("c) En la s%cptima fila (sub%cndice 6 de la figura), las columnas en la figura 2, 4, y 25 del arreglo son p%cxeles de color negro. \nCualquier producto que no cumpla los tres requisitos anteriores se considera falsificado. El n%cmero de errores se calcular%c teniendo en cuenta solo el %cltimo requisito (c), asignando un punto por cada p%cxel de los citados que no sea negro.\n", 130, 161, 161, 163, 169, 163, 161);
    printf("Condici%cn a: Se cumple\nCondici%cn b: %s. N%cmero de píxeles negros = %i\nCondici%cn c: %s.\nErrores: %i %s", 162, 162, conditionB, 163, nBlackPixels, 162, conditionC, nErrors, errors);
}