/**
 * @file parser.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief impl of pl::parser
 * @date 2022-10-02
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */

#include "parser.hpp"

#include <algorithm>
#include <sstream>

#define NAME(x) (#x)

using namespace std;
using namespace pl::types;
using namespace pl::container;

namespace pl::parser {
Parser::Parser(const std::vector<pl::types::Token>& tokenList)
    : _tokenList{tokenList} {}

Parser::~Parser() {}

std::vector<pl::types::Command> Parser::parseAndGenCode(
    const std::vector<pl::types::Token>& replacedDefaultTokenList) {
    _tokenList = replacedDefaultTokenList;
    return parseAndGenCode();
}
std::vector<pl::types::Command> Parser::parseAndGenCode() {
    _genCodeList.clear();
    _failed = false;
    _failedToken = {};

    _container.clear();
    _tempContainer.clear();
    _currentToken = 0;

    _formattedString = {};

    _parse();

    return _genCodeList;
}

std::string Parser::getErrorInfo(string_view rawData) const {
    if (!_failed)
        return {};
    string errorCodeString;
    switch (_failedReason) {
        case ParserError::UNDEFINED_ID:
            errorCodeString = NAME(UNDEFINED_ID);
            break;
        case ParserError::MISSING_ID_IN_ASSIGN:
            errorCodeString = NAME(MISSING_ID_IN_ASSIGN);
            break;
        case ParserError::MISSING_VALUE_AFTER_OPERATOR_PLUS:
            errorCodeString = NAME(MISSING_VALUE_AFTER_OPERATOR_PLUS);
            break;
        case ParserError::MISSING_VALUE_BEFOR_OPERATOR_PLUS:
            errorCodeString = NAME(MISSING_VALUE_BEFOR_OPERATOR_PLUS);
            break;
        default:
            break;
    }

    string errmsg;
    stringstream ss(string{rawData}, ios::in);
    for (size_t lineIndex = 0; lineIndex < _failedToken.row + 1; ++lineIndex)
        getline(ss, errmsg);

    string errLineString = to_string(_failedToken.row + 1) + ": ";
    errmsg = errLineString + errmsg + '\n';
    errmsg +=
        string(errLineString.length() + _failedToken.column + 1, ' ') + "^\n"s;
    errmsg += "Error: "s + errorCodeString + " `"s + _failedToken.data + "`\n"s;
    return errmsg;
}

std::string Parser::getFormattedSource() const {
    string out;
    for_each(_formattedString.cbegin(), _formattedString.cend(),
             [&](const auto& s) {
                 out += s;
                 out += "\n";
             });
    return out;
}

void Parser::_parse() {
    size_t last = 0;
    string sourceCodeFormattedPiece;

    while (_peek() != Token{} && !_failed) {
        if (_peek().type == TYPES::ECHO) {
            _accept();
            _parseEcho();
        } else {
            _parseAssign();
        }

        // 解析完成了一整条语句
        for (auto i = last; i < _currentToken; ++i)
            sourceCodeFormattedPiece += _tokenList[i].data + " ";
        _formattedString.push_back(sourceCodeFormattedPiece);
        last = _currentToken;
    }
    if (_failed)
        _genCodeList.clear();
}

void Parser::_parseEcho() {
    auto addResult = _parseAdd();
    if (addResult.empty()) {
        return;
    }

    _pushCommand({OpCode::ECHO, {}, {OpNumberType::ID, addResult}});
}

void Parser::_parseAssign() {
    if (_peek().type != TYPES::ID) {
        _failed = true;
        _failedToken = _peek();
        _failedReason = ParserError::MISSING_ID_IN_ASSIGN;
    } else {
        auto thisChar = _peek();
        _accept();
        _accept();
        if (_peek() == Token{}) {
            _failed = true;
            _failedToken = _tokenList[_currentToken - 1];
            _failedReason = ParserError::MISSING_ID_IN_ASSIGN;
            return;
        }

        auto addResult = _parseAdd();
        if (addResult.empty()) {
            return;
        }

        _container.insert(makePair(thisChar.data, addResult));
        _pushCommand({OpCode::MOV,
                      {OpNumberType::ID, thisChar.data},
                      {OpNumberType::ID, addResult}});
    }
}

std::string Parser::_parseAdd() {
    if (_peek() == Token{}) {
        --_currentToken;
        _failed = true;
        _failedToken = _peek();
        _failedReason = ParserError::MISSING_VALUE_BEFOR_OPERATOR_PLUS;
        return {};
    }
    // add表达式判断遇到结束符号
    else if (_peekNext() == Token{} || _peekNext().type != TYPES::ADD) {
        switch (_peek().type) {
            case TYPES::INT: {
                string tempId{_getTempId()};
                _tempContainer[tempId] = _peek().toUi64();
                _pushCommand({OpCode::MOV,
                              {OpNumberType::ID, tempId},
                              {OpNumberType::INT, _peek().data}});
                _accept();
                return tempId;
            } break;

            case TYPES::ID: {
                // 判断此ID是否合法，不合法则设置failed位
                if (!_isInTable(_peek().data)) {
                    _failed = true;
                    _failedToken = _peek();
                    _failedReason = ParserError::UNDEFINED_ID;
                    return {};
                } else {
                    auto data = _peek().data;
                    _accept();
                    return data;
                }
            } break;

            default: {
                _failed = true;
                _failedToken = _peek();
                _failedReason = ParserError::MISSING_VALUE_BEFOR_OPERATOR_PLUS;
                return {};
            } break;
        }
    } else {
        // peek() '+' Express
        auto thisChar{_peek()};
        _accept();
        _accept();
        auto expressId{_parseAdd()};

        if (expressId.empty())
            return {};

        if (thisChar.type == TYPES::INT) {
            // 判断ID是否为临时变量，不是临时变量则生成一个
            if (!_isInTempTable(expressId)) {
                string tempId{_getTempId()};
                _tempContainer[tempId] = _container[expressId];
                _pushCommand({OpCode::MOV,
                              {OpNumberType::ID, tempId},
                              {OpNumberType::ID, expressId}});
                _pushCommand({OpCode::ADD,
                              {OpNumberType::ID, tempId},
                              {OpNumberType::INT, thisChar.data}});
                return tempId;
            } else {
                _pushCommand({OpCode::ADD,
                              {OpNumberType::ID, expressId},
                              {OpNumberType::INT, thisChar.data}});
                return expressId;
            }
        } else if (thisChar.type == TYPES::ID) {
            if (!_isInTempTable(expressId) && !_isInTempTable(thisChar.data)) {
                string tempId{_getTempId()};
                _tempContainer[tempId] = _container[thisChar.data];
                _pushCommand({OpCode::MOV,
                              {OpNumberType::ID, tempId},
                              {OpNumberType::ID, expressId}});
                _pushCommand({OpCode::ADD,
                              {OpNumberType::ID, tempId},
                              {OpNumberType::ID, thisChar.data}});
                return tempId;
            } else if (_isInTempTable(expressId)) {
                _pushCommand({OpCode::ADD,
                              {OpNumberType::ID, expressId},
                              {OpNumberType::ID, thisChar.data}});
                return expressId;
            } else if (_isInTempTable(thisChar.data)) {
                _pushCommand({OpCode::ADD,
                              {OpNumberType::ID, thisChar.data},
                              {OpNumberType::ID, expressId}});
                return thisChar.data;
            } else {
                _failed = true;
                _failedToken = thisChar;
                _failedReason = ParserError::MISSING_VALUE_AFTER_OPERATOR_PLUS;
                return {};
            }
        } else {
            _failed = true;
            _failedToken = thisChar;
            _failedReason = ParserError::MISSING_VALUE_AFTER_OPERATOR_PLUS;
            return {};
        }
    }
}

std::string Parser::_getTempId() {
    auto tempNum = _tempContainer.size();
    while (_container.contains(string{"temp_ID_"} + to_string(tempNum)))
        ++tempNum;
    _tempContainer.insert(makePair(string{"temp_ID_"} + to_string(tempNum), 0));
    return string{"temp_ID_"} + to_string(tempNum);
}

}  // namespace pl::parser