/*
 *
 * CSEE 4840 Lab 2 for 2019

 */
#include "fbputchar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>


#define BUFFER_SIZE 128
#define SCREEN_WIDTH 64





// Screen handlers
void clear_table();
void draw_table();


int main()
{
  int err, col;
  char input_buffer[BUFFER_SIZE] = "|\0";;	


  if ((err = fbopen()) != 0) {
    fprintf(stderr, "Error: Could not open framebuffer: %d\n", err);
    exit(1);
  }

  /* Draw rows of asterisks across the top and bottom of the screen */
  for (col = 0 ; col < 64 ; col++) {
    fbputchar('*', 0, col);
    fbputchar('*', 23, col);
  }

  fbputs("HFT Book Builder", 30, 10);
  draw_table(); 		
	
  return 0;
}



void clear_table()
{
/* Draw rows of asterisks across the top and bottom of the screen */
  for (int col = 0 ; col < 64 ; col++) {
	  for(int row = 5; row < 23; row++){
		  fbputchar(' ', row, col);
	  }
  }
}

void draw_table()
{
	for(int col = 0 ; col < 64 ; col++){
	fbputchar('-', 6 , col);
	fbputchar('-', 10 , col);
	fbputchar('-', 14 , col);
	fbputchar('-', 18 , col);
	fbputchar('-', 22 , col);		
	}
	for(int row = 7	; row < 22 ; row++){
		if (row == 10 || row == 14 || row == 18){
			continue;	
		}
		else {
			fbputchar('|', row ,0);
			fbputchar('|', row ,16);
			fbputchar('|', row ,32);
			fbputchar('|', row ,48);	
			fbputchar('|', row ,63);
		}
	}

	for( int col = 33 ; col < 48 ; col++){
		fbputchar('-', 8 , col);
	}

	for( int row = 9 ; row	< 22 ;row ++){
		if (row == 10 || row  == 14 || row == 18){
			continue;
		}
		else {
			fbputchar('|' , row , 40);
		}
	}
	fbputs("Name", 8, 2);
	fbputs("Stock ID", 8 ,18 );
	fbputs("Price", 7 , 34);
	fbputs("Ask", 9 , 34 );
	fbputs("Bid", 9 , 42 );
	fbputs("Quantity", 8, 50);

}





