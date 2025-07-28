namespace NomadEngine::Runtime
{
    void MessageDispatcher::AddHandler(MessageHandlerBase *handler_)
    {
        mHandlers.emplace_back(handler_);
    }

    inline void MessageDispatcher::Dispatch(const Message &message_)
    {
        for (MessageHandlerBase*& handler : mHandlers)
        {
            if (handler->HandleMessage(message_))
            {
                break;
            }
        }
    }

}