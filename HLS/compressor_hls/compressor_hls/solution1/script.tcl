############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project compressor_hls
set_top predictor
add_files predictor.c
add_files predictor.h
add_files sample_adaptative.c
add_files sample_adaptative.h
add_files -tb main.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xcvu5p-flva2104-1-e}
create_clock -period 10 -name default
#source "./compressor_hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
