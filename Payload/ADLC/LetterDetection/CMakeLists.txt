cmake_minimum_required(VERSION 2.8)
project( LetterDetection )
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF)
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package( OpenCV REQUIRED )
#add_executable( LetterDetection tess.cpp )
add_executable( LetterDetection tess.cpp)
target_link_libraries( LetterDetection ${OpenCV_LIBS} )
