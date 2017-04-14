#include "output.h"
#include "png_gen.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void show_tab( int **tab, int r, int c )
{
    int i = 0;      // rows
    int j = 0;      // columns
    printf("\033[H");
    for ( i = 0; i < r; i++ ) {
        for ( j = 0; j < c; j++)
                if (tab[i][j] == 1)
                        printf("\033[07m  \033[m");
                else
                        printf("  ");
        printf("\n");
    }
}


int write_file(int **tab_init, int x_size, int y_size, char *txt_filename, char *png_filename){

        int r,c;
        FILE *out_file = fopen(txt_filename, "w");
        if( out_file == NULL) {
            printf("Problem z plikiem wynikowym!\n");
            return -1;
        }
        fprintf(out_file, "%d\n%d\n", x_size, y_size);
        for( r = 0; r < x_size; r++) {
            for( c = 0; c < y_size; c++)
                fprintf(out_file, "%d ", tab_init[r][c]);
            fprintf(out_file, "\n");
        }
        fclose(out_file);

	process_file(tab_init, x_size, y_size);
	write_png_file(png_filename);
		

        return 0;
}



void display_all(int **tab, int x_size, int y_size, int num_of_gen, char *flag)
{
         show_tab(tab, x_size, y_size);
         int n;
         printf("%c[2J%c[;H",(char) 27, (char) 27);
         for(n = 0; n < num_of_gen; n++){
                next_generation(tab, x_size, y_size, flag);
		
		char txt_filename[28];
		char png_filename[28];
		mkdir ("generations_txt", 0777);
		mkdir ("generations_png", 0777);
		sprintf(txt_filename, "generations_txt/gen_%d.txt", n);
		sprintf(png_filename, "generations_png/gen_%d.png", n);
		write_file(tab, x_size, y_size, txt_filename, png_filename);

                show_tab(tab, x_size, y_size);
                usleep(200000);
         }
}

