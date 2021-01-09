#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkaround(char* point, int direct ,int dimension) {
    //direction 0=up,1=right,2=down,3=left
    //true for safe, false for obstacle
    int returnbool;
    if (direct == 0) {
        if (*(point - 2 * dimension) != '#') {
            returnbool = 0;
        }
        else {
            if (*(point - dimension - 1) != '#' || *(point - dimension + 1) != '#') {
                returnbool = 0;
            }
            else {
                if (*(point - dimension) != 'O') {
                    returnbool = 1;
                }
                else {
                    returnbool = 0;
                }
            }
        }
    }
    else if (direct == 1) {
        if (*(point +2) != '#') {
            returnbool = 0;
        }
        else {
            if (*(point - dimension + 1) != '#' || *(point + dimension + 1) != '#') {
                returnbool = 0;
            }
            else {
                if (*(point+1) != 'O') {
                    returnbool = 1;
                }
                else {
                    returnbool = 0;
                }
            }
        }
    }
    else if (direct == 2) {
        if (*(point + 2*dimension) != '#') {
            returnbool = 0;
        }
        else {
            if (*(point + dimension - 1) != '#' || *(point + dimension + 1) != '#') {
                returnbool = 0;
            }
            else {
                if (*(point + dimension) != 'O') {
                    returnbool = 1;
                }
                else {
                    returnbool = 0;
                }
            }
        }
    }
    else if (direct==3){
        if (*(point - 2) != '#') {
            returnbool = 0;
        }
        else {
            if (*(point - dimension - 1) != '#' || *(point + dimension - 1) != '#') {
                returnbool = 0;
            }
            else {
                if (*(point - dimension) != 'O') {
                    returnbool = 1;
                }
                else {
                    returnbool = 0;
                }
            }
        }
    }
    else {
        printf("Check around Error!");
        exit(EXIT_FAILURE);
    }
    //printf("Check around boolean= %d\n", returnbool);
    return returnbool;
}
int checkborder (char* point, char* maze, int direction, int dimension) {
    int checkborder = 1;
    if (direction%4== 0) {
        char* upperlimit = maze+dimension;
        //printf("Entering!\n");
        if ((point - dimension) < upperlimit) {
            checkborder = 0;
        }
    }
    else if (direction == 1) {
        char* rightlimit = maze + dimension-2;
        if ((point-rightlimit)%dimension==0) {
            checkborder = 0;
        }
    }
    else if (direction == 2) {
        char* downlimit = maze + dimension*(dimension-1)-1;
        if ((point + dimension) > downlimit) {
            checkborder = 0;
        }
    }
    else {
        char* leftlimit = maze + 1;
        if ((point - leftlimit) % dimension == 0) {
            checkborder = 0;
        }
    }
    //printf("Checkborder= %d", checkborder);
    return checkborder;
}
int backtrackingactivator(int* directionarray){
    int backtrackingmode=0;
    if (directionarray[0] == 1 && directionarray[1] == 1 && directionarray[2] == 1 && directionarray[3] == 1) {
        backtrackingmode = 1;
    }
    return backtrackingmode;
}
int backtrackingmode(char* point, int dimension) {
    //used for backtracker direction finder
    *point = 'O';
    int direction;
    if (*(point + 1) == 'X') {
        point += 1;
        //printf("Condition1\n");
        *point = 'O';
        direction = 1;
        return direction;
    }
    else if (*(point - 1) == 'X') {
        point -= 1;
        //printf("Condition2\n");
        *point = 'O';
        direction = 3;
        return direction;
    }
    else if (*(point + dimension) == 'X') {
        point += dimension;
        //printf("Condition3\n");
        *point = 'O';
        direction = 2;
        return direction;
    }
    else if (*(point - dimension) == 'X') {
        point -= dimension;
        //printf("Condition4\n");
        *point = 'O';
        direction = 0;
        return direction;
    }
    if (*(point + 1) == 'O') {
        point += 1;
        //printf("Condition5\n");
        //*point = '.';
        direction = 1;
    }
    else if (*(point - 1) == 'O') {
        point -= 1;
        //printf("Condition6\n");
        //*point = '.';
        direction = 3;
    }
    else if (*(point + dimension) == 'O') {
        point += dimension;
        //printf("Condition7\n");
        //*point = '.';
        direction = 2;
    }
    else if (*(point - dimension) == 'O') {
        point -= dimension;
        //printf("Condition8\n");
        //*point = '.';
        direction = 0;
    }
    else {
        printf("Backtracking error!");
        exit(EXIT_FAILURE);
    }
    return direction;
}
int directiongenerator() {
    int direction = rand() % 4;
    return direction;
}

