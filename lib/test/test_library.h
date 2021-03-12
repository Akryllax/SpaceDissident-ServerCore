#pragma once

//more about this in reference 1
#define DLLExport __declspec(dllexport) // export DLL information
#define DLLImport __declspec(dllimport) // import DLL information

class DLLExport TestLibrary
{
public:
   TestLibrary(void);
   ~TestLibrary(void);

   void hello();
   static void helloStatic();
};