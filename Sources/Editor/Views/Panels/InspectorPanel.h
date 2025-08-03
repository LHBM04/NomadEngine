#ifndef GUARD_INSPECTORPANEL_H
#define GUARD_INSPECTORPANEL_H

#include "EditorPanelBase.h"

namespace NomadEngine::Editor
{
    /**
     * @brief 인스펙터 패널 - 선택된 오브젝트의 속성을 표시/편집
     */
    class InspectorPanel : public EditorPanelBase
    {
    public:
        InspectorPanel();
        virtual ~InspectorPanel() = default;

    protected:
        void RenderContent() override;
        void OnUpdate(float deltaTime) override;

    private:
        void RenderTransformComponent();
        void RenderMeshRendererComponent();
        void RenderColliderComponent();
        
        // 임시 선택된 오브젝트 데이터
        bool mHasSelectedObject;
        std::string mSelectedObjectName;
        
        // 임시 Transform 데이터
        float mPosition[3] = {0.0f, 0.0f, 0.0f};
        float mRotation[3] = {0.0f, 0.0f, 0.0f};
        float mScale[3] = {1.0f, 1.0f, 1.0f};
    };
}

#endif
