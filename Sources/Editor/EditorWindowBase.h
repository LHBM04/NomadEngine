#ifndef EDITORWINDOWBASE_H
#define EDITORWINDOWBASE_H

class EditorWindowBase
{
public:
    /**
     * @brief 생성자.
     */
    EditorWindowBase();

    /**
     * @brief 소멸자.
     */
    virtual ~EditorWindowBase();

    virtual void Intialize() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
};

#endif //EDITORWINDOWBASE_H
