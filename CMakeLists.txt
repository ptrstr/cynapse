cmake_minimum_required(VERSION 3.5)
include(GNUInstallDirs)


# Check for iOS (to compile with Theos)
EXECUTE_PROCESS( COMMAND uname -p COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )

if (APPLE AND UNIX AND ${ARCHITECTURE} STREQUAL "arm64")
  SET(CMAKE_OSX_SYSROOT /var/theos/sdks/iPhoneOS11.2.sdk)
endif (APPLE AND UNIX AND ${ARCHITECTURE} STREQUAL "arm64")

# Project intialization
project(cynapse VERSION 0.1.0)

if (UNIX)
  SET(CMAKE_C_FLAGS "-Wall -Wno-unused-command-line-argument")
endif (UNIX)

# Get SOURCES an HEADERS (public ones)
file(GLOB SOURCES "lib/*.cpp" "lib/*/*.cpp")
file(GLOB HEADERS "include/*.hpp" "include/*/*.hpp")

# Add library
add_library(cynapse STATIC ${SOURCES})

set_target_properties(cynapse PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cynapse PROPERTIES SOVERSION 0)


# Linking (useless with no libs)
if (NOT APPLE AND UNIX)
  target_link_libraries(cynapse m)
endif (NOT APPLE AND UNIX)

if (APPLE)
  target_link_libraries(cynapse m)
endif (APPLE)
