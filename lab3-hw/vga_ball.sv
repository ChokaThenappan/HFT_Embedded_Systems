/* Order book Marcos */

`define IDLE 3'd0
`define ADD_ORDER 3'd1
`define DELETE_ORDER 3'd2
`define SHIFT_BOOK 3'd3
`define FIND_MAX 3'd4
`define DECREASE_ORDER 3'd5

/* Parser Macros */

`define STOCK1 8'h0
`define STOCK2 8'h20
`define STOCK3 8'h30 
`define STOCK4 8'h40 

`define REQ_TYPE_ADD 8'h53
`define REQ_TYPE_DELETE 8'h44
`define REQ_TYPE_DECREASE 8'h45

`define ADD1 12'b100000000000
`define DELETE1 12'b010000000000
`define DECREASE1 12'b001000000000
`define ADD2 12'b000100000000
`define DELETE2 12'b000010000000
`define DECREASE2 12'b000001000000
`define ADD3 12'b000000100000
`define DELETE3 12'b000000010000
`define DECREASE3 12'b000000001000
`define ADD4 12'b000000000100
`define DELETE4 12'b000000000010
`define DECREASE4 12'b000000000001

//`define IDLE 2'b00
//`define SEND_COMMAND 2'b01
//`define WAIT_FOR_RESPONSE 2'b10

typedef struct{
	logic [31:0] order_id;
	logic [31:0] quantity;
	logic [63:0] price;
	logic [11:0] stock_activate;
	logic master_valid;
	logic system_free;
} command_out;

module vga_ball(
/* Shivam changes */
	input logic		clk,
	input logic		reset,
	input logic	[7:0]	writedata,
	input logic		write,
	input logic 		chipselect,
	input logic	[5:0]	address,
	
	output logic [7:0] VGA_R, VGA_G, VGA_B,
	output logic 	   VGA_CLK, VGA_HS, VGA_VS,
		                   VGA_BLANK_n,
	output logic 	   VGA_SYNC_n
);


logic [7:0] message [63:0];
logic [7:0] readdata;
assign VGA_R = 8'd45;
integer i;

always_ff @(posedge clk) begin 
	if (reset) begin
		for (i=0; i<64; i=i+1) message[i] <= 8'd0;
	end else if (write) begin
		message [address] <= writedata;
	end else begin
		assign readdata = VGA_R;
		readdata <= message [address];
	end
end


/*top new_top (
    .clk(clk),
    .resetn(~reset),
    .buffer_not_empty(buffer_not_empty),
    .ff_buffer({ff_buffer_0, ff_buffer_1, ff_buffer_2, ff_buffer_3, ff_buffer_4, ff_buffer_5, ff_buffer_6, ff_buffer_7, ff_buffer_8, ff_buffer_9, ff_buffer_10, ff_buffer_11, ff_buffer_12, ff_buffer_13, ff_buffer_14, ff_buffer_15, ff_buffer_16, ff_buffer_17, ff_buffer_18, ff_buffer_19, ff_buffer_20, ff_buffer_21, ff_buffer_22, ff_buffer_23, ff_buffer_24, ff_buffer_25, ff_buffer_26, ff_buffer_27, ff_buffer_28, ff_buffer_29, ff_buffer_30, ff_buffer_31, ff_buffer_32, ff_buffer_33, ff_buffer_34, ff_buffer_35, ff_buffer_36, ff_buffer_37, ff_buffer_38, ff_buffer_39, ff_buffer_40}),
    .system_free(system_free),
    .max_order_id_1(max_order_id_1),
    .max_quantity_1(max_quantity_1),
    .max_price_1(max_price_1),
    .max_order_id_2(max_order_id_2),
    .max_quantity_2(max_quantity_2),
    .max_price_2(max_price_2),
    .max_order_id_3(max_order_id_3),
    .max_quantity_3(max_quantity_3),
    .max_price_3(max_price_3),
    .max_order_id_4(max_order_id_4),
    .max_quantity_4(max_quantity_4),
    .max_price_4(max_price_4)
);*/


endmodule

module top(
input logic        clk,
input logic 	   reset,
input logic [319:0]  ff_buffer,
input logic 	   buffer_not_empty, 
output logic system_free,
output logic [31:0] max_order_id_1,
output logic [31:0] max_quantity_1,
output logic [63:0] max_price_1,
output logic [31:0] max_order_id_2,
output logic [31:0] max_quantity_2,
output logic [63:0] max_price_2,
output logic [31:0] max_order_id_3,
output logic [31:0] max_quantity_3,
output logic [63:0] max_price_3,
output logic [31:0] max_order_id_4,
output logic [31:0] max_quantity_4,
output logic [63:0] max_price_4
);

logic ready_stock1;
logic ready_stock2;
logic ready_stock3;
logic ready_stock4;

logic [31:0] order_id_p;
logic [31:0] quantity_p;
logic [63:0] price_p;
logic [11:0] stock_activate_out;

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
   
	       
endmodule


module order_book (
input clk,
input resetn,
input valid,
input [31:0] order_id,
input [31:0] quantity,
input [63:0] price,
input [2:0] req_type,
output logic [31:0] max_order_id,
output logic [31:0] max_quantity,
output logic [63:0] max_price,
output logic ready
);

logic [127:0] memory [1023:0];
logic [9:0] pointer;
logic [2:0] current_state;
logic [9:0] search_pointer;
logic [63:0] temp_max;
logic [63:0] temp_max_price;
logic [31:0] temp_max_quantity;
logic [31:0] temp_max_order_id;

