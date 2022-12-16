#include "myexception.cpp"
class SQLException: public MyException {
public:
    SQLException(): MyException() {}
    SQLException(QString errMsg): MyException(errMsg){}
};
