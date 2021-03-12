#pragma once

//more about this in reference 1
#define DLLExport __declspec(dllexport) // export DLL information
#define DLLImport __declspec(dllimport) // import DLL information

namespace NetworkShared
{
    class DLLExport NetworkInterface
    {
        public:
        NetworkInterface();
        ~NetworkInterface();

        int testFunction();
    };

    class DLLExport NetworkSession
    {
        protected:
        NetworkSession();
        ~NetworkSession();
    };
} // namespace NetworkShared
