Package: imgui[core,dx12-binding,win32-binding]:x64-uwp@1.90.2

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.40.33812.0
-    vcpkg-tool version: 2024-03-14-7d353e869753e5609a1f1a057df3db8fd356e49d
    vcpkg-readonly: true
    vcpkg-scripts version: 7f9f0e44db287e8e67c0e888141bfa200ab45121

**To Reproduce**

`vcpkg install --allow-unsupported`
**Failure logs**

```
-- Note: imgui only supports static library linkage. Building static library.
-- Using cached ocornut-imgui-v1.90.2.tar.gz.
-- Cleaning sources at E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/vcpkg/blds/imgui/src/v1.90.2-4442117b09.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/Users/Ádám/AppData/Local/vcpkg/downloads/ocornut-imgui-v1.90.2.tar.gz
-- Using source at E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/vcpkg/blds/imgui/src/v1.90.2-4442117b09.clean
-- Found external ninja('1.11.0').
-- Configuring x64-uwp
-- Building x64-uwp-dbg
CMake Error at scripts/cmake/vcpkg_execute_build_process.cmake:134 (message):
    Command failed: "C:/Program Files/CMake/bin/cmake.exe" --build . --config Debug --target install -- -v -j13
    Working Directory: E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/vcpkg/blds/imgui/x64-uwp-dbg
    See logs for more information:
      E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\install-x64-uwp-dbg-out.log

Call Stack (most recent call first):
  E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/x64-windows/share/vcpkg-cmake/vcpkg_cmake_build.cmake:74 (vcpkg_execute_build_process)
  E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/x64-windows/share/vcpkg-cmake/vcpkg_cmake_install.cmake:16 (vcpkg_cmake_build)
  C:/Users/Ádám/AppData/Local/vcpkg/registries/git-trees/d9be79046f87d6b17d50967e3b76f2460e0d1bf3/portfile.cmake:68 (vcpkg_cmake_install)
  scripts/ports.cmake:175 (include)



```
<details><summary>E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\install-x64-uwp-dbg-out.log</summary>

