#ifndef LANG_UTILS_HPP_INCLUDED
#define LANG_UTILS_HPP_INCLUDED

/**
 @file lang_utils.hpp
 @author François Becker
 
MIT License

Copyright (c) 2018 François Becker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <utility>
#include <functional>

namespace fbu
{
    namespace lang
    {
        class NonCopyable
        {
        public:
            NonCopyable() = default;
            ~NonCopyable() = default;
            
        private:
            NonCopyable(const NonCopyable&) = delete;
            NonCopyable& operator=(const NonCopyable&) = delete;
        };
        
        class NonMovable
        {
        public:
            NonMovable() = default;
            ~NonMovable() = default;
            
        private:
            NonMovable(const NonMovable&&) = delete;
            NonMovable& operator=(const NonMovable&&) = delete;
        };
        
        template <typename T>
        class OnCopy
        {
        public:
            explicit OnCopy(T&& pCopy)
            : mCopy(std::forward<T>(pCopy))
            {
            }
            ~OnCopy() = default;
            OnCopy(const OnCopy& pOther)
            {
                pOther.mCopy();
                mCopy = pOther.mCopy;
            }
            OnCopy& operator=(const OnCopy& pOther)
            {
                pOther.mCopy();
                mCopy = pOther.mCopy;
            }
            T mCopy;
        };
        typedef OnCopy< std::function<void()> > OnCopyFunction;
        
        template <typename T>
        class ScopeExit
        : NonCopyable
        , NonMovable
        {
        public:
            explicit ScopeExit(T&& pExitScope)
            : mExitScope(std::forward<T>(pExitScope))
            {
            }
            ~ScopeExit()
            {
                mExitScope();
            }
        private:
            T mExitScope;
        };
        typedef ScopeExit< std::function<void()> > ScopeExitFunction;
    }
}

#endif
