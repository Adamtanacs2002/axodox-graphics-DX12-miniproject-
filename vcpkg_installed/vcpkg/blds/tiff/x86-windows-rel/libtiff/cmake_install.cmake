# Install script for directory: E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/src/v4.6.0-cea7694842.clean/libtiff

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/pkgs/tiff_x86-windows")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/tiff.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/tiff.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/src/v4.6.0-cea7694842.clean/libtiff/tiff.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/src/v4.6.0-cea7694842.clean/libtiff/tiffio.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/tiffvers.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/tiffconf.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff/TiffTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff/TiffTargets.cmake"
         "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/CMakeFiles/Export/cc2b3a547891f5fbeec431910dcae38b/TiffTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff/TiffTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff/TiffTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/CMakeFiles/Export/cc2b3a547891f5fbeec431910dcae38b/TiffTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/CMakeFiles/Export/cc2b3a547891f5fbeec431910dcae38b/TiffTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/TiffConfigVersion.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/tiff" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/tiff/x86-windows-rel/libtiff/TiffConfig.cmake")
endif()

