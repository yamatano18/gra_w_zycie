#include "logic.h"

#include <string.h>

int neighbours_alive(int row, int col, int **tab, int x_size, int y_size, char *flag){
        int max_row = x_size - 1;
        int max_col = y_size - 1;
        int sum = 0;
        int r,c,x,y;
        for (r = -1; r <= 1; r++){
                for (c = -1; c <= 1; c++){

                        if (strcmp(flag, "-m") == 0){
                                if (!(r == 0 && c == 0)){
                                        x = row + r;    //current row
                                        y = col + c;    //currnet column

                                        if (x < 0)
                                                x = max_row;
                                        else if (x > max_row)
                                                x = 0;

                                        if (y < 0)
                                                y = max_col;
                                        else if (y > max_col)
                                                y = 0;

                                        sum += tab[x][y];
                                }
                        }
                        else if (strcmp(flag, "-n") == 0){
                                if (!((r==0 && c==0) || (r==-1 && c==-1) || (r==-1 && c==1) || (r==1 && c==1) || (r==1 && c==-1))){
                                        x = row + r;
                                        y = col + c;

                                        if (x < 0)
                                                x = max_row;
                                        else if (x > max_row)
                                                x = 0;

                                        if (y < 0)
                                                y = max_col;
                                        else if (y > max_col)
                                                y = 0;

                                        sum += tab[x][y];
                                }
			 }
                }
        }
        return sum;
}


int next_state(int row, int col, int **tab, int x_size, int y_size, char *flag){
        if ((neighbours_alive(row,col,tab, x_size, y_size, flag) == 3) ||
        (tab[row][col] == 1 && neighbours_alive(row,col,tab, x_size, y_size, flag) == 2))
                return 1;
        else
                return 0;
}

int next_generation(int **tab, int x_size, int y_size, char *flag)
{
        int temp[x_size][y_size];
        int r, c;
        for(r = 0; r < x_size; r++){
                for(c = 0; c < y_size; c++){
                        temp[r][c] = next_state(r,c,tab, x_size, y_size, flag);
                }
        }
        for(r = 0; r < x_size; r++){
                for(c = 0; c < y_size; c++)
                        tab[r][c] = temp[r][c];
        }
        return **tab;
}

