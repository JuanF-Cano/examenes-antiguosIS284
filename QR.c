/* 
- Fecha de publicación: 23/09/2024
- Hora de publicación: 2:36 am
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

- Descripción del programa: Este programa genera una matriz de caracteres de 30 x 30 que contiene un laberinto. Se cuenta con la 
    entrada al laberinto en la parte superior izquierda del mismo y la salida se genera de manera aleatoria en el muro izquierdo
    
    Luego, con una función, busca el camino de solución usando la técnica de la recursividad y los ciclos for, en caso de que no
    tenga solución imprime que no la tiene y en caso de que si tenga solución imprime de nuevo el laberinto con el camino encontrado.
    
    Se usa el ASCII 219(█) para representar los muros y el ASCII 184(©) para el camino de solución.
*/

#include <stdio.h>   // Librería estándar de entrada/salida, se usa para imprimir en consola.
#include <stdlib.h>  // Librería estándar de utilidades, se usa para las funciones rand() y srand() para generar números aleatorios.
#include <time.h>    // Librería para manejar el tiempo, se utiliza para obtener la hora actual y como semilla en srand().
#include <string.h>  // Librería para el manejo de strings, se usa para la función strcpy

void PrintTable1(char QR[30][30]) {
    printf("\n         012345678901234567890123456789\n        +------------------------------+\n");
    for (int r = 0; r < 30; r++) {
    printf("%i\t|", r);
            for (int c = 0; c < 30; c++) {
                QR[r][c] = 219;
                int espacio = rand() % 2;
                if (c == 0 || c == 29 || r == 0 || r == 29 || espacio) {
                    QR[r][c] = 32;
                }
                printf("%c", QR[r][c]);
            }
            printf("|%i\n", r);
        }
    printf("        +------------------------------+\n");
}

void PrintTable2(char QR[30][30]) {
    printf("\n        |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|\n        +-----------------------------------------------------------+\n");
    for (int r = 0; r < 30; r++) {
    printf("%i\t|", r);
            for (int c = 0; c < 30; c++) {
                printf("%c|", QR[r][c]);
            }
            printf("%i\n        +-----------------------------------------------------------+\n", r);
        }
}

int ConditionB(char conditionB[15], char QR[30][30]) {
    int count = 0;
    for (int i = 22; i <= 28; i++) {
        for (int j = 1; j <= 7; j++) {
            if (QR[i][j] == -37) {
                count++;
            }
        }
    }
    if (count >= 25) {
        strcpy(conditionB, "Se cumple");
    } else {
        strcpy(conditionB, "NO se cumple");
    }
    return count;
}

int ConditionC(char conditionC[15], char QR[30][30]) {
    int count = 0;
    if (QR[6][2] == 32) {
        count++;
    }
    if (QR[6][4] == 32) {
        count++;    
    } 
    if (QR[6][25] == 32) {
        count++;
    }

    if (count == 0) {
        strcpy(conditionC, "Se cumple");
    } else {
        strcpy(conditionC, "NO se cumple");
    }
    return count;
}

int main() {
    srand(time(NULL));
    char QR[30][30];
    char conditionB[15];
    char conditionC[15];
    char errors[15];

    PrintTable1(QR);
    PrintTable2(QR);

    int nBlackPixels = ConditionB(conditionB, QR);
    int nErrors = ConditionC(conditionC, QR);

    if (nErrors) {
        strcpy(errors, "No es original");
    } else {
        strcpy(errors, "Es original");
    }

    printf("\nRequisitos:\na) Los p%cxeles de la periferia est%cn siempre en blanco\nb) El c%cdigo tiene reservados un cuadrado de 7x7 p%cxeles encajado en la parte más externa superior derecha(sin incluir la periferia), que debe estar formado por al menos 25 p%cxeles negros, con cualquier disposici%Cn\n", 161, 160, 162, 161, 161, 162);
    printf("c) En la s%cptima fila(sub%cndice 6 de la figura), las columnas en la figura 2, 4, y 25 del arreglo son p%cxeles de color negro. \nCualquier producto que no cumpla los tres requisitos anteriores se considera falsificado. El n%cmero de errores se calcular%c teniendo en cuenta solo el %cltimo requisito (c), asignando un punto por cada p%cxel de los citados que no sea negro.\n", 130, 161, 161, 163, 169, 163, 161);
    printf("Condici%cn a: Se cumple\nCondici%cn b: %s. N%cmero de pixeles negros = %i\nCondici%cn c: %s.\nErrores: %i %s", 162, 162, conditionB, 163, nBlackPixels, 162, conditionC, nErrors, errors);
}