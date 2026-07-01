#pragma once
#include <vector>
#include <string>
#include "token.hpp"

namespace mksh{
    class Executor {
    public:
        void execute(const std::vector<Token>& args);
    };
}