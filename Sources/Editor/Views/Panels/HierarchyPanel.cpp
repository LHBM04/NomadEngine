#include "HierarchyPanel.h"
#include <imgui.h>

namespace NomadEngine::Editor
{
    HierarchyPanel::HierarchyPanel()
        : EditorPanelBase("Hierarchy")
        , mSelectedObjectIndex(-1)
    {
        // 임시 씬 오브젝트 데이터
        mSceneObjects = {
            "Main Camera",
            "Directional Light",
            "Player",
            "  Player Mesh",
            "  Player Collider",
            "Environment",
            "  Terrain",
            "  Trees",
            "    Tree_001",
            "    Tree_002",
            "    Tree_003",
            "UI Canvas",
            "  Health Bar",
            "  Minimap"
        };
    }

    void HierarchyPanel::OnUpdate(float /*deltaTime*/)
    {
        // 계층 구조 업데이트 로직
    }

    void HierarchyPanel::RenderContent()
    {
        // 씬 오브젝트 목록 표시
        for (int i = 0; i < mSceneObjects.size(); ++i)
        {
            const std::string& objectName = mSceneObjects[i];
            
            // 들여쓰기 계산
            int depth = 0;
            size_t pos = 0;
            while (pos < objectName.length() && objectName[pos] == ' ')
            {
                depth++;
                pos += 2; // 2칸씩 들여쓰기
            }
            
            std::string displayName = objectName.substr(pos);
            
            // 들여쓰기 적용
            if (depth > 0)
            {
                ImGui::Indent(static_cast<float>(depth * 10));
            }
            
            // 선택 가능한 항목으로 표시
            bool isSelected = (mSelectedObjectIndex == i);
            if (ImGui::Selectable(displayName.c_str(), isSelected))
            {
                mSelectedObjectIndex = i;
            }
            
            // 우클릭 컨텍스트 메뉴
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete"))
                {
                    // TODO: 오브젝트 삭제 로직
                }
                if (ImGui::MenuItem("Duplicate"))
                {
                    // TODO: 오브젝트 복제 로직
                }
                if (ImGui::MenuItem("Rename"))
                {
                    // TODO: 오브젝트 이름 변경 로직
                }
                ImGui::EndPopup();
            }
            
            // 들여쓰기 해제
            if (depth > 0)
            {
                ImGui::Unindent(static_cast<float>(depth * 10));
            }
        }
        
        // 빈 공간 우클릭으로 새 오브젝트 생성
        if (ImGui::BeginPopupContextWindow("HierarchyContext"))
        {
            if (ImGui::MenuItem("Create Empty"))
            {
                // TODO: 빈 오브젝트 생성
            }
            if (ImGui::BeginMenu("3D Object"))
            {
                if (ImGui::MenuItem("Cube")) { /* TODO */ }
                if (ImGui::MenuItem("Sphere")) { /* TODO */ }
                if (ImGui::MenuItem("Plane")) { /* TODO */ }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Light"))
            {
                if (ImGui::MenuItem("Directional Light")) { /* TODO */ }
                if (ImGui::MenuItem("Point Light")) { /* TODO */ }
                if (ImGui::MenuItem("Spot Light")) { /* TODO */ }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }
    }
}
