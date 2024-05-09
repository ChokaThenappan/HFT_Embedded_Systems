#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 42000
#define BUFFER_SIZE 1024
#define QUEUE_SIZE 100

typedef struct {
    char data[BUFFER_SIZE];
} QueueData;

typedef struct {
    QueueData items[QUEUE_SIZE];
    int front, rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

int isQueueFull(Queue *q) {
    return ((q->rear + 1) % QUEUE_SIZE == q->front);
}

void enqueue(Queue *q, QueueData item) {
    if (isQueueFull(q)) {
        printf("Queue is full\n");
        return;
    } else if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % QUEUE_SIZE;
    }
    q->items[q->rear] = item;
}

QueueData dequeue(Queue *q) {
    QueueData item;
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        // You might want to handle this differently based on your application's requirements
        exit(1);
    } else if (q->front == q->rear) {
        item = q->items[q->front];
        q->front = q->rear = -1;
    } else {
        item = q->items[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
    }
    return item;
}

void *network_thread_f(void *);

int main() {
    int sockfd, newsockfd, client_len;
    struct sockaddr_in serv_addr, client_addr;
    pthread_t network_thread;
    Queue dataQueue;
    initializeQueue(&dataQueue);

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
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

        // Simulated delay
        sleep(2);
    }

    // Close the socket
    close(sockfd);

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