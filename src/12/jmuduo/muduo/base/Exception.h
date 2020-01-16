// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

//backtrace 栈回溯, 保存各个栈帧的地址
//backtrace_symbols 根据地址,转成相应的函数符号
//abi: __cxa_dmangle

#ifndef MUDUO_BASE_EXCEPTION_H
#define MUDUO_BASE_EXCEPTION_H

#include <muduo/base/Types.h>
#include <exception>

namespace muduo
{

class Exception : public std::exception
{
 public:
  explicit Exception(const char* what);
  explicit Exception(const string& what);
  virtual ~Exception() throw();
  virtual const char* what() const throw();
  const char* stackTrace() const throw();

 private:
  void fillStackTrace();
  string demangle(const char* symbol);

  string message_;
  string stack_;
};

}

#endif  // MUDUO_BASE_EXCEPTION_H
