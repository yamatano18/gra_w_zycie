#include <stdio.h>
#include <stdlib.h>

#include "logic.h"
#include "output.h"
 
void show_help()
{
    printf("Uruchom program, jako argumenty podaj: nazwe pliku zawierajacego siatke, regule sasiedztwa i liczbe generacji.\n");
    printf("Dostepne reguly sasiedztwa:\n1) Moora - podaj '-m'\n2) Neumanna - podaj '-n'\n");
    printf("./a.out [plik z siatka] [regula_sasiedztwa] [liczba generacji]\n");
}

/* Allocates memory for 2d array */
int** allocate2D(int rows,int cols)
{
    int **arr2D;
    int i;

    arr2D = (int**)malloc(rows*sizeof(int*));
    for(i=0;i<rows;i++)
        arr2D[i] = (int*)malloc(cols*sizeof(int));

	return arr2D;
}

/* Deallocates memory for 2d array */
void deallocate2D(int** arr2D,int rows)
{
    int i;

    for(i=0;i<rows;i++)
    {
        free(arr2D[i]);
    }

    free(arr2D);
}  
 
int main( int argc, char* argv[])
{
    if ( argc < 4 ) {
        show_help();
        return -1;
    }
    else if ( argc == 4 ) {
        FILE *in_file = fopen(argv[1],"r");
 
        char *flag = argv[2];
 
        int x_size = 0;
        int y_size = 0;
 
        if (in_file == NULL) {
            printf("Nie udalo sie otworzyc pliku %s!\n", argv[1]);
            return -1;
        }
        else {
            printf("Plik '%s' zostal otwarty\n", argv[1]);
        }
 
/* Loads dimentions of array, x_size = rows, y_size = columns */
        fscanf(in_file, "%d", &x_size);
        fscanf(in_file, "%d", &y_size);
 
/* Allocates memory for array  */
		int **tab_init = allocate2D(x_size, y_size);

/* Loads values to array, r = rows, c = columns */
        int r,c;
        for ( r = 0; r < x_size; r++ )
            for ( c = 0; c < y_size; c++)
                fscanf(in_file, "%d", &tab_init[r][c]);
	 
        show_tab(tab_init, x_size, y_size);
		fclose(in_file);

/* Conducts number of generations. Number is given as argv[3] */
		int num_of_gen = atoi(argv[3]);
		display_all(tab_init, x_size, y_size, num_of_gen, flag);	 

        deallocate2D(tab_init, x_size);
		return 0;
    }
 
    else {
        printf("Podano za duzo argumentow!");
        show_help();
        return 1;
    }
}

