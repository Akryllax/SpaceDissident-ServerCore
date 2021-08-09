#ifndef SERVER_CORE_MODULE_H_
#define SERVER_CORE_MODULE_H_

class ServerCore;

class ServerCoreModule
{
public:
    virtual void onInitialize(const ServerCore &coreRef){};
    virtual void onConfig(const ServerCore &coreRef){};
    virtual void onTick(const ServerCore &coreRef){};
};

#endif /* SERVER_CORE_MODULE_H_ */