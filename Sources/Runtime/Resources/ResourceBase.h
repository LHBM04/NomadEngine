#ifndef RESOURCEBASE_H
#define RESOURCEBASE_H

#include <string>
#include <string_view>

class ResourceBase
{
public:
    /**
     * @brief 생성자.
     */
    ResourceBase();

    /**
     * @brief 소멸자.
     */
    virtual ~ResourceBase();

    /**
     * @brief
     *
     * @param fileName
     * @param filePath
     *
     * @return
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

#endif //RESOURCEBASE_H
