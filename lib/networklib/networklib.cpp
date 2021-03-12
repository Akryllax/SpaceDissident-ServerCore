#include "networklib.h"

//more about this in reference 1
#define DLLExport __declspec(dllexport) // export DLL information
#define DLLImport __declspec(dllimport) // import DLL information

NetworkShared::NetworkInterface::NetworkInterface()
{

}

NetworkShared::NetworkInterface::~NetworkInterface()
{

}

NetworkShared::NetworkSession::NetworkSession()
{

}

NetworkShared::NetworkSession::~NetworkSession()
{

}

int NetworkShared::NetworkInterface::testFunction()
{
    return 5;
}