/*
- Fecha de publicación: 2/10/2024
- Hora de publicación: 3:00 am
- Versión de su código: 1.0
- Autor: Ing(c): Juan Fernando Cano Duque
- Nombre del lenguaje utilizado: C
- Versión del lenguaje utilizado: C11
- Nombre y versión del Sistema Operativo(S.O) sobre el que compiló y probó los ejecutables: windows 10.0.22631
- Versión del compilador utilizado: Compilado con GCC 6.3.0 (MinGW.org GCC-6.3.0-1)
- Presentado a: Doctor Ricardo Moreno Laverde
- Universidad Tecnológica de Pereira
- Programa de Ingeniería de Sistemas y Computación
- Asignatura IS284 Programación II

- Descripción del programa: Este programa toma una ecuación polinómica introducida por el usuario y descompone sus términos en coeficientes y exponentes. 
   Posteriormente, evalúa dichos términos para distintos valores de x en un rango especificado por el usuario y genera una gráfica en la consola representando la ecuación.

   La ecuación debe ingresarse con el formato: coeficiente, variable y exponente entre paréntesis, por ejemplo: 3x^2 + 5x - 4.
   El programa extrae los coeficientes y exponentes de la ecuación, la evalúa para un rango de valores, y finalmente la gráfica usando caracteres ASCII.

    Salvedad: El programa cuenta con que no se ingrese un polinomio de más de 10 términos, por lo que podría causar problemas uno más largo.
    Además, No se debe poner incrementos negativos ni rangos final menor al rango inicial
*/

#include <stdio.h>   // Librería estándar de entrada/salida, se usa para imprimir en consola.
#include <stdlib.h>  // Librería estándar de utilidades, se usa para las funciones rand() y srand() para generar números aleatorios.
#include <math.h>    // Librerìa con operaciones matemàticas, se usa para las funciones pow() y fabs()

// Funcion que guarda el coeficiente y exponente de un termino
void Term(char equation[], int coeExp[10][2], int previousSign, int pos, int limit) {
    char coe[12] = {'\0'}; // Variable que contiene el string del coeficiente del termino actual
    int i = 0; // Variable que sirve como contador y será usada para revisar todo el término hasta la X, si la tiene
    while (equation[previousSign + i] < 60 && previousSign + i < limit) { // iteramos sobre el termino
        coe[i] = equation[previousSign + i]; // Guardamos cada caracter de la ecuacion en coe, hasta la X
        i++;
    }
    if (i == 0 || (i == 1 && equation[previousSign] == '-')) { // Si el caracter es "x" o "-x"
        coe[i] = '1'; // Se adiciona 1 luego para que quede 1 o -1
        coe[i + 1] = '\0'; // Caracter nulo para marcar el final de la cadena en i+1
    } else {
        coe[i] = '\0'; // Caracter nulo para marcar el final en i, ya que no se le adiciona nada
    }
    i++;
    char exp[10] = {'\0'}; // Variable que contiene el string del exponente del termino actual
    int j = 0; // Variable que sirve como contador y se usará para revisar todo el string del termino a partir de la x
    if (previousSign + i == limit) { // Si en el termino siguiende al de la c está el límite, pone exponente 1
        exp[j] = '1';
        j++;
    } else if (previousSign + i > limit) { // Si el termino siguiente supera al límite significa que no hay "x", deja exponente 0
        exp[j] = '0';
        j++;
    } else {
        if (equation[previousSign + i] == '(') i++; // Si encuentra "(" busca apartir de la posición siguiente
        while (previousSign + i < limit) { // itera sobre la cadena hasta llegar al límite
            exp[j] = equation[previousSign + i];
            j++; i++;
        }
    }
    exp[j] = '\0'; // Añade caracter nulo al final

    coeExp[pos][0] = atoi(coe); // Convierte el string del coeficiente a un entero y lo guarda en la matriz
    coeExp[pos][1] = atoi(exp); // Convierte el string del exponente a un entero y lo guarda en la matriz
    printf("\n---------------------------------\n| %i\t\t", coeExp[pos][0]); // Imprime el termino en la tabla
    printf("| %i\t\t|", coeExp[pos][1]);
}

