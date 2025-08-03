#include "../Rendering/RenderingServer_DX12.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <directx/d3d12.h>
#include <directx/d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <stdexcept>

// Helper function for acquiring the first available hardware adapter that supports Direct3D 12.
// If no such adapter can be found, *ppAdapter will be set to nullptr.
_Use_decl_annotations_
void GetHardwareAdapter(
    IDXGIFactory1* pFactory,
    IDXGIAdapter1** ppAdapter)
{
    *ppAdapter = nullptr;
    for (UINT adapterIndex = 0; ; ++adapterIndex)
    {
        IDXGIAdapter1* pAdapter = nullptr;
        if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, &pAdapter))
        {
            // No more adapters to enumerate.
            break;
        }

        // Check to see if the adapter supports Direct3D 12, but don't create the
        // actual device yet.
        if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr)))
        {
            *ppAdapter = pAdapter;
            return;
        }
        pAdapter->Release();
    }
}

namespace NomadEngine::Runtime
{
    RenderingServer_DX12::RenderingServer_DX12()
        : mFrameIndex(0)
        , mRTVDescriptorSize(0)
        , mFenceValue(0)
        , mFenceEvent(nullptr)
        , mViewport()
        , mScissorRect()
    {
        // Constructor implementation
    }

    RenderingServer_DX12::~RenderingServer_DX12()
    {
        Finalize();
    }

    bool RenderingServer_DX12::Initialize(const RenderingServerDescriptor& descriptor_)
    {
        mViewport = { 0.0f, 0.0f, static_cast<float>(descriptor_.Width), static_cast<float>(descriptor_.Height), 0.0f, 1.0f };
        mScissorRect = { 0, 0, static_cast<LONG>(descriptor_.Width), static_cast<LONG>(descriptor_.Height) };

        UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
        // Enable the debug layer (requires the Graphics Tools "optional feature").
        // NOTE: Enabling the debug layer after device creation will invalidate the active device.
        {
            Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
            {
                debugController->EnableDebugLayer();

                // Enable additional debug layers.
                dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
            }
        }
#endif

        Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
        if (FAILED(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory))))
        {
            return false;
        }

        if (!mCreateDevice(factory.Get())) return false;
        if (!mCreateCommandQueue()) return false;
        if (!mCreateSwapChain(factory.Get(), descriptor_)) return false;
        if (!mCreateDescriptorHeaps()) return false;
        if (!mCreateFrameResources()) return false;
        if (!mCreateCommandList()) return false;
        if (!mCreateSyncObjects()) return false;

        return true;
    }

    void RenderingServer_DX12::PreRender()
    {
        mCommandAllocator->Reset();

        mCommandList->Reset(mCommandAllocator.Get(), nullptr);

        auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(mRenderTargets[mFrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        mCommandList->ResourceBarrier(1, &barrier);

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRTVHeap->GetCPUDescriptorHandleForHeapStart(), mFrameIndex, mRTVDescriptorSize);
        mCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

        const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        mCommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    }

    void RenderingServer_DX12::PostRender()
    {
        CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(mRenderTargets[mFrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        mCommandList->ResourceBarrier(1, &barrier);

        mCommandList->Close();

        ID3D12CommandList* ppCommandLists[] = { mCommandList.Get() };
        mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

        mSwapChain->Present(1, 0);

        mWaitForPreviousFrame();
    }

    bool RenderingServer_DX12::Finalize()
    {
        mWaitForPreviousFrame();

        CloseHandle(mFenceEvent);

        return true;
    }

    void RenderingServer_DX12::mWaitForPreviousFrame()
    {
        const UINT64 fence = mFenceValue;
        mCommandQueue->Signal(mFence.Get(), fence);
        mFenceValue++;

        if (mFence->GetCompletedValue() < fence)
        {
            mFence->SetEventOnCompletion(fence, mFenceEvent);
            WaitForSingleObject(mFenceEvent, INFINITE);
        }

        mFrameIndex = mSwapChain->GetCurrentBackBufferIndex();
    }

    bool RenderingServer_DX12::mCreateDevice(IDXGIFactory4* factory)
    {
        Microsoft::WRL::ComPtr<IDXGIAdapter1> hardwareAdapter;
        GetHardwareAdapter(factory, &hardwareAdapter);

        if (FAILED(D3D12CreateDevice(
            hardwareAdapter.Get(),
            D3D_FEATURE_LEVEL_12_0,
            IID_PPV_ARGS(&mDevice)
        )))
        {
            // TODO: Fallback to WARP device.
            return false;
        }
        return true;
    }

    bool RenderingServer_DX12::mCreateCommandQueue()
    {
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        return SUCCEEDED(mDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCommandQueue)));
    }

    bool RenderingServer_DX12::mCreateSwapChain(IDXGIFactory4* factory, const RenderingServerDescriptor& descriptor)
    {
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.BufferCount = FrameCount;
        swapChainDesc.Width = descriptor.Width;
        swapChainDesc.Height = descriptor.Height;
        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.SampleDesc.Count = 1;

        Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
        if (FAILED(factory->CreateSwapChainForHwnd(
            mCommandQueue.Get(),
            reinterpret_cast<HWND>(descriptor.Hwnd),
            &swapChainDesc,
            nullptr,
            nullptr,
            &swapChain
        )))
        {
            return false;
        }

        if (FAILED(factory->MakeWindowAssociation(reinterpret_cast<HWND>(descriptor.Hwnd), DXGI_MWA_NO_ALT_ENTER)))
        {
            return false;
        }

        if (FAILED(swapChain.As(&mSwapChain)))
        {
            return false;
        }

        mFrameIndex = mSwapChain->GetCurrentBackBufferIndex();
        return true;
    }

    bool RenderingServer_DX12::mCreateDescriptorHeaps()
    {
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = FrameCount;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(mDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRTVHeap))))
        {
            return false;
        }

        mRTVDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        return true;
    }

    bool RenderingServer_DX12::mCreateFrameResources()
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRTVHeap->GetCPUDescriptorHandleForHeapStart());

        for (UINT n = 0; n < FrameCount; n++)
        {
            if (FAILED(mSwapChain->GetBuffer(n, IID_PPV_ARGS(&mRenderTargets[n]))))
            {
                return false;
            }
            mDevice->CreateRenderTargetView(mRenderTargets[n].Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, mRTVDescriptorSize);
        }
        return true;
    }

    bool RenderingServer_DX12::mCreateCommandList()
    {
        if (FAILED(mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCommandAllocator))))
        {
            return false;
        }

        if (FAILED(mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&mCommandList))))
        {
            return false;
        }

        return SUCCEEDED(mCommandList->Close());
    }

    bool RenderingServer_DX12::mCreateSyncObjects()
    {
        if (FAILED(mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence))))
        {
            return false;
        }
        mFenceValue = 1;

        mFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (mFenceEvent == nullptr)
        {
            return FAILED(HRESULT_FROM_WIN32(GetLastError()));
        }

        return true;
    }
} // namespace NomadEngine::Runtime