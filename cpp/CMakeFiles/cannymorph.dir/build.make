# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/calvin/cvproject/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/calvin/cvproject/cpp

# Include any dependencies generated for this target.
include CMakeFiles/cannymorph.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cannymorph.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cannymorph.dir/flags.make

CMakeFiles/cannymorph.dir/cannymorph.cpp.o: CMakeFiles/cannymorph.dir/flags.make
CMakeFiles/cannymorph.dir/cannymorph.cpp.o: cannymorph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calvin/cvproject/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cannymorph.dir/cannymorph.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cannymorph.dir/cannymorph.cpp.o -c /home/calvin/cvproject/cpp/cannymorph.cpp

CMakeFiles/cannymorph.dir/cannymorph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cannymorph.dir/cannymorph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/calvin/cvproject/cpp/cannymorph.cpp > CMakeFiles/cannymorph.dir/cannymorph.cpp.i

CMakeFiles/cannymorph.dir/cannymorph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cannymorph.dir/cannymorph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/calvin/cvproject/cpp/cannymorph.cpp -o CMakeFiles/cannymorph.dir/cannymorph.cpp.s

CMakeFiles/cannymorph.dir/cannymorph.cpp.o.requires:

.PHONY : CMakeFiles/cannymorph.dir/cannymorph.cpp.o.requires

CMakeFiles/cannymorph.dir/cannymorph.cpp.o.provides: CMakeFiles/cannymorph.dir/cannymorph.cpp.o.requires
	$(MAKE) -f CMakeFiles/cannymorph.dir/build.make CMakeFiles/cannymorph.dir/cannymorph.cpp.o.provides.build
.PHONY : CMakeFiles/cannymorph.dir/cannymorph.cpp.o.provides

CMakeFiles/cannymorph.dir/cannymorph.cpp.o.provides.build: CMakeFiles/cannymorph.dir/cannymorph.cpp.o


# Object files for target cannymorph
cannymorph_OBJECTS = \
"CMakeFiles/cannymorph.dir/cannymorph.cpp.o"

# External object files for target cannymorph
cannymorph_EXTERNAL_OBJECTS =

cannymorph: CMakeFiles/cannymorph.dir/cannymorph.cpp.o
cannymorph: CMakeFiles/cannymorph.dir/build.make
cannymorph: /usr/local/lib/libopencv_dnn.so.4.0.0
cannymorph: /usr/local/lib/libopencv_ml.so.4.0.0
cannymorph: /usr/local/lib/libopencv_objdetect.so.4.0.0
cannymorph: /usr/local/lib/libopencv_shape.so.4.0.0
cannymorph: /usr/local/lib/libopencv_stitching.so.4.0.0
cannymorph: /usr/local/lib/libopencv_superres.so.4.0.0
cannymorph: /usr/local/lib/libopencv_videostab.so.4.0.0
cannymorph: /usr/local/lib/libopencv_viz.so.4.0.0
cannymorph: /usr/local/lib/libopencv_calib3d.so.4.0.0
cannymorph: /usr/local/lib/libopencv_features2d.so.4.0.0
cannymorph: /usr/local/lib/libopencv_flann.so.4.0.0
cannymorph: /usr/local/lib/libopencv_highgui.so.4.0.0
cannymorph: /usr/local/lib/libopencv_photo.so.4.0.0
cannymorph: /usr/local/lib/libopencv_video.so.4.0.0
cannymorph: /usr/local/lib/libopencv_videoio.so.4.0.0
cannymorph: /usr/local/lib/libopencv_imgcodecs.so.4.0.0
cannymorph: /usr/local/lib/libopencv_imgproc.so.4.0.0
cannymorph: /usr/local/lib/libopencv_core.so.4.0.0
cannymorph: CMakeFiles/cannymorph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calvin/cvproject/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cannymorph"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cannymorph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cannymorph.dir/build: cannymorph

.PHONY : CMakeFiles/cannymorph.dir/build

CMakeFiles/cannymorph.dir/requires: CMakeFiles/cannymorph.dir/cannymorph.cpp.o.requires

.PHONY : CMakeFiles/cannymorph.dir/requires

CMakeFiles/cannymorph.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cannymorph.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cannymorph.dir/clean

CMakeFiles/cannymorph.dir/depend:
	cd /home/calvin/cvproject/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calvin/cvproject/cpp /home/calvin/cvproject/cpp /home/calvin/cvproject/cpp /home/calvin/cvproject/cpp /home/calvin/cvproject/cpp/CMakeFiles/cannymorph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cannymorph.dir/depend

