#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <QString>

class MyException
{
public:
    MyException();
    MyException(QString errMsg);
    QString message();
private:
    QString errMsg;
};

class SQLException: public MyException
{
public:
    SQLException();
    SQLException(QString errMsg);
};

class IOException: public MyException
{
public:
    IOException();
    IOException(QString errMsg);
};

#endif // MYEXCEPTION_H
