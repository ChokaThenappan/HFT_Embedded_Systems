module full_top(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] ff_buffer,
output reg system_free,
output reg [31:0] bid_max_order_id_1,
output reg [31:0] bid_max_quantity_1,
output reg [63:0] bid_max_price_1,
output reg [31:0] bid_max_order_id_2,
output reg [31:0] bid_max_quantity_2,
output reg [63:0] bid_max_price_2,
output reg [31:0] bid_max_order_id_3,
output reg [31:0] bid_max_quantity_3,
output reg [63:0] bid_max_price_3,
output reg [31:0] bid_max_order_id_4,
output reg [31:0] bid_max_quantity_4,
output reg [63:0] bid_max_price_4,
output reg [31:0] ask_max_order_id_1,
output reg [31:0] ask_max_quantity_1,
output reg [63:0] ask_max_price_1,
output reg [31:0] ask_max_order_id_2,
output reg [31:0] ask_max_quantity_2,
output reg [63:0] ask_max_price_2,
output reg [31:0] ask_max_order_id_3,
output reg [31:0] ask_max_quantity_3,
output reg [63:0] ask_max_price_3,
output reg [31:0] ask_max_order_id_4,
output reg [31:0] ask_max_quantity_4,
output reg [63:0] ask_max_price_4,
);

wire bid_system_free;
wire ask_system_free;
wire bid_buffer_not_empty;
wire ask_buffer_not_empty;

bid_buffer_not_empty = (ff_buffer [151:144]== 8'h42) && buffer_not_empty;
ask_buffer_not_empty = (ff_buffer [151:144]== 8'h44) && buffer_not_empty;

assign system_free = bid_system_free && ask_system_free;


top bid_side(clk,resetn,bid_buffer_not_empty,ff_buffer, bid_system_free, bid_max_order_id_1, bid_max_quantity_1, bid_max_price_1, bid_max_order_id_2, bid_max_quantity_2, bid_max_price_2, bid_max_order_id_3, bid_max_quantity_3, bid_max_price_3, bid_max_order_id_4, bid_max_quantity_4, bid_max_price_4);

top ask_side(clk,resetn,ask_buffer_not_empty,ff_buffer, ask_system_free, ask_max_order_id_1, ask_max_quantity_1, ask_max_price_1, ask_max_order_id_2, ask_max_quantity_2, ask_max_price_2, ask_max_order_id_3, ask_max_quantity_3, ask_max_price_3, ask_max_order_id_4, ask_max_quantity_4, ask_max_price_4);

endmodule
