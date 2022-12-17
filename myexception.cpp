#include <myexception.h>

MyException::MyException() {
    this->errMsg = "";
}
MyException::MyException(QString errMsg)
{
    this->errMsg = errMsg;
}
QString MyException::message()
{
    return errMsg;
}

SQLException::SQLException(): MyException() {}
SQLException::SQLException(QString errMsg): MyException(errMsg) {}

IOException::IOException(): MyException() {}
IOException::IOException(QString errMsg): MyException(errMsg) {}

