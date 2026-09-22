#include <stdio.h>
#include <unistd.h>

void clear_screen() {
    printf("\033[2J");
    fflush(stdout);
}

int main() {
    int sleepTime = 1;

    while (1) {
        for (int y = 17; y >= -17; --y) {

            for (int x = -32; x <= 32; ++x) {

                if (y == 17 || y == -17 || x == 32 || x == -32) {
                    printf("&");
                }
                else {
                    printf(" ");
                }
            }
        printf("\n");
        }
        
        sleep(sleepTime);
        clear_screen();
    }
    

    return 0;
}