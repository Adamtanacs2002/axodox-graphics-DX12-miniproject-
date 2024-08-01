Package: protobuf:x64-windows@3.21.12#1

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.40.33812.0
-    vcpkg-tool version: 2024-03-14-7d353e869753e5609a1f1a057df3db8fd356e49d
    vcpkg-readonly: true
    vcpkg-scripts version: 7f9f0e44db287e8e67c0e888141bfa200ab45121

**To Reproduce**

`vcpkg install `
**Failure logs**

```
-- Using cached protocolbuffers-protobuf-v3.21.12.tar.gz.
-- Extracting source C:/Users/Ádám/AppData/Local/vcpkg/downloads/protocolbuffers-protobuf-v3.21.12.tar.gz
-- Applying patch fix-static-build.patch
-- Applying patch fix-default-proto-file-path.patch
-- Applying patch compile_options.patch
-- Using source at E:/Egyetem/Nyári miniprojekt/axodox-graphics-DX12-miniproject-/vcpkg_installed/vcpkg/blds/protobuf/src/v3.21.12-fdb7676342.clean
-- Found external ninja('1.11.0').
-- Configuring x64-windows
-- Building x64-windows-dbg
-- Building x64-windows-rel
CMake Error at scripts/cmake/vcpkg_copy_tool_dependencies.cmake:31 (message):
  Could not find PowerShell Core; please open an issue to report this.
Call Stack (most recent call first):
  scripts/cmake/vcpkg_copy_tools.cmake:48 (vcpkg_copy_tool_dependencies)
  C:/Users/Ádám/AppData/Local/vcpkg/registries/git-trees/8d742753b6c35666168a4178f0aae986740ae42c/portfile.cmake:92 (vcpkg_copy_tools)
  scripts/ports.cmake:175 (include)



```
**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "dependencies": [
    "opencv4"
  ]
}

```
</details>
