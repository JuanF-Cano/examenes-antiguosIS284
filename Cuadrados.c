#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MakeRectangle(int x1, int x2, int y1, int y2, char screen[30][60]) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            if (screen[i][j] == 46) {
                screen[i][j] = 120;
            }
        }
    }
}

int FindRectangle(char screen[30][60], int x, int y, int rectangle[3][2]) {
    int i = x + 1;
    int j = y + 1;

    while (screen[y][i] != 111 && i < 59) i++;
    if (screen[y][i] == 111) {
        while (screen[j][i] != 111 && j < 29) j++;
        if (screen[j][i] == 111 && screen[j][x] == 111) {
            MakeRectangle(x, i, y, j, screen);
            if ((i - x) * (j - y) < (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1])) {
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
}

int main() {
    srand(time(NULL));

    char screen[30][60];
    int rectangle[3][2] = {{0, 0}, {59, 0}, {59, 59}};
    int area = 0;

    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 60; c++) {
            screen[r][c] = 46;
            int corner = rand() % 20;
            if (!corner) {
                screen[r][c] = 111;
            }
            printf("%c", screen[r][c]);
        }
        printf("\n");
    }

    printf("\n");

    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 60; c++) {
            if (screen[r][c] == 111) {
                if (FindRectangle(screen, c, r, rectangle)) {
                    area = (rectangle[1][0] - rectangle[0][0]) * (rectangle[2][1] - rectangle[1][1]);
                }
            }
        }
    }
    
    printf("\n");
    for (int r = 0; r < 30; r++) {
        for (int c = 0; c < 60; c++) {
            printf("%c", screen[r][c]);
        }
        printf("\n");
    }
    
    printf("\nEl %crea del m%cs peque%co seria %i x %i %i\n", 160, 160, 164, 
    rectangle[1][0] - rectangle[0][0], rectangle[2][1] - rectangle[1][1], area);

    return 0;
}