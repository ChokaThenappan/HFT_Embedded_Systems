`timescale 1ns/ 1ps

module debounce (
    input reset,
    input clock,
    input noisy,
    output clean_out
);

    reg [19:0] count;
    reg input_new;
    reg clean_out_temp;

    assign clean_out_temp = clean_out;

    always_ff@(posedge clock)begin
        if(reset)begin
            input_new <= noisy;
            clean_out_temp <= noisy;
            count <= 0;
        end

        else if (noisy != input_new) begin
            input_new <= noisy;
            count <= 0;
        end

        else if ( count == 10000)begin
            clean_out_temp <= input_new;
        end

        else count <= count + 1b'1;
    end
endmodule