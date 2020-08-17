set(CMAKE_OUTPUT_ROOT_DIR ${CMAKE_SOURCE_DIR}/..) 
set(CMAKE_BINARY_DIR ${CMAKE_OUTPUT_ROOT_DIR}/bin) 
set(CMAKE_ARCHIVE_DIR ${CMAKE_OUTPUT_ROOT_DIR}/lib) 
set(CMAKE_LIBRARY_DIR ${CMAKE_OUTPUT_ROOT_DIR}/lib) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_DIR}) 

add_compile_options(-std=c++2a -include ${CMAKE_CURRENT_LIST_DIR}/utils/log.h)

include_directories(${CMAKE_SOURCE_DIR}/utils)
link_directories(${CMAKE_ARCHIVE_DIR} ${CMAKE_LIBRARY_DIR} )

add_subdirectory(utils)

link_libraries(-lutils)

add_subdirectory(ch01)
add_subdirectory(ch02)
add_subdirectory(ch03)
add_subdirectory(ch04)
add_subdirectory(ch05)
add_subdirectory(ch06)
add_subdirectory(ch07)
add_subdirectory(ch08)
add_subdirectory(ch09)
add_subdirectory(ch10)
# add_subdirectory(appendixA)
# add_subdirectory(appendixB)
# add_subdirectory(appendixC)

