

#include "base_decorator.h"
#include "deco_id.h"
#include "spdlog/spdlog.h"

const uint16_t BaseDecorator::DECO_ID = DECO_ID_BASE;

BaseDecorator::BaseDecorator()
{
  this->initialize();
};

void BaseDecorator::initialize()
{
  spdlog::trace("Creating new BaseDecorator");
}

/**
 * BaseDecorator
 *  Use to implement actions into visitors. Only *real* way to implement functionality into the network stack.
 * @param  {BaseMessage} msg : Const reference to owning message object.
 */
void BaseDecorator::visit(const BaseMessage& msg)
{
  //Base decorator does nothing
}