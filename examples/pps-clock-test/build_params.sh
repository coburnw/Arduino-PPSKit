## build_params.sh
#
# Sketch Build parameters
#    imported by ~/bin/build.sh
#
BASEPATH="/home/pi/Arduino/pps"
PROJECT="pps-clock-test"
SKETCH="$PROJECT.ino"
VERSION_PREFIX="$PROJECT"

CLEAN=""
#CLEAN="--clean"

COMPILE_OPTIONS="--build-property build.extra_flags=-DGT_HW_VER=0"
SKETCH_OPTIONS="$COMPILE_OPTIONS --libraries=$BASEPATH/libraries $CLEAN"

# both board and chip must match. Verify fuses on change.
BOARD="--fqbn DxCore:megaavr:avrdb"
CHIP="avr128db32"

CORE_OPTIONS="chip=$CHIP,millis=tcb2,printf=default,attach=allenabled,wiremode=mors,appspm=no"
FUSE_OPTIONS="clock=24internal,bodvoltage=1v9,bodmode=enabled,resetpin=input,mvio=enabled,startuptime=8,eesave=enable"

## FUSES
#
# Consider selections carefully, double check values.
#   for instance: Fuse_5=0xC1 on db32 is safe, yet disables updi on dd32.  Yikes!
#
# the FUSE_OPTIONS above are only to inform the core of your intentions and have no
#   influence on the values below
#
# AVR64DB32 Fuses        #Register #default #description
#FUSE_0="--fuses 0:0x00"  #WDTCFG   #0x00    # watchdog and watchdog-window timeout value
#FUSE_1="--fuses 1:0x04"  #BODCFG   #0x00    # 1.9V, continuous active mode only
#FUSE_2="--fuses 2:0x00"  #OSCCFG   #0x00    # internal hf osc
FUSE_5="--fuses 5:0xC9"  #SYSCFG0  #0xC0    # 0xC9 = NOCRC, RESET_PIN, retain eeprom
#FUSE_6="--fuses 6:0x1C"  #SYSCFG1  #0x08    # 0x1C = MVIO off, 8ms startup 
#FUSE_7="--fuses 7:0x00"  #CODESIZE #0x00    # Code section size
#FUSE_8="--fuses 8:0x00"  #BOOTSIZE #0x00    # Boot section size (0=all)

# AVR64DD32 Fuses        #Register #default #description
#FUSE_0="--fuses 0:0x00"  #WDTCFG   #0x00    # watchdog window:period timeout value
#FUSE_1="--fuses 1:0x04"  #BODCFG   #0x00    # 1.9V, continuous active mode only
#FUSE_2="--fuses 2:0x00"  #OSCCFG   #0x00    # internal hf osc
#FUSE_5="--fuses 5:0xD9"  #SYSCFG0  #0xD0    # 0xD9 = NOCRC, UPDI_PIN, RESET_PIN, retain eeprom
#FUSE_6="--fuses 6:0x0C"  #SYSCFG1  #0x08    # 0x0C = MVIO on, 8ms startup 
#FUSE_7="--fuses 7:0x00"  #CODESIZE #0x00    # Code section size
#FUSE_8="--fuses 8:0x00"  #BOOTSIZE #0x00    # Boot section size (0=all)
