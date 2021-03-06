#options
#PNG_INCLUDE
#PNG_LIBRARY
#HDF5_INCLUDE
#HDF5_HL_INCLUDE
#HDF5_LIBRARY
#HDF5_HL_LIBRARY
#ZLIB_LIBRARY
#SZIP_LIBRARY

cmake_minimum_required(VERSION 2.8)
project (h5png)
include(CheckCXXCompilerFlag)

find_path(PNG_INCLUDE_FOUND png.h HINTS ${PNG_INCLUDE})
if(NOT PNG_INCLUDE_FOUND)
  message(FATAL_ERROR "png.h header file not found")
else()
  message("-- Found png.h header file at: " ${PNG_INCLUDE_FOUND})
endif()

find_library(PNG_LIBRARY NAMES png)
if(NOT PNG_LIBRARY)
  message(FATAL_ERROR "png library not found")
else()
  message("-- Found png library at: " ${PNG_LIBRARY})
endif()

set(HEADER_HDF5_HINTS ${HEADER_HDF5_HINTS} "/usr/include/hdf5/serial")
set(HEADER_HDF5_HINTS ${HEADER_HDF5_HINTS} "/data/starfs1/libs/hdf5-1.8.7-linux-x86_64-static/include")
find_path(HDF5_INCLUDE_FOUND hdf5.h HINTS ${HDF5_INCLUDE}  ${HEADER_HDF5_HINTS})
if(NOT HDF5_INCLUDE_FOUND)
  message(FATAL_ERROR "hdf5.h header file not found")
else()
  message("-- Found hdf5.h header file at: " ${HDF5_INCLUDE_FOUND})
endif()

set(LIB_HDF5_HINTS ${LIB_HDF5_HINTS} "/usr/lib/i386-linux-gnu/hdf5/serial")
set(LIB_HDF5_HINTS ${LIB_HDF5_HINTS} "/data/starfs1/libs/hdf5-1.8.7-linux-x86_64-static/lib")
find_library(HDF5_LIBRARY NAMES hdf5 HINTS ${LIB_HDF5_HINTS})
if(NOT HDF5_LIBRARY)
  message(FATAL_ERROR "hdf5 library not found")
else()
  message("-- Found hdf5 library at: " ${HDF5_LIBRARY})
endif()

find_path(HDF5_HL_INCLUDE_FOUND hdf5_hl.h HINTS ${HDF5_HL_INCLUDE} ${HEADER_HDF5_HINTS})
if(NOT HDF5_HL_INCLUDE_FOUND)
  message(FATAL_ERROR "hdf5_hl.h header file not found")
else()
  message("-- Found hdf5_hl.h header file at: " ${HDF5_HL_INCLUDE_FOUND})
endif()

find_library(HDF5_HL_LIBRARY NAMES hdf5_hl HINTS ${LIB_HDF5_HINTS})
if(NOT HDF5_HL_LIBRARY)
  message(FATAL_ERROR "hdf5 high level library not found")
else()
  message("-- Found hdf5 high level library at: " ${HDF5_HL_LIBRARY})
endif()

find_library(ZLIB_LIBRARY NAMES z HINTS "/data/starfs1/libs/hdf5-1.8.7-linux-x86_64-static/lib")
if(NOT ZLIB_LIBRARY)
  message(FATAL_ERROR "zlib library not found")
else()
  message("-- Found zlib library at: " ${ZLIB_LIBRARY})
endif()

find_library(SZIP_LIBRARY NAMES sz HINTS "/data/starfs1/libs/hdf-4.2.6-linux-x86_64/lib/" "/root/usr2/MRT/lib")
if(NOT SZIP_LIBRARY)
  message(FATAL_ERROR "szip library not found")
else()
  message("-- Found szip library at: " ${SZIP_LIBRARY})
endif()

if (MSVC)
  add_definitions( "/D_CRT_SECURE_NO_WARNINGS /D_WINSOCK_DEPRECATED_NO_WARNINGS" )
  if (STATIC_CRT)
    message("-- Building with static runtime library")
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_MINSIZEREL     "/MT /O1 /Ob1 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE        "/MT /O2 /Ob2 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /D NDEBUG")
  endif()  
  set(WINSOCK_LIBRARY ws2_32.lib)
endif(MSVC)

if (CMAKE_VERSION VERSION_LESS "3.1")
 if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
   CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
   if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
   endif()
 endif()
else ()
  set (CMAKE_CXX_STANDARD 11)
endif()

if (CMAKE_VERSION VERSION_LESS "3.1")
 if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
   CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
   if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
   else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
   endif()
 endif()
else ()
  set (CMAKE_CXX_STANDARD 11)
endif()

set(LIBS ${LIBS} ${PNG_LIBRARY} ${HDF5_HL_LIBRARY} ${HDF5_LIBRARY} ${ZLIB_LIBRARY} ${SZIP_LIBRARY} ${WINSOCK_LIBRARY})
include_directories(${PNG_INCLUDE_FOUND} ${HDF5_INCLUDE_FOUND} ${HDF5_HL_INCLUDE_FOUND})
set(SOURCES h5png.cc h5png.hh)
add_executable(h5png h5png_main.cc ${SOURCES})
target_link_libraries (h5png ${LIBS})

