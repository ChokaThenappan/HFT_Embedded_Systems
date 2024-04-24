module order_book_parser(
input clk,
input resetn,
input buffer_not_empty,
input [319:0] ff_buffer,
output reg [7:0] req_type,
output reg [31:0] order_id,
output reg [31:0] stock_id,
output reg [31:0] quantity,
output reg [63:0] price,
output reg [7:0] side,
output reg ready);

  
always@(posedge clk)begin
	if (!resetn)begin
		req_type <= 0;
		stock_id <= 0;
		order_id <= 0;
		quantity <= 0;
      		price <= 0;
      		side <= 0;
		ready <= 1'b1;
	end
  	else if (buffer_not_empty == 1'b1 && ready == 1'b1)begin
		ready <= 1'b0;
		req_type <= ff_buffer[319:312];
		//319:312 - 8
		//311:248 - 64
		//247:216 - 32
		//215:184 - 32
		//183:152 - 32
		//151:144 - 8
		//143:112 - 32
		//111:48 - 64
		//47:16 - 32
		//15:0 - 16
		stock_id <= ff_buffer[183:152];
		order_id <= ff_buffer[247:216];
		quantity <= ff_buffer[143:112];
      		price <= ff_buffer[111:48];
      		side <= ff_buffer[151:144];
	end
    	else ready <= 1'b1;
end    
endmodule
