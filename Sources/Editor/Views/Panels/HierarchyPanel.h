#ifndef GUARD_HIERARCHYPANEL_H
#define GUARD_HIERARCHYPANEL_H

#include "EditorPanelBase.h"
#include <vector>
#include <string>

namespace NomadEngine::Editor
{
    /**
     * @brief 계층 구조 패널 - 씬 오브젝트 트리를 표시
     */
    class HierarchyPanel : public EditorPanelBase
    {
    public:
        HierarchyPanel();
        virtual ~HierarchyPanel() = default;

    protected:
        void RenderContent() override;
        void OnUpdate(float deltaTime) override;

    private:
        void RenderSceneNode(const std::string& nodeName, int depth = 0);
        
        // 임시 씬 데이터
        std::vector<std::string> mSceneObjects;
        int mSelectedObjectIndex;
    };
}

#endif
