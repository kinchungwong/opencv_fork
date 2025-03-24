// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#include "../precomp.hpp"
#include "logcallbackmanager.hpp"

namespace cv {
namespace utils {
namespace logging {

LogCallbackManager::LogCallbackManager()
    : m_mutex()
    , m_callbacks()
{
}

LogCallbackManager::~LogCallbackManager()
{
}

size_t LogCallbackManager::count() const
{
    const LockType lock(m_mutex);
    return m_callbacks.size();
}

bool LogCallbackManager::contains(LoggingCallbackPtrType callback) const
{
    const LockType lock(m_mutex);
    return m_callbacks.find(callback) != m_callbacks.end();
}

void LogCallbackManager::add(LoggingCallbackPtrType callback)
{
    const LockType lock(m_mutex);
    m_callbacks.insert(callback);
}

void LogCallbackManager::remove(LoggingCallbackPtrType callback)
{
    const LockType lock(m_mutex);
    m_callbacks.erase(callback);
}

void LogCallbackManager::removeAll()
{
    const LockType lock(m_mutex);
    m_callbacks.clear();
}

void LogCallbackManager::readInto(std::vector<LoggingCallbackPtrType>& callbacks) const
{
    const LockType lock(m_mutex);
    callbacks.assign(m_callbacks.cbegin(), m_callbacks.cend());
}

size_t LogCallbackManager::tryReadIntoSz(LoggingCallbackPtrType (&callbacks)[], size_t arr_sz) const
{
    const LockType lock(m_mutex);
    const auto it_end = m_callbacks.cend();
    auto iter = m_callbacks.cbegin();
    for (size_t idx = 0u; idx < arr_sz; ++idx)
    {
        if (iter == it_end)
        {
            callbacks[idx] = nullptr;
        }
        else
        {
            callbacks[idx] = *iter;
            ++iter;
        }
    }
    return m_callbacks.size();
}

}}} //namespace
