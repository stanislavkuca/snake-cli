#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

struct termios orig_termios;

void disable_raw_mode() {
    printf("\033[?25h");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void enable_raw_mode() {
    printf("\033[?25l");
    fflush(stdout);
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}


typedef struct {
    int x;
    int y;
} Point;

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}


int xMinScreen = 0;
int xMaxScreen = 25;
int yMinScreen = 0;
int yMaxScreen = 10;

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
    enable_raw_mode();
    srand(time(NULL));

    int sleepTime = 200 * 1000; //ms
    int snakeDirection = 1; // 0N, 1E, 2S, 3W
    int isGameOver = 0;
    int snakeSize = 3;
    int xApple = 0;
    int yApple = 0;
    int isAppleEaten = 1;
    
    Point head;
    head.x = rand() % xMaxScreen + 1;
    if (head.x > (xMaxScreen / (xMinScreen + 2))) {head.x -= xMaxScreen / 5;}
    head.y = rand() % yMaxScreen + 1;
    if (head.y == yMaxScreen) {head.y--;}

    Point body[100];

    while (1) {
        for (int i = snakeSize - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }
        body[0] = head;

        if (isAppleEaten) {
            int isOnSnake = 1;

            do {
                isOnSnake = 0;

                xApple = rand() % (xMaxScreen - 1) + 1;
                yApple = rand() % (yMaxScreen - 1) + 1;

                if (xApple == head.x && yApple == head.y) {
                    isOnSnake = 1;
                }

                for (int i = 0; i < snakeSize; i++) {
                    if (xApple == body[i].x && yApple == body[i].y) {
                        isOnSnake = 1;
                        break;
                    }
                }
            } while (isOnSnake == 1);
            

            isAppleEaten = 0;
        }

        int ch = getchar();
        if(ch != EOF) {
            if (ch == 'w') snakeDirection = 0; // North
            if (ch == 'd') snakeDirection = 1; // East
            if (ch == 's') snakeDirection = 2; // South
            if (ch == 'a') snakeDirection = 3; // West
            if (ch == 'q') break;
        }

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
                    for (int i = 1; i < snakeSize; i++) {
                        if (head.x == body[i].x && head.y == body[i].y) {
                            isGameOver = 1;
                            break;
                        }
                    }

                    printf("O");

                    if (head.y == yApple && head.x == xApple) {
                        isAppleEaten = 1;
                        snakeSize++;
                    }
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
                    else if (x == xApple && y == yApple) {
                        printf("x");
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
    
    disable_raw_mode();
    return 0;
}