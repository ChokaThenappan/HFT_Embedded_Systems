`include "constants.sv"

typedef struct packed{
logic [15:0] price; 
logic [15:0] order_id;
logic [15:0] quantity; 
} book_entry;

module order_book(
    input clk,
    input rst,
    input book_entry incoming_order,
    input start_book,
    input delete_flag,
    input request_type,
    input [15:0] cancel_order_id,
    input [15:0] cancel_quantity,
    output logic busy,
    output logic [2:0] cancel_update,
    output logic [15:0] best_price_output,
    output logic best_price_valid,
    output logic [7:0] size_book
);

logic start;
logic [7:0] addr;
logic [7:0] add_addr;
logic [15:0] best_price = 0;

logic [15:0] add_best_price;
logic [15:0] decrease_best_price;

assign best_price_output = best_price;

book_entry data_i;
book_entry data_o;

endmodule