#include "../Runtime/Application/Application.h"

#include <iostream>

#include "Platform/PlatformWindow_SDL.h"
#include "Backends/RenderBackend_SDLRenderer.h"

namespace NomadEngine::Runtime
{
     Application::Application()
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
         while (true)
         {
             WindowEvent event = { };
             if (mPlatformWindow->WaitEvent(&event))
             {
                 mPlatformWindow->TranslateEvent(&event);
                 mPlatformWindow->DispatchEvent(event);

             }
             else
             {
                 mRenderBackend->BeginFrame();
                 // TODO: Update and render your game logic here.
                 mRenderBackend->EndFrame();

             }
         }

     }

}