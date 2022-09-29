#pragma once

#include <string>

/**
 * @brief Plus Language 解释器IO模块命名空间
 *
 */
namespace pl::io {

/**
 * @brief pl解释器的io模块
 * 负责从.pl格式的Plus Language源码文件中读取raw data.
 *
 */
class FileReader {
   public:
    explicit FileReader(const std::string& filePath);
    explicit FileReader(void) = delete;
    ~FileReader();

    /**
     * @brief 从设置的路径中读取pl源码，出现错误时置位good()标志
     *
     * @param srcRawData
     */
    inline void operator>>(std::string& srcRawData) {
        return _readFromFile(srcRawData);
    }

    inline void setFilePath(const std::string& filePath) {
        _filePath = filePath;
    }

    inline bool good() const { return _good; }

   private:
    void _readFromFile(std::string& data);
    bool _good = false;
    std::string _filePath;
};

}  // namespace pl::io
