@echo off
set PATH=C:/Program Files/Hopsan214/mingw64/bin;%PATH%
@echo on
if exist FuelCellLib.dll (
  del FuelCellLib.dll
)
g++ -I"C:/Program Files/Hopsan214/HopsanCore/include" -fPIC -w -Wl,--rpath,"G:/Git/development-libraries/FuelCellLib" -DHOPSAN_BUILD_TYPE_RELEASE  FuelCellLib.cc -L"C:/Program Files/Hopsan214/bin" -L"C:/Program Files/Hopsan214/lib" -lhopsancore  -shared -o FuelCellLib.dll
