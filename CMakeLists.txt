cmake_minimum_required(VERSION 3.1)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

include(ExternalProject)

# this references the native makefile
ExternalProject_Add(
    "Native-makefile-build"
    DOWNLOAD_COMMAND true
    CONFIGURE_COMMAND true
    BUILD_COMMAND /bin/make -C ${CMAKE_SOURCE_DIR} TOP=${CMAKE_SOURCE_DIR} all
    INSTALL_COMMAND true
)

# this forces a rebuild every execution
ExternalProject_Add_Step("Native-makefile-build" forceconfigure
    COMMAND ${CMAKE_COMMAND} -E echo "Force configure of myProject"
    DEPENDEES update
    DEPENDERS configure
    ALWAYS 1
)