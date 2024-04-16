// This is the exchange file which takes the Stream nasdaq
#include <stdio.h>
#define MAX_SIZE 5


//  Price || Order_id || Quantity
int mem0 [3][5];

//int *mem_0 = malloc(5*sizeof (struct book_entry));


//request : ADD | CANCEL | Execute
//            0       1       2


typedef struct book_entry{
    int price;
    int order_id;
    int quantity;
} BookEntry;

typedef struct hw_output{
    int best_price_0;
    int best_price_1;
    int best_price_2;
    int best_price_3;
    int quantity0;
    int quantity1;
    int quantity2;
    int quantity3;
    int size_pointer0;
    int size_pointer1;
    int size_pointer2;
    int size_pointer3;
} HwOutput;

struct hw_output current_state = {0};

void add_order0(struct book_entry order_to_add, int stock_id){

    if (current_state.size_pointer0 < MAX_SIZE) {
        mem0 [0][current_state.size_pointer0] = order_to_add.order_id;
        mem0 [1][current_state.size_pointer0] = order_to_add.price;
        mem0 [2][current_state.size_pointer0] = order_to_add.quantity;
        current_state.size_pointer0++;
        }
    if (current_state.size_pointer0 == MAX_SIZE){
        current_state.size_pointer0 = 0;
    }
    if (current_state.best_price_0 < order_to_add.price){
            current_state.best_price_0 = order_to_add.price;
        }
    else {
            if(0){};
        }
 }

 int decrease_order0(int order_id, int dec_quantity, int delete_flag){

    int temp_delete = delete_flag;
    for (int i = 0; i < current_state.size_pointer0 ; i++ ){
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
                for (int j = i; i < current_state.size_pointer0; j++ ){
                    mem0[0][i] = mem0[0][i+1];
                    mem0[1][i] = mem0[1][i+1];
                    mem0[2][i] = mem0[2][i+1];
                }
                current_state.size_pointer0--;
                break;
            }
        }
    }
 }

int hw_sim(struct book_entry order_to_add, int stock_id, int quantity, int request){
//(order, 1, 1, 0, 1, prev_price);
    switch (request){
        case 0: //add_order
            if (stock_id == 0){
                add_order0(order_to_add, stock_id);
                
            }
            break;
        case 1: //cancel_order
            if (stock_id == 0){
                decrease_order0(order_to_add.order_id, quantity, 0);
            }
            break;
        default: if (0){}
    } 
    return 1;
 }

int main() {
    int a;
    struct book_entry order = {1, 1, 1};
    struct hw_output prev_price = {0}; // Assuming initial values are zero
    //(struct book_entry order_to_add, int stock_id, int quantity, int request)
    a = hw_sim(order, 0, 1, 0); // Example call
    order.order_id = 2;
   a = hw_sim(order, 0, 1, 0); // Example call
    order.order_id = 3; 
     a = hw_sim(order, 0, 1, 0); // Example call
    order.order_id = 4;
    order.price = 8;
    a = hw_sim(order, 0, 1, 0); // Example call
    order.order_id = 5;
    order.price = 9;
    a = hw_sim(order, 0, 1, 0); // Example call
    order.order_id = 6;
    order.price = 9;
    a = hw_sim(order, 0, 1, 0); // Example call
    printf(" Stock 0: Order ID | Price | Quantity \n");

    for (int i =0 ; i < 5 ; i++ ){
        printf("              %d    |    %d    |    %d \n", mem0 [0][i], mem0 [1][i] , mem0 [2][i]);
    }
    return 0;
}