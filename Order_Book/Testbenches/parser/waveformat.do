onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /testbench/clk
add wave -noupdate /testbench/resetn
add wave -noupdate /testbench/buffer_not_empty
add wave -noupdate /testbench/valid
add wave -noupdate /testbench/stock_ready
add wave -noupdate -radix unsigned /testbench/ff_buffer
add wave -noupdate -radix unsigned /testbench/out_order_id
add wave -noupdate -radix unsigned /testbench/out_quantity
add wave -noupdate -radix unsigned /testbench/out_price
add wave -noupdate -radix unsigned /testbench/current_state

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