// Funcion para obtener e imprimir los coeficientes y exponentes del polinomio (string) ingresado
void getCoeExp(char equation[], int coeExp[10][2], int previousSign, int pos) {
    int i = 1; // Inicia el contador en 1 para tener en cuenta hasta el último número
    while (equation[i - 1] != '\0') { // Iteramos hasta que encuentre el final de la cadena
        if ((equation[i] == '-' && equation[i - 1] != '(') || equation[i] == '+' || equation[i] == '\0') {
            // Si encuentra un signo que no sea de un exponente marca la posición para mandar los limites del termino a la función Term
            Term(equation, coeExp, previousSign, pos, i);
            pos++; previousSign = i;
        }
        i++;
    }
    while (pos < 10) { // Si hay lugares vacíos en el array de coeExp los llena de 0 y 1 para evitar resultados inesperados
        coeExp[pos][0] = 0;
        coeExp[pos][1] = 1;
        pos++;
    }
}

// Funcion que toma un valor de "X" y evalua el "f(x)" prara ese punto
double Evaluate(int coeExp[10][2], int x, int count) {
    if (count == 10) { // cuando llegue al máximo de terminos que recibe el programa
        return 0;
    } else { // Devuelve la suma de la evaluacion en el termino actual más los siguientes
        return coeExp[count][0] * pow(x, coeExp[count][1]) + Evaluate(coeExp, x, count + 1);
    }
}

// Funcion que grafica el polinomio ingresado
void Graphing(char graph[26][101], double evaluation[101][2], double dom, double ran, double minX, double minY, double maxY, double nDatos) {
    // Busca el lugar en el que está el 0 de "X" con respecto a "Y" y el 0 de "Y" con respecto a "X", para graficar los ejes
    double zeroX = (fabs(0 - minX) * 99 / dom);
    double zeroY = (fabs(maxY - 0) * 24 / ran);

    for (int i = 0; i < 100; i++) { // Llena la horizontal en la que va el eje x con ASCII 196(─)
        graph[(int)round(zeroY)][i] = 196;
    }
    for (int j = 0; j < 26; j++) { // Llena la vertical en la que va el eje y con ASCII 179(|)
        graph[j][(int)round(zeroX)] = 179;
    }
    graph[(int)round(zeroY)][(int)round(zeroX)] = 197; // Pone en el origen el ASCII 197(┼)

    for (int m = 0; m <= nDatos; m++) { // Por cada dato pone una x en la matriz
        // Calcula las posiciones "X" e "Y" del punto con respecto a la escala que estamos manejando
        double x = (fabs(evaluation[m][0] - minX) * 99 / dom);
        double y = (fabs(maxY - evaluation[m][1]) * 24 / ran);
        // Guarda el valor redondeado
        int xRounded = (int)round(x);
        int yRounded = (int)round(y);
        // Pregunta si el valor redondeado esta dentro de los limites del cuadro
        if (xRounded >= 0 && xRounded < 101 && yRounded >= 0 && yRounded < 26) {
            graph[yRounded][xRounded] = 'x'; // Pone la x en la matriz
        }
    }

    // Etiquetas para el eje X
    for (int k = 0; k <= dom; k++) {
        double xValue = minX + (k * (dom / nDatos)); // Calculamos el valor de x 
        char xLabel[10] = "          "; // Inicializamos el string con espacios
        sprintf(xLabel, "%.0f", xValue); // Formateamos la cadena con el valor de x xValue
        int xPos = (int)round(fabs(xValue - minX) * 99 / dom); // Buscamos la posición para poner x
        if (xPos >= 0 && xPos < 101) { // Si la posicion está dentro de los limites guarda el texto en la matriz
            for (int l = 0; l < 10; l++) {
                if (xLabel[l] != '\0') { // Itera hasta llegar al final de la cadena de la etiqueta
                    graph[(int)round(zeroY) + 1][xPos + l] = xLabel[l]; // Guarda digito por digito de la etiqueta
                }
            }
        }
    }

    // Etiquetas para el eje Y
    for (int k = 0; k <= 5; k++) {
    double yValue = minY + k * (ran / 5); // Calculamos el valor de Y
    char yLabel[20] = "                    "; // Inicializamos el string con espacios 
    sprintf(yLabel, "%.2f", yValue); // Formateamos la cadena con el valor de y yValue
    int yPos = (int)round(fabs(maxY - yValue) * 24 / ran);  // Buscamos la posición para poner y

    if (yPos >= 0 && yPos < 26) { // Si la posición está dentro de los límites guarda el texto en la matriz
        for (int l = 0; l < 20 && yLabel[l] != '\0'; l++) { // Itera hasta que llega al final de la cadena
            if (zeroX < 5) { // Cuando la ordenada esté a la izquierda de la pantalla
                if (yValue < 0) { // Cuadrante inferior izquierdo
                    graph[yPos][(int)round(zeroX) + 1 + l] = yLabel[l]; // Etiquetas a la derecha
                } else { // Cuadrante superior izquierdo
                    graph[yPos][(int)round(zeroX) + 1 + l] = yLabel[l]; // Etiquetas a la derecha
                }
            } else { // Cuando la ordenada esté a la derecha de la pantalla
                if (yValue < 0) { // Cuadrante inferior derecho
                    graph[yPos][(int)round(zeroX) - 5 + l] = yLabel[l]; // Etiquetas a la izquierda
                } else { // Cuadrante superior derecho
                    graph[yPos][(int)round(zeroX) - 5 + l] = yLabel[l]; // Etiquetas a la izquierda
                }
            }
        }
    }
}

}

