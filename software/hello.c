#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "vga_ball.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_HOST "128.59.64.144"
#define SERVER_PORT 42001
#define BUFFER_SIZE 1024
#define QUEUE_SIZE 100

int vga_ball_fd;

/* READ THE MESSAGE */
void read_message() {
	vga_ball_arg_t vla;
	
	if (ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla)) {
		perror("ioctl(VGA_BALL_READ_DATA) failed");
      		return;
  	}
	printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x\n", vla.message.msg_type, vla.message.timestamp, vla.message.order_ref_number, 			vla.message.trans_id, vla.message.order_book_id, vla.message.side, vla.message.qty, vla.message.price, vla.message.yield);
}

/* WRITE THE MESSAGE */

void write_message(const vga_ball_color_t *c) {
	vga_ball_arg_t vla;
	vla.message = *c;

    if (bufferNotEmpty && readPort) {

	if (ioctl(vga_ball_fd, VGA_BALL_WRITE_DATA, &vla)) {
		perror("ioctl(VGA_BALL_WRITE_DATA) failed");
		return;
	}
    printf("Data written to device\n");
    }
    else {
        printf("Waiting for buffer and port to be ready...\n");
        sleep(1);
    }
}
printf('Buffer is full, now write data \n');
}

typedef struct {
    char data[BUFFER_SIZE];
} QueueData;

typedef struct {
    QueueData items[QUEUE_SIZE];
    int front, rear;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

int isQueueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int isQueueFull(Queue *q) {
    return ((q->rear + 1) % QUEUE_SIZE == q->front);
}

void enqueue(Queue *q, QueueData item) {
    pthread_mutex_lock(&q->mutex);
    while (isQueueFull(q)) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    if (isQueueFull(q)) {
        printf("Queue is full\n");
        return;
    } else if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % QUEUE_SIZE;
    }
    q->items[q->rear] = item;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

QueueData dequeue(Queue *q) {
    pthread_mutex_lock(&q->mutex);
    while (isQueueEmpty(q)) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    QueueData item;
    /*
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        // You might want to handle this differently based on your application's requirements
        exit(1);
    } else 
    */
    if (q->front == q->rear) {
        item = q->items[q->front];
        q->front = q->rear = -1;
    } else {
        item = q->items[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
    }

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
    return item;
}

void *network_thread_f(void *);

int main() {
    const char *device_path = "/dev/vga_ball";

    if ((vga_ball_fd = open(device_path, O_RDWR)) < 0) {
        perror("Failed to open vga_ball device");
        exit(1);
    }
    
    int sockfd, newsockfd, client_len;
    struct sockaddr_in serv_addr, client_addr;
    pthread_t network_thread;
    Queue dataQueue;
    initializeQueue(&dataQueue);

    // Create a TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error: Could not create socket\n");
        exit(1);
    }

    // Set up the server address struct
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept incoming connections
    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(1);
    }

    // Start the network thread
    if (pthread_create(&network_thread, NULL, network_thread_f, (void *) newsockfd) != 0) {
        perror("Error creating network thread");
        exit(1);
    }

    // Simulated FPGA process
    while (1) {
        // Simulated data generation
        char data[BUFFER_SIZE];
        sprintf(data, "Data from FPGA");
	
        // Enqueue data
        QueueData newData;
        strcpy(newData.data, data);
        enqueue(&dataQueue, newData);
	
	QueueData dataItem = dequeue(&dataQueue);
	vga_ball_color_t vla;
	memcpy(&vla, dataItem.data, sizeof(vga_ball_color_t));
	write_message(&vla);
        // Simulated delay
        sleep(2);
    }

    // Close the socket
    close(sockfd);
    close(vga_ball_fd);

    return 0;
}

void *network_thread_f(void *arg) {
    int sockfd = (int) arg;
    char recvBuf[BUFFER_SIZE];

    // Receive data from PC
    while (1) {
        int n = read(sockfd, recvBuf, BUFFER_SIZE);
        if (n < 0) {
            perror("Error reading from socket");
            exit(1);
        } else if (n == 0) {
            printf("Connection closed by client\n");
            close(sockfd);
            break; // Exit the thread
        }
        // recvBuf[n] = '\0';
        for (int i = 0; i < n; i++) {
            printf("%02X ", (unsigned char)recvBuf[i]);
        }
        printf("\n");
    }

    return NULL;
}
