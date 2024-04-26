`define STOCK1 8'h10
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

`define IDLE 2'b00
`define SEND_COMMAND 2'b01
`define WAIT_FOR_RESPONSE 2'b10

typedef struct{
	reg [31:0] order_id;
	reg [31:0] quantity;
	reg [63:0] price;
	reg [11:0] stock_activate;
} command_out;

module parser(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] ff_buffer,
input stock_ready, 
output reg valid,
output reg [31:0] out_order_id,
output reg [31:0] out_quantity,
output reg [63:0] out_price,
output reg [1:0] current_state
);

reg [7:0] req_type;
reg [31:0] order_id;
reg [31:0] stock_id;
reg [31:0] quantity;
reg [63:0] price;
reg [7:0] side;
//reg [1:0] current_state;
reg [1:0] next_state;
command_out ns_command;
command_out cs_command;
command_out stock_command;

assign out_order_id = cs_command.order_id;
assign out_quantity = cs_command.quantity;
assign out_price = cs_command.price;
assign req_type = ff_buffer[319:312];
assign stock_id = ff_buffer[183:152];
assign order_id = ff_buffer[247:216];
assign quantity = ff_buffer[143:112];
assign price = ff_buffer[111:48];
assign side = ff_buffer[151:144];
assign stock_command = cs_command;

always@(*) begin
	case (current_state)
	`IDLE: begin
		valid <= 1'b0;
		ns_command.stock_activate <= 12'd0;
		if (buffer_not_empty == 1'b1)begin
			next_state <= `SEND_COMMAND;
		end
	end
	`SEND_COMMAND: begin
		valid <= 1'b0;
		ns_command.order_id <= order_id;
		ns_command.quantity <= quantity;
		ns_command.price <= price;
		if (stock_id == `STOCK1)begin
			if (req_type == `REQ_TYPE_ADD)begin
				ns_command.stock_activate <= `ADD1;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				ns_command.stock_activate <= `DELETE1;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				ns_command.stock_activate <= `DECREASE1;
			end
		end
		if (stock_id == `STOCK2)begin
			if (req_type == `REQ_TYPE_ADD)begin
				ns_command.stock_activate <= `ADD2;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				ns_command.stock_activate <= `DELETE2;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				ns_command.stock_activate <= `DECREASE2;
			end
		end
		if (stock_id == `STOCK3)begin
			if (req_type == `REQ_TYPE_ADD)begin
				ns_command.stock_activate <= `ADD3;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				ns_command.stock_activate <= `DELETE3;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				ns_command.stock_activate <= `DECREASE3;
			end
		end
		if (stock_id == `STOCK4)begin
			if (req_type == `REQ_TYPE_ADD)begin
				ns_command.stock_activate <= `ADD4;
			end
			else if (req_type == `REQ_TYPE_DELETE)begin
				ns_command.stock_activate <= `DELETE4;
			end
			else if (req_type == `REQ_TYPE_DECREASE)begin
				ns_command.stock_activate <= `DECREASE4;
			end
		end
		next_state <= `WAIT_FOR_RESPONSE;
	end
	`WAIT_FOR_RESPONSE: begin
		valid <= 1'b1;
		@(posedge stock_ready) begin
			next_state <= `IDLE;
		end
	end
	endcase
end


always@(posedge clk)begin
	if (!resetn) begin
		current_state <= `IDLE;
	end
	else begin
		current_state <= next_state;
		cs_command <= ns_command;
	end
end

endmodule
