cmake_minimum_required(VERSION 3.6)
project(Proyecto1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c hashTable.h hashTable.c  lex.yy.c)
add_executable(Proyecto1 ${SOURCE_FILES} )

target_link_libraries(Proyecto1 m)