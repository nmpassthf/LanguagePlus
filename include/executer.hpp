#pragma once

#include <string>
#include <vector>

#include "container.hpp"
#include "typeTable.hpp"

namespace pl::executer {
class Executer {
   public:
    Executer();
    ~Executer();

    std::string exec(const std::vector<pl::types::Command>& commands);

   private:
    pl::container::KeyValContainer kv;


    std::string getFinalId(std::pair<pl::types::OpNumberType, std::string> value);
};
}  // namespace pl::executer
