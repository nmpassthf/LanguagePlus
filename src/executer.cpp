/**
 * @file executer.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief vm的实现
 * @date 2022-10-03
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */

#include "executer.hpp"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using namespace pl::container;
using namespace pl::types;

namespace pl::executer {
Executer::Executer() {}
Executer::~Executer() {}

std::string Executer::exec(const std::vector<pl::types::Command>& commands) {
    string result{};

    kv.clear();

    for_each(
        commands.cbegin(), commands.cend(), [&](const pl::types::Command& cmd) {
            switch (cmd.operation) {
                case pl::types::OpCode::ADD:
                    kv[getFinalId(cmd.operationNumberDest)] =
                        get<size_t>(kv[getFinalId(cmd.operationNumberDest)]) +
                        (cmd.operationNumberSrc.first ==
                                 pl::types::OpNumberType::INT
                             ? stoull(cmd.operationNumberSrc.second)
                             : get<size_t>(
                                   kv[getFinalId(cmd.operationNumberSrc)]));
                    break;
                case pl::types::OpCode::ECHO:
                    result += to_string(
                        get<size_t>(kv[getFinalId(cmd.operationNumberSrc)]));
                    result += "\n";
                    cout << get<size_t>(kv[getFinalId(cmd.operationNumberSrc)])
                         << endl;
                    break;
                case pl::types::OpCode::MOV:
                    if (kv.contains(cmd.operationNumberDest.second)) {
                        if (cmd.operationNumberSrc.first ==
                            pl::types::OpNumberType::INT) {
                            kv[getFinalId(cmd.operationNumberDest)] =
                                stoull(cmd.operationNumberSrc.second);
                        } else {
                            kv[getFinalId(cmd.operationNumberDest)] =
                                get<size_t>(
                                    kv[getFinalId(cmd.operationNumberSrc)]);
                        }
                    } else {
                        if (cmd.operationNumberSrc.first ==
                            pl::types::OpNumberType::INT) {
                            kv.insert(makePair(
                                cmd.operationNumberDest.second,
                                stoull(cmd.operationNumberSrc.second)));
                        } else {
                            kv.insert(makePair(
                                cmd.operationNumberDest.second,
                                get<size_t>(
                                    kv[getFinalId(cmd.operationNumberSrc)])));
                        }
                    }
                    break;

                default:
                    break;
            }
        });
    return result;
}

std::string Executer::getFinalId(
    std::pair<pl::types::OpNumberType, std::string> value) {
    string newValue{value.second};
    while (kv[newValue].index() == 1) {
        newValue = get<string>(kv[newValue]);
    }
    return newValue;
}

}  // namespace pl::executer
