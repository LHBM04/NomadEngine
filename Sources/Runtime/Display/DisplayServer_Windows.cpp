#include "../Runtime/Display/DisplayServer_Windows.h"

namespace NomadEngine::Runtime
{
    DisplayServer_Windows::DisplayServer_Windows()
        : mWindowHandle(nullptr)
    {

    }

    DisplayServer_Windows::~DisplayServer_Windows()
    {
        DisplayServer_Windows::Finalize();
    }
} // nnamespace NomadEngine::Runtime