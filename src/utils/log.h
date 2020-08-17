#pragma once

#include <iostream>
#include <fstream>
#include <mutex>

class Log {
    std::mutex mu_;
    std::ostream &os_;
public:
    explicit Log(std::ostream &os):os_(os){}
    template<typename T, typename ...Tn> inline Log & print(const T& o, const Tn&...args) {
        std::lock_guard<std::mutex> lg(mu_);
        os_<<o; 
        ((os_<<" "<<args),...);
        return *this;
    }

    template<typename ...Tn> inline Log & println(const Tn& ...args) {return print(args...,"\n");}

public:
    template<typename T> friend inline Log & operator <<(Log & log, const T & o) {return log.print(o);}
    friend inline Log & operator <<(Log & log, std::ostream& (*f)(std::ostream&)){return log.print(f);}
};

extern Log stdlog;