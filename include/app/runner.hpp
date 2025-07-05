#pragma once

#include <format>
#include <app/cli.hpp>

namespace app::eggtimer {

    struct Runner {
        explicit Runner(const Config& config);
        void run();

    private:
        Config context;
    };

}  // namespace app::eggtimer
