"""
Taking the data type as Arrays

Implementing - 
    1. Insertion (enqueue)
    2. Getting best price (peek_max)
"""

import sys

class message:
    price = 0
    priority = 0

class order_book:

    pr = [None] * (100000)

    size = -1

    def add_order(price, priority):
        order_book.size += 1

        order_book.pr[order_book.size] = message()
        order_book.pr[order_book.size].price = price 
        order_book.pr[order_book.size].priority = priority
    
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

    def peek_max():
        """
        peek for the max price in the data structure
        """
        pass


    def main(args):
        print("Main function")
        order_book.add_order(10, 4)
        order_book.add_order(14, 4)
        order_book.add_order(16, 4)
        order_book.add_order(12, 4)

        print(order_book.size)
        
        ind = order_book.peek()
        print(order_book.pr[ind].price)

                                 
if __name__ == "__main__":
    # Change this to the function name
    order_book.main([])

