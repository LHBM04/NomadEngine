#ifndef GUARD_DISPLAYSERVERDESCRIPTOR_H
#define GUARD_DISPLAYSERVERDESCRIPTOR_H

namespace NomadEngine::Runtime
{
    /**
     * @struct DisplayServerDescriptor
     *
     * @brief 디스플레이 서버의 설정을 기술합니다.
     */
    struct DisplayServerDescriptor
    {
        const char* title;  // 이름.
        int x;              // X 좌표.
        int y;              // Y 좌표.
        int width;          // 너비.
        int height;         // 높이.
        bool fullscreen;    // 전체 화면 모드 여부.
        bool vsync;         // VSync 활성화 여부.
        bool resizable;     // 창 크기 조절 가능 여부.
        bool borderless;    // 테두리 없는 창 여부.
    };
}

#endif // !GUARD_DISPLAYSERVERDESCRIPTOR_H
