﻿/**
 * @file lex.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief impl of pl::lex
 * @date 2022-09-29
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */
#include "lex.hpp"

#include <cassert>

using namespace std;
namespace pl::lex {
Lex::Lex(string_view inputStringStream) : _input{inputStringStream} {}
Lex::Lex() : _input{} {}
Lex::~Lex() {}

std::vector<pl::types::Token> Lex::start(string_view inputString) {
    _input = inputString;
    return start();
}
std::vector<pl::types::Token> Lex::start() {
    vector<pl::types::Token> resultTokenList{};
    pl::types::Token token{};
    size_t inputLen{_input.length()};

    DFA_TYPE state{DFA_TYPE::START};

    _index = size_t{};

    auto creativeNewToken = [&](pl::types::TYPES tokenType) {
        if (_tokenStringBuffer.empty())
            return;
        token.type = tokenType;
        token.data = _tokenStringBuffer;
        token.tokenIndex = _index;
        resultTokenList.push_back(token);
    };
    auto setDFA = [&](DFA_TYPE dfaState) { state = dfaState; };
    auto accept = [&]() {
        _tokenStringBuffer.push_back(_peek());
        ++_index;
    };

    do {
        bool endCycle{false};
        // 判断当前状态
        switch (state) {
            case DFA_TYPE::END_OF_FILE: {
                setDFA(DFA_TYPE::END);
            } break;

            case DFA_TYPE::END: {
                endCycle = true;
            } break;

            case DFA_TYPE::START: {
                // 重置内部变量（为多次调用做准备）
                _tokenStringBuffer = string{};

                if (_isNumber(_peek())) {
                    setDFA(DFA_TYPE::NUM);
                    accept();
                } else if (_isAlphabetOrUnderLine(_peek())) {
                    if (_isKeyWordContains(_peek())) {
                        setDFA(DFA_TYPE::ALPHABET_OPT_NUM_WITH_KEY);
                        accept();
                    } else {
                        setDFA(DFA_TYPE::ALPHABET_NO_KEY);
                        accept();
                    }
                } else if (_isEOF(_peek())) {
                    setDFA(DFA_TYPE::END);
                } else if (isspace(_peek())) {
                    setDFA(DFA_TYPE::EMPTY_CHAR);
                    accept();
                } else if (_isSymbol(_peek())) {
                    if (_peek() == pl::symbol::SYMBOL_ADD) {
                        setDFA(DFA_TYPE::END_ADD);
                        accept();
                    } else if (_peek() == pl::symbol::SYMBOL_ASSIGN) {
                        setDFA(DFA_TYPE::END_ASSIGN);
                        accept();
                    }
                } else {
                    setDFA(DFA_TYPE::INVALID_CHAR);
                }
            } break;

            case DFA_TYPE::EMPTY_CHAR: {
                if (isspace(_peek())) {
                    accept();
                } else
                    setDFA(DFA_TYPE::START);
                // if (_isEOF(_peek())) {
                //     setDFA(DFA_TYPE::END_OF_FILE);
                // } else if (_isNumber(_peek())) {
                //     setDFA(DFA_TYPE::NUM);
                //     accept();
                // } else if (_isAlphabetOrUnderLine(_peek())) {
                //     if (_isKeyWordContains(_peek())) {
                //         setDFA(DFA_TYPE::ALPHABET_OPT_NUM_WITH_KEY);
                //         accept();
                //     } else {
                //         setDFA(DFA_TYPE::ALPHABET_NO_KEY);
                //         accept();
                //     }
                // }
            } break;

            case DFA_TYPE::NUM: {
                if (_isNumber(_peek())) {
                    accept();
                } else {
                    setDFA(DFA_TYPE::END_NUM);
                }
            } break;

            case DFA_TYPE::END_NUM: {
                creativeNewToken(pl::types::TYPES::INT);
                setDFA(DFA_TYPE::START);
            } break;

            case DFA_TYPE::ALPHABET_NO_KEY: {
                if (_isAlphabetOrUnderLine(_peek())) {
                    accept();
                } else if (_isNumber(_peek())) {
                    setDFA(DFA_TYPE::ALPHABET_WITH_NUM);
                    accept();
                } else {
                    setDFA(DFA_TYPE::END_ID);
                }
            } break;

            case DFA_TYPE::ALPHABET_OPT_NUM_WITH_KEY: {
                if (_isAlphabetOrUnderLine(_peek())) {
                    if (_isKeyWordContains(_peek())) {
                        accept();
                    } else {
                        setDFA(DFA_TYPE::ALPHABET_NO_KEY);
                        accept();
                    }
                } else if (_isNumber(_peek())) {
                    setDFA(DFA_TYPE::ALPHABET_WITH_NUM);
                    accept();
                } else {
                    setDFA(DFA_TYPE::END_ECHO);
                }
            } break;

            case DFA_TYPE::ALPHABET_WITH_NUM: {
                if (_isNumber(_peek()) || _isAlphabetOrUnderLine(_peek()))
                    accept();
                else
                    setDFA(DFA_TYPE::END_ID);
            } break;

            case DFA_TYPE::END_ID: {
                creativeNewToken(pl::types::TYPES::ID);
                setDFA(DFA_TYPE::START);
            } break;

            case DFA_TYPE::END_ECHO: {
                creativeNewToken(pl::types::TYPES::ECHO);
                setDFA(DFA_TYPE::START);
            } break;

            case DFA_TYPE::END_ADD: {
                creativeNewToken(pl::types::TYPES::ADD);
                setDFA(DFA_TYPE::START);
            } break;

            case DFA_TYPE::END_ASSIGN: {
                creativeNewToken(pl::types::TYPES::ASSIGN);
                setDFA(DFA_TYPE::START);
            } break;

            case DFA_TYPE::INVALID_CHAR: {
                creativeNewToken(pl::types::TYPES::LEX_ERROR);
                setDFA(DFA_TYPE::END);
            } break;

            default:
                assert(false);
                break;
        }

        if (endCycle)
            break;
    } while (_index <= inputLen);

    // DFA解析inputString
    return resultTokenList;
}

char Lex::_peekNext() const {
    if (_input.size() > _index + 1)
        return _input[_index + 1];
    else
        return EOF;
}
char Lex::_peek() const {
    if (_input.size() > _index)
        return _input[_index];
    else
        return EOF;
}
char Lex::_last() const {
    if (_tokenStringBuffer.empty())
        return EOF;
    else
        return _tokenStringBuffer[_tokenStringBuffer.length()];
}
char Lex::_first() const {
    if (_tokenStringBuffer.empty())
        return EOF;
    else
        return _tokenStringBuffer[0];
}
bool Lex::_isEOF(char c) const { return c == EOF; }
bool Lex::_isAlphabetOrUnderLine(char c) const {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}
bool Lex::_isNumber(char c) const { return c >= '0' && c <= '9'; }
bool Lex::_isSymbol(char c) const {
    return (c == pl::symbol::SYMBOL_ADD) || (c == pl::symbol::SYMBOL_ASSIGN);
}
bool Lex::_isKeyWordContains(char c) const {
    return pl::symbol::SYMBOL_ECHO.starts_with(_tokenStringBuffer + c);
}
}  // namespace pl::lex