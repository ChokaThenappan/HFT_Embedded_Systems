// This is the exchange file which takes the Stream nasdaq
#include <stdio.h>
#define MAX_SIZE 5


//  Price || Order_id || Quantity
int mem0 [3][5];
int mem1 [3][5];
int mem2 [3][5];
int mem3 [3][5];

//int *mem_0 = malloc(5*sizeof (struct book_entry));


//request : ADD | CANCEL | Execute
//            0       1       2


typedef struct book_entry{
    int price;
    int order_id;
    int quantity;
};

typedef struct hw_output{
    int best_price_0;
    int best_price_1;
    int best_price_2;
    int best_price_3;
    int size_of_stock_0;
    int size_of_stock_1;
    int size_of_stock_2;
    int size_of_stock_3;
};

int add_order0(struct book_entry order_to_add, int stock_id, int size_pointer, int order_id, int prev_best){
    if (size_pointer < MAX_SIZE) {
        mem0 [0][size_pointer] = order_to_add.order_id;
        mem0 [1][size_pointer] = order_to_add.price;
        mem0 [2][size_pointer] = order_to_add.quantity;
        }
    if (prev_best < order_to_add.price){
            return 1;
        }
    else {
            return 0;
        }
 }

 int add_order1(struct book_entry order_to_add, int stock_id, int size_pointer, int order_id, int prev_best){
    if (size_pointer < MAX_SIZE) {
        mem1 [0][size_pointer] = order_to_add.order_id;
        mem1 [1][size_pointer] = order_to_add.price;
        mem1 [2][size_pointer] = order_to_add.quantity;
        }
    if (prev_best < order_to_add.price){
            return 1;
        }
    else {
            return 0;
        }
 }

  int add_order0(struct book_entry order_to_add, int stock_id, int size_pointer, int order_id, int prev_best){
    if (size_pointer < MAX_SIZE) {
        mem2 [0][size_pointer] = order_to_add.order_id;
        mem2 [1][size_pointer] = order_to_add.price;
        mem2 [2][size_pointer] = order_to_add.quantity;
        }
    if (prev_best < order_to_add.price){
            return 1;
        }
    else {
            return 0;
        }
 }

  int add_order1(struct book_entry order_to_add, int stock_id, int size_pointer, int prev_best){
    if (size_pointer < MAX_SIZE) {
        mem3 [0][size_pointer] = order_to_add.order_id;
        mem3 [1][size_pointer] = order_to_add.price;
        mem3 [2][size_pointer] = order_to_add.quantity;
        }
    if (prev_best < order_to_add.price){
            return 1;
        }
    else {
            return 0;
        }
 }

 int decrease_order0(int order_id, int dec_quantity, int prev_best, int delete_flag, int size_pointer){

    int temp_delete = delete_flag;
    for (int i = 0; i < MAX_SIZE ; i++ ){
        if (mem0[0][i] == order_id){
            temp_delete = delete_flag;
            if (!delete_flag){
                if (mem0[2][i] < dec_quantity){
                    temp_delete = 1;
                }
                mem0[2][i] = mem0[2][i] - dec_quantity;
                if (!temp_delete){break;}
            }
            if(temp_delete){
                for (int j = i; i < size_pointer; j++ ){
                    mem0[0][i] = mem0[0][i+1];
                    mem0[1][i] = mem0[1][i+1];
                    mem0[2][i] = mem0[2][i+1];
                }
                break;
            }
            
        }
    }

 }

  int decrease_order1(int order_id, int dec_quantity, int prev_best, int delete_flag, int size_pointer){

    int temp_delete = delete_flag;
    for (int i = 0; i < MAX_SIZE ; i++ ){
        if (mem1[0][i] == order_id){
            temp_delete = delete_flag;
            if (!delete_flag){
                if (mem1[2][i] < dec_quantity){
                    temp_delete = 1;
                }
                mem1[2][i] = mem1[2][i] - dec_quantity;
                if (!temp_delete){break;}
            }
            if(temp_delete){
                for (int j = i; i < size_pointer; j++ ){
                    mem1[0][i] = mem1[0][i+1];
                    mem1[1][i] = mem1[1][i+1];
                    mem1[2][i] = mem1[2][i+1];
                }
                break;
            }
            
        }
    }

 }

  int decrease_order2(int order_id, int dec_quantity, int prev_best, int delete_flag, int size_pointer){

    int temp_delete = delete_flag;
    for (int i = 0; i < MAX_SIZE ; i++ ){
        if (mem2[0][i] == order_id){
            temp_delete = delete_flag;
            if (!delete_flag){
                if (mem2[2][i] < dec_quantity){
                    temp_delete = 1;
                }
                mem2[2][i] = mem2[2][i] - dec_quantity;
                if (!temp_delete){break;}
            }
            if(temp_delete){
                for (int j = i; i < size_pointer; j++ ){
                    mem2[0][i] = mem2[0][i+1];
                    mem2[1][i] = mem2[1][i+1];
                    mem2[2][i] = mem2[2][i+1];
                }
                break;
            }
            
        }
    }

 }

  int decrease_order3(int order_id, int dec_quantity, int prev_best, int delete_flag, int size_pointer){

    int temp_delete = delete_flag;
    for (int i = 0; i < MAX_SIZE ; i++ ){
        if (mem3[0][i] == order_id){
            temp_delete = delete_flag;
            if (!delete_flag){
                if (mem3[2][i] < dec_quantity){
                    temp_delete = 1;
                }
                mem3[2][i] = mem3[2][i] - dec_quantity;
                if (!temp_delete){break;}
            }
            if(temp_delete){
                for (int j = i; i < size_pointer; j++ ){
                    mem3[0][i] = mem3[0][i+1];
                    mem3[1][i] = mem3[1][i+1];
                    mem3[2][i] = mem3[2][i+1];
                }
                break;
            }
            
        }
    }

 }


int hw_sim(struct book_entry order_to_add, int stock_id, int quantity, int request, int order_id, struct hw_output prev_price){

    switch (request){
        case 0: //add_order
            
        case 1: //cancel_order
    }



 }


