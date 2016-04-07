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
SOURCEFILES_QUOTED_IF_SPACED=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_overdrive.s src/assembly_ruido.s src/main.c src/assembly_flanger.s src/assembly_delaylineinit.s src/assembly_flanger_triang.s src/assembly_loopback.s src/twiddleFactors.c src/assembly_complex_in.s src/assembly_complex_out.s src/assembly_fft_test.s src/assembly_manual_reverse.s src/twiddleFactors_real.c src/Flanger.c src/funciones_pre_assembler.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_flanger.o ${OBJECTDIR}/src/assembly_delaylineinit.o ${OBJECTDIR}/src/assembly_flanger_triang.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/twiddleFactors.o ${OBJECTDIR}/src/assembly_complex_in.o ${OBJECTDIR}/src/assembly_complex_out.o ${OBJECTDIR}/src/assembly_fft_test.o ${OBJECTDIR}/src/assembly_manual_reverse.o ${OBJECTDIR}/src/twiddleFactors_real.o ${OBJECTDIR}/src/Flanger.o ${OBJECTDIR}/src/funciones_pre_assembler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/adcdacDrv.o.d ${OBJECTDIR}/src/assembly_distorsion.o.d ${OBJECTDIR}/src/assembly_overdrive.o.d ${OBJECTDIR}/src/assembly_ruido.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/assembly_flanger.o.d ${OBJECTDIR}/src/assembly_delaylineinit.o.d ${OBJECTDIR}/src/assembly_flanger_triang.o.d ${OBJECTDIR}/src/assembly_loopback.o.d ${OBJECTDIR}/src/twiddleFactors.o.d ${OBJECTDIR}/src/assembly_complex_in.o.d ${OBJECTDIR}/src/assembly_complex_out.o.d ${OBJECTDIR}/src/assembly_fft_test.o.d ${OBJECTDIR}/src/assembly_manual_reverse.o.d ${OBJECTDIR}/src/twiddleFactors_real.o.d ${OBJECTDIR}/src/Flanger.o.d ${OBJECTDIR}/src/funciones_pre_assembler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_flanger.o ${OBJECTDIR}/src/assembly_delaylineinit.o ${OBJECTDIR}/src/assembly_flanger_triang.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/twiddleFactors.o ${OBJECTDIR}/src/assembly_complex_in.o ${OBJECTDIR}/src/assembly_complex_out.o ${OBJECTDIR}/src/assembly_fft_test.o ${OBJECTDIR}/src/assembly_manual_reverse.o ${OBJECTDIR}/src/twiddleFactors_real.o ${OBJECTDIR}/src/Flanger.o ${OBJECTDIR}/src/funciones_pre_assembler.o

# Source Files
SOURCEFILES=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_overdrive.s src/assembly_ruido.s src/main.c src/assembly_flanger.s src/assembly_delaylineinit.s src/assembly_flanger_triang.s src/assembly_loopback.s src/twiddleFactors.c src/assembly_complex_in.s src/assembly_complex_out.s src/assembly_fft_test.s src/assembly_manual_reverse.s src/twiddleFactors_real.c src/Flanger.c src/funciones_pre_assembler.c


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
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adcdacDrv.c  -o ${OBJECTDIR}/src/adcdacDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/adcdacDrv.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/adcdacDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/twiddleFactors.o: src/twiddleFactors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/twiddleFactors.o.d 
	@${RM} ${OBJECTDIR}/src/twiddleFactors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/twiddleFactors.c  -o ${OBJECTDIR}/src/twiddleFactors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/twiddleFactors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/twiddleFactors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/twiddleFactors_real.o: src/twiddleFactors_real.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/twiddleFactors_real.o.d 
	@${RM} ${OBJECTDIR}/src/twiddleFactors_real.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/twiddleFactors_real.c  -o ${OBJECTDIR}/src/twiddleFactors_real.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/twiddleFactors_real.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/twiddleFactors_real.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Flanger.o: src/Flanger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Flanger.o.d 
	@${RM} ${OBJECTDIR}/src/Flanger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Flanger.c  -o ${OBJECTDIR}/src/Flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Flanger.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/Flanger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/funciones_pre_assembler.o: src/funciones_pre_assembler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/funciones_pre_assembler.o.d 
	@${RM} ${OBJECTDIR}/src/funciones_pre_assembler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/funciones_pre_assembler.c  -o ${OBJECTDIR}/src/funciones_pre_assembler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/funciones_pre_assembler.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/funciones_pre_assembler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	
