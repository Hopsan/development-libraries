@echo off
set PATH=C:/Program Files/Hopsan214/mingw64/bin;%PATH%
@echo on
if exist ActivityDiagramLibrary.dll (
  del ActivityDiagramLibrary.dll
)
g++ -I"C:/Program Files/Hopsan214/HopsanCore/include" -fPIC -w -Wl,--rpath,"H:/PettersDropbox/Dropbox/HopsanComponents/ActivityDiagramLibrary" -DHOPSAN_BUILD_TYPE_RELEASE -std=c++11  ActivityDiagramLib.cc -L"C:/Program Files/Hopsan214/bin" -L"C:/Program Files/Hopsan214/lib" -lhopsancore  -shared -o ActivityDiagramLibrary.dll
