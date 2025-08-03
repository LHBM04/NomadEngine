#ifndef GUARD_IEDITORPANEL_H
#define GUARD_IEDITORPANEL_H

#include <string>
#include <memory>

namespace NomadEngine::Editor
{
    /**
     * @brief ImGui 기반 에디터 패널 인터페이스
     */
    class IEditorPanel
    {
    public:
        virtual ~IEditorPanel() = default;

        /**
         * @brief 패널을 초기화합니다.
         * @return 성공 시 true
         */
        virtual bool Initialize() = 0;

        /**
         * @brief 패널을 업데이트합니다.
         * @param deltaTime 델타 타임
         */
        virtual void Update(float deltaTime) = 0;

        /**
         * @brief 패널을 렌더링합니다.
         */
        virtual void Render() = 0;

        /**
         * @brief 패널을 해제합니다.
         */
        virtual void Finalize() = 0;

        /**
         * @brief 패널 이름을 반환합니다.
         */
        virtual const std::string& GetName() const = 0;

        /**
         * @brief 패널이 표시되는지 여부를 반환합니다.
         */
        virtual bool IsVisible() const = 0;

        /**
         * @brief 패널 표시 여부를 설정합니다.
         */
        virtual void SetVisible(bool visible) = 0;
    };

    using EditorPanelPtr = std::shared_ptr<IEditorPanel>;
}

#endif
