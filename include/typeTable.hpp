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
 * @brief Plus Language 解释器的符号模块命名空间
 *
 */
namespace pl::symbol {
constexpr char SYMBOL_ADD = '+';
constexpr char SYMBOL_ASSIGN = '=';
constexpr std::string_view SYMBOL_ECHO = "echo";
}  // namespace pl::symbol

/**
 * @brief Plus Language 解释器的类型模块命名空间
 *
 */
namespace pl::types {

/**
 * @brief pl语言可用的类型
 * 指代token中所有的类型
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
    size_t row, column;
    size_t index;

    inline bool operator==(const Token&) const = default;
    inline uint64_t toUi64() { return stoull(data); }
};

/**
 * @brief 操作符的枚举类型
 * 源操作数1, [源操作数2] -> 目的操作数
 */
enum class OpCode {
    /**
     * @brief 赋值或加载值
     * mov dest src;
     * src 必须为ID类型
     */
    MOV,
    /**
     * @brief 加法
     * add dest src;
     * dest必须为ID类型
     */
    ADD,
    /**
     * @brief 输出命令
     * echo src
     * src 必须为ID类型
     */
    ECHO
};
inline std::string_view opCodeToString(OpCode code) {
    switch (code) {
        case OpCode::ADD:
            return "ADD";
            break;

        case OpCode::ECHO:
            return "ECHO";
            break;
        case OpCode::MOV:
            return "MOV";
            break;
        default:
            return {};
            break;
    }
};
enum class OpNumberType { INT, ID };
struct Command {
    OpCode operation;
    std::pair<OpNumberType, std::string> operationNumberDest,
        operationNumberSrc;

    inline bool operator==(const Command&) const = default;
    inline std::string toString() const {
        return std::string{opCodeToString(operation)} + " " +
               operationNumberDest.second + " " + operationNumberSrc.second;
    }
};
enum class ParserError {
    UNDEFINED_ID,
    MISSING_ID_IN_ASSIGN,
    MISSING_VALUE_AFTER_OPERATOR_PLUS,
    MISSING_VALUE_BEFOR_OPERATOR_PLUS
};

}  // namespace pl::types