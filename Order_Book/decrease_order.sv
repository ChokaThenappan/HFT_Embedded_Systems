`include typedef1.sv

module decrease_order(
    input clk, 
    input book_entry order, 
    input delete, 
    input mem_valid,
    input [8:0] size, 
    input [15:0] best_price, 
	input start,
	input book_entry data_r,
	input mem_struct mem_control,
	output book_entry data_w,
    output logic ready, 
    output logic [7:0] size_update_o,
    output logic  [15:0] update );

    
endmodule

