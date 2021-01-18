#pragma once
#include "../util/config_reader.h"
class ServerCore
{
public:
	ServerCore();
	~ServerCore();

	void tick();
	void initialize();
};
