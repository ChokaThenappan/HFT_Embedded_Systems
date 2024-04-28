`timescale 1ns/1ps
`define SD #0.010
`define HALF_CLOCK_PERIOD #2

module testbench();
reg clk;
reg resetn;
reg valid;
reg [31:0] order_id;
reg [31:0] quantity;
reg [63:0] price;
reg [2:0] req_type;
wire [31:0] max_order_id;
wire [31:0] max_quantity;
wire [63:0] max_price;
wire ready;

integer i;

order_book stock1 (clk, resetn, valid, order_id, quantity, price, req_type, max_order_id, max_quantity, max_price, ready);

	
always begin
	`HALF_CLOCK_PERIOD;
	clk = ~clk;
end

initial begin

	$dumpfile("dump.vcd"); 
	$dumpvars;
	clk = 0;
	resetn = 0;
	valid = 0;
	req_type = 3'b000;
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	resetn = 1;
	@(posedge clk);
	@(posedge clk);
	@(posedge clk);
	for(i=0; i<100; i++)begin
		order_id = i;
		req_type = 3'b100;
		quantity = 32'h435365;
		price = (i * 20);
		valid = 1;
		@(posedge ready);
		valid = 0;
		@(posedge clk);
	end
	order_id = 100;
	req_type = 3'b100;
	quantity = 32'h435365;
	price = 64'h3981;
	valid = 1;
	@(posedge ready);
	valid = 0;
	@(posedge clk);
	
	for(i=101; i<200; i++)begin
		order_id = i;
		req_type = 3'b100;
		quantity = 32'h435365;
		price = (i * 20);
		valid = 1;
		@(posedge ready);
		valid = 0;
		@(posedge clk);
	end
	order_id = 40;
	req_type = 3'b001;
	quantity = 32'hF;
	price = (i * 20);
	valid = 1;
	@(posedge ready);
	valid = 0;
	@(posedge clk);
	
	order_id = 100;
	req_type = 3'b010;
	quantity = 32'hFFFF;
	price = 64'h3981;
	valid = 1;
	@(posedge ready);
	valid = 0;
	@(posedge clk);
	$finish;
end
endmodule // testbench
