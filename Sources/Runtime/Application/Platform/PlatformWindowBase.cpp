#include "PlatformWindowBase.h"
#include "PlatformWindowEvent.h"

namespace NomadEngine::Runtime
{
    PlatformWindowBase::PlatformWindowBase(
        std::wstring_view caption_,
        int width_,
        int height_)
        : mCaption(caption_),
          mWidth(width_),
          mHeight(height_),
          mFocused(false)
    {

    }

    PlatformWindowBase::~PlatformWindowBase()
       = default;

    bool PlatformWindowBase::WaitPlatformWindowEvent(PlatformWindowEvent& message_)
    {
        // 큐에서 이벤트를 가져올 때까지 대기
        if (!mWindowEventQueue.empty())
        {
            message_ = mWindowEventQueue.front();
            mWindowEventQueue.pop();
            return true;
        }
        return false;
    }

    bool PlatformWindowBase::PollPlatformWindowEvent(PlatformWindowEvent& message_)
    {
        // 큐에서 이벤트를 즉시 가져오기 (논블로킹)
        if (!mWindowEventQueue.empty())
        {
            message_ = mWindowEventQueue.front();
            mWindowEventQueue.pop();
            return true;
        }
        return false;
    }

    void PlatformWindowBase::TranslatePlatformWindowEvent(const PlatformWindowEvent& message_)
    {
        // 플랫폼별 특수 처리가 필요한 경우 파생 클래스에서 오버라이드
        // 기본적으로는 아무 처리하지 않음
    }

    void PlatformWindowBase::DispatchPlatformWindowEvent(const PlatformWindowEvent& message_)
    {
        // 이벤트를 적절한 핸들러로 디스패치
        // 기본 구현에서는 로그만 출력
        switch (message_.type)
        {
            case PlatformWindowEvent::EType::Quit:
                std::cout << "Quit event received" << std::endl;
                break;
            case PlatformWindowEvent::EType::KeyDown:
                std::cout << "Key down: " << message_.keyCode << std::endl;
                break;
            case PlatformWindowEvent::EType::KeyUp:
                std::cout << "Key up: " << message_.keyCode << std::endl;
                break;
            case PlatformWindowEvent::EType::MouseMove:
                std::cout << "Mouse move: (" << message_.x << ", " << message_.y << ")" << std::endl;
                break;
            case PlatformWindowEvent::EType::MouseButtonDown:
                std::cout << "Mouse down: button " << message_.keyCode << " at (" << message_.x << ", " << message_.y << ")" << std::endl;
                break;
            case PlatformWindowEvent::EType::MouseButtonUp:
                std::cout << "Mouse up: button " << message_.keyCode << " at (" << message_.x << ", " << message_.y << ")" << std::endl;
                break;
            default:
                break;
        }
    }

}