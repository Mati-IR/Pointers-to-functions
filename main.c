#include <stdio.h>
#include "board.h"

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }while(c != '\n' && c != EOF);
}
void game_loop(int choice, struct board_t *playboard){
    do {//      main game loop
        if (choice == 'w' || choice == 0 || choice == 's' || choice == 'a' || choice == 'd'){
            display_board(playboard);
            clean_stdin();}
        printf("Choose your choice: ");
        scanf("%c", &choice);

        if (choice == 'w')
            playboard->move_player_up(playboard);
        else if (choice == 's')
            playboard->move_player_down(playboard);
        else if (choice == 'a')
            playboard->move_player_left(playboard);
        else if (choice == 'd')
            playboard->move_player_right(playboard);
        else if (choice != 'q'){
            clean_stdin();
            printf("Incorrect choice\n");
        }
    } while (choice != 'q');
}

int main() {

    int width,height;
    printf("width and height of playing field (x y):");
    if(scanf("%d %d", &width, &height) < 2){
        printf("Incorrect input");
        return 1;
    }

    if( width < 1 || height < 1 ){
        printf("Incorrect input data");
        return 2;
    }

    struct board_t *playboard;
    struct board_t **ptr = &playboard;
    int create = create_board(ptr, width, height);
    if( create == 2){
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Starting coordinates: (x y)\n");
    int x,y;
    if (scanf("%d %d", &x, &y)!=2){
        printf("Incorrect input");
        free_board(playboard);
        return 1;
    } else if (width < 0 || height < 0 || set_player(playboard, x, y) != 0){
        printf("Incorrect input data");
        free_board(playboard);
        return 2;
    }


    char choice = 0;

    game_loop(choice, playboard);

    free_board(playboard);
    return 0;
}

