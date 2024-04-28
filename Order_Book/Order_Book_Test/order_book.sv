`define IDLE 3'd0
`define ADD_ORDER 3'd1
`define DELETE_ORDER 3'd2
`define SHIFT_BOOK 3'd3
`define FIND_MAX 3'd4
`define DECREASE_ORDER 3'd5
module order_book (
input clk,
input reset,
input valid,
input [31:0] order_id,
input [31:0] quantity,
input [63:0] price,
input [2:0] req_type,
output reg [31:0] max_order_id,
output reg [31:0] max_quantity,
output reg [63:0] max_price,
output reg ready
);

reg [127:0] memory [1023:0];
reg [9:0] pointer;
reg [2:0] current_state;
reg [9:0] search_pointer;
reg [63:0] temp_max;
reg [63:0] temp_max_price;
reg [31:0] temp_max_quantity;
reg [31:0] temp_max_order_id;

always@(posedge clk)begin
    case (current_state)
        `IDLE: begin
            ready <= 1'b1;
            search_pointer <= 10'd0;
            if (ready == 1'b1 && valid == 1'b1)begin
                if (req_type == 3'b100)begin
                    current_state <= `ADD_ORDER;
                end
                else if (req_type == 3'b010)begin
                    current_state <= `DELETE_ORDER; 
                end
                else if (req_type == 3'b001)begin
                    current_state <= `DECREASE_ORDER;
                end
            end
        end 
        `ADD_ORDER: begin
            ready <= 1'b0;
            current_state <= `IDLE;
            pointer <= pointer + 1;
            memory [pointer] <= { order_id, quantity, price};
            if (price > max_price)begin
                max_order_id <= order_id;
                max_quantity <= quantity;
                max_price <= price;
            end
        end
        `DELETE_ORDER: begin
            ready <= 1'b0;
            if (memory[search_pointer][127:96] == order_id)begin
                pointer <= pointer - 1;
                current_state <= `SHIFT_BOOK;
            end
            else search_pointer = search_pointer + 1'b1;
        end
        `SHIFT_BOOK: begin
            if (search_pointer == (pointer + 1)) begin
                if (order_id == max_order_id) begin
                    current_state <= `FIND_MAX;
                    search_pointer <= 10'd0;
                    temp_max <= 64'd0;
                end
                else current_state <= `IDLE;
            end
            else begin
                memory [search_pointer] <= memory [search_pointer+1];
                search_pointer <= search_pointer + 1;
            end
        end
        `FIND_MAX:begin
            if (memory[search_pointer][63:0] > temp_max )begin
                temp_max_order_id <= memory [search_pointer][127:96];
                temp_max_quantity <= memory [search_pointer][95:64];
                temp_max_price <= memory [search_pointer][63:0];
            end
            search_pointer <= search_pointer + 1'b1;
            if (search_pointer == pointer) begin
                current_state <= `IDLE;
                max_order_id <= temp_max_order_id;
                max_price <= temp_max_price;
                max_quantity <= temp_max_quantity;
            end
        end
        `DECREASE_ORDER: begin
            ready <= 1'b0;
            if (memory[search_pointer][127:96] == order_id)begin
                if (memory[search_pointer][95:64] > quantity)
                    memory[search_pointer][95:64] <= memory[search_pointer][95:64] - quantity;
                else memory[search_pointer][95:64] <= 32'd0;
                current_state <= `IDLE;
            end
	    search_pointer <= search_pointer + 1;
        end
        default: current_state <= `IDLE;
    endcase
end

always@(*)begin
    if (!reset)begin
        pointer <= 10'd0;
        current_state <= `IDLE;
	max_price <= 64'd0;
    end
end

endmodule