int main()
{
    srand(time(NULL));
    int dimension;
    scanf_s("%d", &dimension);
    char* maze = (char*)malloc(dimension * dimension * sizeof(char*));
    char* endmaze = maze + dimension * dimension;
    int direction; //0 up, 1 right, 2 down, 3 left
    int directionarray[] = { 0,0,0,0 };
    for (char* point = maze; point <= endmaze; point++) {
        *point = '#';
    }
    int backtrackingbool = 0; //1 for true
    int situationsurvey;
    char* endingline = maze + dimension - 2;
    char* point = maze + dimension + 1;//roaming pointer in the maze
    *point = 'X';
    int borderchecker;
    char* startingpoint = maze;
    int mazeswitch = 1; //0 if immediately move
    while(*(startingpoint+dimension+1)!='O'||mazeswitch) {
        if (backtrackingbool) {
            //printf("Backtrackingbegins!\n");
            direction=backtrackingmode(point, dimension);
            if (direction % 4 == 0)point -= dimension;
            else if (direction % 4 == 1)point+=1;
            else if (direction % 4 == 2)point+=dimension;
            else point-=1;
            direction += 2;
            situationsurvey = checkaround(point, (direction + 1) % 4, dimension);
            maze = startingpoint;
            /*for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    printf("%c", *maze);
                    maze++;
                }
                printf("\n");
            }*/
            if (situationsurvey) {
                maze = startingpoint;
                borderchecker = checkborder(point, maze, (direction + 1) % 4, dimension);
                if (borderchecker) {
                    for (int j = 0; j < 4; j++) {
                        directionarray[j] = 0;
                    }
                    backtrackingbool = 0;
                    //printf("backtracking ended!%d\n", direction);
                    *point = 'X';
                    //printf("%d\n", point - startingpoint);
                }
            }
            else {
                situationsurvey = checkaround(point, (direction + 2) % 4, dimension);
                if (situationsurvey) {
                    maze = startingpoint;
                    borderchecker = checkborder(point, maze, (direction + 2) % 4, dimension);
                    if (borderchecker) {
                        for (int j = 0; j < 4; j++) {
                            directionarray[j] = 0;
                        }
                        backtrackingbool = 0;
                        //printf("backtracking ended!%d\n", direction);
                        *point = 'X';
                        //printf("%d\n", point - startingpoint);
                    }
                }
                else {
                    situationsurvey = checkaround(point, (direction + 3) % 4, dimension);
                    if (situationsurvey) {
                        maze = startingpoint;
                        borderchecker = checkborder(point, maze, (direction + 2) % 4, dimension);
                        if (borderchecker) {
                            for (int j = 0; j < 4; j++) {
                                directionarray[j] = 0;
                            }
                            backtrackingbool = 0;
                            //printf("backtracking ended!%d\n", direction);
                            *point = 'X';
                            //printf("%d\n", point - startingpoint);
                        }
                    }
                }
            }
        }
        else {
            direction = directiongenerator();
            if (directionarray[direction] == 1) {
                //printf("Checking\n");
                backtrackingbool=backtrackingactivator(directionarray);
                //if (backtrackingbool == 1)printf("FULL!");
                /*for (int z = 0; z < 4; z++) {
                    printf("%d",directionarray[z]);
                }
                printf("\n");*/
                continue;
            }
            else {
                maze = startingpoint;
                //printf("Running!\n");
                situationsurvey = checkaround(point, direction, dimension);
                if (situationsurvey) {
                    //printf("Running! Level 2\n");
                    directionarray[(direction + 2) % 4] = 1;
                    if (direction == 0) {
                        //up
                        borderchecker = checkborder(point, maze, direction, dimension);
                        //printf("Border checker= %d", borderchecker);
                        if (borderchecker) {
                            mazeswitch = 0;
                            //printf("Direction 0\n");
                            //printf("i= %d\n", i);
                            if (*(point - dimension) == 'O')directionarray[direction] = 1;
                            else {
                                for (int j = 0; j < 4; j++) {
                                    directionarray[j] = 0;
                                }
                                point -= dimension;
                                *point = 'X';
                            }
                        }
                        else {
                            directionarray[direction] = 1;
                        }

                    }
                    else if (direction == 1) {
                        //right
                        borderchecker = checkborder(point, maze, direction, dimension);
                        if (borderchecker) {
                            //printf("Direction 1\n");
                            //printf("i= %d\n", i);
                            if (*(point +1) == 'O')directionarray[direction] = 1;
                            else {
                                for (int j = 0; j < 4; j++) {
                                    directionarray[j] = 0;
                                }
                                point += 1;
                                *point = 'X';
                            }
                        }
                        else {
                            directionarray[direction] = 1;
                        }
                    }
                    else if (direction == 2) {
                        //down
                        borderchecker = checkborder(point, maze, direction, dimension);
                        if (borderchecker) {
                            mazeswitch = 0;
                            //printf("Direction 2\n");
                            //printf("i= %d\n", i);
                            if (*(point + dimension) == 'O')directionarray[direction] = 1;
                            else {
                                for (int j = 0; j < 4; j++) {
                                    directionarray[j] = 0;
                                }
                                point += dimension;
                                *point = 'X';
                            }
                        }
                        else {
                            directionarray[direction] = 1;
                        }
                    }
                    else {
                        //left
                        borderchecker = checkborder(point, maze, direction, dimension);
                        if (borderchecker){ 
                            mazeswitch = 0;
                            //printf("Direction 3\n");
                            //printf("i= %d\n", i);
                            if (*(point -1) == 'O')directionarray[direction] = 1;
                            else {
                                for (int j = 0; j < 4; j++) {
                                    directionarray[j] = 0;
                                }
                                point -= 1;
                                *point = 'X';
                            }
                        }
                        else {
                            directionarray[direction] = 1;
                        }
                    }
                }
                else {
                    directionarray[direction] = 1;
                }
            }
        }
        /*maze = startingpoint;
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                printf("%c", *maze);
                maze++;
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");*/
    }
    while (1) {
        maze = startingpoint;
        int randomnumber = rand() % (dimension - 2) + 1;
        if (*(maze + randomnumber*dimension + 1) == 'O') {
            *(maze + randomnumber*dimension) = 'O';
            break;
        }
    }
    while (1) {
        maze = startingpoint;
        int randomnumber = rand() % (dimension - 2) + 1;
        if (*(maze + randomnumber*dimension + dimension-2) == 'O') {
            *(maze + randomnumber*dimension+dimension-1) = 'O';
            break;
        }
    }
    maze = startingpoint;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (*maze == 'O')*maze = 'X';
            maze++;
        }
    }
    maze = startingpoint;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%c", *maze);
            maze++;
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

