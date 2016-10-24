# CMakeLists.txt --- CMake project settings

cmake_minimum_required(VERSION 2.8)
project(unboost)

#
# options
#
option(USE_CXX11    "Use C++11" OFF)
option(USE_TR1      "Use TR1" OFF)
option(USE_BOOST    "Use Boost" OFF)
option(NO_CXX11     "Don't use C++11" OFF)
option(NO_TR1       "Don't use TR1" OFF)
option(NO_BOOST     "Don't use Boost" OFF)

#
# process of options
#
if(USE_CXX11)
    add_definitions(-DUNBOOST_USE_CXX11)
endif(USE_CXX11)

if(USE_TR2)
    add_definitions(-DUNBOOST_USE_TR2)
endif(USE_TR2)

if(USE_BOOST)
    add_definitions(-DUNBOOST_USE_BOOST)
endif(USE_BOOST)

if(NO_CXX11)
    add_definitions(-DUNBOOST_NO_CXX11)
endif(NO_CXX11)

if(NO_TR1)
    add_definitions(-DUNBOOST_NO_TR1)
endif(NO_TR1)

if(NO_BOOST)
    add_definitions(-DUNBOOST_NO_BOOST)
endif(NO_BOOST)

#
# Boost
#
set(MY_BOOST_COMPONENTS 
    system-mt 
    filesystem-mt 
    regex-mt 
    thread-mt
    chrono-mt)
if(USE_BOOST)
    find_package(Boost REQUIRED COMPONENTS ${MY_BOOST_COMPONENTS})
else(USE_BOOST)
    if(NO_BOOST)
    else(NO_BOOST)
        find_package(Boost COMPONENTS ${MY_BOOST_COMPONENTS})
    endif(NO_BOOST)
endif(USE_BOOST)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_libraries(${Boost_LIBRARIES})
endif(Boost_FOUND)

#
# C++11
#
if(USE_CXX11)
    set(CMAKE_CXX_STANDARD 11)
endif(USE_CXX11)

if((CMAKE_CXX_STANDARD EQUAL 11) OR (CMAKE_CXX_STANDARD GREATER 11))
    set(CXX11_AVAILABLE ON)
endif((CMAKE_CXX_STANDARD EQUAL 11) OR (CMAKE_CXX_STANDARD GREATER 11))

#
# sample programs
#
include_directories(.)

add_executable(array samples/array.cpp)
add_executable(assert samples/assert.cpp)
add_executable(chrono samples/chrono.cpp)
add_executable(conversion samples/conversion.cpp)
add_executable(filesystem samples/filesystem.cpp)
add_executable(ratio samples/ratio.cpp)
add_executable(smart_ptr samples/smart_ptr.cpp)
add_executable(static_assert samples/static_assert.cpp)
add_executable(string_algorithm samples/string_algorithm.cpp)
add_executable(thread samples/thread.cpp)
add_executable(type_traits samples/type_traits.cpp)
if(Boost_FOUND OR CXX11_AVAILABLE)
    add_executable(complex samples/complex.cpp)
    add_executable(foreach samples/foreach.cpp)
    add_executable(random samples/random.cpp)
    add_executable(regex samples/regex.cpp)
    add_executable(tuple samples/tuple.cpp)
    add_executable(unordered samples/unordered.cpp)
endif(Boost_FOUND OR CXX11_AVAILABLE)
