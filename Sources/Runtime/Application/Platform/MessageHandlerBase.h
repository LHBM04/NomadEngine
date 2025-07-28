#ifndef GUARD_MESSAGEHANDLERBASE_H
#define GUARD_MESSAGEHANDLERBASE_H

#include "../Runtime/Application/Platform/PlatformWindowEvent.h"

/**
 * @class MessageHandlerBase
 *
 * @brief 타입에 따른 메시지를 처리하는 동작을 정의합니다.
 */
class MessageHandlerBase
{
public:
    /**
     * @brief 소멸자.
     */
    virtual ~MessageHandlerBase() = default;

 /**
  * @brief 메시지를 처리합니다.
  *
  * @param message_ 처리할 메시지.
  *
  * @return bool 처리되었다면 true, 아니라면 false를 반환합니다.
  */
    virtual bool HandleMessage(const Message& message_) = 0;

};

#endif // !GUARD_MESSAGEHANDLERBASE_H
