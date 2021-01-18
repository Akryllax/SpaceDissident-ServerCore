#include "base_message.h"
#include <algorithm>
#include "spdlog/spdlog.h"
#include "base_decorator.h"
#include <concepts>
#include "deco_id.h"

const uint16_t deco::BaseDecorator::DECO_ID = DECO_ID_BASE;

BaseMessage::BaseMessage(){
    spdlog::info("Creating new BaseMessage");
};

BaseMessage::~BaseMessage()
{
    std::for_each(this->_decoList.begin(), this->_decoList.end(), [this](deco::BaseDecorator const &deco) {
        // this->removeDecorator(deco);
    });
}

template <>
bool BaseMessage::removeDecorator<deco::BaseDecorator>()
{
    spdlog::info("BaseMessage::removeDecorator");
    auto item = std::find_if(this->_decoList.begin(), this->_decoList.end(), [](auto it) {
        return std::is_base_of<decltype(it), deco::BaseDecorator>();
    });

    bool result = false;
    if (item != this->_decoList.end())
    {
    }

    return result;
};
