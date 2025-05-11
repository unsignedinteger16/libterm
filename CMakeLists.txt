cmake_minimum_required(VERSION 3.30)
project(libterm
    VERSION 0.0.1
    DESCRIPTION 
        "Lightweight terminal library in C99"
    LANGUAGES C
)


include(CMakePackageConfigHelpers)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(LIBTERM_ENABLE_EVENTS "Enables events system" ON)
option(LIBTERM_COMPILE_EXAMPLES "Compiles examples" OFF)

if(LIBTERM_COMPILE_EXAMPLES)
    add_subdirectory(examples/)
endif()

if(LIBTERM_ENABLE_EVENTS)
    set(LIBTERM_EVENTS_SRC_GLOB "src/events/*.c" "src/events/*.h")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LIBTERM_PLATFORM_SRC_GLOB "src/linux/*.c" "src/linux/*.h")
else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

set(LIBTERM_SHARED_SRC_GLOB "src/shared/*.c src/shared/*.h")

file(GLOB SOURCES ${LIBTERM_EVENTS_SRC_GLOB} ${LIBTERM_SHARED_SRC_GLOB} ${LIBTERM_PLATFORM_SRC_GLOB})

add_library(libterm ${SOURCES})
target_include_directories(libterm PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
$<INSTALL_INTERFACE:include>)

install(
    TARGETS libterm
    EXPORT LibtermTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
