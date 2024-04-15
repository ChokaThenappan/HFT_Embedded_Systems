`define IDLE 0
`define READ 1
`define WRITE 2

module memory(
input clk,
input [11:0] address_in,
input [31:0] data_in,
input write_request,
input data_read,
output [31:0]data_out,
output out_valid

);


logic [31:0] mem [0:4096];
logic write_busy0, out_valid0;
logic [31:0] data_out0;
logic in_req_type0;

always@(posedge clk) begin
	if (out_valid <= 1'b1) begin
		if (data_read == 1'b1) out_valid <= 1'b0;
	end
	else begin
		if (write_request)begin 
			mem[address_in] <= data_in;
		end
		else begin
			data_out <= mem[address];
			out_valid <= 1'b1;
		end
	end
	
end

endmodule
