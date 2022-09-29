#pragma once

#include <map>
#include <string>
#include <variant>
/**
 * @brief Plus Language 解释器的容器模块命名空间
 *
 */
namespace pl::container {

using ValueType = std::variant<size_t, std::string>;

enum class ValueTypeIndex : size_t { SIZE_T_TYPE = 0, STRING_TYPE = 1 };

/**
 * @brief pl解释器的容器类型
 * 键为标识符组成的字符串
 * 值为其他标识符或地址下标
 *
 */
class KeyValContainer : public std::map<std::string, ValueType> {
   public:
    KeyValContainer() = default;
    ~KeyValContainer() = default;
};

/**
 * @brief 使用参数构造一个pl解释器的容器pair
 *
 * @param key 必定是标识符
 * @param value size_t类型，代表地址
 * @return const std::pair<std::string, ValueType>
 */
inline const std::pair<std::string, ValueType> makePair(const std::string& key,
                                                        const size_t& value) {
    return std::make_pair<std::string, ValueType>(std::string{key},
                                                  ValueType{value});
}
/**
 * @brief 使用参数构造一个pl解释器的容器pair
 *
 * @param key 必定是标识符
 * @param value std::string类型，是标识符字符串
 * @return const std::pair<std::string, ValueType>
 */
inline const std::pair<std::string, ValueType> makePair(
    const std::string& key, const std::string& value) {
    return std::make_pair<std::string, ValueType>(std::string{key},
                                                  ValueType{value});
}

}  // namespace pl::container
