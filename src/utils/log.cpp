#include <iostream>
#include "log.h"

using namespace std;

Log stdlog(std::clog);


static std::ostream& fff(std::ostream& os) {
    os<<"hello---world."<<endl;
    return os;
}

void testlog()
{
    stdlog.println("aa","bb","cc");
    stdlog.println("aa","bb","cc",fff,"ooo");
    stdlog.print("aa","bb","cc");
    stdlog.print(fff);
}
