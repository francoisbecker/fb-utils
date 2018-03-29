#ifndef POSSIBLE_ERROR_HPP_INCLUDED
#define POSSIBLE_ERROR_HPP_INCLUDED

/**
 @file possible_error.hpp
 @author François Becker

MIT License

Copyright (c) 2017-2018 François Becker

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

#include <cassert>

template <typename E>
struct Error
{
    E mError;
    Error(E pError)
    : mError(pError)
    {}
};
// shortcut as class template argument deduction is only possible from C++17
template <typename E>
Error<E> error(E pError)
{
    return Error<E>(pError);
}

template<typename T> class is_bool{ static const bool value = false; };
template<> class is_bool<bool>{ static const bool value = true; };

template <typename T, typename E = int>
struct PossibleError
{
    T mValue;
    E mError;
    bool mHasError = false;
    
    bool hasError() const { return mHasError; }
    operator T() const { static_assert(!is_bool<T>(), "Don't rely on the cast operator if your value is of bool type, as bool casting is used to check absence of error. Use the direct to the value member instead"); assert(!mHasError); return mValue; } // do not trust if T is bool
    operator bool() const { return !mHasError; }
    PossibleError(T& pValue) : mValue(pValue) {}
    PossibleError(T&& pValue) : mValue(std::move(pValue)) {}
    PossibleError(Error<E> pError) : mError(pError.mError), mHasError(true) {}
    T& operator ()() {
        return mValue;
    }
};

#endif
