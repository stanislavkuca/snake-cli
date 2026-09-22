#include <stdio.h>
#include <unistd.h>

int xMinScreen = 0;
int xMaxScreen = 60;
int yMinScreen = 0;
int yMaxScreen = 35;

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

int isXOutOfBounds(int xCoords) {
        if (xCoords > xMinScreen && xCoords < xMaxScreen) {
            return 0;
        } else return 1;
    }

int isYOutOfBounds(int yCoords) {
        if (yCoords > yMinScreen && yCoords < yMaxScreen) {
            return 0;
        } else return 1;
    }


int main() {
    int sleepTime = 100 * 1000; //ms
    int xStartSnake = 30;
    int yStartSnake = 15;
    int xRealSnake = xStartSnake;
    int yRealSnake = yStartSnake;
    int snakeDirection = 0; // 0N, 1E, 2S, 3W

    while (1) {
        switch (snakeDirection) {
            case 0:
                if (!isYOutOfBounds(yRealSnake + 1)) {
                    yRealSnake++;
                }
                break;
            case 1:
                if (!isXOutOfBounds(xRealSnake + 1)) {
                    xRealSnake++;
                } 
                break;
            case 2:
                if (!isYOutOfBounds(yRealSnake - 1)) {
                    yRealSnake--;
                }
                break;
            case 3:
                if (!isXOutOfBounds(xRealSnake - 1)) {
                    xRealSnake--;
                }
                break;
        }

        for (int y = yMinScreen; y <= yMaxScreen; ++y) {

            for (int x = xMinScreen; x <= xMaxScreen; ++x) {

                if (y == yMinScreen || y == yMaxScreen || x == xMinScreen || x == xMaxScreen) {
                    printf("&");
                } 
                else if (y == yRealSnake && x == xRealSnake) {
                    printf("O");
                }
                else {
                    printf(" ");
                }
            }
        printf("\n");
        }
        
        usleep(sleepTime);
        clear_screen();
    }
    

    return 0;
}