#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Utilities/SingletonBase.h"

namespace NomadEngine::Runtime
{
    /**
     * @class ResourceManager
     *
     * @brief 리소스 관리자의 기본 클래스를 정의합니다.
     */
    class ResourceManager
        : public SingletonBase<ResourceManager>
    {
        
    };
}

#endif //RESOURCEMANAGER_H
