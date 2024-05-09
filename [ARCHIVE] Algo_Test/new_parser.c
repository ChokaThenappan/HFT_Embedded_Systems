#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

#define MAX_SIZE 15

// Data structures and global variables from hw_debug.c
int mem0 [3][15];

const char buffer[] = {
        0x53, // msg_type: 'S -> Add order'
        0x78, 0x56, 0x34, 0x12,0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x01, 0x03, 0xEA,  // order_reference_number: 0x12345678 in network byte order
        0x08, 0x00, 0x00, 0x06, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id: 0x12345678 in network byte order
        0x42, // side
        0x00, 0x00, 0x00, 0x64, // quantity: 100 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, // price = 100
        0x06, 0x00, 0x00, 0x05, // yield: 0x00000001 in network byte order
        '\0', '\0', // Stock: "ABCDEF\0\0" (including null terminator)


        0x53, // msg_type: 'S -> Add order'
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x00, 0x03, 0xFA,  // order_reference_number: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id
        0x42, // side
        0x00, 0x00, 0x00, 0x24, // quantity: 36 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // price = 100
        0x00, 0x00, 0x00, 0x00, // yield: 0x00000001 in network byte order
        '\0', '\0',

        0x53, // msg_type: 'S -> Add order'
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x00, 0x02, 0xEA,  // order_reference_number: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id
        0x42, // side
        0x00, 0x00, 0x02, 0x67, // quantity: 615 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // price = 100
        0x00, 0x00, 0x00, 0x00, // yield: 0x00000001 in network byte order
        '\0', '\0',

        0x44, // msg_type: 'D -> Delete order'
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x00, 0x03, 0xFA,  // order_reference_number: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id
        0x42, // side
        0x00, 0x00, 0x02, 0x67, // quantity: 615 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // price = 100
        0x00, 0x00, 0x00, 0x00, // yield: 0x00000001 in network byte order
        '\0', '\0',

        0x53, // msg_type: 'S -> Add order'
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x00, 0x02, 0xAA,  // order_reference_number: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id
        0x42, // side
        0x00, 0x00, 0x02, 0x07, // quantity: 615 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // price = 100
        0x00, 0x00, 0x00, 0x00, // yield: 0x00000001 in network byte order
        '\0', '\0',

        0x45, // msg_type: 'E -> Execute order'
        0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12,  // time stamp: 0x12345678 in network byte order
        0x00, 0x01, 0x03, 0xEA,  // order_reference_number: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // transaction id: 0x12345678 in network byte order
        0x00, 0x00, 0x00, 0x00, // order_book_id aka stock_id
        0x42, // side
        0x00, 0x00, 0x00, 0x04, // quantity: 615 in network byte order
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // price = 100
        0x00, 0x00, 0x00, 0x00, // yield: 0x00000001 in network byte order
        '\0', '\0', 0x55,

    };

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

    for (int i = 0; i < MAX_SIZE ; i++ ){
        if (mem0[0][i] == order_id){
            if (!delete_flag){
                mem0[2][i] = mem0[2][i] - dec_quantity;
            }
            if(delete_flag){
                for (int j = i; j < MAX_SIZE - 1; j++ ){
                    mem0[0][j] = mem0[0][j+1];
                    mem0[1][j] = mem0[1][j+1];
                    mem0[2][j] = mem0[2][j+1];
                }

                current_state.size_pointer0--;
            }
        }
    }
    return 0;
 }

int hw_sim(struct book_entry order_to_add, int stock_id, int quantity, int request){
//(order, 1, 1, 0, 1, prev_price);
    switch (request){
        case 0: //add_order
            if (stock_id == 0){
                add_order0(order_to_add, stock_id);
                
            }
            break;
        case 1: //delete_order
            if (stock_id == 0){
                decrease_order0(order_to_add.order_id, quantity, 1);
            }
            break;
        case 2: //update_order
            if (stock_id == 0){
                decrease_order0(order_to_add.order_id, quantity, 0);
            }
            break;
        default: if (0){}
    } 
    return 1;
 }

typedef struct {
    int request;
    uint64_t timestamp;
    uint32_t order_reference_number;
    uint32_t transaction_id;
    uint32_t order_book_id;
    char side; // B -> Buy, S -> Sell
    uint32_t quantity;
    uint64_t price;
    uint32_t yield;
} Stock_Directory_Message;
int offset = 0;

void parse_stock_directory_message(const char* buffer, Stock_Directory_Message* message) 
{
    if (buffer[offset] == 0x53) {
        message->request = 0;
    } 
    else if (buffer[offset] == 0x44) {
        message->request = 1;
    } 
    else if (buffer[offset] == 0x45) {
        message->request = 2;
    }
    offset ++;
    message->timestamp = ntohll(*(uint64_t*)(buffer+offset));
    offset += 8;
    message->order_reference_number = ntohl(*(uint32_t*)(buffer+offset));
    offset += 4;

    // Passing the transaction_id to the message structure
    message->transaction_id = ntohl(*(uint32_t*)(buffer+offset));
    offset += 4;

    message->order_book_id = ntohl(*(uint32_t*)(buffer+offset));
    offset += 4;

    // Passing the side to the message structure
    message->side = buffer[offset];
    offset ++;

    // Passing the quantity to the message structure    
    message->quantity = ntohl(*(uint32_t*)(buffer+offset));
    offset += 4;

    // Passing the price to the message structure
    message->price = ntohll(*(uint64_t*)(buffer+offset));
    offset += 8;

    // Passing the yield to the message structure
    message->yield = ntohl(*(uint32_t*)(buffer+offset));
    offset += 4;
   
	offset += 2; // 2 null characters
}

int main(int argc, char *agv[])
{
    BookEntry order;  // Declare the order variable here

    int buffer_size = sizeof(buffer);
    int offset = 0;

    for (int h = 0; h < 6 ; h++) {

        Stock_Directory_Message message;
        int stock_id = 0;
        int quantity =0;
        int request = 0;
        parse_stock_directory_message(buffer + offset, &message);

       
       
        // parse the request type from the message and call hw_sim function
        order.price = message.price;
        order.order_id = message.order_reference_number;
        order.quantity = message.quantity;
        stock_id = message.order_book_id;
        quantity = message.quantity;
        request = message.request;
        // printf("Request type: %d\n", request);
        // printf("Timestamp: %llu\n", message.timestamp);
        // printf("Order ID: %d\n", order.order_id);
        // printf("Price: %llu\n", message.price);
        // printf("Quantity: %d\n", order.quantity);
        // printf("Stock ID: %d\n", stock_id);

        hw_sim(order, stock_id, quantity, request);

        // Print the order book for stock 0 as in hw_debug.c
        printf("Request ID = %d\n", request);
        printf(" Stock 0:  Order ID | Price | Quantity \n");
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("              %d    |    %d    |    %d \n", mem0[0][i], mem0[1][i], mem0[2][i]);
        }
        printf("-------------------------------------------------------------------\n");
        
        
    }

    return 0;
}