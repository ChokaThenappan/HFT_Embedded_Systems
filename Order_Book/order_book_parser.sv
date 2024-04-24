module order_book_parser(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] ff_buffer,
output reg [161:0] out_object,
output reg ready);

//Outformat: MSG_TYPE [2]| Stock_ID [32]| Order_ID [32]| Quantity [32] | Price [64] 

///reg [319:0] ff_buffer;
  
always@(posedge clk)begin
	//ff_buffer <= buffer_text;
	if (!resetn)begin
		out_object <= 162'd0;
		ready <= 1'b1;
	end
  	else if (buffer_not_empty == 1'b1 && ready == 1'b1)begin
		ready <= 1'b0;
      	out_object <= {ff_buffer[319:312], ff_buffer[184:153], ff_buffer[249:218], ff_buffer[143:112], ff_buffer[111:48]};
	end
    	else ready <= 1'b1;
end    
endmodule
