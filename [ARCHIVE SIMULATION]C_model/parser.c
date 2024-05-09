#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

typedef struct 
{
	char msg_type;
	uint32_t stock_addr;
	uint32_t stock_id;
	uint32_t timestamp;
	int req_type[3];
	int qty;
	uint32_t order_id;
	char Stock[9];
} Stock_Directory_Message;

void parse_stock_directory_message(const char* buffer, Stock_Directory_Message* message) 
{
	int offset = 0;

	message->req_type[0] = 0;
    message->req_type[1] = 1;
    message->req_type[2] = 2;

	message->msg_type = buffer[offset];
	offset += sizeof(char);

	message->stock_addr = ntohl(*(uint32_t*)(buffer+offset));
	offset += sizeof(uint32_t);
	
	message->stock_id = ntohl(*(uint32_t*)(buffer+offset));
	offset += sizeof(uint32_t);

	message->timestamp = ntohll(*(uint64_t*)(buffer+offset));
	offset += sizeof(uint64_t);

	for (int i=0; i<3; i++)
	{
		message->req_type[i] = ntohl(*(int*)(buffer+offset));
		offset += sizeof(int);
	}

	message->qty = ntohl(*(int*)(buffer+offset));
	offset += sizeof(int);
	
	message->order_id = ntohl(*(uint32_t*)(buffer+offset));
	offset += sizeof(uint32_t);
	
	for (int i = 0; i < 8; i++) {
        	message->Stock[i] = buffer[offset+i];
    	}

	offset += 8;
}

int main(int argc, char *agv[])
{

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
    };

	Stock_Directory_Message message;

	parse_stock_directory_message(buffer, &message);

	printf("Stock ID: %u\n", message.stock_id);
	printf("Quantity: %d:", message.qty);

	return 0;
}

