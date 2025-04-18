#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, key, score;
int x, y, fruitx, fruity;
void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitx = rand() % WIDTH;
    fruity = rand() % HEIGHT;
    while (fruitx == 0)
        fruitx = rand() % WIDTH;
    while (fruity == 0)
        fruity = rand() % HEIGHT;
    score = 0;
}
void draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruity && j == fruitx)
                printf("*");
            else {
                int printTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        printf("o");
                        printTail = 1;
                    }
                }
                if (!printTail)
                    printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");
    printf("Score = %d\n", score);
    printf("Press W, A, S, D for movement.\n");
    printf("Press X to quit the game.\n");
}
void input() {
    if (kbhit()) {
        switch (tolower(getch())) {
        case 'a': 
            if (key != 2) key = 1;
            break;
        case 'd': 
            if (key != 1) key = 2;
            break;
        case 'w':
            if (key != 4) key = 3;
            break;
        case 's': 
            if (key != 3) key = 4;
            break;
        case 'x': 
            gameover = 1;
            break;
        }
    }
}
void logic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (key) {
    case 1: 
        x--;
        break;
    case 2: 
        x++;
        break;
    case 3: 
        y--;
        break;
    case 4: 
        y++;
        break;
    default:
        break;
    }
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }
    if (x == fruitx && y == fruity) {
        fruitx = rand() % WIDTH;
        fruity = rand() % HEIGHT;
        while (fruitx == 0)
            fruitx = rand() % WIDTH;
        while (fruity == 0)
            fruity = rand() % HEIGHT;
        
        score += 10;
        snakeTailLen++;
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();    
        input();   
        logic();   
        Sleep(66); 
    }

    return 0;
}
