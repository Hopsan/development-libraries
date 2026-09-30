@echo off
set PATH=C:/Program Files/Hopsan/mingw64/bin;%PATH%
@echo on
if exist selter.dll (
  del selter.dll
)
g++ -I"C:/Program Files/Hopsan/HopsanCore/include" -std=c++14 -fPIC -w -Wl,--rpath,"C:/development-libraries/selter" -DHOPSAN_BUILD_TYPE_RELEASE -DHOPSANCORE_DLLIMPORT  selter.cpp -L"C:/Program Files/Hopsan/bin" -L"C:/Program Files/Hopsan/lib" -lhopsancore  -shared -o selter.dll
