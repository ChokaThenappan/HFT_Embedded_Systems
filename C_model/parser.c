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
        0x41, // msg_type: 'A'
        0x78, 0x56, 0x34, 0x12, // stock_addr: 0x12345678 in network byte order
        0xF0, 0xDE, 0xBC, 0x9A, // stock_id: 0x9ABCDEF0 in network byte order
        0x89, 0x67, 0x45, 0x23, 0x01, 0x00, 0x00, 0x00, // timestamp: 0x0000000123456789 in network byte order
        0x00, 0x00, 0x00, 0x00, // req_type[0]: 0
        0x01, 0x00, 0x00, 0x00, // req_type[1]: 1
        0x02, 0x00, 0x00, 0x00, // req_type[2]: 2
        0x64, 0x00, 0x00, 0x00, // qty: 100 in network byte order
        0x0D, 0x0C, 0x0B, 0x0A, // order_id: 0x0A0B0C0D in network byte order
        'A', 'B', 'C', 'D', 'E', 'F', '\0', '\0' // Stock: "ABCDEF\0\0" (including null terminator)
    };

	Stock_Directory_Message message;

	parse_stock_directory_message(buffer, &message);

	printf("Stock ID: %u\n", message.stock_id);
	printf("Quantity: %d:", message.qty);

	return 0;
}

