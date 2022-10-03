#pragma once

#include <string_view>
#include <vector>

#include "typeTable.hpp"

/**
 * @brief Plus Language 解释器的词法模块命名空间
 *
 */
namespace pl::lex {
/**
 * @brief pl解释器的lex模块
 * 将输入的字符串分割为一个个token
 *
 */
class Lex {
   public:
    explicit Lex(std::string_view inputString);
    explicit Lex();
    ~Lex();

    /**
     * @brief 启动词法分析
     *
     * @param inputString 使用此参数的值进行词法解析
     * 注意此函数将覆写构造函数中的字符串view
     *
     * @return std::vector<pl::types::Token>
     */
    [[nodiscard]] std::vector<pl::types::Token> start(
        std::string_view inputString);
    /**
     * @brief 启动词法分析
     *
     * @return std::vector<pl::types::Token>
     */
    [[nodiscard]] std::vector<pl::types::Token> start();

    std::string getErrorInfo() const;
    inline bool good() const { return !_failed; }

   private:
    bool _failed;
    pl::types::Token _failedToken;

    std::string_view _input;
    size_t _index;
    size_t _row, _column;
    std::string _tokenStringBuffer;
    pl::types::TYPES _currentTokenType;

   private:
    inline char _peekNext() const {
        if (_input.size() > _index + 1)
            return _input[_index + 1];
        else
            return EOF;
    }
    inline char _peek() const {
        if (_input.size() > _index)
            return _input[_index];
        else
            return EOF;
    }
    inline char _last() const {
        if (_tokenStringBuffer.empty())
            return EOF;
        else
            return _tokenStringBuffer[_tokenStringBuffer.length()];
    }
    inline char _first() const {
        if (_tokenStringBuffer.empty())
            return EOF;
        else
            return _tokenStringBuffer[0];
    }
    inline bool _isEOF(char c) const { return c == EOF; }
    inline bool _isAlphabetOrUnderLine(char c) const {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
    }
    inline bool _isNumber(char c) const { return c >= '0' && c <= '9'; }
    inline bool _isSymbol(char c) const {
        return (c == pl::symbol::SYMBOL_ADD) ||
               (c == pl::symbol::SYMBOL_ASSIGN);
    }
    inline bool _isKeyWordContains(char c) const {
        return pl::symbol::SYMBOL_ECHO.starts_with(_tokenStringBuffer + c);
    }
    inline bool _isKeyWordEqual(std::string s) const {
        return pl::symbol::SYMBOL_ECHO == s;
    }

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