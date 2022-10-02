#pragma once

#include <string>
#include <vector>

#include "container.hpp"
#include "typeTable.hpp"

/**
 * @brief Plus Language 解释器的语法模块命名空间
 *
 */
namespace pl::parser {

/**
 * @brief pl解释器的parser模块
 * 将输入的token列表转换为OC列表
 *
 */
class Parser {
   public:
    explicit Parser(const std::vector<pl::types::Token>& tokenList);
    ~Parser();

    std::vector<pl::types::Command> parseAndGenCode(
        const std::vector<pl::types::Token>& replacedDefaultTokenList);
    std::vector<pl::types::Command> parseAndGenCode();

    std::string getErrorInfo(std::string_view rawData) const;
    inline bool good() const { return !_failed; }

    /**
     * @brief Get the Formatted Source object
     * parseAndGenCode()函数之后再调用此函数
     *
     * @return std::string
     */
    std::string getFormattedSource() const;

   private:
    std::vector<pl::types::Token> _tokenList;
    size_t _currentToken;

    pl::container::KeyValContainer _container, _tempContainer;

    std::vector<pl::types::Command> _genCodeList;
    bool _failed;
    pl::types::Token _failedToken;
    pl::types::ParserError _failedReason;

    std::vector<std::string> _formattedString;

   private:
    inline pl::types::Token _peek() const {
        return _currentToken >= _tokenList.size() ? pl::types::Token{}
                                                  : _tokenList[_currentToken];
    }
    inline pl::types::Token _peekNext() const {
        return _currentToken + 1 >= _tokenList.size()
                   ? pl::types::Token{}
                   : _tokenList[_currentToken + 1];
    }
    inline bool _isInTable(std::string id) {
        return _container.contains(id) || _tempContainer.contains(id);
    }
    inline bool _isInTempTable(std::string id) {
        return _tempContainer.contains(id);
    }
    inline void _accept() { ++_currentToken; }

    inline void _pushCommand(pl::types::Command c) {
        _genCodeList.push_back(c);
    }

   private:
    /**
     * @brief Start -> {Statement}
     *
     */
    void _parse();
    /**
     * @brief Statement -> `echo` Express
     *
     */
    void _parseEcho();
    /**
     * @brief Statement -> Identifier `=` Express
     *
     */
    void _parseAssign();
    /**
     * @brief Statement -> Identifier `+` Express
     *
     * @return std::string 返回加法表达式最终的结果(临时变量名或者变量名)
     */
    std::string _parseAdd();
    /**
     * @brief 生成一个临时变量名
     *
     * @return std::string
     */
    std::string _getTempId();
};

}  // namespace pl::parser
