`timescale 1ns/1ps
`define SD #0.010
`define HALF_CLOCK_PERIOD #2

module testbench();

	reg clk;
	reg resetn;
	reg buffer_not_empty;
	reg [319:0] ff_buffer;
  	reg stock_ready;
	wire [31:0] max_order_id_1;
	wire [31:0] max_quantity_1;
	wire [63:0] max_price_1;
	wire [31:0] max_order_id_2;
	wire [31:0] max_quantity_2;
	wire [63:0] max_price_2;
	wire [31:0] max_order_id_3;
	wire [31:0] max_quantity_3;
	wire [63:0] max_price_3;
	wire [31:0] max_order_id_4;
	wire [31:0] max_quantity_4;
	wire [63:0] max_price_4;
	wire system_free;
	integer i;
  top bid_side(clk,resetn,buffer_not_empty,ff_buffer, system_free, max_order_id_1, max_quantity_1, max_price_1, max_order_id_2, max_quantity_2, max_price_2, max_order_id_3, max_quantity_3, max_price_3, max_order_id_4, max_quantity_4, max_price_4);
	
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
		ff_buffer = 320'h537856341278563412000103EA08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge clk);
		@(posedge clk);
      		@(posedge clk);
		resetn = 1;

		for(i = 0; i < 100; i++) begin
			buffer_not_empty = 1;
			ff_buffer = ff_buffer + 320'h00000000000000000000000001000000000000000000_0000_0001_0000_0000_0000_0002_0000_0000_0000;
			@(posedge system_free);
		end
ff_buffer = 320'h537856341278563412000103EA08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
		for(i = 0; i < 100; i++) begin
			buffer_not_empty = 1;
			ff_buffer = ff_buffer + 320'h00000000000000000000000001000000000000000000_0000_0001_0000_0000_0000_0002_0000_0000_0000;
			@(posedge system_free);
		end

		ff_buffer = 320'h447856341278563412000103FF08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
ff_buffer = 320'h4478563412785634120001044608000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
ff_buffer = 320'h4478563412785634120001044608000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
ff_buffer = 320'h457856341278563412000103EA08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
ff_buffer = 320'h537856341278563412000203EA08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
		for(i = 0; i < 100; i++) begin
			buffer_not_empty = 1;
			ff_buffer = ff_buffer + 320'h00000000000000000000000001000000000000000000_0000_0001_0000_0000_0000_0002_0000_0000_0000;
			@(posedge system_free);
		end
		/*ff_buffer = 320'h4478563412785634120001040708000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
		ff_buffer = 320'h457856341278563412000103FC08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);
		for(i = 0; i < 100; i++) begin
			buffer_not_empty = 1;
			ff_buffer = ff_buffer + 320'h00000000000000000000000001000000000000000000_0000_0001_0000_0000_0000_0002_0000_0000_0000;
			@(posedge system_free);
		end
		ff_buffer = 320'h457856341278563412000103FF08000006000000_0042_0000_0064_0000_0000_0000_0055_0600_0005_0000;
		@(posedge system_free);*/
		@(posedge clk);
		$finish;
	end 

endmodule // testbench
