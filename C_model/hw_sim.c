// This is the exchange file which takes the Stream nasdaq
typedef struct book_entry{
    int price;
    int order_id;
    int quantity;
};

typedef struct hw_output{
    int best_price_0;
    int best_price_1;
    int best_price_2;
    int best_price_3;
    int size_of_stock_0;
    int size_of_stock_1;
    int size_of_stock_2;
    int size_of_stock_3;
};


 int hw_sim(struct book_entry order_to_add, int stock_id, int quantity, int request, int order_id){


 }