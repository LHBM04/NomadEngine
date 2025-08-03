#ifndef GUARD_RENDERSYSTEM_WINDOWS_H
#define GUARD_RENDERSYSTEM_WINDOWS_H

#include <wrl.h>

#include "../Rendering/IRenderingServer.h"
#include "../Rendering/RenderingServerDescriptor.h"

// Forward declarations
struct IDXGIFactory7;
struct IDXGIAdapter4;
struct ID3D12Device;
struct ID3D12CommandQueue;
struct IDXGISwapChain4;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12Fence1;
struct D3D12_VIEWPORT;
struct D3D12_RECT;
typedef void* HANDLE;

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

        static constexpr UINT FrameCount = 2;

        // Pipeline objects.
        Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
        Microsoft::WRL::ComPtr<IDXGISwapChain4> mSwapChain;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRTVHeap;
        Microsoft::WRL::ComPtr<ID3D12Resource> mRenderTargets[FrameCount];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCommandAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;
        UINT mRTVDescriptorSize;

        UINT mFrameIndex;
        HANDLE mFenceEvent;
        Microsoft::WRL::ComPtr<ID3D12Fence1> mFence;
        UINT64 mFenceValue;

        D3D12_VIEWPORT mViewport;
        D3D12_RECT mScissorRect;
    };
}

#endif // !GUARD_RENDERSYSTEM_WINDOWS_H