${OBJECTDIR}/src/twiddleFactors.o: src/twiddleFactors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/twiddleFactors.o.d 
	@${RM} ${OBJECTDIR}/src/twiddleFactors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/twiddleFactors.c  -o ${OBJECTDIR}/src/twiddleFactors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/twiddleFactors.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/twiddleFactors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/twiddleFactors_real.o: src/twiddleFactors_real.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/twiddleFactors_real.o.d 
	@${RM} ${OBJECTDIR}/src/twiddleFactors_real.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/twiddleFactors_real.c  -o ${OBJECTDIR}/src/twiddleFactors_real.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/twiddleFactors_real.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/twiddleFactors_real.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/Flanger.o: src/Flanger.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/Flanger.o.d 
	@${RM} ${OBJECTDIR}/src/Flanger.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/Flanger.c  -o ${OBJECTDIR}/src/Flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/Flanger.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/Flanger.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/funciones_pre_assembler.o: src/funciones_pre_assembler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/funciones_pre_assembler.o.d 
	@${RM} ${OBJECTDIR}/src/funciones_pre_assembler.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/funciones_pre_assembler.c  -o ${OBJECTDIR}/src/funciones_pre_assembler.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/funciones_pre_assembler.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/funciones_pre_assembler.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/assembly_distorsion.o: src/assembly_distorsion.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_distorsion.s  -o ${OBJECTDIR}/src/assembly_distorsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_distorsion.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_distorsion.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive.o: src/assembly_overdrive.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive.s  -o ${OBJECTDIR}/src/assembly_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_ruido.o: src/assembly_ruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_ruido.s  -o ${OBJECTDIR}/src/assembly_ruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_ruido.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_ruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger.o: src/assembly_flanger.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger.s  -o ${OBJECTDIR}/src/assembly_flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_delaylineinit.o: src/assembly_delaylineinit.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_delaylineinit.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_delaylineinit.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_delaylineinit.s  -o ${OBJECTDIR}/src/assembly_delaylineinit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_delaylineinit.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_delaylineinit.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger_triang.o: src/assembly_flanger_triang.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger_triang.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger_triang.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger_triang.s  -o ${OBJECTDIR}/src/assembly_flanger_triang.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger_triang.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger_triang.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loopback.o: src/assembly_loopback.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loopback.s  -o ${OBJECTDIR}/src/assembly_loopback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loopback.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loopback.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_complex_in.o: src/assembly_complex_in.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_complex_in.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_complex_in.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_complex_in.s  -o ${OBJECTDIR}/src/assembly_complex_in.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_complex_in.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_complex_in.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_complex_out.o: src/assembly_complex_out.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_complex_out.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_complex_out.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_complex_out.s  -o ${OBJECTDIR}/src/assembly_complex_out.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_complex_out.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_complex_out.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_fft_test.o: src/assembly_fft_test.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_fft_test.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_fft_test.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_fft_test.s  -o ${OBJECTDIR}/src/assembly_fft_test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_fft_test.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_fft_test.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_manual_reverse.o: src/assembly_manual_reverse.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_manual_reverse.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_manual_reverse.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_manual_reverse.s  -o ${OBJECTDIR}/src/assembly_manual_reverse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_manual_reverse.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_manual_reverse.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/assembly_distorsion.o: src/assembly_distorsion.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_distorsion.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_distorsion.s  -o ${OBJECTDIR}/src/assembly_distorsion.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_distorsion.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_distorsion.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive.o: src/assembly_overdrive.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive.s  -o ${OBJECTDIR}/src/assembly_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_ruido.o: src/assembly_ruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_ruido.s  -o ${OBJECTDIR}/src/assembly_ruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_ruido.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_ruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger.o: src/assembly_flanger.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger.s  -o ${OBJECTDIR}/src/assembly_flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_delaylineinit.o: src/assembly_delaylineinit.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_delaylineinit.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_delaylineinit.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_delaylineinit.s  -o ${OBJECTDIR}/src/assembly_delaylineinit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_delaylineinit.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_delaylineinit.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger_triang.o: src/assembly_flanger_triang.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger_triang.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger_triang.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger_triang.s  -o ${OBJECTDIR}/src/assembly_flanger_triang.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger_triang.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger_triang.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_loopback.o: src/assembly_loopback.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_loopback.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_loopback.s  -o ${OBJECTDIR}/src/assembly_loopback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_loopback.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_loopback.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_complex_in.o: src/assembly_complex_in.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_complex_in.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_complex_in.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_complex_in.s  -o ${OBJECTDIR}/src/assembly_complex_in.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_complex_in.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_complex_in.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_complex_out.o: src/assembly_complex_out.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_complex_out.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_complex_out.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_complex_out.s  -o ${OBJECTDIR}/src/assembly_complex_out.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_complex_out.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_complex_out.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_fft_test.o: src/assembly_fft_test.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_fft_test.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_fft_test.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_fft_test.s  -o ${OBJECTDIR}/src/assembly_fft_test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_fft_test.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_fft_test.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_manual_reverse.o: src/assembly_manual_reverse.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_manual_reverse.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_manual_reverse.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_manual_reverse.s  -o ${OBJECTDIR}/src/assembly_manual_reverse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_manual_reverse.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_manual_reverse.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
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
