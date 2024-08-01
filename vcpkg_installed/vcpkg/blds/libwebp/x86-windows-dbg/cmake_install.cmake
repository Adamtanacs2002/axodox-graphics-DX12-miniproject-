# Install script for directory: E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/pkgs/libwebp_x86-windows/debug")
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
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/sharpyuv/libsharpyuv.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libsharpyuv.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libsharpyuv.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp/sharpyuv" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/sharpyuv/sharpyuv.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/sharpyuv/sharpyuv_csp.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/src/libwebpdecoder.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/src/libwebp.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/src/demux/libwebpdemux.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/src/mux/libwebpmux.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpdecoder.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpdecoder.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/decode.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebp.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebp.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/decode.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/encode.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpdemux.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpdemux.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/decode.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/demux.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/mux_types.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpmux.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/libwebpmux.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/mux.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/mux_types.h"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/src/v1.3.2-11232cde94.clean/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake"
         "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/WebPConfigVersion.cmake"
    "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/WebPConfig.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
  file(WRITE "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libwebp/x86-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
