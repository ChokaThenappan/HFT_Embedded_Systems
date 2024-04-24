`timescale 1ns/1ps
`define SD #0.010
`define HALF_CLOCK_PERIOD #2

module testbench();

	reg clk;
	reg resetn;
	reg buffer_not_empty;
	reg [319:0] ff_buffer;
    wire [161:0] out_object;
	wire ready;

	order_book_parser order(clk,resetn,buffer_not_empty,ff_buffer,out_object,ready);
	
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
		buffer_not_empty = 0;
		ff_buffer = 320'h447856341278563412000103EA080000060000000042000000640000000000000055060000050000;
		@(posedge clk);
		@(posedge clk);
		resetn = 1;
		buffer_not_empty = 1;
		ff_buffer = 320'h447856341278563412000103EA080000060000000042000000640000000000000055060000050000;
		
		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
		@(posedge clk);
		
		
		
		$finish;
	end 

endmodule // testbench
