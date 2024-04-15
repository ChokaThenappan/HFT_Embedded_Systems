`include typedef1.sv

module add_order(
    input clk, 
    input book_entry order, 
    input start, 
    input valid,
    input [7:0] price_distr ,
    input [8:0] size, 
    input [15:0] best_price, 
    input price_valid,
    output logic [15:0] addr,  
    output logic mem_start,
    output book_entry data_w,
    output logic price_update,
    output logic quantity_update,
    output quantity,
    output logic is_write, 
    output logic ready, 
    output logic [7:0] size_update_o,
    output logic  [15:0] add_best_price );

    logic state = 0;
 	logic size_update = 0;
    always_ff@(posedge clk) begin
        case(state)
        1'b0: begin
            ready <= 0;
            if (start) begin
                    addr <= size;
                    is_write <= 1;
                    size_update <= size + 1;
                    state <= 1'b0;
                    data_w <= order;
                    mem_start <= 1;
                    price_update <= order.price;
                    quantity_update <= order.quantity;
                    if (!price_valid || (order.price > best_price) == 200)begin
                        add_best_price <= order.price;
                    end
                    else begin
                        add_best_price <= best_price;
                    end
            end
        end

        1'b1: begin
            mem_start <= 0;
            if(valid) begin
                ready <= 1;
                state <= 1'b0;
            end
        end
        endcase
    end
endmodule

