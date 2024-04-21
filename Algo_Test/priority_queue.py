import sys
import time

class message:
    price = 0
    priority = 0

class order_book:

    pr = [None] * (100000)

    size = -1

    @staticmethod
    def add_order(price, priority):
        start_time = time.time()

        order_book.size += 1

        order_book.pr[order_book.size] = message()
        order_book.pr[order_book.size].price = price 
        order_book.pr[order_book.size].priority = priority

        end_time = time.time()
        print(f"Time taken to add_order: {end_time - start_time} seconds")
    
    @staticmethod
    def peek():
        highestPriority = -sys.maxsize
        ind = -1

        i = 0
        while(i <= order_book.size):
            if (highestPriority == order_book.pr[i].priority and ind > -1 and order_book[ind].price < order_book.pr[i].price):
                highestPriority = order_book.pr[i].priority
                ind = i
            elif(highestPriority < order_book.pr[i].priority):
                highestPriority = order_book.pr[i].priority
                ind = i
            i += 1

        return ind

    @staticmethod
    def peek_max():
        start_time = time.time()

        temp_max = -sys.maxsize
        for i in range(order_book.size + 1):  # Adjusted to include the last element
            if (temp_max < order_book.pr[i].price):
                temp_max = order_book.pr[i].price
        
        end_time = time.time()
        print(f"Time taken to peek_max: {end_time - start_time} seconds")
        return temp_max

    @staticmethod
    def main(args):
        print("Main function")
        order_book.add_order(10, 1)
        order_book.add_order(14, 2)
        order_book.add_order(16, 3)
        order_book.add_order(12, 4)

        # Print current size
        print(f"Current size of order_book: {order_book.size + 1}")

        # ind = order_book.peek()
        # print(order_book.pr[ind].price)
        # print(order_book.pr[ind].priority)
        res = order_book.peek_max()
        print(f"Max price in order_book: {res}")

if __name__ == "__main__":
    order_book.main([])
