#include "SceneViewPanel.h"
#include <imgui.h>
#include <GL/glew.h>
#include <iostream>

namespace NomadEngine::Editor
{
    SceneViewPanel::SceneViewPanel()
        : EditorPanelBase("Scene View")
        , mFramebuffer(0)
        , mColorTexture(0)
        , mDepthTexture(0)
        , mViewportWidth(800)
        , mViewportHeight(600)
    {
    }

    bool SceneViewPanel::Initialize()
    {
        if (!EditorPanelBase::Initialize())
            return false;

        // 프레임버퍼 생성
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

        // 컬러 텍스처 생성
        glGenTextures(1, &mColorTexture);
        glBindTexture(GL_TEXTURE_2D, mColorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mViewportWidth, mViewportHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexture, 0);

        // 깊이 텍스처 생성
        glGenTextures(1, &mDepthTexture);
        glBindTexture(GL_TEXTURE_2D, mDepthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mViewportWidth, mViewportHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0);

        // 프레임버퍼 완성도 확인
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "Scene View framebuffer is not complete!" << std::endl;
            return false;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        std::cout << "Scene View Panel initialized successfully" << std::endl;
        return true;
    }

    void SceneViewPanel::OnUpdate(float /*deltaTime*/)
    {
        // 씬 업데이트 로직
    }

    void SceneViewPanel::RenderContent()
    {
        // 뷰포트 크기 가져오기
        ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();
        
        if (contentRegionAvail.x != mViewportWidth || contentRegionAvail.y != mViewportHeight)
        {
            // 뷰포트 크기 변경 시 텍스처 재생성
            mViewportWidth = static_cast<int>(contentRegionAvail.x);
            mViewportHeight = static_cast<int>(contentRegionAvail.y);
            
            if (mViewportWidth > 0 && mViewportHeight > 0)
            {
                // 컬러 텍스처 재생성
                glBindTexture(GL_TEXTURE_2D, mColorTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mViewportWidth, mViewportHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                
                // 깊이 텍스처 재생성
                glBindTexture(GL_TEXTURE_2D, mDepthTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mViewportWidth, mViewportHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            }
        }

        // 씬 렌더링을 프레임버퍼에 수행
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
        glViewport(0, 0, mViewportWidth, mViewportHeight);
        
        // 배경 클리어
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // TODO: 실제 씬 렌더링 로직 추가
        // RenderScene();
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // ImGui에 텍스처 표시
        if (mViewportWidth > 0 && mViewportHeight > 0)
        {
            ImGui::Image(
                static_cast<ImTextureID>(mColorTexture),
                ImVec2(static_cast<float>(mViewportWidth), static_cast<float>(mViewportHeight)),
                ImVec2(0, 1), // UV 좌표 (OpenGL은 Y축이 뒤집힘)
                ImVec2(1, 0)
            );
        }
    }
}
