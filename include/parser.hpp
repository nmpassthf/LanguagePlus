#pragma once

#include <vector>

#include "typeTable.hpp"

/**
 * @brief Plus Language 解释器的语法模块命名空间
 *
 */
namespace pl::parser {
class Parser {
   public:
    explicit Parser(const std::vector<pl::types::Token>& tokenList);
    ~Parser();

   private:
    // void start
};

}  // namespace pl::parser
