#include "board.h"
#include <stdio.h>
#include <stdlib.h>


int create_board(struct board_t **board,int width,int height){
    if(board == NULL || width < 1 || height < 1){
        return 1;
    }
    *board = malloc(sizeof(struct board_t));
    if(*board==NULL){
        return 2;
    }
    (*board)->board = malloc(height * sizeof(char *) );
    if (((*board)->board)==NULL){
        free(*board);
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *((*board)->board+i) = calloc(width+1,sizeof(char));
        if (!(*((*board)->board+i))){
            for (int j = i-1; j >= 0; --j)
                free(*((*board)->board+j));
            free((*board)->board);
            free(*board);
            return 2;
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            *(*((*board)->board+i)+j) = '.';
        }
    }(*board)->is_init = 0;
    (*board)->width = width;
    (*board)->height = height;
    (*board)->move_player_up = &move_player_up;
    (*board)->move_player_down = &move_player_down;
    (*board)->move_player_left = &move_player_left;
    (*board)->move_player_right = &move_player_right;
    return 0;
}
void display_board(const struct board_t *board){
    if(board != NULL || board->height < 1 || board->width < 1 ){
        for(int i=0;i<board->height;i++) {
            for (int j=0;j<board->width;j++)
                printf("%c", *(*(board->board+i)+j));
            printf("\n");
        }
    }
}

void free_board(struct board_t *board){
    if(board == NULL || board->height < 1|| board->width < 1 || !board->board ){}

    for(int i=0; i<board->height;i++){
        free(*(board->board+i));}
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y){
    if(board==NULL||x<0||y<0||board->board==NULL||x>board->width-1||y>board->height-1|| board->is_init == 1){
        return 1;
    }
    if (board->is_init != 0) return 0;
    *(*(board->board + y) + x) = '@';
    board->player.y=y;
    board->player.x=x;
    board->is_init = 1;
    return 0;
}

struct board_t* move_player_up(struct board_t* board){
    if (board==NULL||board->is_init==0||board->height<1||board->width<1||board->board==NULL||board->player.x<0||board->player.y<0||board->player.x>=board->width||board->player.y>=board->height) {
        return NULL;
    }
    *(*(board->board+board->player.y)+board->player.x) = '.';
    if (board->player.y == 0)
        board->player.y = board->height - 1;
    else
        board->player.y --;
    *(*(board->board+board->player.y)+board->player.x) = '@';
    return board;
}


struct board_t* move_player_down(struct board_t* board){
    if (board==NULL||board->is_init==0||board->height<1||board->width<1||board->board==NULL||board->player.x<0||board->player.y<0||board->player.x>=board->width||board->player.y>=board->height) {
        return NULL;
    }
    *(*(board->board+board->player.y)+board->player.x) = '.';
    if (board->player.y == board->height-1)
        board->player.y = 0;
    else
        board->player.y ++;
    *(*(board->board+board->player.y)+board->player.x) = '@';
    return board;
}


struct board_t* move_player_left(struct board_t*  board){
    if (board==NULL||board->is_init==0||board->height<1||board->width<1||board->board==NULL||board->player.x<0||board->player.y<0||board->player.x>=board->width||board->player.y>=board->height) {
        return NULL;
    }
    *(*(board->board+board->player.y)+board->player.x) = '.';
    if (board->player.x == 0)
        board->player.x = board->width-1;
    else
        board->player.x --;
    *(*(board->board+board->player.y)+board->player.x) = '@';
    return board;
}


struct board_t* move_player_right(struct board_t* board){
    if (board==NULL||board->is_init==0||board->height<1||board->width<1||board->board==NULL||board->player.x<0||board->player.y<0||board->player.x>=board->width||board->player.y>=board->height) {
        return NULL;
    }
    *(*(board->board+board->player.y)+board->player.x) = '.';
    if (board->player.x == board->width-1)
        board->player.x = 0;
    else
        board->player.x ++;
    *(*(board->board+board->player.y)+board->player.x) = '@';
    return board;
}
