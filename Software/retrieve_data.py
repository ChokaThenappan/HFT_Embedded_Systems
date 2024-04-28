import random
import struct
import queue
import time

# NASDAQ ITCH protocol constants
ITCH_HEADER_LEN = 11
ITCH_MESSAGE_TYPES = {
    'S': 'System Event',
    'R': 'Stock Directory',
    'H': 'Stock Trading Action',
    'Y': 'Reg SHO Restriction',
    'L': 'Market Participant Position',
    'V': 'Add Order (With MPID)',
    'W': 'Add Order (Without MPID)',
    'D': 'Order Delete',
    'U': 'Replace Order',
    'P': 'Trade (Non-Cross)',
    'Q': 'Cross Trade',
    'B': 'Broken Trade',
    'I': 'NOII',
}

# Create a queue to store the simulated messages
message_queue = queue.Queue()

# Simulate messages for a certain duration (e.g., 10 seconds)
end_time = time.time() + 10

while time.time() < end_time:
    # Generate a random message length
    message_len = random.randint(ITCH_HEADER_LEN + 1, 100)

    # Generate a random message type
    message_type = random.choice(list(ITCH_MESSAGE_TYPES.keys()))

    # Construct the header
    header = struct.pack('!Hc', message_len, message_type.encode())

    # Generate a random message body
    body_len = max(0, message_len - ITCH_HEADER_LEN)
    body = b''.join(bytes([random.randint(97, 122)]) for _ in range(body_len))

    # Construct the full message
    message = header + body

    # Store the message in the queue
    message_queue.put(message)

    # Process the message (if needed)
    print(f'Simulated {ITCH_MESSAGE_TYPES[message_type]} message')

    # Wait for one second
    time.sleep(1)

# Process the messages in the queue
while not message_queue.empty():
    message = message_queue.get()
    message_len, = struct.unpack('!H', message[:2])
    message_type = message[2].decode()
    body = message[ITCH_HEADER_LEN:]

    print(f'Processing {ITCH_MESSAGE_TYPES[message_type]} message of length {message_len}: {body}')
