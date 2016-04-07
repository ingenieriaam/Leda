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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_eco.s src/assembly_loopback.s src/assembly_overdrive.s src/assembly_overdrivemediaonda.s src/assembly_ruido.s src/cero.s src/main.c src/assembly_xdata_init.s src/assembly_eco_xdata.s src/assembly_xdata_init_BitReversed.s src/assembly_puertaruido.s src/SPIDrv.c src/assembly_vibrato.s src/assembly_loadsine.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_eco.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/cero.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_xdata_init.o ${OBJECTDIR}/src/assembly_eco_xdata.o ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o ${OBJECTDIR}/src/assembly_puertaruido.o ${OBJECTDIR}/src/SPIDrv.o ${OBJECTDIR}/src/assembly_vibrato.o ${OBJECTDIR}/src/assembly_loadsine.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/adcdacDrv.o.d ${OBJECTDIR}/src/assembly_distorsion.o.d ${OBJECTDIR}/src/assembly_eco.o.d ${OBJECTDIR}/src/assembly_loopback.o.d ${OBJECTDIR}/src/assembly_overdrive.o.d ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d ${OBJECTDIR}/src/assembly_ruido.o.d ${OBJECTDIR}/src/cero.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/assembly_xdata_init.o.d ${OBJECTDIR}/src/assembly_eco_xdata.o.d ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d ${OBJECTDIR}/src/assembly_puertaruido.o.d ${OBJECTDIR}/src/SPIDrv.o.d ${OBJECTDIR}/src/assembly_vibrato.o.d ${OBJECTDIR}/src/assembly_loadsine.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_eco.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/cero.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_xdata_init.o ${OBJECTDIR}/src/assembly_eco_xdata.o ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o ${OBJECTDIR}/src/assembly_puertaruido.o ${OBJECTDIR}/src/SPIDrv.o ${OBJECTDIR}/src/assembly_vibrato.o ${OBJECTDIR}/src/assembly_loadsine.o

