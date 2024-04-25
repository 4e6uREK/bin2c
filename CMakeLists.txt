cmake_minimum_required(VERSION 3.20)

file(GLOB SOURCES *.c)

project(bin2c VERSION 1.0.0 DESCRIPTION "4e6uREK's fork of bin2c" LANGUAGES C)

include(CTest)
include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SOURCES})

# Add compile flags for different compilers
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if(${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_C_FLAGS "-O0 -std=c11 -Weverything -Werror -DDEBUG")
    elseif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-O0 -std=c11 -Wall -Wextra -Werror -g --coverage -DDEBUG")
    endif()
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    if(${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_C_FLAGS "-O2 -std=c11 -Weverything -Werror -DRELEASE")
    elseif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-O2 -std=c11 -Wall -Wextra -Werror -DRELEASE")
    endif()
endif()

add_custom_target(copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_BINARY_DIR}/..
    COMMENT "Copying compile_commands.json to ${CMAKE_BINARY_DIR}/..")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
