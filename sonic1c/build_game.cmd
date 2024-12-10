echo \" <<'BATCH_SCRIPT' >/dev/null ">NUL "\" \`" <#"
@ECHO OFF
REM ===== Batch Script Begin =====
%cd%/../tcc/tcc.exe -g -rdynamic -shared ./*.c ./objects/*.c ./zones/*.c -o ../sonic1.dll
REM ====== Batch Script End ======
GOTO :eof
TYPE CON >NUL
BATCH_SCRIPT
#> | Out-Null


echo \" <<'POWERSHELL_SCRIPT' >/dev/null # " | Out-Null
# ===== PowerShell Script Begin =====
./tcc/tcc.exe -g -rdynamic -shared ./*.c ./objects/*.c ./zones/*.c -o ../sonic1.dll
# ====== PowerShell Script End ======
while ( ! $MyInvocation.MyCommand.Source ) { $input_line = Read-Host }
exit
<#
POWERSHELL_SCRIPT


set +o histexpand 2>/dev/null
# ===== Bash Script Begin =====
./tcc/tcc.exe -g -shared ./*.c ./objects/*.c ./zones/*.c -o ../libsonic1.so
# ====== Bash Script End ======
case $- in *"i"*) cat /dev/stdin >/dev/null ;; esac
exit
#>