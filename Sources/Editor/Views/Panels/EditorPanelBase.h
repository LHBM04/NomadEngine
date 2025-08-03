#pragma once

#include "IEditorPanel.h"

namespace NomadEngine::Editor
{
    /**
     * @brief 에디터 패널 기본 구현
     */
    class EditorPanelBase : public IEditorPanel
    {
    public:
        explicit EditorPanelBase(const std::string& name);
        virtual ~EditorPanelBase() = default;

        bool Initialize() override;
        void Update(float deltaTime) override;
        void Render() override;
        void Finalize() override;

        const std::string& GetName() const override { return mName; }
        bool IsVisible() const override { return mVisible; }
        void SetVisible(bool visible) override { mVisible = visible; }

    protected:
        /**
         * @brief 실제 패널 내용을 렌더링합니다.
         * 하위 클래스에서 구현해야 합니다.
         */
        virtual void RenderContent() = 0;

        /**
         * @brief 패널별 업데이트 로직을 구현합니다.
         * 필요한 경우 하위 클래스에서 오버라이드합니다.
         */
        virtual void OnUpdate(float /*deltaTime*/) {}

    private:
        std::string mName;
        bool mVisible;
        bool mInitialized;
    };
}
