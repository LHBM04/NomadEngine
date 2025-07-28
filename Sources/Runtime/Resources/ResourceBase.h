#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>
#include <string_view>

namespace NomadEngine::Runtime
{
    /**
     * @class ResourceBase
     *
     * @brief 리소스.
     */
    class ResourceBase
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~ResourceBase();

        /**
         * @brief 리소스를 로드합니다.
         *
         * @param fileName 리소스 이름.
         * @param filePath 리소스 경로.
         *
         * @return bool 성공하면 true, 실패하면 false를 반환합니다.
         */
        virtual bool Load(
            std::string_view fileName,
            std::string_view filePath) = 0;

    private:
        /**
         * @brief 해당 리소스의 이름.
         */
        std::wstring name;

        /**
         * @brief 해당 리소스의 위치.
         */
        std::wstring path;

    };

}

#endif //RESOURCEBASE_H
