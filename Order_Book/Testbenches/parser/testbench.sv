`timescale 1ns/1ps
`define SD #0.010
`define HALF_CLOCK_PERIOD #2
typedef struct{
	reg [31:0] order_id;
	reg [31:0] quantity;
	reg [63:0] price;
	reg [11:0] stock_activate;
} command_out;

module testbench();

	reg clk;
	reg resetn;
	reg buffer_not_empty;
	reg [319:0] ff_buffer;
  	reg stock_ready;
	wire valid;
	wire [1:0] current_state;
	wire [31:0] out_order_id;
	wire [31:0] out_quantity;
	wire [63:0] out_price;


  parser order(clk,resetn,buffer_not_empty,ff_buffer,stock_ready, valid,out_order_id, out_quantity, out_price,  current_state);
	
	always begin
		`HALF_CLOCK_PERIOD;
		clk = ~clk;
	end
//537856341278563412000103EA080000060000000042000000640000000000000055060000050000
	initial begin
        
		$dumpfile("dump.vcd"); 
  		$dumpvars;
		clk = 0;
		resetn = 0;
      		stock_ready = 1'b0;
		buffer_not_empty = 0;
		ff_buffer = 320'h0;
		
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
      		
		buffer_not_empty = 1;
		
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
      		
		stock_ready = 1'b1;
		resetn = 1;
		ff_buffer = 320'h447856341278563412000103EA080000060000000042000000640000000000000055060000050000;
		
		@(posedge clk);
		stock_ready = 1'b0;
		buffer_not_empty = 0;
		
		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
		stock_ready = 1'b1;
      		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
		$finish;
	end
endmodule // testbench
