#include "../Runtime/Application/Application.h"

#include <iostream>

namespace NomadEngine::Runtime
{
     /*Application::Application()
         : mPlatformWindow(nullptr)
         , mRenderBackend(nullptr)
     {

     }

     Application::~Application()
     {

     }

     bool Application::Initialize()
     {
         mPlatformWindow = std::make_unique<PlatformWindow_SDL>(L"Nomad Engine", 1280, 720);
         if (!mPlatformWindow->Initialize())
         {
             std::wcerr << L"Failed to initialize SDL3 window: " << SDL_GetError() << std::endl;
             return false;
         }

         mRenderBackend = std::make_unique<RenderBackend_SDLRenderer>();
         if (!mRenderBackend->Initialize(mPlatformWindow->GetPlatformData()))
         {
             std::wcerr << L"Failed to initialize SDL renderer: " << SDL_GetError() << std::endl;
             return false;
         }

         return true;
     }

     void Application::Run()
     {
         bool mIsRunning = true;
         while (mIsRunning)
         {
             PlatformWindowEvent event;
             while (mPlatformWindow->WaitEvent(event))
             {
                 mPlatformWindow->TranslateEvent(event);
                 HandlePlatformWindowEvent(event);
             }

             mRenderBackend->BeginFrame();
             // TODO: Update and render your game logic here.
             mRenderBackend->EndFrame();
         }

         mRenderBackend->Release();
         mPlatformWindow->Release();
     }*/

}