# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (PIXMIX)

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE "ON")

#check here https://rix0r.nl/blog/2015/08/13/cmake-guide/

# Recurse into subdirectories.
subdirs (src)
