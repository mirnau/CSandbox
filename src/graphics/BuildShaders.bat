@echo off
setlocal enabledelayedexpansion

REM Loop through all .hlsl files in the current directory
for %%f in (*.hlsl) do (
    REM Get the file name without the extension
    set "fileName=%%~nf"
    
    REM Check if the filename contains 'vertex' or 'pixel'
    if "!fileName!"=="!fileName:vertex=!" (
        REM If filename does not contain 'vertex', assume it's a pixel shader
        echo Compiling pixel shader: %%f
        fxc /T ps_5_0 /Fo "!fileName!.cso" "%%f"
    ) else if "!fileName!"=="!fileName:pixel=!" (
        REM If filename does not contain 'pixel', assume it's a vertex shader
        echo Compiling vertex shader: %%f
        fxc /T vs_5_0 /Fo "!fileName!.cso" "%%f"
    ) else (
        echo Warning: Filename does not contain 'vertex' or 'pixel', skipping %%f
    )
)

echo Done compiling shaders.
PAUSE
