#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Term(char equation[], int coeExp[10][2], int previousSign, int pos, int limit) {
    char coe[12];
    int i = 0;
    while (equation[previousSign + i] < 60 && previousSign + i < limit) {
        coe[i] = equation[previousSign + i];
        i++;
    }
    if (i == 0 || (i == 1 && equation[previousSign] == '-')) {
        coe[i] = '1';
        coe[i + 1] = '\0';
    } else {
        coe[i] = '\0';
    }
    i++;

    char exp[10];
    int j = 0;
    if (previousSign + i == limit) {
        exp[j] = '1';
        j++;
    } else if (previousSign + i > limit) {
        exp[j] = '0';
        j++;
    } else {
        if (equation[previousSign + i] == '(') {
            i++;
        }
        while (previousSign + i < limit) {
            exp[j] = equation[previousSign + i];
            j++; i++;
        }
    }
    exp[j] = '\0';

    coeExp[pos][0] = atoi(coe);
    coeExp[pos][1] = atoi(exp);
    printf("\n---------------------------------\n| %i\t\t", coeExp[pos][0]);
    printf("| %i\t\t|", coeExp[pos][1]);
}

void getCoeExp(char equation[], int coeExp[10][2], int previousSign, int pos) {
    int i = 1;
    while (equation[i - 1] != '\0') {
        if ((equation[i] == '-' && equation[i - 1] != '(') || equation[i] == '+' || equation[i] == '\0') {
            Term(equation, coeExp, previousSign, pos, i);
            pos++;
            previousSign = i;
        }
        i++;
    }
    while (pos < 10) {
        coeExp[pos][0] = 0;
        coeExp[pos][1] = 1;
        pos++;
    }
}

double Evaluate(int coeExp[10][2], int x, int count) {
    if (count == 10) {
        return 0;
    } else {
        return coeExp[count][0] * pow(x, coeExp[count][1]) + Evaluate(coeExp, x, count + 1);
    }
}

void Graphing(char graph[26][101], double evaluation[101][2], double dom, double ran, double minX, double minY, double maxY, double nDatos) {
    double zeroX = (fabs(0 - minX) * 99 / dom);
    double zeroY = (fabs(maxY - 0) * 24 / ran);

    for (int i = 0; i < 100; i++) {
        graph[(int)round(zeroY)][i] = 196;
    }
    for (int j = 0; j < 26; j++) {
        graph[j][(int)round(zeroX)] = 179;
    }
    graph[(int)round(zeroY)][(int)round(zeroX)] = 197;

    for (int m = 0; m <= nDatos; m++) {
        double x = (fabs(evaluation[m][0] - minX) * 99 / dom);
        double y = (fabs(maxY - evaluation[m][1]) * 24 / ran);
        
        int xRounded = (int)round(x);
        int yRounded = (int)round(y);

        if (xRounded >= 0 && xRounded < 101 && yRounded >= 0 && yRounded < 26) {
            graph[yRounded][xRounded] = 'x';
        }
    }

    for (int k = 0; k <= dom; k++) {
        double xValue = minX + (k * (dom / nDatos));
        char xLabel[10] = "          ";
        sprintf(xLabel, "%.0f", xValue);
        int xPos = (int)round(fabs(xValue - minX) * 99 / dom);
        if (xPos >= 0 && xPos < 101) {
            for (int l = 0; l < 10; l++) {
                if (xLabel[l] != '\0') {
                    graph[(int)round(zeroY) + 1][xPos + l] = xLabel[l];
                }
            }
        }
    }

    for (int k = 0; k <= 5; k++) { 
    double yValue = minY + k * (ran / 5); 
    char yLabel[20];
    sprintf(yLabel, "%.2f", yValue); 
    int yPos = (int)round(fabs(maxY - yValue) * 24 / ran); 
    if (yPos >= 0 && yPos < 26) {
        for (int l = 0; l < 20 && yLabel[l] != '\0'; l++) {
            if (zeroX < 5) {
                graph[yPos][(int)round(zeroX) + 1 + l] = yLabel[l]; 
            } else {
                graph[yPos][(int)round(zeroX) - 5 + l] = yLabel[ 1];
            }
        }
    }
}
}

int main() {
    char equation[30] = "";

    printf("\nIngrese la ecuaci%cn a graficar: ", 162);
    scanf("%s", equation);

    int coeExp[10][2];
    printf("\nCOEFICIENTE         POTENCIA");
    getCoeExp(equation, coeExp, 0, 0);
    printf("\n---------------------------------");

    int initial = 0, final = 0, increase = 0;
    printf("\n\nIngrese rango incial: ");
    scanf("%i", &initial);
    printf("Ingrese rango final: ");
    scanf("%i", &final);
    printf("Ingrese el incremento: ");
    scanf("%i", &increase);

    double domain = fabs(final - initial);

    double evaluation[101][2];
    int i = 0;
    printf("\n    X\t\t  Y\n--------------------------\n");
    for (i = 0; initial < final; initial = initial + increase, i++) {
        evaluation[i][0] = initial;
        evaluation[i][1] = Evaluate(coeExp, initial, 0);
        printf("| %0.f\t| %.2f\t\n--------------------------\n", evaluation[i][0], evaluation[i][1]);
    }

    evaluation[i][0] = final;
    evaluation[i][1] = Evaluate(coeExp, final, 0);
    printf("| %0.f\t| %.2f\t\n--------------------------\n", evaluation[i][0], evaluation[i][1]);

    char graph[26][101];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 101; j++) {
            graph[i][j] = 32;
        }
    }

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

    if (minY > 0) minY = 0; 
    if (maxY < 0) maxY = 0; 
    if (minX > 0) {
        minX = 0;
        domain = fabs(final);
    } 
    if (final < 0) domain = fabs(evaluation[0][0]);

    double range = fabs(maxY - minY);
    Graphing(graph, evaluation, domain, range, minX, minY, maxY, i);

    printf("\n\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 101; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}