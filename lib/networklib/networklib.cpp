#include "networklib.h"

NetworkShared::NetworkInterface::NetworkInterface() { }

NetworkShared::NetworkInterface::~NetworkInterface() { }

NetworkShared::NetworkSession::NetworkSession() { }

NetworkShared::NetworkSession::~NetworkSession() { }

int NetworkShared::NetworkInterface::testFunction()
{
  return 5;
}