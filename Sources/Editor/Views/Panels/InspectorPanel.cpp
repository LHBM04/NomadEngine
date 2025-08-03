#include "InspectorPanel.h"
#include <imgui.h>

namespace NomadEngine::Editor
{
    InspectorPanel::InspectorPanel()
        : EditorPanelBase("Inspector")
        , mHasSelectedObject(true) // 임시로 true 설정
        , mSelectedObjectName("Player")
    {
    }

    void InspectorPanel::OnUpdate(float /*deltaTime*/)
    {
        // 선택된 오브젝트 정보 업데이트
    }

    void InspectorPanel::RenderContent()
    {
        if (!mHasSelectedObject)
        {
            ImGui::Text("No object selected");
            return;
        }

        // 오브젝트 이름
        ImGui::Text("Object: %s", mSelectedObjectName.c_str());
        ImGui::Separator();

        // 컴포넌트들 렌더링
        RenderTransformComponent();
        RenderMeshRendererComponent();
        RenderColliderComponent();

        // 컴포넌트 추가 버튼
        ImGui::Separator();
        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            if (ImGui::MenuItem("Mesh Renderer")) { /* TODO */ }
            if (ImGui::MenuItem("Box Collider")) { /* TODO */ }
            if (ImGui::MenuItem("Rigidbody")) { /* TODO */ }
            if (ImGui::MenuItem("Audio Source")) { /* TODO */ }
            ImGui::EndPopup();
        }
    }

    void InspectorPanel::RenderTransformComponent()
    {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::PushItemWidth(-1);
            
            ImGui::Text("Position");
            ImGui::DragFloat3("##Position", mPosition, 0.1f);
            
            ImGui::Text("Rotation");
            ImGui::DragFloat3("##Rotation", mRotation, 1.0f, -180.0f, 180.0f);
            
            ImGui::Text("Scale");
            ImGui::DragFloat3("##Scale", mScale, 0.1f, 0.1f, 10.0f);
            
            ImGui::PopItemWidth();
        }
    }

    void InspectorPanel::RenderMeshRendererComponent()
    {
        if (ImGui::CollapsingHeader("Mesh Renderer"))
        {
            static int currentMesh = 0;
            const char* meshes[] = { "Cube", "Sphere", "Plane", "Cylinder" };
            ImGui::Combo("Mesh", &currentMesh, meshes, IM_ARRAYSIZE(meshes));
            
            static int currentMaterial = 0;
            const char* materials[] = { "Default", "Metal", "Wood", "Stone" };
            ImGui::Combo("Material", &currentMaterial, materials, IM_ARRAYSIZE(materials));
            
            static bool castShadows = true;
            ImGui::Checkbox("Cast Shadows", &castShadows);
            
            static bool receiveShadows = true;
            ImGui::Checkbox("Receive Shadows", &receiveShadows);
        }
    }

    void InspectorPanel::RenderColliderComponent()
    {
        if (ImGui::CollapsingHeader("Box Collider"))
        {
            static bool isTrigger = false;
            ImGui::Checkbox("Is Trigger", &isTrigger);
            
            static float center[3] = {0.0f, 0.0f, 0.0f};
            ImGui::DragFloat3("Center", center, 0.1f);
            
            static float size[3] = {1.0f, 1.0f, 1.0f};
            ImGui::DragFloat3("Size", size, 0.1f, 0.1f, 10.0f);
            
            if (ImGui::Button("Remove Component"))
            {
                // TODO: 컴포넌트 제거 로직
            }
        }
    }
}
