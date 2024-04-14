`timescale 1ns/1ps
`include "clog2_function.vh"

`ifndef CONSTANTS
`define CONSTANTS

parameter N = 4;
parameter LOGN = $clog2(N);

parameter N = 4; // number of rows/cols parameter LOGN = 2;
parameter R = 2; // number of rotators
parameter NUM_STOCKS = 1;
parameter NUM_STOCK_INDEX = NUM_STOCKS - 1;
parameter STOCK_INDEX = 1;
parameter MAX_INDEX = 100;
parameter NUM_PRICES = 200;
//3 index
parameter PRICE_INDEX = 15;
parameter ORDER_INDEX = 7;
parameter QUANTITY_INDEX = 7;
parameter TOTAL_BITS = PRICE_INDEX +1 + ORDER_INDEX + 1 + QUANTITY_INDEX + 1;
parameter ADDRESS_INDEX = 7;
parameter ENTRY_INDEX = TOTAL_BITS - 1;
parameter BRAM_LATENCY = 2;
parameter SIZE_INDEX = 8;
parameter CANCEL_UPDATE_INDEX = 2;
parameter MAX = 1;
parameter BUY_SIDE = 1; //interested in max price
parameter SELL_SIDE = 0; // interested in min price
parameter ADD_ORDER = 3'b001;
parameter CANCEL_ORDER = 3'b000;
parameter EXECUTE_ORDER = 3'b010;
typedef struct packed {
 logic [PRICE_INDEX:0] price;
 logic [ORDER_INDEX:0] order_id;
 logic [QUANTITY_INDEX:0] quantity;
} book_entry;