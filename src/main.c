#include <stdio.h>
#include <unistd.h>

int xMinScreen = 0;
int xMaxScreen = 60;
int yMinScreen = 0;
int yMaxScreen = 35;

typedef struct {
    int x;
    int y;
} Point;

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
    int sleepTime = 200 * 1000; //ms
    int snakeDirection = 0; // 0N, 1E, 2S, 3W
    int isGameOver = 0;
    int snakeSize = 3;

    Point head;
    head.x = 30;
    head.y = 15;

    Point body[100];

    while (1) {
        for (int i = snakeSize - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }
        body[0] = head;

        switch (snakeDirection) {
            case 0: // going up
                if (!isYOutOfBounds(head.y - 1)) {
                    head.y--;
                } else isGameOver = 1;
                break;

            case 1: // going right
                if (!isXOutOfBounds(head.x + 1)) {
                    head.x++;
                } else isGameOver = 1;
                break;

            case 2: // going down
                if (!isYOutOfBounds(head.y + 1)) {
                    head.y++;
                } else isGameOver = 1;
                break;
                
            case 3: // going left
                if (!isXOutOfBounds(head.x - 1)) {
                    head.x--;
                } else isGameOver = 1;
                break;
        }

        if (isGameOver) {
            printf("GAME OVER\n");
            break;
        }

        for (int y = yMinScreen; y <= yMaxScreen; ++y) {

            for (int x = xMinScreen; x <= xMaxScreen; ++x) {

                if (y == yMinScreen || y == yMaxScreen || x == xMinScreen || x == xMaxScreen) {
                    printf("&");
                } 
                else if (y == head.y && x == head.x) {
                    printf("O");
                }
                else {
                    int isBody = 0;
                    for (int i = 0; i < snakeSize; i++) {
                        if (x == body[i].x && y == body[i].y) {
                            isBody = 1;
                            break;
                        }
                    }
                    if (isBody) {
                        printf("o");
                    }
                    else {
                        printf(" ");
                    }
                    
                }
            }
        printf("\n");
        }
        
        usleep(sleepTime);
        clear_screen();
    }
    

    return 0;
}