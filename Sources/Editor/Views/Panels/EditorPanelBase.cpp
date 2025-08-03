#include "EditorPanelBase.h"
#include <imgui.h>
#include <iostream>

namespace NomadEngine::Editor
{
    EditorPanelBase::EditorPanelBase(const std::string& name)
        : mName(name)
        , mVisible(true)
        , mInitialized(false)
    {
    }

    bool EditorPanelBase::Initialize()
    {
        if (mInitialized)
            return true;

        std::cout << "Initializing panel: " << mName << std::endl;
        mInitialized = true;
        return true;
    }

    void EditorPanelBase::Update(float deltaTime)
    {
        if (!mInitialized || !mVisible)
            return;

        OnUpdate(deltaTime);
    }

    void EditorPanelBase::Render()
    {
        if (!mInitialized || !mVisible)
            return;

        // ImGui 윈도우 시작
        if (ImGui::Begin(mName.c_str(), &mVisible))
        {
            RenderContent();
        }
        ImGui::End();
    }

    void EditorPanelBase::Finalize()
    {
        if (!mInitialized)
            return;

        std::cout << "Finalizing panel: " << mName << std::endl;
        mInitialized = false;
    }
}
