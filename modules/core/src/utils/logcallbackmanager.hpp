// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_CORE_LOGCALLBACKMANAGER_HPP
#define OPENCV_CORE_LOGCALLBACKMANAGER_HPP

#if 1 // if not already in precompiled headers
#include <mutex>
#include <unordered_set>
#include <array>
#endif

#include <opencv2/core/utils/logger.defines.hpp>

namespace cv {
namespace utils {
namespace logging {

class LogCallbackManager
{
private:
    using MutexType = cv::Mutex;
    using LockType = cv::AutoLock;

public:
    explicit LogCallbackManager();
    ~LogCallbackManager();

    size_t count() const;
    bool contains(LoggingCallbackPtrType callback) const;
    void add(LoggingCallbackPtrType callback);
    void remove(LoggingCallbackPtrType callback);
    void removeAll();
    void readInto(std::vector<LoggingCallbackPtrType>& callbacks) const;

    /**
     * @brief Read as many callbacks as possible into a fixed-size receiving array.
     * @param callbacks The receiving array. Unused entries will be set to nullptr.
     * @param arr_sz Capacity of the receiving array.
     * @return Actual number of callbacks that have been registered. If this number 
     *         is greater than arr_sz, some callbacks have not been copied.
     */
    template <size_t arr_sz>
    size_t tryReadInto(std::array<LoggingCallbackPtrType, arr_sz>& callbacks) const
    {
        return this->tryReadIntoSz(callbacks.data(), arr_sz);
    }

        /**
     * @brief Read as many callbacks as possible into a fixed-size receiving array.
     * @param callbacks The receiving array. Unused entries will be set to nullptr.
     * @param arr_sz Capacity of the receiving array.
     * @return Actual number of callbacks that have been registered. If this number 
     *         is greater than arr_sz, some callbacks have not been copied.
     */
    template <size_t arr_sz>
    size_t tryReadInto(LoggingCallbackPtrType (&callbacks)[arr_sz]) const
    {
        return this->tryReadIntoSz(&callbacks, arr_sz);
    }

private:
    LogCallbackManager(const LogCallbackManager&) = delete;
    LogCallbackManager(LogCallbackManager&&) = delete;
    LogCallbackManager& operator=(const LogCallbackManager&) = delete;
    LogCallbackManager& operator=(LogCallbackManager&&) = delete;

    size_t tryReadIntoSz(LoggingCallbackPtrType (&callbacks)[], size_t arr_sz) const;

private:
    mutable MutexType m_mutex;
    std::unordered_set<LoggingCallbackPtrType> m_callbacks;
};

}}} //namespace

#endif //OPENCV_CORE_LOGCALLBACKMANAGER_HPP
