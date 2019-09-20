cmake_minimum_required(VERSION 3.5)

project(filecluster)

# Find boost library
find_package(Boost 1.58 REQUIRED COMPONENTS program_options)

# Enable C++14 and warnings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g3 -ggdb -Wall -Wextra")

include_directories(
  include
  lib
)

set( H_FILES 
    lib/jaroWinkler.hpp
    include/utils.hpp  
    include/string_for_kmean.hpp
    include/kmeans.hpp
    include/unit_test.hpp
)

set( SRC_FILES
    lib/jaroWinkler.cpp
    src/string_for_kmean.cpp
    src/kmeans.cpp
    src/unit_test.cpp
    src/main.cpp   
)

# Create a executable file
add_executable(filecluster 
    ${SRC_FILES} ${H_FILES}
)
# Link libraries  
target_link_libraries(filecluster
    ${Boost_LIBRARIES}
)