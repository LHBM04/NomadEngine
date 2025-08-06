#ifndef RUNTIME_IDISPLAYSERVER_H
#define RUNTIME_IDISPLAYSERVER_H

namespace NomadEngine::Runtime
{
    /**
     * @interface IDisplayServer
     */
    class DisplayeServer
    {
    public:
        /**
         * @brief 소멸자.
         */
        virtual ~IDisplayServer();
    }; // IDisplayServer
} // namespace NomadEngine::Runtime

#endif // #ifndef RUNTIME_IDISPLAYSERVER_H