# Source Files
SOURCEFILES=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_eco.s src/assembly_loopback.s src/assembly_overdrive.s src/assembly_overdrivemediaonda.s src/assembly_ruido.s src/cero.s src/main.c src/assembly_xdata_init.s src/assembly_eco_xdata.s src/assembly_xdata_init_BitReversed.s src/assembly_puertaruido.s src/SPIDrv.c src/assembly_vibrato.s src/assembly_loadsine.s


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP802
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/adcdacDrv.o: src/adcdacDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o.d 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adcdacDrv.c  -o ${OBJECTDIR}/src/adcdacDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/adcdacDrv.o.d"      -g -D__DEBUG   -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/adcdacDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG   -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SPIDrv.o: src/SPIDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/SPIDrv.o.d 
	@${RM} ${OBJECTDIR}/src/SPIDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SPIDrv.c  -o ${OBJECTDIR}/src/SPIDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SPIDrv.o.d"      -g -D__DEBUG   -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/SPIDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/adcdacDrv.o: src/adcdacDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o.d 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adcdacDrv.c  -o ${OBJECTDIR}/src/adcdacDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/adcdacDrv.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/adcdacDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/SPIDrv.o: src/SPIDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/SPIDrv.o.d 
	@${RM} ${OBJECTDIR}/src/SPIDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/SPIDrv.c  -o ${OBJECTDIR}/src/SPIDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/SPIDrv.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/SPIDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/assembly_distorsion.o: src/assembly_distorsion.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_distorsion.s  -o ${OBJECTDIR}/src/assembly_distorsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_distorsion.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_distorsion.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_eco.o: src/assembly_eco.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_eco.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_eco.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_eco.s  -o ${OBJECTDIR}/src/assembly_eco.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_eco.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_eco.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loopback.o: src/assembly_loopback.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loopback.s  -o ${OBJECTDIR}/src/assembly_loopback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loopback.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loopback.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive.o: src/assembly_overdrive.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive.s  -o ${OBJECTDIR}/src/assembly_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrivemediaonda.o: src/assembly_overdrivemediaonda.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrivemediaonda.s  -o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_ruido.o: src/assembly_ruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_ruido.s  -o ${OBJECTDIR}/src/assembly_ruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_ruido.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_ruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/cero.o: src/cero.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cero.o.d 
	@${RM} ${OBJECTDIR}/src/cero.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/cero.s  -o ${OBJECTDIR}/src/cero.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/cero.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/cero.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_xdata_init.o: src/assembly_xdata_init.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_xdata_init.s  -o ${OBJECTDIR}/src/assembly_xdata_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_xdata_init.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_xdata_init.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_eco_xdata.o: src/assembly_eco_xdata.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_eco_xdata.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_eco_xdata.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_eco_xdata.s  -o ${OBJECTDIR}/src/assembly_eco_xdata.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_eco_xdata.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_eco_xdata.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o: src/assembly_xdata_init_BitReversed.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_xdata_init_BitReversed.s  -o ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_puertaruido.o: src/assembly_puertaruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_puertaruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_puertaruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_puertaruido.s  -o ${OBJECTDIR}/src/assembly_puertaruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_puertaruido.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_puertaruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_vibrato.o: src/assembly_vibrato.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_vibrato.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_vibrato.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_vibrato.s  -o ${OBJECTDIR}/src/assembly_vibrato.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_vibrato.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_vibrato.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loadsine.o: src/assembly_loadsine.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loadsine.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loadsine.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loadsine.s  -o ${OBJECTDIR}/src/assembly_loadsine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loadsine.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loadsine.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/assembly_distorsion.o: src/assembly_distorsion.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_distorsion.s  -o ${OBJECTDIR}/src/assembly_distorsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_distorsion.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_distorsion.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_eco.o: src/assembly_eco.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_eco.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_eco.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_eco.s  -o ${OBJECTDIR}/src/assembly_eco.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_eco.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_eco.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loopback.o: src/assembly_loopback.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loopback.s  -o ${OBJECTDIR}/src/assembly_loopback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loopback.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loopback.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive.o: src/assembly_overdrive.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive.s  -o ${OBJECTDIR}/src/assembly_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrivemediaonda.o: src/assembly_overdrivemediaonda.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrivemediaonda.s  -o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_ruido.o: src/assembly_ruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_ruido.s  -o ${OBJECTDIR}/src/assembly_ruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_ruido.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_ruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/cero.o: src/cero.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cero.o.d 
	@${RM} ${OBJECTDIR}/src/cero.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/cero.s  -o ${OBJECTDIR}/src/cero.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/cero.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/cero.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_xdata_init.o: src/assembly_xdata_init.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_xdata_init.s  -o ${OBJECTDIR}/src/assembly_xdata_init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_xdata_init.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_xdata_init.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_eco_xdata.o: src/assembly_eco_xdata.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_eco_xdata.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_eco_xdata.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_eco_xdata.s  -o ${OBJECTDIR}/src/assembly_eco_xdata.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_eco_xdata.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_eco_xdata.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o: src/assembly_xdata_init_BitReversed.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_xdata_init_BitReversed.s  -o ${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_xdata_init_BitReversed.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_puertaruido.o: src/assembly_puertaruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_puertaruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_puertaruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_puertaruido.s  -o ${OBJECTDIR}/src/assembly_puertaruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_puertaruido.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_puertaruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_vibrato.o: src/assembly_vibrato.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_vibrato.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_vibrato.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_vibrato.s  -o ${OBJECTDIR}/src/assembly_vibrato.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_vibrato.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_vibrato.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loadsine.o: src/assembly_loadsine.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loadsine.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loadsine.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loadsine.s  -o ${OBJECTDIR}/src/assembly_loadsine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loadsine.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loadsine.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
