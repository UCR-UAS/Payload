# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark

# Include any dependencies generated for this target.
include CMakeFiles/SpectralSaliency.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SpectralSaliency.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpectralSaliency.dir/flags.make

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o: CMakeFiles/SpectralSaliency.dir/flags.make
CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o: OnlySpec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o -c /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/OnlySpec.cpp

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/OnlySpec.cpp > CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.i

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/OnlySpec.cpp -o CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.s

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.requires:

.PHONY : CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.requires

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.provides: CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.requires
	$(MAKE) -f CMakeFiles/SpectralSaliency.dir/build.make CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.provides.build
.PHONY : CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.provides

CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.provides.build: CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o


# Object files for target SpectralSaliency
SpectralSaliency_OBJECTS = \
"CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o"

# External object files for target SpectralSaliency
SpectralSaliency_EXTERNAL_OBJECTS =

SpectralSaliency: CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o
SpectralSaliency: CMakeFiles/SpectralSaliency.dir/build.make
SpectralSaliency: /usr/lib/libopencv_vstab.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_imuvstab.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_facedetect.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_esm_panorama.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_detection_based_tracker.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_videostab.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_ts.a
SpectralSaliency: /usr/lib/libopencv_superres.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_contrib.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_tegra.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_stitching.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_gpu.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_photo.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_legacy.so.2.4.13
SpectralSaliency: /usr/local/cuda-8.0/lib64/libcufft.so
SpectralSaliency: /usr/lib/libopencv_video.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_objdetect.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_ml.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_calib3d.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_features2d.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_highgui.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_imgproc.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_flann.so.2.4.13
SpectralSaliency: /usr/lib/libopencv_core.so.2.4.13
SpectralSaliency: /usr/local/cuda-8.0/lib64/libcudart.so
SpectralSaliency: /usr/local/cuda-8.0/lib64/libnppc.so
SpectralSaliency: /usr/local/cuda-8.0/lib64/libnppi.so
SpectralSaliency: /usr/local/cuda-8.0/lib64/libnpps.so
SpectralSaliency: CMakeFiles/SpectralSaliency.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SpectralSaliency"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpectralSaliency.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SpectralSaliency.dir/build: SpectralSaliency

.PHONY : CMakeFiles/SpectralSaliency.dir/build

CMakeFiles/SpectralSaliency.dir/requires: CMakeFiles/SpectralSaliency.dir/OnlySpec.cpp.o.requires

.PHONY : CMakeFiles/SpectralSaliency.dir/requires

CMakeFiles/SpectralSaliency.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpectralSaliency.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpectralSaliency.dir/clean

CMakeFiles/SpectralSaliency.dir/depend:
	cd /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark /home/ubuntu/Payload/Payload/ADLC/GPUBenchmark/CMakeFiles/SpectralSaliency.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpectralSaliency.dir/depend

