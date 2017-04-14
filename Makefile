CC = cc

all: logic.o output.o png_gen.o main.c
	$(CC) logic.o output.o png_gen.o main.c -o life -Wall -lpng

output.o: output.c output.h
	$(CC) -c output.c  

png_gen.o: png_gen.c png_gen.h
	$(CC) -c png_gen.c

logic.o: logic.c logic.h
	$(CC) -c logic.c 

.PHONY: clean

clean:
	-rm *.o life
	-rm -r generations_txt generations_png 



