@echo off

set cmake_dir=%1
set cmake_dir=%cmake_dir:"=%

set input_dir=%2
set input_dir=%input_dir:"=%

set output_dir=%3
set output_dir=%output_dir:"=%
set output_dir=%output_dir%/.file-lists

echo [Check] Checking for file-list changes

if exist "%output_dir%\" (
    rem Get modules file listings
    dir /B/S *.c;*.cpp;*.h;*.hpp "%input_dir%" > "%output_dir%\current.txt"

    rem Compare changes
    fc "%output_dir%\current.txt" "%output_dir%\previous.txt" > nul
    if errorlevel 1 goto files_different
    echo [Check] File-lists have not changed.
    goto EOF

    :files_different
    echo [Check] File-lists have changed! Force reloading of CMake...
    copy "%output_dir%\current.txt" "%output_dir%\previous.txt"
    rem copy CMakeLists.txt /B+ ,,/Y
    cmake "%cmake_dir%"

    goto EOF

) else (

    echo [Check] File-lists check has not run before, preparing for next run. Skipping check for now

    mkdir "%output_dir%"
    dir /B /S *.c;*.cpp;*.h;*.hpp "%input_dir%" > "%output_dir%\previous.txt"

    goto EOF

)

:EOF