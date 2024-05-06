
CUSTOM_MATRIX = lite

# # project specific files
SRC += matrix.c
QUANTUM_LIB_SRC += uart.c

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
