# Install script for directory: C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/googletest-master/googlemock

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2022.3.3/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/googletest-master/googlemock/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/skeletons/matlab-1/cmake-build-debug/lib/libgmock.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/skeletons/matlab-1/cmake-build-debug/lib/libgmock_main.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/skeletons/matlab-1/cmake-build-debug/googletest-master/googletest/generated/gmock.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/skeletons/matlab-1/cmake-build-debug/googletest-master/googletest/generated/gmock_main.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/bialo/OneDrive/Pulpit/Studia/Projects/zadania_c_cpp/mdig-agh-lang_cpp__exercises-288bd81c85d7/mdig-agh-lang_cpp__exercises-288bd81c85d7/skeletons/matlab-1/cmake-build-debug/googletest-master/googletest/cmake_install.cmake")

endif()

