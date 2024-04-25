`define ADD 3'b001
`define DECREASE 3'b010 
`define DELETE 3'b100

`define STOCK1 100
`define STOCK2 200 
`define STOCK3 300 
`define STOCK3 400  

typedef struct{
	reg [31:0] order_id;
	reg [31:0] quantity;
	reg [63:0] price;
	reg [2:0] order_type;
}command_out;

module order_book_parser(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] ff_buffer,
output reg ready,
output command_out stock1_command,
output reg stock1_valid
);

reg [7:0] req_type;
reg [31:0] order_id;
reg [31:0] stock_id;
reg [31:0] quantity;
reg [63:0] price;
reg [7:0] side;

assign req_type = ff_buffer[319:312];
assign stock_id = ff_buffer[183:152];
assign order_id = ff_buffer[247:216];
assign quantity = ff_buffer[143:112];
assign price = ff_buffer[111:48];
assign side = ff_buffer[151:144];

always@(posedge clk)begin
	if (!resetn)begin
		ready <= 1'b1;
		stock1_valid <= 1'b0;
	end
  	else if (buffer_not_empty == 1'b1 && ready == 1'b1)begin
		ready <= 1'b0;
		case(stock_id)
			`STOCK1: begin
				stock1_command.order_id <= order_id;
				stock1_command.quantity <= quantity;
				stock1_command.price <= price;
				stock1_command.order_type <= (req_type == 8'h53)? `ADD : ((req_type == 8'h44)? `DELETE : ((req_type == 8'h45)?`DECREASE: 3'b000));
			end
			`STOCK2: begin
				stock2_command.order_id <= order_id;
				stock2_command.quantity <= quantity;
				stock2_command.price <= price;
				stock2_command.order_type <= (req_type == 8'h53)? `ADD : ((req_type == 8'h44)? `DELETE : ((req_type == 8'h45)?`DECREASE: 3'b000));
			end
			`STOCK3: begin
				stock3_command.order_id <= order_id;
				stock3_command.quantity <= quantity;
				stock3_command.price <= price;
				stock3_command.order_type <= (req_type == 8'h53)? `ADD : ((req_type == 8'h44)? `DELETE : ((req_type == 8'h45)?`DECREASE: 3'b000));
			end
			`STOCK4: begin
				stock4_command.order_id <= order_id;
				stock4_command.quantity <= quantity;
				stock4_command.price <= price;
				stock4_command.order_type <= (req_type == 8'h53)? `ADD : ((req_type == 8'h44)? `DELETE : ((req_type == 8'h45)?`DECREASE: 3'b000));
			end
		endcase		
	end
    	else ready <= 1'b1;
end    
endmodule
