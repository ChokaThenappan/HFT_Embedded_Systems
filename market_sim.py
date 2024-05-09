import random
import struct
import time
import socket

# Change teh IP address to the IP address of the FPGA (arthur.cs.columbia.edu)
# SERVER_IP = "128.59.19.114"
FPGA_IP = "127.0.0.1"
FPGA_PORT = 42000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect((FPGA_IP, FPGA_PORT))

# List to store existing orders
existing_orders = []

# Function to generate random message
def generate_message(order_book_id_int):
    order_reference_number = 0

    msg_type = random.choice([0x53, 0x44, 0x45])

   
    if msg_type == 0x44:
        if existing_orders:
            order_reference_number = random.choice(existing_orders)
            existing_orders.remove(order_reference_number)
        else:
            msg_type = 0x53  
    elif msg_type == 0x53:
        order_reference_number = random.randint(1, 0xFFFFFFFF)  
        existing_orders.append(order_reference_number)
    
    if order_book_id_int == 0:
        stock = b"AAPLE\0\0\0"
    elif order_book_id_int == 1:
        stock = b"META\0\0\0\0"
    elif order_book_id_int == 2:
        stock = b"NETFLIX"
    else:
        stock = b"ARM\0\0\0\0\0"
    
    time_stamp = 0x12345678  #
    transaction_id = random.randint(1, 0xFFFFFFFF)  
    side = 0x42  
    quantity = 0x64  
    price = random.randint(1, 1000)  
    order_book_id = order_book_id_int  
    yield_value = 0x0000000500000005 

    message = struct.pack(
        "!BIIIIBIQQ8s",
        msg_type,
        time_stamp,
        order_reference_number,
        transaction_id,
        order_book_id,
        side,
        quantity,
        price,
        yield_value,
        stock
    )
    return message


for order_book_id_int in range(4):
    print(f"Order Book ID: {order_book_id_int}")
    sock.sendall(generate_message(order_book_id_int))
    for _ in range(1000):
        message = generate_message(order_book_id_int)
        print(" ".join(f"{b:02X}" for b in message))
        sock.sendall(message)
        time.sleep(0.1)

sock.close()