```
Change Dir: 'E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/x64-uwp/vcpkg/blds/imgui/x64-uwp-dbg'

Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/2022/Enterprise/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v -v -j13 install
[1/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\backends\imgui_impl_win32.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp"
FAILED: CMakeFiles/imgui.dir/backends/imgui_impl_win32.cpp.obj 
C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\backends\imgui_impl_win32.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp"
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(130): error C2039: 'GetKeyboardLayout': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(130): error C3861: 'GetKeyboardLayout': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(227): error C2039: 'SetCursor': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(227): error C3861: 'SetCursor': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(245): error C2039: 'SetCursor': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(245): error C2039: 'LoadCursor': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(245): error C3861: 'LoadCursor': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(245): error C3861: 'SetCursor': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(252): error C2039: 'GetKeyState': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(252): error C3861: 'GetKeyState': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(293): error C2039: 'GetForegroundWindow': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(293): error C3861: 'GetForegroundWindow': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(301): error C2039: 'ClientToScreen': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(301): error C3861: 'ClientToScreen': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(302): error C2039: 'SetCursorPos': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(302): error C3861: 'SetCursorPos': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(310): error C2039: 'GetCursorPos': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(310): error C3861: 'GetCursorPos': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(310): error C2039: 'ScreenToClient': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(310): error C3861: 'ScreenToClient': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(381): error C2039: 'GetClientRect': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(381): error C3861: 'GetClientRect': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(563): error C2039: 'GetMessageExtraInfo': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(563): error C3861: 'GetMessageExtraInfo': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(590): error C2065: 'TRACKMOUSEEVENT': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(590): error C2146: syntax error: missing ';' before identifier 'tme_cancel'
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(590): error C2065: 'tme_cancel': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(590): error C2065: 'tme_cancel': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(590): error C3079: an initializer list cannot be used as the right operand of this assignment operator
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(591): error C2065: 'TRACKMOUSEEVENT': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(591): error C2146: syntax error: missing ';' before identifier 'tme_track'
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(591): error C2065: 'tme_track': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(591): error C2065: 'tme_track': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(591): error C3079: an initializer list cannot be used as the right operand of this assignment operator
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(593): error C2039: 'TrackMouseEvent': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(593): error C2065: 'tme_cancel': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(593): error C3861: 'TrackMouseEvent': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(594): error C2039: 'TrackMouseEvent': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(594): error C2065: 'tme_track': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(594): error C3861: 'TrackMouseEvent': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(597): error C3861: 'GET_X_LPARAM': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(597): error C3861: 'GET_Y_LPARAM': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(598): error C2039: 'ScreenToClient': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(598): error C3861: 'ScreenToClient': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(714): error C2039: 'IsWindowUnicode': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(714): error C3861: 'IsWindowUnicode': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(774): error C3861: 'VER_SET_CONDITION': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(775): error C3861: 'VER_SET_CONDITION': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(821): error C2039: 'SetProcessDPIAware': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(821): error C3861: 'SetProcessDPIAware': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(846): error C2039: 'GetDC': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(846): error C3861: 'GetDC': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(847): error C2039: 'GetDeviceCaps': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(847): error C3861: 'GetDeviceCaps': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(848): error C2039: 'GetDeviceCaps': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(848): error C3861: 'GetDeviceCaps': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(850): error C2039: 'ReleaseDC': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(850): error C3861: 'ReleaseDC': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(857): error C2039: 'MonitorFromWindow': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(857): error C3861: 'MonitorFromWindow': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(878): error C2039: 'DwmIsCompositionEnabled': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(878): error C3861: 'DwmIsCompositionEnabled': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(883): error C2039: 'DwmGetColorizationColor': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(883): error C3861: 'DwmGetColorizationColor': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(885): error C2039: 'CreateRectRgn': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(885): error C3861: 'CreateRectRgn': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(886): error C2065: 'DWM_BLURBEHIND': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(886): error C2146: syntax error: missing ';' before identifier 'bb'
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(886): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(886): error C3079: an initializer list cannot be used as the right operand of this assignment operator
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(887): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(887): error C2065: 'DWM_BB_ENABLE': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(887): error C2065: 'DWM_BB_BLURREGION': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(888): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(889): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(890): error C2039: 'DwmEnableBlurBehindWindow': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(890): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(890): error C3861: 'DwmEnableBlurBehindWindow': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(891): error C2039: 'DeleteObject': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(891): error C3861: 'DeleteObject': identifier not found
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(895): error C2065: 'DWM_BLURBEHIND': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(895): error C2146: syntax error: missing ';' before identifier 'bb'
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(895): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(895): error C3079: an initializer list cannot be used as the right operand of this assignment operator
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(896): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(896): error C2065: 'DWM_BB_ENABLE': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(897): error C2039: 'DwmEnableBlurBehindWindow': is not a member of '`global namespace''
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(897): error C2065: 'bb': undeclared identifier
E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_win32.cpp(897): error C3861: 'DwmEnableBlurBehindWindow': identifier not found
[2/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\misc\cpp\imgui_stdlib.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\misc\cpp\imgui_stdlib.cpp"
[3/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\backends\imgui_impl_dx12.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\backends\imgui_impl_dx12.cpp"
[4/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\imgui_tables.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\imgui_tables.cpp"
[5/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\imgui_demo.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\imgui_demo.cpp"
[6/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\imgui_draw.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\imgui_draw.cpp"
[7/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\imgui_widgets.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\imgui_widgets.cpp"
[8/10] C:\PROGRA~1\MICROS~2\2022\ENTERP~1\VC\Tools\MSVC\1440~1.338\bin\Hostx64\x64\cl.exe   /TP  -I"E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean" /DWIN32 /D_WINDOWS /D_UNICODE /DUNICODE /DWINAPI_FAMILY=WINAPI_FAMILY_APP /D__WRL_NO_DEFAULT_LIB__ /nologo /Z7 /MP /GS /Gd /Gm- /W3 /WX- /Zc:wchar_t /Zc:inline /Zc:forScope /fp:precise /Oy- /EHsc  /utf-8  /D_DEBUG /MDd /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\imgui.dir\imgui.cpp.obj /FdCMakeFiles\imgui.dir\imgui.pdb /FS -c "E:\Egyetem\Nyári miniprojekt\axodox-graphics-DX12-miniproject-\vcpkg_installed\x64-uwp\vcpkg\blds\imgui\src\v1.90.2-4442117b09.clean\imgui.cpp"
ninja: build stopped: subcommand failed.
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "dependencies": [
    {
      "name": "imgui",
      "features": [
        "dx12-binding",
        "win32-binding"
      ]
    }
  ]
}

```
</details>
