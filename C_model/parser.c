#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

typedef struct 
{
	char msg_type;
	uint32_t stock_addr;
	uint32_t stock_id;
	uint32_t timestamp;
	int req_type[3] = {0,1,2};
	int qty;
	uint32_t order_id;
	char Stock[8];
} Stock_Directory_Message;

void parse_stock_directory_message(const char* buffer, Stock_Directory_Message* message) 
{
	int offset = 0;

	message->msg_type = buffer[offset];
	offset += sizeof(char);

	message->stock_addr = ntohl(*(uint32_t*)(buffer+offset));
	offset += sizeof(uint32_t);
	
	message->stock_id = ntohl(*(uint32_t*)(buffer+offset));
	offset += sizeof(uint32_t);

	message->timestamp;
	offset += sizeof(uint64_t);

	message->req_type;
	// offset

	message->qty;
	// offset
	
	message->order_id;
	// offset
	
	message->Stock;
	// offset
	
	message->stock_id;
	// offset
}

int main()
{
	printf("Hello, world!");
	return 0;
}

