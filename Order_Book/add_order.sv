`define WAIT 
`define SERVE_ORDER

typedef struct{
    reg wr_valid,
	reg rd_valid,
	reg [9:0] address,
	reg [128:0] data_in,
} memory_request;

module add_order (
    input valid,
    input [31:0] order_id,
	input [31:0] quantity,
	input [63:0] price,
    output ready
);

memory_request cs_request;
memory_request ns_request;
reg debounce_flag;

always@(*) begin
    case (current_state)
    `WAIT:  begin
        ready <= 1'b1;
        debounce_flag <= 1'b0;
        ns_request.wr_valid <= 1'b0;
        ns_request.rd_valid <= 1'b0;
    end
    `SERVE_ORDER: begin
        ready <= 1'b0;
        wr_valid <= 1'b1;
        

    end
    default: 
endcase
end



    
endmodule