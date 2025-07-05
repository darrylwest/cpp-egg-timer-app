#pragma once

#include <app/cli.hpp>
#include <format>

namespace app::eggtimer {

    struct Runner {
        explicit Runner(const Config& config);
        void run();

      private:
        Config context;
    };

}  // namespace app::eggtimer
