#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    int x = 1;                    // player position (0 to 2)
    int step = 0;                 // obstacle vertical movement
    int obstaclePos = rand() % 3; // 0,1,2 lane

    int lives = 3;     // number of lives
    int score = 0;     // score increments when obstacle is avoided
    int baseSpeed = 120; // base sleep/ms
    int minSpeed = 30;   // minimum sleep (max difficulty)

    while (1) {

        // ---- INPUT ----
        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT arrow
                x--;

            if (ch == 77 && x < 2)        // RIGHT arrow
                x++;
        }

        // compute dynamic speed and difficulty
        int speed = baseSpeed - score * 3; // speed decreases as score increases
        if (speed < minSpeed) speed = minSpeed;
        int difficultyLevel = 1 + score / 5; // simple level based on score

        // ---- DRAW ----
        system("cls");
        printf("|--- --- ---|\n");
        printf("Lives: %d   Score: %d   Difficulty: %d\n\n", lives, score, difficultyLevel);

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("| %c         |\n", 78);

                else if (obstaclePos == 1)
                    printf("|     %c     |\n", 78);

                else if (obstaclePos == 2)
                    printf("|        %c  |\n", 78);

            } else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER ----
        if (x == 0)
            printf("| %c         |\n", 65);
        else if (x == 1)
            printf("|     %c     |\n", 65);
        else if (x == 2)
            printf("|        %c  |\n", 65);

        // ---- COLLISION ----
        if (step == 10 && x == obstaclePos) {
            lives--;
            if (lives <= 0) {
                system("cls");
                printf("\n========== GAME OVER! ==========\n");
                printf("Final Score: %d\n", score);
                printf("=================================\n\n");
                break;
            } else {
                // show hit briefly then reset obstacle
                system("cls");
                printf("\n*** HIT! Lives left: %d ***\n", lives);
                Sleep(700);
                step = 0;
                obstaclePos = rand() % 3;
                continue;
            }
        }

        Sleep(speed);

        // Move obstacle down
        step++;

        // Reset when reaches bottom -> player avoided obstacle
        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3;
            score++; // increase score for successfully avoiding
        }
    }

    return 0;
}
