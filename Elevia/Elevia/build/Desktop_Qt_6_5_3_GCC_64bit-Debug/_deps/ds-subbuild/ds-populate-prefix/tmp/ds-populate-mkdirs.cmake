# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-src")
  file(MAKE_DIRECTORY "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-src")
endif()
file(MAKE_DIRECTORY
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-build"
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix"
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/tmp"
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/src"
  "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/amir/Desktop/Elevia/Elevia/build/Desktop_Qt_6_5_3_GCC_64bit-Debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
