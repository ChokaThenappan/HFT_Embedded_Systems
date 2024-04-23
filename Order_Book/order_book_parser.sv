module order_book_parser(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] buffer_text,
output [161:0] out_object,
output ready);

//Outformat: MSG_TYPE [2]| Stock_ID [32]| Order_ID [32]| Quantity [32] | Price [64] 

reg [319:0] ff_buffer;
reg [161:0] out_object_reg;
//reg [1:0] msg_type;
reg ready_reg;

assign ready = ready_reg;
assign out_object = out_object_reg;
always@(posedge clk)begin
	ready_reg <= 1'b1;
	if (!resetn)begin
		out_object_reg <= 162'd0;
		ff_buffer <= 320'd0;
		msg_type <= 2'd3;
		ready_reg <= 1'b1;
	end
	else if (buffer_not_empty == 1'b1 && ready_reg == 1'b1)begin
		ff_buffer <= buffer_text;
		ready_reg <= 1'b0;
		//if (ff_buffer[319:312] == 8'h53) msg_type <= 2'b00;
		//else if (ff_buffer[319:312] == 8'h44) msg_type <= 2'b01;
		//else if (ff_buffer[319:312] == 8'h45) msg_type <= 2'b10; 
		//ff_buffer [319:312] == 8'h53 ? 2'b00 : ((ff_buffer[319:312] == 8'h44)? 2'b00 : 2'b10)
		out_object_reg <= {ff_buffer [319:312] == 8'h53 ? 2'b00 : ((ff_buffer[319:312] == 8'h44)? 2'b00 : 2'b10), ff_buffer[184:153], ff_buffer[249:218], ff_buffer[143:112], ff_buffer[111:48]};
	end
end    
endmodule
