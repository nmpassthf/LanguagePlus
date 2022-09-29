#pragma once

#include <string_view>
#include <vector>

#include "typeTable.hpp"

/**
 * @brief Plus Language 解释器的词法模块命名空间
 *
 */
namespace pl::lex {
class Lex {
   public:
    explicit Lex(std::string_view inputString);
    explicit Lex();
    ~Lex();

    /**
     * @brief start lex
     *
     * @param inputString 使用此参数的值进行词法解析
     * 注意此函数将覆写构造函数中的字符串view
     *
     * @return std::vector<pl::types::Token>
     */
    std::vector<pl::types::Token> start(std::string_view inputString);
    /**
     * @brief start lex
     *
     * @return std::vector<pl::types::Token>
     */
    std::vector<pl::types::Token> start();

   private:
    char _peekNext() const;
    char _peek() const;
    char _last() const;
    char _first() const;
    bool _isEOF(char c) const;
    bool _isAlphabetOrUnderLine(char c) const;
    bool _isNumber(char c) const;
    bool _isSymbol(char c) const;
    bool _isKeyWordContains(char c) const;

   private:
    std::string_view _input;
    size_t _index;
    std::string _tokenStringBuffer;
    pl::types::TYPES _currentTokenType;

    enum class DFA_TYPE {
        /**
         * @brief 文件读取结束状态
         *
         */
        END_OF_FILE,
        /**
         * @brief END状态
         *
         */
        END,
        /**
         * @brief DFA启动状态
         *
         */
        START,
        /**
         * @brief 空字符状态
         *
         */
        EMPTY_CHAR,
        /**
         * @brief 纯数字状态
         *
         */
        NUM,
        /**
         * @brief 结果为整型字面量
         *
         */
        END_NUM,
        /**
         * @brief 纯字母表状态，且首字母不匹配任何关键字
         *
         */
        ALPHABET_NO_KEY,
        /**
         * @brief 字母表（可能后接数字）状态，且包含部分关键字
         *
         */
        ALPHABET_OPT_NUM_WITH_KEY,
        /**
         * @brief 字母表后接数字
         *
         */
        ALPHABET_WITH_NUM,
        /**
         * @brief 结果为标识符的状态
         *
         */
        END_ID,
        /**
         * @brief 结果为echo关键字的状态
         *
         */
        END_ECHO,
        /**
         * @brief 结果为'+符号状态
         *
         */
        END_ADD,
        /**
         * @brief 结果为'='符号状态
         *
         */
        END_ASSIGN,
        /**
         * @brief 出现非法字符的状态
         *
         */
        INVALID_CHAR,
        /**
         * @brief 非法情形退出
         *
         */
        END_ERROR
    };
};
}  // namespace pl::lex
   //