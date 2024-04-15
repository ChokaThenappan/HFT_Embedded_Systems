`timescale 1ns/1ps

typedef struct packed {
 logic [15:0] price;
 logic [7:0] order_id;
 logic [7:0] quantity;
} book_entry;
