#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void welcome_screen();
int choose_char();
void print_arr(char *, int);
int handle_io(char *);
char check_gamestate(char *);

int main() {
    char player_1_char, player_2_char;
    switch (choose_char())
    {
    case 1:
        player_1_char = 'x';
        player_2_char = 'o';
        break;
    case 2:
        player_1_char = 'x';
        player_2_char = 'o';
        break;
    default:
        break;
    }
    // printf("Character for player 1: %c\n", player_1_char);
    // printf("Character for player 2: %c\n", player_2_char);


    // gameloop variables:
    char table[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
    int curr_player = 1; // 1 for player 1, 2 for player 2;
    int cell;
    int turns =1;
    char winner = '-';
    // gameloop
    while (1) {
        switch (curr_player)
        {
        case 1:
            printf("\nTurn: Player 1 (%c)\n", player_1_char);
            cell = handle_io(table);
            table[cell-1] = player_1_char;    
            curr_player = 2;
            break;
        case 2:
            printf("\nTurn: Player 2 (%c)\n" ,player_2_char);
            cell = handle_io(table);
            table[cell-1] = player_2_char;
            curr_player = 1;
            break;
        default:
            break;
        }

        // check game every iteration to see if the game has ended;
        if(turns>=5){   // game is decided after atlest 5 game turns
            winner = check_gamestate(table);
            if(winner==player_1_char) {
                printf("Congratulation!!! player 1 (%c) you have won\n", player_1_char);
                break;
            }
            if(winner==player_2_char) {
                printf("Congratulation!!! player 2 (%c) you have won\n", player_2_char);
                break;
            }
            if(winner=='-'&&turns>=9) {
                printf("Its a draw!!!\n");
                break;
            }
        }

        turns++;
        //break;
    }
    return 0;
}

void welcome_screen() {
    printf("Select character for player 1:\n");
    printf("1: x\n");
    printf("2: o\n");
}

int choose_char() {
    int opt;
    char msg[100] = "";
    do
    {
        printf("%s", msg);
        welcome_screen();
        scanf("%d", &opt);
        strcat(msg, "!!!Choose between given option 1 or 2\n\n");
    } while (opt < 1 || opt > 2);
    return opt;
}

void print_arr(char *ch, int n) {
    for(int i=0; i<n; i++) {
        if(i%3==0)
            printf("\n");
        printf("%5c", *ch);
        ch++;
    }
    printf("\n");
}

int handle_io(char *arr) {
    printf("Enter cell to fill (1-9)\n");
    int cell, available = 1; // if cell is not available availables value is changed to 0;
    char msg[100] = "";
    do
    {
        printf("%s\n", msg);
        print_arr(arr, 9);
        scanf("%d", &cell);
        if(cell<1||cell>9) {
            //printf("test cell limit\n");
            strcat(msg, "!!!Enter a valid position (1-9)\n");
            continue;
            //printf("test continue 1");
        }
        //printf("test continue 2\n");
        if(*(arr+cell-1)!='-') {
            available=0;
            strcat(msg, "!!!selected cell is not available.\n");
        }

    } while (cell<1||cell>9||available==0);
    return cell;
}

char check_gamestate(char *arr) {
    char winner = '-';
    // row and column checking
    for(int i=0; i<3; i++) {
        //row checking
        char *start = arr + 3*i;
        if(*start==*(start+1) && *start==*(start+2)) {
            winner = *start;
            return winner;
        }
        //column checking
        start = arr+i;
        if(*start==*(start+3) && *start==*(start+6)) {
            winner = *start;
            return winner;
        }
    }
    // diagonal checking
    
    // main diagonal
    if(*arr==*(arr+4) && *arr==*(arr+8)){
        winner = *arr;
        return winner;
    }
    //antu diagonal
    if(*(arr+2)==*(arr+4)&&*(arr+2)==*(arr+6)) {
        winner = *(arr+2);
        return winner;
    }
    return winner;
}