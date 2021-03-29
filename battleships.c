#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define rows 9
#define cols 9

int carrier[] = {5,5};
int battleship[] = {4,4};
int destroyer[] = {3,3};
int submarine[] = {2,2};
int patrol[] = {2,2};
int result[] ={0,0};
int game_over = 0;

void Display(int board_1[rows][cols], int board_2 [rows][cols], int player) {
    if(player == 1){
        for(int i =0; i<rows; i++){
            for(int j=0; j<cols;j++){
                if(i==0 && j ==0){
                    printf(" ");
                }else if (i == 0 && j !=0){
                    printf(" %d",j);
                }else if (i !=0 && j ==0){
                    printf("%c|", 'A'+i-1);
                }else{
                    if(board_2[i][j]== 0){
                        printf("X|");
                    }else if (board_2[i][j] == -2){
                        printf("0|");
                    }else{
                        printf(" |");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    else{
        for(int i =0; i<rows; i++){
            for(int j=0; j<cols;j++){
                if(i==0 && j ==0){
                    printf(" ");
                }else if (i == 0 && j !=0){
                    printf(" %d",j);
                }else if (i !=0 && j ==0){
                    printf("%c|", 'A'+i-1);
                }else{
                    if(board_1[i][j]== 0){
                        printf("X|");
                    }else if (board_1[i][j] == -2){
                        printf("0|");
                    }else{
                        printf(" |");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

void Setup(int board_1[rows][cols], int board_2[rows][cols], int num[100], char **ships){
    for(int i =0; i < rows; i++){
        for(int j =0; j<cols;j++){
            if (i != 0 && j!=0){
                board_1[i][j] = -1;
                board_2[i][j] = -1;
            }
        }
    }
    int k = 0;
    int x = 0;
    unsigned char y;
    char ori;
    int Y = 0;
    printf("Player 1, please set up your ships (y, x, orientation)\n");
    while(k<5){
        printf("%s: ",ships[k]);
        if(scanf(" %c %d %c",&y,&x,&ori)!=3){
            printf("Invalid ship configuration\n");
        }else{
            Y = num[y];
            int all_set =1;
            int n = 5-k;
            if(n<2){
                n=2;
            }
            if(x<1||x>8||Y<1||Y>8){
                printf("Invalid ship configuration\n");
            }else if('V'== ori){
                if(n+Y>9){
                    printf("Invalid ship configuration\n");
                }else{
                    for(int i =0;i<n;i++){
                        if(board_1[Y+i][x]!=-1){
                            printf("Invalid ship configuration\n");
                            all_set = 0;
                            break;
                        }else{
                            board_1[Y+i][x]=(5-k);
                        }
                    }if(all_set)
                        k++;
                }
            }else if('H' == ori){
                if(n+x>9){
                    printf("Invalid ship configuration\n");
                }else{
                    for(int i =0;i<n;i++){
                        if(board_1[Y][x+i]!=-1){
                            printf("Invalid ship configuration\n");
                            all_set = 0;
                            break;
                        }else{
                            board_1[Y][x+i]=(5-k);
                        }
                    }if(all_set)
                        k++;
                }
            }
            else{
                printf("Invalid ship configuration\n");
            }
        }
        fflush(stdin);
    }

    k = 0;
    printf("\n\nPlayer 2, please set up your ships (y, x, orientation)\n");
    while(k<5){
        printf("%s: ",ships[k]);
        scanf(" %c %d %c",&y,&x,&ori);
        Y = num[y];
        int all_set =1;
        int n = 5-k;
        if(n<2)
        n=2;
        if(x<1||x>8||Y<1||Y>8){
            printf("Invalid ship configuration\n");
        }else if('V'== ori){
            if(n+Y>9){
                printf("Invalid ship configuration\n");
            }else{
                for(int i =0;i<n;i++){
                    if(board_2[Y+i][x]!=-1){
                        printf("Invalid ship configuration\n");
                        all_set = 0;
                        break;
                    }else{
                        board_2[Y+i][x]=(5-k);
                    }
                }if(all_set)
                    k++;
            }
        }else if('H' == ori){
            if(n+x>9){
                printf("Invalid ship configuration\n");
            }else{
                for(int i =0;i<n;i++){
                    if(board_2[Y][x+i]!=-1){
                        printf("Invalid ship configuration\n");
                        all_set = 0;
                        break;
                    }else{
                        board_2[Y][x+i]=(5-k);
                    }
                }if(all_set)
                    k++;
            }
        }
        else{
            printf("Invalid ship configuration\n");
        }
        fflush(stdin);
    }

    printf("\nAll boats set up, Player 1 can now strike.\n\n");
}

int fireShip(int board[rows][cols], int y, int x, int player){
    if(board[y][x]== -2 || board[y][x] == 0){
        printf("You have already fired at this location\n");
        return 0;
    }else{

        switch(board[y][x]){
            case 5:
                board[y][x] = 0;
                carrier[player]--;
                result[player]++;
                if(carrier[player]==0){
                    printf("\nWe have sunk your Carrier!\n");
                    break;
                }
                else{
                    printf("\nWe have hit the target!\n");
                    break;
                }

            case 4:
                board[y][x] = 0;
                battleship[player]--;
                result[player]++;
                if(battleship[player] > 0){
                    printf("\nWe have hit the target!\n");
                    break;
                }else{
                    printf("\nWe have sunk your Battleship!\n");
                    break;
                }
            case 3:
                board[y][x] = 0;
                destroyer[player]--;
                result[player]++;
                if(destroyer[player]> 0){
                    printf("\nWe have hit the target!\n");
                    break;
                }else{
                    printf("\nWe have sunk your Destroyer!\n");
                    break;
                }
            case 2:
                board[y][x] = 0;
                submarine[player]--;
                result[player]++;
                if(submarine[player]> 0){
                    printf("\nWe have hit the target!\n");
                    break;
                }else{
                    printf("\nWe have sunk your Submarine!\n");
                    break;
                }
            case 1:
                board[y][x] = 0;
                patrol[player]--;
                result[player]++;
                if(patrol[player]> 0){
                    printf("\nWe have hit the target!\n");
                    break;
                }else{
                    printf("\nWe have sunk your Patrol Boat!\n");
                    break;
                }
            default:
                board[y][x] = -2;
                printf("\nYou have missed!\n");
                break;
        }

        if(result[player] == 16){
            if(player%2 == 0){
                player = 2;
            }else{
                player = 1;
            }
            printf("\nPlayer %d wins!\n",player);
            game_over = 1;
            return 2;

        }else{
            if(player){
                printf("\nPlayer 2's turn\n\n");
            }
            else{
                printf("\nPlayer 1's turn\n\n");
            }
        }

    }
    return 1;
}




int main(void){
    int player = 1;
    char *ships[5] = {"Carrier","Battleship","Destroyer","Submarine","Patrol Boat"};
    int x_axis;
    unsigned char y_axis;
    int board_1[rows][cols];
    int board_2[rows][cols];
    char str[20];
    int num[100] ={0};
    num['A'] = 1;
    num['B'] = 2;
    num['C'] = 3;
    num['D'] = 4;
    num['E'] = 5;
    num['F'] = 6;
    num['G'] = 7;
    num['H'] = 8;

    Setup(board_1,board_2,num,ships);
    fflush(stdin);

    while(1){
        player = player%2;
        fgets(str,20,stdin);
        if(strncmp("shots",str,5)==0){
            printf("\n");
            Display(board_1,board_2,player);
        }else if (strncmp("exit",str,4) == 0){
            break;
        }else if (strncmp("fire",str,4) == 0){
            x_axis = atoi((str+7));
            y_axis = num[str[5]];

            if(x_axis<1||x_axis>8||y_axis<1||y_axis>8){
                printf("Invalid coordinates\n");
            }else{
                if(player == 1){
                    player +=fireShip(board_2,y_axis,x_axis,player);
                }
                else{
                    player +=fireShip(board_1,y_axis,x_axis,player);
                }

                if(game_over){
                    break;
                }
            }
        }
    }



    return 0;
}
