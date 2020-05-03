cmake_minimum_required(VERSION 3.5)

EXECUTE_PROCESS( COMMAND uname -p COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if (APPLE AND UNIX AND ${ARCHITECTURE} STREQUAL "arm64")
  SET(CMAKE_OSX_SYSROOT /var/theos/sdks/iPhoneOS11.2.sdk)
endif (APPLE AND UNIX AND ${ARCHITECTURE} STREQUAL "arm64")

project(cynapse)

if (UNIX)
  SET(CMAKE_C_FLAGS "-Wall -Wno-unused-command-line-argument")
endif (UNIX)

file(GLOB SOURCES "lib/*.cpp" "lib/*/*.cpp")

add_library(cynapse ${SOURCES})
if (NOT APPLE AND UNIX)
  target_link_libraries(cynapse)
endif (NOT APPLE AND UNIX)

if (APPLE)
  target_link_libraries(chameleo)
endif (APPLE)
