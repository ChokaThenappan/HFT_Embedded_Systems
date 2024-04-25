module Memory (
	input clk,
	input reset,
	input wr_valid,
	input rd_valid,
	input [9:0] address,
	input [128:0] data_in,
	output reg [128:0] data_out
);

	reg [128:0] memory [1023:0];
	reg [128:0] data_out;
	reg ready;

	always @(posedge clk) begin
		if (reset) begin
			data_out <= 0;
			ready <= 0;
		end
		else if (wr_valid) begin
			memory[address] <= data_in;
		end
		else if (rd_data) begin
			data_out <= memory[address];
		end
	end

endmodule
