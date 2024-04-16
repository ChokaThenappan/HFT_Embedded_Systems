
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
  clear_table();
  fbputs("HFT Book Builder", 1 , 20);
  draw_table(); 		
	
  return 0;
}



void clear_table()
{
/* Draw rows of asterisks across the top and bottom of the screen */
  for (int col = 0 ; col < 64 ; col++) {
	  for(int row = 0; row < 24; row++){
		  fbputchar(' ', row, col);
	  }
  }
}

void draw_table()
{
	for(int col = 0 ; col < 64 ; col++){
	fbputchar('-', 2 , col);
	fbputchar('-', 6 , col);
	fbputchar('-', 10 , col);
	fbputchar('-', 14 , col);
	fbputchar('-', 18 , col);
	fbputchar('-', 22 , col);
		
	}
	for(int row = 3	; row < 22 ; row++){
		if (row == 6 || row == 10 || row == 14 || row ==18){
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
		fbputchar('-', 4 , col);
	}

	for( int row = 5 ; row	< 22 ;row ++){
		if (row == 6 || row  == 10 || row == 14 || row == 18){
			continue;
		}
		else {
			fbputchar('|' , row , 40);
		}
	}
	fbputs("Name", 4, 2);
	fbputs("Stock ID", 4 ,18 );
	fbputs("Price", 3 , 34);
	fbputs("Ask", 5 , 34 );
	fbputs("Bid", 5 , 42 );
	fbputs("Quantity", 4, 50);

	// Variables to be changed later
	// var 1
	fbputs("Apple",8 ,2);
	fbputs("213123",8,18);
	fbputs("614",8, 34);
	fbputs("550",8,42);
	fbputs("4",8,50);

	// var 2
        fbputs("ARM",12 ,2);
        fbputs("64564",12,18);
        fbputs("354",12, 34);
        fbputs("440",12,42);
        fbputs("2",12,50);

	// var 3
        fbputs("Oracle",16 ,2);
        fbputs("236563",16,18);
        fbputs("525",16, 34);
        fbputs("565",16,42);
        fbputs("8",16,50);

	// var 4
        fbputs("Meta",20 ,2);
        fbputs("89045",20,18);
        fbputs("725",20, 34);
        fbputs("695",20,42);
        fbputs("10",20,50);
         

}





