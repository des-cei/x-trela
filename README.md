# SoC Soñamos repository and Virtual Machine instructions

`VM password:` linuxboss

## Repo setup

1. Navigate to directory
```bash
cd work/soc_sonhamos
```
2. Activate enviroment and add variables to path
```bash
source ./env.sh
```

## Makefile rules

- `mcu-gen`: Generate the SoC with the configurations of `/configs`
- `verilator-sim` and `run-app-verilator` to compile the Verilator simulator and execute the simulation. A different program to be compiled can be selected by including `PROJECT=name_of_application` in the make command. The same applies for the Questasim simulation (`questasim-sim-opt` and `run-app-questasim`)
- `vivado-fpga`: Generate the SoC bitstream for the PYNQ-Z2 board

## Debugging in the PYNQ-Z2 board

1. Open Vivado and program the FPGA
2. Close Vivado to release the JTAG
3. Execute OpenOCD and leave the terminal running
```bash
openocd -f hw/vendor/esl_epfl_x_heep/tb/core-v-mini-mcu-pynq-z2-bscan.cfg
```
4. Open other terminal and compile a program for the PYNQ-Z2:
```bash
make app PROJECT=name_of_application TARGET=pynq-z2
```
5. Start a GDB debugging session:
```bash
riscv32-unknown-elf-gdb sw/build/main.elf
```
6. Inside the GDB session, connect to OpenOCD server:
```
target extended-remote localhost:3333
load
continue
```