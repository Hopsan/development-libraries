@echo off
set PATH=C:/Program Files/Hopsan/mingw64/bin;%PATH%
@echo on
if exist Diff.dll (
  del Diff.dll
)
g++ -I"C:/Program Files/Hopsan/HopsanCore/include" -fPIC -w -Wl,--rpath,"C:/datafile/LSelter/Documents/Hopsan/development-libraries/diff" -DHOPSAN_BUILD_TYPE_RELEASE -DHOPSANCORE_DLLIMPORT  Diff.cpp -L"C:/Program Files/Hopsan/bin" -L"C:/Program Files/Hopsan/lib" -lhopsancore  -shared -o Diff.dll
