#include <QString>
class MyException {
public:
    MyException(): errMsg("") {}
    MyException(QString errMsg)
    {
        this->errMsg = errMsg;
    }
    QString message()
    {
        return errMsg;
    }

private:
    QString errMsg;
};
