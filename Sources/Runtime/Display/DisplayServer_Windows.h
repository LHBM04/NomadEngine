#ifndef GUARD_DISPLAYSERVER_WINDOWS_H
#define GUARD_DISPLAYSERVER_WINDOWS_H

#include "../Display/IDisplayServer.h"
#include "../Display/DisplayServerDescriptor.h"

#include <string>

struct HWND__;
struct HINSTANCE__;

namespace NomadEngine::Runtime
{
    class DisplayServer_Windows
        : public IDisplayServer
    {
    public:
        /**
         * @brief 생성자.
         */
        DisplayServer_Windows();

        /**
         * @brief 소멸자.
         */
        virtual ~DisplayServer_Windows() override;

        /**
         * @brief 디스플레이 서버를 초기화합니다.
         *
         * @param descriptor_ 디스플레이 서버의 설정 기술.
         *
         * @return bool 성공 여부.
         */
        virtual bool Initialize(const DisplayServerDescriptor& descriptor_) override;

        /**
         * @brief 디스플레이 서버를 종료합니다.
         *
         * @return bool 성공 여부.
         */
        virtual bool Finalize() override;

        /**
         * @brief 창 핸들을 반환합니다.
         * @return HWND__* 창 핸들.
         */
        HWND__* GetWindowHandle() const;

    private:
        /**
         * @brief Window Procedure 함수.
         */
        static long long __stdcall WindowProc(HWND__* hwnd, unsigned int msg, unsigned long long wParam, long long lParam);

        HWND__* mWindow;
        HINSTANCE__* m_hinstance;
        std::string m_windowClassName;
    };
}

#endif // !GUARD_DISPLAYSERVER_WINDOWS_H
