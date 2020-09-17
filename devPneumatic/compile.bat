@echo off
set PATH=C:/Program Files/Hopsan212/mingw64/bin;%PATH%
@echo on
if exist PneumaticLib.dll (
  del PneumaticLib.dll
)
g++ -I"C:/Program Files/Hopsan212/HopsanCore/include" -fPIC -w -Wl,--rpath,"C:/Users/petkr14/Dropbox/HopsanComponents/PneumaticDevelop" -DRELEASECOMPILING -std=c++11  Pneumatic.cc -L"C:/Program Files/Hopsan212/bin" -lhopsancore  -shared -o PneumaticLib.dll
