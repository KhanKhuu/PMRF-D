cmake_minimum_required(VERSION 2.8)
project( PMRF-D )
find_package( OpenCV REQUIRED )

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( PMRF-D PMRF-D.cpp Utilities/io.cpp Utilities/LAP.cpp Model/Node.cpp Model/AuxMRF.cpp ICM/ICM.cpp)
target_link_libraries( PMRF-D ${OpenCV_LIBS} )