always_ff@(posedge clk)begin
    case (current_state)
        `IDLE: begin
            //ready <= 1'b1;
            search_pointer <= 10'd0;
            if (ready == 1'b1 && valid == 1'b1 && req_type != 3'b000 && resetn != 1'b0)begin
                if (req_type == 3'b100)begin
                    current_state <= `ADD_ORDER;
		    ready <= 1'b0;
                end
                else if (req_type == 3'b010)begin
                    current_state <= `DELETE_ORDER;
		    ready <= 1'b0; 
                end
                else if (req_type == 3'b001)begin
                    current_state <= `DECREASE_ORDER;
		    ready <= 1'b0;
                end
            end
        end 
        `ADD_ORDER: begin
            ready <= 1'b1;
            current_state <= `IDLE;
            pointer <= pointer + 1;
            memory [pointer] <= { order_id, quantity, price};
            if (price > max_price)begin
                max_order_id <= order_id;
                max_quantity <= quantity;
                max_price <= price;
            end
        end
        `DELETE_ORDER: begin
            //ready <= 1'b0;
            if (memory[search_pointer][127:96] == order_id)begin
                pointer <= pointer - 1;
                current_state <= `SHIFT_BOOK;
            end
            else begin 
		search_pointer = search_pointer + 1'b1;
		if (search_pointer == pointer) begin 
			current_state <= `IDLE;
			ready <= 1'b1;
		end
	    end
        end
        `SHIFT_BOOK: begin
            if (search_pointer == (pointer + 1)) begin
                if (order_id == max_order_id) begin
                    current_state <= `FIND_MAX;
                    search_pointer <= 10'd0;
                    temp_max <= 64'd0;
                end
                else begin 
			current_state <= `IDLE;
			ready <= 1'b1;
		end
            end
            else begin
                memory [search_pointer] <= memory [search_pointer+1];
                search_pointer <= search_pointer + 1;
            end
        end
        `FIND_MAX:begin
            if (memory[search_pointer][63:0] > temp_max )begin
                temp_max_order_id <= memory [search_pointer][127:96];
                temp_max_quantity <= memory [search_pointer][95:64];
                temp_max_price <= memory [search_pointer][63:0];
            end
            search_pointer <= search_pointer + 1'b1;
            if (search_pointer == pointer) begin
                current_state <= `IDLE;
		ready <= 1'b1;
                max_order_id <= temp_max_order_id;
                max_price <= temp_max_price;
                max_quantity <= temp_max_quantity;
            end
        end
        `DECREASE_ORDER: begin
            ready <= 1'b0;
            if (memory[search_pointer][127:96] == order_id)begin
                if (memory[search_pointer][95:64] > quantity)
                    memory[search_pointer][95:64] <= memory[search_pointer][95:64] - quantity;
                else memory[search_pointer][95:64] <= 32'd0;
                current_state <= `IDLE;
		ready <= 1'b1;
            end
	    search_pointer <= search_pointer + 1;
	    if (search_pointer == pointer) begin 
			current_state <= `IDLE;
			ready <= 1'b1;
		end
        end
        default: current_state <= `IDLE;
    endcase
end

always_comb begin
    if (!resetn)begin
	ready <= 1'b1;
        pointer <= 10'd0;
        current_state <= `IDLE;
	max_price <= 64'd0;
    end
end

endmodule

module parser(
input [319:0] ff_buffer,
output logic [31:0] out_order_id,
output logic [31:0] out_quantity,
output logic [63:0] out_price,
output logic [11:0] stock_activate
);

logic [7:0] req_type;
logic [31:0] order_id;
logic [31:0] stock_id;
logic [31:0] quantity;
logic [63:0] price;
logic [7:0] side;
logic [1:0] current_state;
logic [1:0] next_state;
command_out ns_command;
command_out cs_command;
command_out stock_command;
assign req_type = ff_buffer[319:312];
assign stock_id = ff_buffer[183:152];
assign order_id = ff_buffer[247:216];
assign quantity = ff_buffer[143:112];
assign price = ff_buffer[111:48];
assign side = ff_buffer[151:144];
assign stock_command = cs_command;
assign stock_activate_out = cs_command.stock_activate;
assign master_valid = cs_command.master_valid;
assign system_free = cs_command.system_free;
assign out_order_id = order_id;
assign out_quantity = quantity;
assign out_price = price;

always_comb begin
		if (stock_id == `STOCK1)begin
			if (req_type == `REQ_TYPE_ADD)begin
				stock_activate <= `ADD1;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				stock_activate <= `DELETE1;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				stock_activate <= `DECREASE1;
			end
		end
		if (stock_id == `STOCK2)begin
			if (req_type == `REQ_TYPE_ADD)begin
				stock_activate <= `ADD2;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				stock_activate <= `DELETE2;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				stock_activate <= `DECREASE2;
			end
		end
		if (stock_id == `STOCK3)begin
			if (req_type == `REQ_TYPE_ADD)begin
				stock_activate <= `ADD3;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				stock_activate <= `DELETE3;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				stock_activate <= `DECREASE3;
			end
		end
		if (stock_id == `STOCK4)begin
			if (req_type == `REQ_TYPE_ADD)begin
				stock_activate <= `ADD4;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				stock_activate <= `DELETE4;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				stock_activate <= `DECREASE4;
			end
		end
end



endmodule


