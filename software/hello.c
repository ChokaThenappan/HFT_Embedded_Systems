#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
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

uint64_t current_timestamp = 0;

uint64_t generate_increasing_timestamp() {
    return current_timestamp++;
}

uint32_t generate_random_32bit() {
    return rand();
}

uint64_t generate_random_64bit() {
    return ((uint64_t)rand() << 32) | rand();
}

void write_message(const vga_ball_color_t *c) {
    vga_ball_arg_t vla;
    vla.message = *c;
    unsigned char bufferNotEmpty = ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla);
    unsigned char readPort = ioctl(vga_ball_fd, VGA_BALL_READ_DATA, &vla);
    if (bufferNotEmpty && readPort) {

    if (ioctl(vga_ball_fd, VGA_BALL_WRITE_DATA, &vla)) {
        perror("ioctl(VGA_BALL_WRITE_DATA) failed");
        return;
    }
    printf("Data written to device:\n");
    printf("Msg Type: %02x, Timestamp: %02x, Order Ref Number: %02x, Trans ID: %02x, Order Book ID: %02x, Side: %02x, Qty: %02x, Price: %02x, Yield: %02x\n",
           vla.message.msg_type, vla.message.timestamp, vla.message.order_ref_number,
           vla.message.trans_id, vla.message.order_book_id, vla.message.side,
           vla.message.qty, vla.message.price, vla.message.yield);

    }
    else {
        printf("Waiting for ready...\n");
        // printf("Data written to device:\n");

        srand(time(NULL));

        uint8_t msg_type = rand() % 3 == 0 ? 0x53 : (rand() % 2 == 0 ? 0x44 : 0x45);
        uint64_t timestamp = generate_increasing_timestamp();
        uint32_t order_ref_number = generate_random_32bit();
        uint32_t order_book_id = rand() % 4;
        uint32_t qty = generate_random_32bit();
        uint64_t price = generate_random_64bit();

        printf("Msg Type: 0x%02x, Timestamp: 0x%016llx, Order Ref Number: 0x%08x, Order Book ID: 0x%02x, Qty: 0x%08x, Price: 0x%016llx \n",
               msg_type, timestamp, order_ref_number, order_book_id, qty, price);

        printf("Done!")

        printf("\n")

        // Sleep based on the message type
        if (msg_type == 0x44) {
            sleep(4);
        } else if (msg_type == 0x45) {
            sleep(2);
        }
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