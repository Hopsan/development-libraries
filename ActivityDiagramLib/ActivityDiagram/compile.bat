@echo off
set PATH=C:/Program Files/Hopsan/mingw64/bin;%PATH%
@echo on
if exist ActivityDiagramLib.dll (
  del ActivityDiagramLib.dll
)
g++ -I"C:/Program Files/Hopsan/HopsanCore/include" -fPIC -w -Wl,--rpath,"C:/Users/petkr14/Git/development-libraries/ActivityDiagramLib/ActivityDiagram" -DHOPSAN_BUILD_TYPE_RELEASE -DHOPSANCORE_DLLIMPORT -std=c++11  ActivityDiagramLib.cc -L"C:/Program Files/Hopsan/bin" -L"C:/Program Files/Hopsan/lib" -lhopsancore  -shared -o ActivityDiagramLib.dll
