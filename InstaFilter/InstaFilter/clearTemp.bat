@echo off
@FOR /F "delims=" %%a IN ('DIR "*.exp" "*.obj" "*.lib" "*.pdb" "*.tlog" "*.log" "*.manifest" "*.lastbuildstate" "*.DS_Store" /S /B') DO del /F /Q "%%a"