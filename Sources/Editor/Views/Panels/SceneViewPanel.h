#ifndef GUARD_SCENEVIEWPANEL_H
#define GUARD_SCENEVIEWPANEL_H

#include "EditorPanelBase.h"

namespace NomadEngine::Editor
{
    /**
     * @brief 씬 뷰 패널 - 3D 씬을 표시
     */
    class SceneViewPanel : public EditorPanelBase
    {
    public:
        SceneViewPanel();
        virtual ~SceneViewPanel() = default;

        bool Initialize() override;

    protected:
        void RenderContent() override;
        void OnUpdate(float deltaTime) override;

    private:
        // 렌더 타겟 텍스처 ID (OpenGL)
        unsigned int mFramebuffer;
        unsigned int mColorTexture;
        unsigned int mDepthTexture;
        int mViewportWidth;
        int mViewportHeight;
    };
}

#endif
