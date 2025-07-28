#ifndef GUARD_MESSAGEHANDLERHELPERS_H
#define GUARD_MESSAGEHANDLERHELPERS_H

#include <functional>
#include <unordered_map>
#include "MessageHandlerBase.h"
#include "Message.h"

namespace NomadEngine::Runtime
{
    /**
     * @class TypedMessageHandler
     *
     * @brief 특정 메시지 타입만 처리하는 편의 핸들러 클래스
     */
    class TypedMessageHandler : public MessageHandlerBase
    {
    public:
        /**
         * @brief 생성자
         *
         * @param targetType 처리할 메시지 타입
         * @param handler 메시지 처리 함수
         */
        TypedMessageHandler(Message::EType targetType, std::function<bool(const Message&)> handler)
            : mTargetType(targetType), mHandler(std::move(handler))
        {
        }

        /**
         * @brief 메시지를 처리합니다.
         */
        bool HandleMessage(const Message& message_) override
        {
            if (message_.type == mTargetType && mHandler)
            {
                return mHandler(message_);
            }
            return false;
        }

    private:
        Message::EType mTargetType;
        std::function<bool(const Message&)> mHandler;
    };

    /**
     * @class MultiTypeMessageHandler
     *
     * @brief 여러 메시지 타입을 각각 다른 핸들러로 처리하는 클래스
     */
    class MultiTypeMessageHandler : public MessageHandlerBase
    {
    public:
        /**
         * @brief 특정 타입의 메시지 핸들러를 등록합니다.
         */
        void RegisterHandler(Message::EType type, std::function<bool(const Message&)> handler)
        {
            mHandlers[type] = std::move(handler);
        }

        /**
         * @brief 특정 타입의 핸들러를 제거합니다.
         */
        void UnregisterHandler(Message::EType type)
        {
            mHandlers.erase(type);
        }

        /**
         * @brief 메시지를 처리합니다.
         */
        bool HandleMessage(const Message& message_) override
        {
            auto it = mHandlers.find(message_.type);
            if (it != mHandlers.end() && it->second)
            {
                return it->second(message_);
            }
            return false;
        }

    private:
        std::unordered_map<Message::EType, std::function<bool(const Message&)>> mHandlers;
    };

    /**
     * @brief 키보드 입력 핸들러를 쉽게 만들기 위한 헬퍼 함수들
     */
    namespace InputHelpers
    {
        /**
         * @brief 키 다운 이벤트 핸들러 생성
         */
        inline std::unique_ptr<TypedMessageHandler> CreateKeyDownHandler(
            std::function<bool(int keyCode)> handler)
        {
            return std::make_unique<TypedMessageHandler>(
                Message::EType::KeyDown,
                [handler](const Message& msg) { return handler(msg.keyCode); }
            );
        }

        /**
         * @brief 키 업 이벤트 핸들러 생성
         */
        inline std::unique_ptr<TypedMessageHandler> CreateKeyUpHandler(
            std::function<bool(int keyCode)> handler)
        {
            return std::make_unique<TypedMessageHandler>(
                Message::EType::KeyUp,
                [handler](const Message& msg) { return handler(msg.keyCode); }
            );
        }

        /**
         * @brief 마우스 이동 이벤트 핸들러 생성
         */
        inline std::unique_ptr<TypedMessageHandler> CreateMouseMoveHandler(
            std::function<bool(int x, int y)> handler)
        {
            return std::make_unique<TypedMessageHandler>(
                Message::EType::MouseMove,
                [handler](const Message& msg) { return handler(msg.x, msg.y); }
            );
        }

        /**
         * @brief 마우스 버튼 다운 이벤트 핸들러 생성
         */
        inline std::unique_ptr<TypedMessageHandler> CreateMouseDownHandler(
            std::function<bool(int button, int x, int y)> handler)
        {
            return std::make_unique<TypedMessageHandler>(
                Message::EType::MouseButtonDown,
                [handler](const Message& msg) { return handler(msg.keyCode, msg.x, msg.y); }
            );
        }

        /**
         * @brief 마우스 버튼 업 이벤트 핸들러 생성
         */
        inline std::unique_ptr<TypedMessageHandler> CreateMouseUpHandler(
            std::function<bool(int button, int x, int y)> handler)
        {
            return std::make_unique<TypedMessageHandler>(
                Message::EType::MouseButtonUp,
                [handler](const Message& msg) { return handler(msg.keyCode, msg.x, msg.y); }
            );
        }
    }
}

#endif // !GUARD_MESSAGEHANDLERHELPERS_H