int main() {
    char equation[30] = {'\0'}; // Inicializa la cadena con un carácter nulo

    // Pide y resive un polinomio en modo string y lo guarda en equation
    printf("\nIngrese la ecuaci%cn a graficar: ", 162);
    scanf("%s", equation);

    // Imprime el cuadro de coeficientes y exponentes del polinomio ingresado
    int coeExp[10][2] = {0}; // Inicializa todos los elementos a cero
    printf("\nCOEFICIENTE         POTENCIA");
    getCoeExp(equation, coeExp, 0, 0);
    printf("\n---------------------------------");

    // Recive los datos de rango inicial, final e incremento para la segunda tabla
    int initial = 0, final = 0, increase = 0;
    printf("\n\nIngrese rango inicial: ");
    scanf("%i", &initial);
    do {
        printf("\nIngrese rango final: ");
        scanf("%i", &final);
    } while (final < initial);
    do {
        printf("\nIngrese el incremento: ");
        scanf("%i", &increase);
    } while (increase <= 0);

    double domain = fabs(final - initial); // Calcula el dominio de la función en decimales
    double evaluation[101][2] = {0}; // Inicializa en 0 la variable que contiene la tabla de los valores de "X" e "Y"
    int i = 0; // Inicializa un contador que se usará para saber el número de datos de la función
    
    // Evalua e imprime la tabla con las X y f(X) 
    printf("\n    X\t\t  Y\n--------------------------\n");
    for (i = 0; initial < final; initial = initial + increase, i++) {
        evaluation[i][0] = initial;
        evaluation[i][1] = Evaluate(coeExp, initial, 0);
        printf("| %0.f\t| %.2f\t\n--------------------------\n", evaluation[i][0], evaluation[i][1]);
    }
    evaluation[i][0] = final;
    evaluation[i][1] = Evaluate(coeExp, final, 0);
    printf("| %0.f\t| %.2f\t\n--------------------------\n", evaluation[i][0], evaluation[i][1]);

    // Inicializa una matriz y la llena de espacios
    char graph[26][101];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 101; j++) {
            graph[i][j] = 32;
        }
    }

    // Calcula y maximo, y minimo, x minimo Y el rango
    double maxY = -1000000000;
    for (int k = 0; k <= i; k++) {
        if (!isinf(evaluation[k][1]) && evaluation[k][1] > maxY) {
            maxY = evaluation[k][1];
        }
    }
    double minY = 1000000000;
    for (int l = 0; l <= i; l++) {
        if (!isinf(evaluation[l][1]) && evaluation[l][1] < minY) {
            minY = evaluation[l][1];
        }
    }
    double minX = evaluation[0][0];
    // Manejo de excepciones para que siempre se muestren los ejes
    if (minY > 0) minY = 0; 
    if (maxY < 0) maxY = 0; 
    if (minX > 0) {
        minX = 0;
        domain = fabs(final);
    } 
    if (final < 0) domain = fabs(evaluation[0][0]);
    double range = fabs(maxY - minY);

    Graphing(graph, evaluation, domain, range, minX, minY, maxY, i);

    // Imprime la gráfica luego de hacerle todos los cambios
    printf("\n\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 101; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}