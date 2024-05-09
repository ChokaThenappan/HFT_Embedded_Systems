onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /testbench/clk
add wave -noupdate /testbench/resetn
add wave -noupdate /testbench/buffer_not_empty
add wave -noupdate /testbench/system_free
add wave -noupdate -radix unsigned /testbench/ff_buffer
add wave -noupdate -radix unsigned /testbench/max_order_id_1
add wave -noupdate -radix unsigned /testbench/max_quantity_1
add wave -noupdate -radix unsigned /testbench/max_price_1

add wave -noupdate -radix unsigned /testbench/max_order_id_2
add wave -noupdate -radix unsigned /testbench/max_quantity_2
add wave -noupdate -radix unsigned /testbench/max_price_2

add wave -noupdate -radix unsigned /testbench/max_order_id_3
add wave -noupdate -radix unsigned /testbench/max_quantity_3
add wave -noupdate -radix unsigned /testbench/max_price_3

add wave -noupdate -radix unsigned /testbench/max_order_id_4
add wave -noupdate -radix unsigned /testbench/max_quantity_4
add wave -noupdate -radix unsigned /testbench/max_price_4

add wave -noupdate -radix unsigned /bid_side/stock1/current_state
add wave -noupdate -radix unsigned /bid_side/stock1/search_pointer
add wave -noupdate -radix unsigned /p_block/cs_command

add wave -noupdate -radix unsigned /bid_side/valid1
add wave -noupdate -radix unsigned /bid_side/valid2
add wave -noupdate -radix unsigned /bid_side/valid3
add wave -noupdate -radix unsigned /bid_side/valid4

add wave -noupdate -radix unsigned /bid_side/out_order_id_p
add wave -noupdate -radix unsigned /bid_side/stock_ready_p
add wave -noupdate -radix unsigned /bid_side/stock_activate_out
add wave -noupdate -radix unsigned /bid_side/out_quantity_p
add wave -noupdate -radix unsigned /bid_side/out_price_p
add wave -noupdate -radix unsigned /bid_side/valid_p
add wave -noupdate -radix unsigned /bid_side/stock1/memory
add wave -noupdate -radix unsigned bid_side/p_block/stock_id
add wave -noupdate -radix unsigned bid_side/p_block/current_state
add wave -noupdate -radix unsigned bid_side/p_block/ns_command
add wave -noupdate -radix unsigned bid_side/p_block/cs_command


TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {3 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 223
configure wave -valuecolwidth 89
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ns} {12 ns}


