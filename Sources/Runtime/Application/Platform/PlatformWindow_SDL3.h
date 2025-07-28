        /**
         * @brief SDL3 윈도우 핸들을 반환합니다.
         */
        [[nodiscard]]
        virtual WindowHandle GetWindowHandle() const override;

        /**
         * @brief SDL3 메시지를 처리합니다.
         */
        virtual bool ProcessMessages() override;

    protected:
        /**
         * @brief SDL3 네이티브 이벤트를 PlatformWindowEvent로 변환합니다.
         */
        virtual PlatformWindowEvent ConvertNativeEvent(void* nativeEvent) override;

    private:
        /**
         * @brief SDL3 이벤트를 PlatformWindowEvent로 변환합니다.
         */
        PlatformWindowEvent ConvertSDLEvent(const SDL_Event& event);
