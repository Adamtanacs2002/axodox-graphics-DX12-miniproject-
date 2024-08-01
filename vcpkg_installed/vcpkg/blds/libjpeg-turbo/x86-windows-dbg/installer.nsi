!include x64.nsh
Name "libjpeg-turbo SDK for Visual C++"
OutFile "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}libjpeg-turbo-3.0.2-vc.exe"
InstallDir "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\vcpkg\pkgs\libjpeg-turbo_x86-windows\debug"

SetCompressor bzip2

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

Section "libjpeg-turbo SDK for Visual C++ (required)"
!ifdef WIN64
	${If} ${RunningX64}
	${DisableX64FSRedirection}
	${Endif}
!endif
	SectionIn RO
!ifdef GCC
	IfFileExists $SYSDIR/libturbojpeg.dll exists 0
!else
	IfFileExists $SYSDIR/turbojpeg.dll exists 0
!endif
	goto notexists
	exists:
!ifdef GCC
	MessageBox MB_OK "An existing version of the libjpeg-turbo SDK for Visual C++ is already installed.  Please uninstall it first."
!else
	MessageBox MB_OK "An existing version of the libjpeg-turbo SDK for Visual C++ or the TurboJPEG SDK is already installed.  Please uninstall it first."
!endif
	quit

	notexists:
	SetOutPath $SYSDIR
!ifdef GCC
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libturbojpeg.dll"
!else
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}turbojpeg.dll"
!endif
	SetOutPath $INSTDIR\bin
!ifdef GCC
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libturbojpeg.dll"
!else
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}turbojpeg.dll"
!endif
!ifdef GCC
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libjpeg-62.dll"
!else
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}jpeg62.dll"
!endif
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}cjpeg.exe"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}djpeg.exe"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}jpegtran.exe"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}tjbench.exe"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}rdjpgcom.exe"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}wrjpgcom.exe"
	SetOutPath $INSTDIR\lib
!ifdef GCC
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libturbojpeg.dll.a"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libturbojpeg.a"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libjpeg.dll.a"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\libjpeg.a"
!else
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}turbojpeg.lib"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}turbojpeg-static.lib"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}jpeg.lib"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\${BUILDDIR}jpeg-static.lib"
!endif
	SetOutPath $INSTDIR\lib\pkgconfig
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\pkgscripts\libjpeg.pc"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\pkgscripts\libturbojpeg.pc"
	SetOutPath $INSTDIR\lib\cmake\libjpeg-turbo
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\pkgscripts\libjpeg-turboConfig.cmake"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\pkgscripts\libjpeg-turboConfigVersion.cmake"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\win\libjpeg-turboTargets.cmake"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\win\libjpeg-turboTargets-release.cmake"
!ifdef JAVA
	SetOutPath $INSTDIR\classes
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\java\turbojpeg.jar"
!endif
	SetOutPath $INSTDIR\include
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/x86-windows-dbg\jconfig.h"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\jerror.h"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\jmorecfg.h"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\jpeglib.h"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\turbojpeg.h"
	SetOutPath $INSTDIR\doc
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\README.ijg"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\README.md"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\LICENSE.md"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\example.c"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\libjpeg.txt"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\structure.txt"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\usage.txt"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\wizard.txt"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\tjexample.c"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\java\TJExample.java"
!ifdef GCC
	SetOutPath $INSTDIR\man\man1
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\cjpeg.1"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\djpeg.1"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\jpegtran.1"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\rdjpgcom.1"
	File "E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/libjpeg-turbo/src/3.0.2-c04fb0ca25.clean\wrjpgcom.1"
!endif

	WriteRegStr HKLM "SOFTWARE\libjpeg-turbo 3.0.2" "Install_Dir" "$INSTDIR"

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\libjpeg-turbo 3.0.2" "DisplayName" "libjpeg-turbo SDK v3.0.2 for Visual C++"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\libjpeg-turbo 3.0.2" "UninstallString" '"$INSTDIR\uninstall_3.0.2.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\libjpeg-turbo 3.0.2" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\libjpeg-turbo 3.0.2" "NoRepair" 1
	WriteUninstaller "uninstall_3.0.2.exe"
SectionEnd

