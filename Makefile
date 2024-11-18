# Copyright 2024 CEI-UPM

FUSESOC := $(shell which fusesoc)
PYTHON  := $(shell which python)

BASE_DIR = ../../..

MCU_CFG_PERIPHERALS ?= configs/ext_mcu_cfg.hjson
X_HEEP_CFG ?= configs/ext_mem_cfg.hjson
PAD_CFG ?= configs/ext_pad_cfg.hjson

PROJECT ?= hello_world_ext

mcu-gen:
	$(MAKE) -C hw/vendor/esl_epfl_x_heep X_HEEP_CFG=$(BASE_DIR)/$(X_HEEP_CFG) MCU_CFG_PERIPHERALS=$(BASE_DIR)/$(MCU_CFG_PERIPHERALS) PAD_CFG=$(BASE_DIR)/$(PAD_CFG) mcu-gen
	$(PYTHON) util/mcu_gen.py --config $(X_HEEP_CFG) --cfg_peripherals $(MCU_CFG_PERIPHERALS) --pads_cfg $(PAD_CFG) --outdir tb/ --tpl-sv tb/tb_util.svh.tpl
	bash -c "cd hw/vendor/cei_upm_strela/data; source gen_strela_regs.sh; cd ../../../../"
	$(MAKE) verible

verible:
	util/format-verible

## Verilator simulation with C++
verilator-sim:
	$(FUSESOC) --cores-root . run --no-export --target=sim --tool=verilator $(FUSESOC_FLAGS) --build ceiupm:systems:x_trela ${FUSESOC_PARAM} 2>&1 | tee buildsim.log

run-app-verilator:
	$(MAKE) app PROJECT=$(PROJECT)
	cd build/ceiupm_systems_x_trela_0/sim-verilator/ && ./Vtestharness +firmware=../../../sw/build/main.hex
	cat build/ceiupm_systems_x_trela_0/sim-verilator/uart0.log

# Questasim simulation
questasim-sim:
	$(FUSESOC) --cores-root . run --no-export --target=sim --tool=modelsim $(FUSESOC_FLAGS) --build ceiupm:systems:x_trela ${FUSESOC_PARAM} 2>&1 | tee buildsim.log

# Questasim simulation with HDL optimized compilation
questasim-sim-opt: questasim-sim
	$(MAKE) -C build/ceiupm_systems_x_trela_0/sim-modelsim opt

run-app-questasim:
	$(MAKE) app PROJECT=$(PROJECT)
	$(MAKE) -C build/ceiupm_systems_x_trela_0/sim-modelsim run RUN_OPT=1 PLUSARGS="c firmware=../../../sw/build/main.hex"
	cat build/ceiupm_systems_x_trela_0/sim-modelsim/uart0.log

run-gui-app-questasim:
	$(MAKE) app PROJECT=$(PROJECT)
	$(MAKE) -C build/ceiupm_systems_x_trela_0/sim-modelsim run-gui RUN_OPT=1 PLUSARGS="c firmware=../../../sw/build/main.hex"
	cat build/ceiupm_systems_x_trela_0/sim-modelsim/uart0.log

FPGA_BOARD ?= vc709

vivado-fpga: mcu-gen
	$(FUSESOC) --cores-root . run --no-export --target=$(FPGA_BOARD) --flag=use_bscane_xilinx --build ceiupm:systems:x_trela ${FUSESOC_PARAM} 2>&1 | tee buildvivado.log

openocd:
	openocd -f tb/core-v-mini-mcu-vc709-bscan.cfg

gdb:
	$(MAKE) app PROJECT=$(PROJECT) TARGET=pynq-z2
	riscv32-unknown-elf-gdb -x connect_gdb sw/build/main.elf

minicom:
	minicom -b 115200 -D $(DEVICE)

vendor-xheep:
	./util/vendor.py hw/vendor/esl_epfl_x_heep.vendor.hjson -v --update

vendor-strela:
	./util/vendor.py hw/vendor/cei_upm_strela.vendor.hjson -v --update

# Include X-HEEP targets
export HEEP_DIR = hw/vendor/esl_epfl_x_heep/
XHEEP_MAKE = $(HEEP_DIR)/external.mk
include $(XHEEP_MAKE)