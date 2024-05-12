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

typedef struct {
    char data[BUFFER_SIZE];
} QueueData;

typedef struct {
    QueueData items[QUEUE_SIZE];
    int front, rear;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
} Queue;

Queue dataQueue;

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
    if (isQueueFull(q)) {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    if (isQueueEmpty(q)) {
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

    QueueData item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % QUEUE_SIZE;
    }

    pthread_mutex_unlock(&q->mutex);
    return item;
}

void read_message() {
    vga_ball_arg_t vla;
    if (ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla)) {
        perror("ioctl(VGA_BALL_READ_DATA) failed");
        return;
    }
    // printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
    //        vla.message.msg_type, vla.message.timestamp, vla.message.order_ref_number,
    //        vla.message.trans_id, vla.message.order_book_id, vla.message.side,
    //        vla.message.qty, vla.message.price, vla.message.yield);
}

void write_message(const vga_ball_color_t *c) {
    vga_ball_arg_t vla;
    vla.message = *c;

    unsigned char bufferNotEmpty = ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla);
    unsigned char readPort = ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla);

    if (bufferNotEmpty && readPort) {

    if (ioctl(vga_ball_fd, VGA_BALL_WRITE_DATA, &vla)) {
        printf("Data written to device:\n");
        printf("Msg Type: %02x, Timestamp: %02x, Order Ref Number: %02x, Trans ID: %02x, Order Book ID: %02x, Side: %02x, Qty: %02x, Price: %02x, Yield: %02x\n",
           vla.message.msg_type, vla.message.timestamp, vla.message.order_ref_number,
           vla.message.trans_id, vla.message.order_book_id, vla.message.side,
           vla.message.qty, vla.message.price, vla.message.yield);
        perror("ioctl(VGA_BALL_WRITE_DATA) failed");
        return;
    }

    }
    else {
        printf("Waiting for buffer and port to be ready...\n");
    }
}

void *network_thread_f(void *arg) {
    int sockfd = *(int *)arg;
    char recvBuf[BUFFER_SIZE];

    while (1) {
        int n = read(sockfd, recvBuf, BUFFER_SIZE);
        if (n < 0) {
            perror("Error reading from socket");
            exit(1);
        } else if (n == 0) {
            // printf("Connection closed by client\n");
            close(sockfd);
            break;
        }
        // printf("Received data:\n");
        // for (int i = 0; i < n; i++) {
        //     printf("%02X ", (unsigned char)recvBuf[i]);
        // }
        // printf("\n");
    }

    return NULL;
}

int main() {
    const char *device_path = "/dev/vga_ball";
    if ((vga_ball_fd = open(device_path, O_RDWR)) < 0) {
        perror("Failed to open vga_ball device");
        exit(1);
    }

    int sockfd, newsockfd, client_len;
    struct sockaddr_in serv_addr, client_addr;
    pthread_t network_thread;

    initializeQueue(&dataQueue);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error: Could not create socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    listen(sockfd, 5);
    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(1);
    }

    if (pthread_create(&network_thread, NULL, network_thread_f, (void *)&newsockfd) != 0) {
        perror("Error creating network thread");
        exit(1);
    }

    while (1) {
        char data[BUFFER_SIZE] = "Data from FPGA";
        QueueData newData;
        strcpy(newData.data, data);
        enqueue(&dataQueue, newData);

        QueueData dataItem = dequeue(&dataQueue);
        vga_ball_color_t vla;
        memcpy(&vla, dataItem.data, sizeof(vga_ball_color_t));
        write_message(&vla);
        sleep(2);
    }

    close(sockfd);
    close(vga_ball_fd);

    return 0;
}
