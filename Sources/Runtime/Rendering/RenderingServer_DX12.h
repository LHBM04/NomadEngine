#ifndef GUARD_RENDERSYSTEM_WINDOWS_H
#define GUARD_RENDERSYSTEM_WINDOWS_H

#include <d3d12.h>
#include <d3dx12.h>
#include <wrl.h>
#include <windows.h>

#include "../Common/Defines.h"
#include "../Common/Types.h"
#include "../Rendering/IRenderingServer.h"
#include "../Rendering/RenderingServerDescriptor.h"

namespace NomadEngine::Runtime
{
    /**
     * @class RenderingServer_DX12
     *
     * @brief Windows 플랫폼을 위한 렌더링 시스템을 정의합니다.
     */
    class RenderingServer_DX12
        : public IRenderingServer
    {
    public:
        /**
         * @brief 생성자.
         */
        RenderingServer_DX12();

        /**
         * @brief 소멸자.
         */
        virtual ~RenderingServer_DX12() override;

        /**
         * @brief 렌더링 시스템을 초기화합니다.
         *
         * @param descriptor_ 렌더링 시스템 초기화 설정.
         *
         * @return bool 성공 여부.
         */
        virtual bool Initialize(const RenderingServerDescriptor& descriptor_) override;

        /**
         * @brief 렌더링이 시작되기 전 호출됩니다.
         */
        virtual void PreRender() override;

        /**
         * @brief 렌더링이 종료되기 전 호출됩니다.
         */
        virtual void PostRender() override;

        /**
         * @brief 렌더링 시스템을 종료합니다.
         *
         * @return bool 성공 여부.
         */
        virtual bool Finalize() override;

    private:
        void mGetHardwareAdapter(IDXGIFactory7* pFactory, IDXGIAdapter4** ppAdapter);
        void mWaitForPreviousFrame();

        bool mCreateDevice(IDXGIFactory4* factory);
        bool mCreateCommandQueue();
        bool mCreateSwapChain(IDXGIFactory4* factory, const RenderingServerDescriptor& descriptor);
        bool mCreateDescriptorHeaps();
        bool mCreateFrameResources();
        bool mCreateCommandList();
        bool mCreateSyncObjects();

        static constexpr UInt32 FrameCount = 2;

        Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
        Microsoft::WRL::ComPtr<IDXGISwapChain4> mSwapChain;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRTVHeap;
        Microsoft::WRL::ComPtr<ID3D12Resource> mRenderTargets[FrameCount];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCommandAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
        UInt32 mRTVDescriptorSize;

        UInt32 mFrameIndex;
        HANDLE mFenceEvent;
        Microsoft::WRL::ComPtr<ID3D12Fence1> mFence;
        UInt64 mFenceValue;

        D3D12_VIEWPORT mViewport;
        D3D12_RECT mScissorRect;
    };
}

#endif // !GUARD_RENDERSYSTEM_WINDOWS_H
