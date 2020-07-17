# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/users/malarkins/PMRF-D/master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/users/malarkins/PMRF-D/master

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/users/malarkins/PMRF-D/master/CMakeFiles /home/users/malarkins/PMRF-D/master/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/users/malarkins/PMRF-D/master/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named PMRF-D

# Build rule for target.
PMRF-D: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PMRF-D
.PHONY : PMRF-D

# fast build rule for target.
PMRF-D/fast:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/build
.PHONY : PMRF-D/fast

ICM/ICM.o: ICM/ICM.cpp.o

.PHONY : ICM/ICM.o

# target to build an object file
ICM/ICM.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/ICM/ICM.cpp.o
.PHONY : ICM/ICM.cpp.o

ICM/ICM.i: ICM/ICM.cpp.i

.PHONY : ICM/ICM.i

# target to preprocess a source file
ICM/ICM.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/ICM/ICM.cpp.i
.PHONY : ICM/ICM.cpp.i

ICM/ICM.s: ICM/ICM.cpp.s

.PHONY : ICM/ICM.s

# target to generate assembly for a file
ICM/ICM.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/ICM/ICM.cpp.s
.PHONY : ICM/ICM.cpp.s

Model/AuxMRF.o: Model/AuxMRF.cpp.o

.PHONY : Model/AuxMRF.o

# target to build an object file
Model/AuxMRF.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/AuxMRF.cpp.o
.PHONY : Model/AuxMRF.cpp.o

Model/AuxMRF.i: Model/AuxMRF.cpp.i

.PHONY : Model/AuxMRF.i

# target to preprocess a source file
Model/AuxMRF.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/AuxMRF.cpp.i
.PHONY : Model/AuxMRF.cpp.i

Model/AuxMRF.s: Model/AuxMRF.cpp.s

.PHONY : Model/AuxMRF.s

# target to generate assembly for a file
Model/AuxMRF.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/AuxMRF.cpp.s
.PHONY : Model/AuxMRF.cpp.s

Model/Node.o: Model/Node.cpp.o

.PHONY : Model/Node.o

# target to build an object file
Model/Node.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/Node.cpp.o
.PHONY : Model/Node.cpp.o

Model/Node.i: Model/Node.cpp.i

.PHONY : Model/Node.i

# target to preprocess a source file
Model/Node.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/Node.cpp.i
.PHONY : Model/Node.cpp.i

Model/Node.s: Model/Node.cpp.s

.PHONY : Model/Node.s

# target to generate assembly for a file
Model/Node.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Model/Node.cpp.s
.PHONY : Model/Node.cpp.s

PMRF-D.o: PMRF-D.cpp.o

.PHONY : PMRF-D.o

# target to build an object file
PMRF-D.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/PMRF-D.cpp.o
.PHONY : PMRF-D.cpp.o

PMRF-D.i: PMRF-D.cpp.i

.PHONY : PMRF-D.i

# target to preprocess a source file
PMRF-D.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/PMRF-D.cpp.i
.PHONY : PMRF-D.cpp.i

PMRF-D.s: PMRF-D.cpp.s

.PHONY : PMRF-D.s

# target to generate assembly for a file
PMRF-D.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/PMRF-D.cpp.s
.PHONY : PMRF-D.cpp.s

Utilities/LAP.o: Utilities/LAP.cpp.o

.PHONY : Utilities/LAP.o

# target to build an object file
Utilities/LAP.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/LAP.cpp.o
.PHONY : Utilities/LAP.cpp.o

Utilities/LAP.i: Utilities/LAP.cpp.i

.PHONY : Utilities/LAP.i

# target to preprocess a source file
Utilities/LAP.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/LAP.cpp.i
.PHONY : Utilities/LAP.cpp.i

Utilities/LAP.s: Utilities/LAP.cpp.s

.PHONY : Utilities/LAP.s

# target to generate assembly for a file
Utilities/LAP.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/LAP.cpp.s
.PHONY : Utilities/LAP.cpp.s

Utilities/io.o: Utilities/io.cpp.o

.PHONY : Utilities/io.o

# target to build an object file
Utilities/io.cpp.o:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/io.cpp.o
.PHONY : Utilities/io.cpp.o

Utilities/io.i: Utilities/io.cpp.i

.PHONY : Utilities/io.i

# target to preprocess a source file
Utilities/io.cpp.i:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/io.cpp.i
.PHONY : Utilities/io.cpp.i

Utilities/io.s: Utilities/io.cpp.s

.PHONY : Utilities/io.s

# target to generate assembly for a file
Utilities/io.cpp.s:
	$(MAKE) -f CMakeFiles/PMRF-D.dir/build.make CMakeFiles/PMRF-D.dir/Utilities/io.cpp.s
.PHONY : Utilities/io.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... PMRF-D"
	@echo "... edit_cache"
	@echo "... ICM/ICM.o"
	@echo "... ICM/ICM.i"
	@echo "... ICM/ICM.s"
	@echo "... Model/AuxMRF.o"
	@echo "... Model/AuxMRF.i"
	@echo "... Model/AuxMRF.s"
	@echo "... Model/Node.o"
	@echo "... Model/Node.i"
	@echo "... Model/Node.s"
	@echo "... PMRF-D.o"
	@echo "... PMRF-D.i"
	@echo "... PMRF-D.s"
	@echo "... Utilities/LAP.o"
	@echo "... Utilities/LAP.i"
	@echo "... Utilities/LAP.s"
	@echo "... Utilities/io.o"
	@echo "... Utilities/io.i"
	@echo "... Utilities/io.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

