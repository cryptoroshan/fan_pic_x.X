#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Config_2.mk)" "nbproject/Makefile-local-Config_2.mk"
include nbproject/Makefile-local-Config_2.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Config_2
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../framework/usb/src/usb_device.c ../framework/usb/src/usb_device_cdc.c src/main.c src/fan_config.c src/fan_data.c src/eeprom.c src/usb_descriptors.c src/usb_events.c src/sensors.c src/utils.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2142726457/usb_device.p1 ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 ${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/fan_config.p1 ${OBJECTDIR}/src/fan_data.p1 ${OBJECTDIR}/src/eeprom.p1 ${OBJECTDIR}/src/usb_descriptors.p1 ${OBJECTDIR}/src/usb_events.p1 ${OBJECTDIR}/src/sensors.p1 ${OBJECTDIR}/src/utils.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2142726457/usb_device.p1.d ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d ${OBJECTDIR}/src/main.p1.d ${OBJECTDIR}/src/fan_config.p1.d ${OBJECTDIR}/src/fan_data.p1.d ${OBJECTDIR}/src/eeprom.p1.d ${OBJECTDIR}/src/usb_descriptors.p1.d ${OBJECTDIR}/src/usb_events.p1.d ${OBJECTDIR}/src/sensors.p1.d ${OBJECTDIR}/src/utils.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2142726457/usb_device.p1 ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 ${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/fan_config.p1 ${OBJECTDIR}/src/fan_data.p1 ${OBJECTDIR}/src/eeprom.p1 ${OBJECTDIR}/src/usb_descriptors.p1 ${OBJECTDIR}/src/usb_events.p1 ${OBJECTDIR}/src/sensors.p1 ${OBJECTDIR}/src/utils.p1

# Source Files
SOURCEFILES=../framework/usb/src/usb_device.c ../framework/usb/src/usb_device_cdc.c src/main.c src/fan_config.c src/fan_data.c src/eeprom.c src/usb_descriptors.c src/usb_events.c src/sensors.c src/utils.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Config_2.mk ${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2550
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2142726457/usb_device.p1: ../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2142726457/usb_device.p1 ../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device.d ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1: ../framework/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 ../framework/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.d ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/fan_config.p1: src/fan_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fan_config.p1.d 
	@${RM} ${OBJECTDIR}/src/fan_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/fan_config.p1 src/fan_config.c 
	@-${MV} ${OBJECTDIR}/src/fan_config.d ${OBJECTDIR}/src/fan_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/fan_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/fan_data.p1: src/fan_data.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fan_data.p1.d 
	@${RM} ${OBJECTDIR}/src/fan_data.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/fan_data.p1 src/fan_data.c 
	@-${MV} ${OBJECTDIR}/src/fan_data.d ${OBJECTDIR}/src/fan_data.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/fan_data.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eeprom.p1: src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/eeprom.p1 src/eeprom.c 
	@-${MV} ${OBJECTDIR}/src/eeprom.d ${OBJECTDIR}/src/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_descriptors.p1: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/usb_descriptors.p1 src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/src/usb_descriptors.d ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_events.p1: src/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/usb_events.p1 src/usb_events.c 
	@-${MV} ${OBJECTDIR}/src/usb_events.d ${OBJECTDIR}/src/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/sensors.p1: src/sensors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sensors.p1.d 
	@${RM} ${OBJECTDIR}/src/sensors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/sensors.p1 src/sensors.c 
	@-${MV} ${OBJECTDIR}/src/sensors.d ${OBJECTDIR}/src/sensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/sensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/utils.p1: src/utils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/utils.p1.d 
	@${RM} ${OBJECTDIR}/src/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/utils.p1 src/utils.c 
	@-${MV} ${OBJECTDIR}/src/utils.d ${OBJECTDIR}/src/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/2142726457/usb_device.p1: ../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2142726457/usb_device.p1 ../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device.d ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1: ../framework/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/_ext/2142726457" 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1 ../framework/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.d ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2142726457/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/fan_config.p1: src/fan_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fan_config.p1.d 
	@${RM} ${OBJECTDIR}/src/fan_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/fan_config.p1 src/fan_config.c 
	@-${MV} ${OBJECTDIR}/src/fan_config.d ${OBJECTDIR}/src/fan_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/fan_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/fan_data.p1: src/fan_data.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fan_data.p1.d 
	@${RM} ${OBJECTDIR}/src/fan_data.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/fan_data.p1 src/fan_data.c 
	@-${MV} ${OBJECTDIR}/src/fan_data.d ${OBJECTDIR}/src/fan_data.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/fan_data.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/eeprom.p1: src/eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/eeprom.p1 src/eeprom.c 
	@-${MV} ${OBJECTDIR}/src/eeprom.d ${OBJECTDIR}/src/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_descriptors.p1: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/usb_descriptors.p1 src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/src/usb_descriptors.d ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_events.p1: src/usb_events.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_events.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_events.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/usb_events.p1 src/usb_events.c 
	@-${MV} ${OBJECTDIR}/src/usb_events.d ${OBJECTDIR}/src/usb_events.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_events.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/sensors.p1: src/sensors.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sensors.p1.d 
	@${RM} ${OBJECTDIR}/src/sensors.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/sensors.p1 src/sensors.c 
	@-${MV} ${OBJECTDIR}/src/sensors.d ${OBJECTDIR}/src/sensors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/sensors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/utils.p1: src/utils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/utils.p1.d 
	@${RM} ${OBJECTDIR}/src/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -DXPRJ_Config_2=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/utils.p1 src/utils.c 
	@-${MV} ${OBJECTDIR}/src/utils.d ${OBJECTDIR}/src/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_Config_2=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     -mrom=default,-7dc0-7fff -mram=default,-3f4-3ff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.map  -DXPRJ_Config_2=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -Dself_power=1 -xassembler-with-cpp -I"include" -I"../framework/usb/inc" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file -mcodeoffset=0x1000  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c90 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/fan_pic_x.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
