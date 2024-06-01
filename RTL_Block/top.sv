module top(
input clk,
input reset,
input buffer_not_empty,
input [319:0] ff_buffer,
output reg system_free,
output reg [31:0] max_order_id_1,
output reg [31:0] max_quantity_1,
output reg [63:0] max_price_1,
output reg [31:0] max_order_id_2,
output reg [31:0] max_quantity_2,
output reg [63:0] max_price_2,
output reg [31:0] max_order_id_3,
output reg [31:0] max_quantity_3,
output reg [63:0] max_price_3,
output reg [31:0] max_order_id_4,
output reg [31:0] max_quantity_4,
output reg [63:0] max_price_4
);

wire ready_stock1;
wire ready_stock2;
wire ready_stock3;
wire ready_stock4;

wire [31:0] order_id_p;
wire [31:0] quantity_p;
wire [63:0] price_p;
wire [11:0] stock_activate_out;

assign system_free = ready_stock1 && ready_stock2 && ready_stock3 && ready_stock4 ;

parser p_block(
.ff_buffer(ff_buffer),
.out_order_id(order_id_p), 
.out_quantity(quantity_p), 
.out_price(price_p),
.stock_activate(stock_activate_out));

order_book stock1(
.clk(clk), 
.reset(reset), 
.valid(buffer_not_empty), 
.order_id(order_id_p), 
.quantity(quantity_p), 
.price(price_p), 
.req_type(stock_activate_out[11:9]), 
.max_order_id(max_order_id_1), 
.max_quantity(max_quantity_1), 
.max_price(max_price_1), 
.ready(ready_stock1));

order_book stock2(
.clk(clk), 
.reset(reset), 
.valid(buffer_not_empty), 
.order_id(order_id_p), 
.quantity(quantity_p), 
.price(price_p), 
.req_type(stock_activate_out[8:6]), 
.max_order_id(max_order_id_2), 
.max_quantity(max_quantity_2), 
.max_price(max_price_2), 
.ready(ready_stock2));

order_book stock3(
.clk(clk), 
.reset(reset), 
.valid(buffer_not_empty), 
.order_id(order_id_p), 
.quantity(quantity_p), 
.price(price_p), 
.req_type(stock_activate_out[5:3]), 
.max_order_id(max_order_id_3), 
.max_quantity(max_quantity_3), 
.max_price(max_price_3), 
.ready(ready_stock3));

order_book stock4(
.clk(clk), 
.reset(reset), 
.valid(buffer_not_empty), 
.order_id(order_id_p), 
.quantity(quantity_p), 
.price(price_p), 
.req_type(stock_activate_out[2:0]), 
.max_order_id(max_order_id_4), 
.max_quantity(max_quantity_4), 
.max_price(max_price_4), 
.ready(ready_stock4));


/*parser p_block(clk, reset, buffer_not_empty, ff_buffer, slave_ready, system_free,master_valid, out_order_id ,out_quantity_p,out_price_p, stock_activate_out);

order_book stock1(
clk, reset, valid1, out_order_id_p, out_quantity_p, out_price_p, stock_activate_out[11:9], max_order_id_1, max_quantity_1, max_price_1, ready_1);

order_book stock2(
clk, reset, valid2, out_order_id_p, out_quantity_p, out_price_p, stock_activate_out[8:6], max_order_id_2, max_quantity_2, max_price_2, ready_2);

order_book stock3(
clk, reset, valid3, out_order_id_p, out_quantity_p, out_price_p, stock_activate_out[5:3], max_order_id_3, max_quantity_3, max_price_3, ready_3);

order_book stock4(
clk, reset, valid4, out_order_id_p, out_quantity_p, out_price_p, stock_activate_out[2:0], max_order_id_4, max_quantity_4, max_price_4, ready_4);

always@(*) begin
	if (valid1) begin
		max_order_id <= max_order_id_1;
		max_quantity <= max_quantity_1;
		max_price <= max_price_1; 
	end
	else if (valid2) begin
		max_order_id <= max_order_id_2;
		max_quantity <= max_quantity_2;
		max_price <= max_price_2; 
	end
	else if (valid3) begin
		max_order_id <= max_order_id_3;
		max_quantity <= max_quantity_3;
		max_price <= max_price_3; 
	end
	else if (valid4) begin
		max_order_id <= max_order_id_4;
		max_quantity <= max_quantity_4;
		max_price <= max_price_4; 
	end
end*/

endmodule