Section "Uninstall"
!ifdef WIN64
	${If} ${RunningX64}
	${DisableX64FSRedirection}
	${Endif}
!endif

	SetShellVarContext all

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\libjpeg-turbo 3.0.2"
	DeleteRegKey HKLM "SOFTWARE\libjpeg-turbo 3.0.2"

!ifdef GCC
	Delete $INSTDIR\bin\libjpeg-62.dll
	Delete $INSTDIR\bin\libturbojpeg.dll
	Delete $SYSDIR\libturbojpeg.dll
	Delete $INSTDIR\lib\libturbojpeg.dll.a
	Delete $INSTDIR\lib\libturbojpeg.a
	Delete $INSTDIR\lib\libjpeg.dll.a
	Delete $INSTDIR\lib\libjpeg.a
!else
	Delete $INSTDIR\bin\jpeg62.dll
	Delete $INSTDIR\bin\turbojpeg.dll
	Delete $SYSDIR\turbojpeg.dll
	Delete $INSTDIR\lib\jpeg.lib
	Delete $INSTDIR\lib\jpeg-static.lib
	Delete $INSTDIR\lib\turbojpeg.lib
	Delete $INSTDIR\lib\turbojpeg-static.lib
!endif
	Delete $INSTDIR\lib\pkgconfig\libjpeg.pc
	Delete $INSTDIR\lib\pkgconfig\libturbojpeg.pc
	Delete $INSTDIR\lib\cmake\libjpeg-turbo\libjpeg-turboConfig.cmake
	Delete $INSTDIR\lib\cmake\libjpeg-turbo\libjpeg-turboConfigVersion.cmake
	Delete $INSTDIR\lib\cmake\libjpeg-turbo\libjpeg-turboTargets.cmake
	Delete $INSTDIR\lib\cmake\libjpeg-turbo\libjpeg-turboTargets-release.cmake
!ifdef JAVA
	Delete $INSTDIR\classes\turbojpeg.jar
!endif
	Delete $INSTDIR\bin\cjpeg.exe
	Delete $INSTDIR\bin\djpeg.exe
	Delete $INSTDIR\bin\jpegtran.exe
	Delete $INSTDIR\bin\tjbench.exe
	Delete $INSTDIR\bin\rdjpgcom.exe
	Delete $INSTDIR\bin\wrjpgcom.exe
	Delete $INSTDIR\include\jconfig.h
	Delete $INSTDIR\include\jerror.h
	Delete $INSTDIR\include\jmorecfg.h
	Delete $INSTDIR\include\jpeglib.h
	Delete $INSTDIR\include\turbojpeg.h
	Delete $INSTDIR\uninstall_3.0.2.exe
	Delete $INSTDIR\doc\README.ijg
	Delete $INSTDIR\doc\README.md
	Delete $INSTDIR\doc\LICENSE.md
	Delete $INSTDIR\doc\example.c
	Delete $INSTDIR\doc\libjpeg.txt
	Delete $INSTDIR\doc\structure.txt
	Delete $INSTDIR\doc\usage.txt
	Delete $INSTDIR\doc\wizard.txt
	Delete $INSTDIR\doc\tjexample.c
	Delete $INSTDIR\doc\TJExample.java
!ifdef GCC
	Delete $INSTDIR\man\man1\cjpeg.1
	Delete $INSTDIR\man\man1\djpeg.1
	Delete $INSTDIR\man\man1\jpegtran.1
	Delete $INSTDIR\man\man1\rdjpgcom.1
	Delete $INSTDIR\man\man1\wrjpgcom.1
!endif

	RMDir "$INSTDIR\include"
	RMDir "$INSTDIR\lib\pkgconfig"
	RMDir "$INSTDIR\lib\cmake\libjpeg-turbo"
	RMDir "$INSTDIR\lib\cmake"
	RMDir "$INSTDIR\lib"
	RMDir "$INSTDIR\doc"
!ifdef GCC
	RMDir "$INSTDIR\man\man1"
	RMDir "$INSTDIR\man"
!endif
!ifdef JAVA
	RMDir "$INSTDIR\classes"
!endif
	RMDir "$INSTDIR\bin"
	RMDir "$INSTDIR"

SectionEnd
