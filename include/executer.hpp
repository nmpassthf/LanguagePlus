#pragma once

#include <vector>

#include "container.hpp"
#include "typeTable.hpp"

namespace pl::executer {
class Executer {
   public:
    Executer();
    ~Executer();

    void exec(const std::vector<pl::types::Command> &commands);

   private:
    pl::container::KeyValContainer kv;

    size_t& getValue(std::pair<pl::types::OpNumberType, std::string> value);
};
}  // namespace pl::executer
