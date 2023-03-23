# number of IO in the configuration stream for each chain
NUM_IO = 19

# defines these values for IO configurations
C_MGMT_OUT = 0
C_MGMT_IN = 1
C_USER_BIDIR = 2
C_DISABLE = 3
C_ALL_ONES = 4
C_USER_BIDIR_WPU = 5
C_USER_BIDIR_WPD = 6
C_USER_IN_NOPULL = 7
C_USER_OUT = 8

config_h = [
    C_DISABLE,  #37
    C_DISABLE,  #36
    C_DISABLE,  #35
    C_DISABLE,  #34
    C_DISABLE,  #33
    C_DISABLE,  #32
    C_DISABLE,  #31
    C_DISABLE,  #30
    C_DISABLE,  #29
    C_DISABLE,  #28
    C_DISABLE,  #27
    C_DISABLE,  #26
    C_DISABLE,  #25
    C_DISABLE,  #24
    C_DISABLE,  #23
    C_DISABLE,  #22
    C_DISABLE,  #21
    C_DISABLE,  #20
    C_DISABLE,  #19
]

del config_h[NUM_IO:]

config_l = [
    C_DISABLE,   #0
    C_DISABLE,   #1
    C_DISABLE,   #2
    C_DISABLE,   #3
    C_DISABLE,   #4
    C_DISABLE,   #5
    C_DISABLE,   #6
    C_DISABLE,   #7
    C_DISABLE,   #8  RSTN
    C_USER_OUT,   #9  CSN
    C_USER_OUT,   #10 CLK
    C_USER_OUT,   #11 CLKN
    C_DISABLE,   #12
    C_DISABLE,   #13
    C_DISABLE,   #14
    C_DISABLE,   #15
    C_DISABLE,   #16
    C_DISABLE,   #17
    C_DISABLE,   #18
]

del config_l[NUM_IO:]
