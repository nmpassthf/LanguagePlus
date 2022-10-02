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

void Executer::exec(const std::vector<pl::types::Command>& commands) {
    kv.clear();

    for_each(
        commands.cbegin(), commands.cend(), [&](const pl::types::Command& cmd) {
            switch (cmd.operation) {
                case pl::types::OpCode::ADD:
                    getValue(cmd.operationNumberDest) +=
                        getValue(cmd.operationNumberSrc);
                    break;
                case pl::types::OpCode::ECHO:
                    cout << getValue(cmd.operationNumberSrc) << endl;
                    break;
                case pl::types::OpCode::MOV:
                    if (kv.contains(cmd.operationNumberDest.second)) {
                        getValue(cmd.operationNumberDest) =
                            getValue(cmd.operationNumberSrc);
                    } else {
                        if (cmd.operationNumberSrc.first ==
                            pl::types::OpNumberType::INT) {
                            kv.insert(makePair(
                                cmd.operationNumberDest.second,
                                stoull(cmd.operationNumberSrc.second)));
                        } else {
                            kv.insert(makePair(cmd.operationNumberDest.second,
                                               cmd.operationNumberSrc.second));
                        }
                    }
                    break;

                default:
                    break;
            }
        });
}

size_t& Executer::getValue(
    std::pair<pl::types::OpNumberType, std::string> value) {
    string newValue{value.second};
    while (kv[newValue].index() == 1) {
        newValue = get<string>(kv[newValue]);
    }
    return get<size_t>(kv[newValue]);
}

}  // namespace pl::executer
