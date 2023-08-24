@echo off
set DSD_ROOT=C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\etc\Gateway\root_default\dsd
set DSD_JOBSROOT=C:\ProgramData\BIOVIA\Materials Studio\20.1\Gateway-x64\root_default\dsd
set CFG_ROOT=C:\ProgramData\BIOVIA\Materials Studio\20.1\Gateway-x64\configurations\default
set PERL5LIB=
set SMPD_OPTION_BINARY=C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\bin\smpd.exe
set PATH=C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\Program Files\dotnet\;C:\WINDOWS\system32\config\systemprofile\AppData\Local\Microsoft\WindowsApps
"C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\bin\perl.exe" -I"C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\lib" -I"C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\lib\site_perl" -I"C:\Program Files (x86)\BIOVIA\Materials Studio 20.1 x64 Server\etc\Gateway\root_default\dsd\commands" "C:\ProgramData\BIOVIA\Materials Studio\20.1\Gateway-x64\root_default\dsd\servers/VAMP.pl"   2>std.err
