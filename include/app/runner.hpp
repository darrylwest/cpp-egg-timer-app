#pragma once

#include <memory>
#include <string>

namespace app::eggtimer {

    class IRunner {
      public:
        virtual ~IRunner() = default;
        virtual void run() = 0;
    };

    class DefaultTimerRunner : public IRunner {
      public:
        explicit DefaultTimerRunner(int total_seconds);
        void run() override;

      private:
        int m_total_seconds;
    };

    class CustomCommandRunner : public IRunner {
      public:
        explicit CustomCommandRunner(int total_seconds, const std::string& command);
        void run() override;

      private:
        int m_total_seconds;
        std::string m_command;
    };

}  // namespace app::eggtimer
