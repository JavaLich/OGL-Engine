# Install script for directory: C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp-4.0.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp4.0.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-4.0" TYPE FILE FILES
    "C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/assimp-config.cmake"
    "C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/assimp-config-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "libassimp4.0.1-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/contrib/zlib/cmake_install.cmake")
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/contrib/cmake_install.cmake")
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/code/cmake_install.cmake")
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/tools/assimp_view/cmake_install.cmake")
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/tools/assimp_cmd/cmake_install.cmake")
  include("C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Akash/Desktop/Akash/C++/Workspace/OGL/Libraries/assimp/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
