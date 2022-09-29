/**
 * @file typeTable.hpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief single header of all types in pl
 * @date 2022-09-29
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */

#pragma once

#include <string>
#include <variant>

/**
 * @brief pl语言的符号命名空间
 *
 */
namespace pl::symbol {
constexpr char SYMBOL_ADD = '+';
constexpr char SYMBOL_ASSIGN = '=';
constexpr std::string_view SYMBOL_ECHO = "echo";

}  // namespace pl::symbol

/**
 * @brief pl语言的类型命名空间
 *
 */
namespace pl::types {

/**
 * @brief pl语言可用的类型
 *
 */
enum class TYPES {
    /**
     * @brief pl语言中的整型类型
     * 以[0-9]开头并结尾
     */
    INT,
    /**
     * @brief pl语言中的标识符类型
     * 以[AlphaBet]开头，[AlphaBet|INT]结尾
     * 其中AlphaBet 为 [['A'-'Z']|['a'-'z']|'_']
     */
    ID,
    /**
     * @brief pl语言中的加法类型
     *
     */
    ADD,
    /**
     * @brief pl语言中的赋值类型
     *
     */
    ASSIGN,
    /**
     * @brief pl语言中的输出类型
     *
     */
    ECHO,
    /**
     * @brief pl语言中词法分析产生错误的类型
     * 
     */
    LEX_ERROR,
};

/**
 * @brief 每一个截取出来的token的类型
 * 包含token本身的类型和token的值
 */
struct Token {
    pl::types::TYPES type;
    std::string data;
    size_t tokenIndex;
};

}  // namespace pl::types