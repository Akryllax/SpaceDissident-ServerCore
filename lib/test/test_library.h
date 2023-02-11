#pragma once

#ifdef _WIN32
//more about this in reference 1
#define DLLExport __declspec(dllexport) // export DLL information
#define DLLImport __declspec(dllimport) // import DLL information
#elif __linux__
#define DLLExport
#define DLLImport
#endif

class DLLExport TestLibrary
{
public:
  TestLibrary(void);
  ~TestLibrary(void);

  void hello();
  static void helloStatic();
};