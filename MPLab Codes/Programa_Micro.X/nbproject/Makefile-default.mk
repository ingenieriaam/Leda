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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=null
DEBUGGABLE_SUFFIX=null
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=null
DEBUGGABLE_SUFFIX=null
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_overdrive.s src/assembly_ruido.s src/main.c src/assembly_eco.s src/assembly_loopback.s src/assembly_overdrivemediaonda.s src/cero.s src/assembly_flanger.s src/assembly_overdrive2.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s src/assembly_reverb.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c overdrive_num.s overdrive_dem.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_eco.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o ${OBJECTDIR}/src/cero.o ${OBJECTDIR}/src/assembly_flanger.o ${OBJECTDIR}/src/assembly_overdrive2.o ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o ${OBJECTDIR}/src/assembly_reverb.o ${OBJECTDIR}/_ext/864401932/c_overdrive.o ${OBJECTDIR}/overdrive_num.o ${OBJECTDIR}/overdrive_dem.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/adcdacDrv.o.d ${OBJECTDIR}/src/assembly_distorsion.o.d ${OBJECTDIR}/src/assembly_overdrive.o.d ${OBJECTDIR}/src/assembly_ruido.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/assembly_eco.o.d ${OBJECTDIR}/src/assembly_loopback.o.d ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d ${OBJECTDIR}/src/cero.o.d ${OBJECTDIR}/src/assembly_flanger.o.d ${OBJECTDIR}/src/assembly_overdrive2.o.d ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d ${OBJECTDIR}/src/assembly_reverb.o.d ${OBJECTDIR}/_ext/864401932/c_overdrive.o.d ${OBJECTDIR}/overdrive_num.o.d ${OBJECTDIR}/overdrive_dem.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/adcdacDrv.o ${OBJECTDIR}/src/assembly_distorsion.o ${OBJECTDIR}/src/assembly_overdrive.o ${OBJECTDIR}/src/assembly_ruido.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/assembly_eco.o ${OBJECTDIR}/src/assembly_loopback.o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o ${OBJECTDIR}/src/cero.o ${OBJECTDIR}/src/assembly_flanger.o ${OBJECTDIR}/src/assembly_overdrive2.o ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o ${OBJECTDIR}/src/assembly_reverb.o ${OBJECTDIR}/_ext/864401932/c_overdrive.o ${OBJECTDIR}/overdrive_num.o ${OBJECTDIR}/overdrive_dem.o

# Source Files
SOURCEFILES=src/adcdacDrv.c src/assembly_distorsion.s src/assembly_overdrive.s src/assembly_ruido.s src/main.c src/assembly_eco.s src/assembly_loopback.s src/assembly_overdrivemediaonda.s src/cero.s src/assembly_flanger.s src/assembly_overdrive2.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s src/assembly_reverb.s ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c overdrive_num.s overdrive_dem.s


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP802
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/adcdacDrv.o: src/adcdacDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o.d 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adcdacDrv.c  -o ${OBJECTDIR}/src/adcdacDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/adcdacDrv.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/adcdacDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/864401932/c_overdrive.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/c_overdrive.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/c_overdrive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c  -o ${OBJECTDIR}/_ext/864401932/c_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/864401932/c_overdrive.o.d"      -g -D__DEBUG     -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/c_overdrive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/adcdacDrv.o: src/adcdacDrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o.d 
	@${RM} ${OBJECTDIR}/src/adcdacDrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/adcdacDrv.c  -o ${OBJECTDIR}/src/adcdacDrv.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/adcdacDrv.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/adcdacDrv.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/864401932/c_overdrive.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/c_overdrive.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/c_overdrive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/c_overdrive.c  -o ${OBJECTDIR}/_ext/864401932/c_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/864401932/c_overdrive.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/c_overdrive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	
${OBJECTDIR}/src/assembly_overdrive.o: src/assembly_overdrive.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive.s  -o ${OBJECTDIR}/src/assembly_overdrive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_ruido.o: src/assembly_ruido.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_ruido.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_ruido.s  -o ${OBJECTDIR}/src/assembly_ruido.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_ruido.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_ruido.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
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
	
${OBJECTDIR}/src/assembly_overdrivemediaonda.o: src/assembly_overdrivemediaonda.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrivemediaonda.s  -o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/cero.o: src/cero.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cero.o.d 
	@${RM} ${OBJECTDIR}/src/cero.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/cero.s  -o ${OBJECTDIR}/src/cero.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/cero.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/cero.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger.o: src/assembly_flanger.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger.s  -o ${OBJECTDIR}/src/assembly_flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive2.o: src/assembly_overdrive2.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive2.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive2.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive2.s  -o ${OBJECTDIR}/src/assembly_overdrive2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive2.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive2.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s  -o ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s  -o ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_reverb.o: src/assembly_reverb.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_reverb.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_reverb.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_reverb.s  -o ${OBJECTDIR}/src/assembly_reverb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_reverb.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_reverb.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/overdrive_num.o: overdrive_num.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/overdrive_num.o.d 
	@${RM} ${OBJECTDIR}/overdrive_num.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  overdrive_num.s  -o ${OBJECTDIR}/overdrive_num.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/overdrive_num.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/overdrive_num.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/overdrive_dem.o: overdrive_dem.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/overdrive_dem.o.d 
	@${RM} ${OBJECTDIR}/overdrive_dem.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  overdrive_dem.s  -o ${OBJECTDIR}/overdrive_dem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG   -omf=elf -Wa,-MD,"${OBJECTDIR}/overdrive_dem.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/overdrive_dem.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
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
	
${OBJECTDIR}/src/assembly_overdrivemediaonda.o: src/assembly_overdrivemediaonda.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrivemediaonda.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrivemediaonda.s  -o ${OBJECTDIR}/src/assembly_overdrivemediaonda.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrivemediaonda.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/cero.o: src/cero.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/cero.o.d 
	@${RM} ${OBJECTDIR}/src/cero.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/cero.s  -o ${OBJECTDIR}/src/cero.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/cero.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/cero.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_flanger.o: src/assembly_flanger.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_flanger.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_flanger.s  -o ${OBJECTDIR}/src/assembly_flanger.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_flanger.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_flanger.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_overdrive2.o: src/assembly_overdrive2.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive2.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_overdrive2.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_overdrive2.s  -o ${OBJECTDIR}/src/assembly_overdrive2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_overdrive2.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_overdrive2.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_eco_xdata.s  -o ${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/assembly_eco_xdata.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o: ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/864401932 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d 
	@${RM} ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../UTN/DPlab/04-11-14/Programa_Micro.X/src/assembly_xdata_init_BitReversed.s  -o ${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/864401932/assembly_xdata_init_BitReversed.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/assembly_reverb.o: src/assembly_reverb.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/assembly_reverb.o.d 
	@${RM} ${OBJECTDIR}/src/assembly_reverb.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/assembly_reverb.s  -o ${OBJECTDIR}/src/assembly_reverb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/src/assembly_reverb.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/src/assembly_reverb.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/overdrive_num.o: overdrive_num.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/overdrive_num.o.d 
	@${RM} ${OBJECTDIR}/overdrive_num.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  overdrive_num.s  -o ${OBJECTDIR}/overdrive_num.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/overdrive_num.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/overdrive_num.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/overdrive_dem.o: overdrive_dem.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/overdrive_dem.o.d 
	@${RM} ${OBJECTDIR}/overdrive_dem.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  overdrive_dem.s  -o ${OBJECTDIR}/overdrive_dem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -Wa,-MD,"${OBJECTDIR}/overdrive_dem.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/overdrive_dem.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf     -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Programa_Micro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
