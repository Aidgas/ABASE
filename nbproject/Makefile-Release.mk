#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/include/ah_api.o \
	${OBJECTDIR}/include/ah_api_common.o \
	${OBJECTDIR}/include/ah_page.o \
	${OBJECTDIR}/include/cparser/builtin-features.o \
	${OBJECTDIR}/include/cparser/containers.o \
	${OBJECTDIR}/include/cparser/functions.o \
	${OBJECTDIR}/include/cparser/packToken.o \
	${OBJECTDIR}/include/cparser/shunting-yard.o \
	${OBJECTDIR}/include/database.o \
	${OBJECTDIR}/include/jspy/cparse-custom.o \
	${OBJECTDIR}/include/jspy/global-setup.o \
	${OBJECTDIR}/include/jspy/matcher.o \
	${OBJECTDIR}/include/jspy/pattern.o \
	${OBJECTDIR}/include/jspy/range.o \
	${OBJECTDIR}/include/jspy/statements.o \
	${OBJECTDIR}/include/nrex/nrex.o \
	${OBJECTDIR}/include/utils/buf.o \
	${OBJECTDIR}/include/utils/lock.o \
	${OBJECTDIR}/include/utils/simple_tpl.o \
	${OBJECTDIR}/include/utils/util_filesys.o \
	${OBJECTDIR}/include/utils/util_string.o \
	${OBJECTDIR}/include/utils/utils.o \
	${OBJECTDIR}/include/utils/void_array.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/abase_2021

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/abase_2021: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/abase_2021 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/include/ah_api.o: include/ah_api.cpp
	${MKDIR} -p ${OBJECTDIR}/include
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/ah_api.o include/ah_api.cpp

${OBJECTDIR}/include/ah_api_common.o: include/ah_api_common.cpp
	${MKDIR} -p ${OBJECTDIR}/include
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/ah_api_common.o include/ah_api_common.cpp

${OBJECTDIR}/include/ah_page.o: include/ah_page.cpp
	${MKDIR} -p ${OBJECTDIR}/include
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/ah_page.o include/ah_page.cpp

${OBJECTDIR}/include/cparser/builtin-features.o: include/cparser/builtin-features.cpp
	${MKDIR} -p ${OBJECTDIR}/include/cparser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/cparser/builtin-features.o include/cparser/builtin-features.cpp

${OBJECTDIR}/include/cparser/containers.o: include/cparser/containers.cpp
	${MKDIR} -p ${OBJECTDIR}/include/cparser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/cparser/containers.o include/cparser/containers.cpp

${OBJECTDIR}/include/cparser/functions.o: include/cparser/functions.cpp
	${MKDIR} -p ${OBJECTDIR}/include/cparser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/cparser/functions.o include/cparser/functions.cpp

${OBJECTDIR}/include/cparser/packToken.o: include/cparser/packToken.cpp
	${MKDIR} -p ${OBJECTDIR}/include/cparser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/cparser/packToken.o include/cparser/packToken.cpp

${OBJECTDIR}/include/cparser/shunting-yard.o: include/cparser/shunting-yard.cpp
	${MKDIR} -p ${OBJECTDIR}/include/cparser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/cparser/shunting-yard.o include/cparser/shunting-yard.cpp

${OBJECTDIR}/include/database.o: include/database.cpp
	${MKDIR} -p ${OBJECTDIR}/include
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/database.o include/database.cpp

${OBJECTDIR}/include/jspy/cparse-custom.o: include/jspy/cparse-custom.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/cparse-custom.o include/jspy/cparse-custom.cpp

${OBJECTDIR}/include/jspy/global-setup.o: include/jspy/global-setup.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/global-setup.o include/jspy/global-setup.cpp

${OBJECTDIR}/include/jspy/matcher.o: include/jspy/matcher.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/matcher.o include/jspy/matcher.cpp

${OBJECTDIR}/include/jspy/pattern.o: include/jspy/pattern.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/pattern.o include/jspy/pattern.cpp

${OBJECTDIR}/include/jspy/range.o: include/jspy/range.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/range.o include/jspy/range.cpp

${OBJECTDIR}/include/jspy/statements.o: include/jspy/statements.cpp
	${MKDIR} -p ${OBJECTDIR}/include/jspy
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/jspy/statements.o include/jspy/statements.cpp

${OBJECTDIR}/include/nrex/nrex.o: include/nrex/nrex.cpp
	${MKDIR} -p ${OBJECTDIR}/include/nrex
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/nrex/nrex.o include/nrex/nrex.cpp

${OBJECTDIR}/include/utils/buf.o: include/utils/buf.c
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/buf.o include/utils/buf.c

${OBJECTDIR}/include/utils/lock.o: include/utils/lock.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/lock.o include/utils/lock.cpp

${OBJECTDIR}/include/utils/simple_tpl.o: include/utils/simple_tpl.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/simple_tpl.o include/utils/simple_tpl.cpp

${OBJECTDIR}/include/utils/util_filesys.o: include/utils/util_filesys.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/util_filesys.o include/utils/util_filesys.cpp

${OBJECTDIR}/include/utils/util_string.o: include/utils/util_string.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/util_string.o include/utils/util_string.cpp

${OBJECTDIR}/include/utils/utils.o: include/utils/utils.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/utils.o include/utils/utils.cpp

${OBJECTDIR}/include/utils/void_array.o: include/utils/void_array.cpp
	${MKDIR} -p ${OBJECTDIR}/include/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/include/utils/void_array.o include/utils/void_array.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
