
#ifndef  JSEXCEPTION_H
#define  JSEXCEPTION_H

#include <stdexcept>
class ArgumentLengthError : public std::logic_error{
public:
	ArgumentLengthError() : logic_error("argument  length error"){}
};

class ArgumentTypeError : public std::logic_error{
public:
	ArgumentTypeError(): logic_error("argument type is error"){}

};

#endif   /* JSEXCEPTION_H */
