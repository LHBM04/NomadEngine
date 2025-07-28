#ifndef GUARD_MESSAGEDISPATCHER_H
#define GUARD_MESSAGEDISPATCHER_H

#include <algorithm>
#include <vector>

#include "../Runtime/Application/Platform/Message.h"
#include "../Runtime/Application/Platform/MessageHandlerBase.h"

class MessageHandlerBase;

namespace NomadEngine::Runtime
{
    /**
     * @class MessageDispatcher
     *
     * @brief 메시지 디스패처 클래스입니다.
     */
    class MessageDispatcher
    {
    public:
        /**
         * @brief 생성자.
         */
        MessageDispatcher() = default;

        /**
         * @brief 소멸자.
         */
        virtual ~MessageDispatcher() = default;

        /**
         * @brief 메시지 핸들러를 추가합니다.
         */
        void __inline AddHandler(MessageHandlerBase* handler_);

        /**
         * @brief 메시지를 디스패치합니다.
         */
        void __inline Dispatch(const Message& message_);

    private:
        /**
         * @brief 메시지 핸들러 목록.
         */
        std::vector<MessageHandlerBase*> mHandlers;

    };
}

#endif // !GUARD_MESSAGEDISPATCHER_H

#include "../Runtime/Application/Platform/MessageDispatcher.inl"
