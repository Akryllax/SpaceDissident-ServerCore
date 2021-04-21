#pragma once

#ifdef _WIN32
//more about this in reference 1
#define DLLExport __declspec(dllexport) // export DLL information
#define DLLImport __declspec(dllimport) // import DLL information
#elif __linux__
#define DLLExport
#define DLLImport
#endif

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
