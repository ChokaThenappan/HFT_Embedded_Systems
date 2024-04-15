`timescale 1ns/1ps

typedef struct packed {
 logic [PRICE_INDEX:0] price;
 logic [ORDER_INDEX:0] order_id;
 logic [QUANTITY_INDEX:0] quantity;
} book_entry;
