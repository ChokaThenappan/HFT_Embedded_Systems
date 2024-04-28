##################################################
#  Modelsim do file to run simuilation
#  MS 7/2015
##################################################

vlib work 
vmap work work

# Include Netlist and Testbench
vlog +acc -incr order_book.sv 
vlog +acc -incr testbench.sv 

# Run Simulator 
vsim +acc -t ps -lib work testbench 
do waveformat.do   
run -all
