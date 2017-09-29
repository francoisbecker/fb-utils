#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED

/**
 @file singleton.hpp
 @author François Becker
 
MIT License

Copyright (c) 2017 François Becker

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

#if __cplusplus < 201103
#error "This Singleton class implementation requires C++11 support"
#endif

#include <chrono>
#include <iostream>
#include <future>

/**
 @class Singleton
 @brief Meyers' Singleton implementation.
        In order to create a singleton class, inherit this class templated with
        the subclass, e.g. class MySingleton : public Singleton<MySingleton> { ... };
 */
template <class T>
class Singleton
{
public:
    static T& getInstance()
    {
        static T instance; // init and release are thread-safe by C++11 standard
        return instance;
    }
    
protected:
    Singleton()= default;
    ~Singleton()= default;
    
private:
    Singleton(const Singleton&)= delete;
    Singleton& operator=(const Singleton&)= delete;
};

#endif
