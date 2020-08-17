#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <functional>

class Log;
class LogModifier {
    std::function<void(Log&)> f_;
public:
    explicit LogModifier(std::function<void(Log&)> f):f_(f){}
    inline void operator()(Log & log) const {f_(log);}
};

class Log {
    std::mutex mu_;
    std::ostream &os_;
    std::string sep_;
public:
    explicit Log(std::ostream &os, const std::string &sep=" "):os_(os),sep_(sep){}

    inline void setSep(const std::string & sep) {sep_=sep;}
    inline const std::string & getSep() const {return sep_;}
    inline const std::string & getSep() {return sep_;}

private:
    template<typename T, typename ...Tn> inline void write(const T& o, const Tn&...args) {
        os_<<o; 
        if(sizeof...(args)) {
            if(!sep_.empty()) os_<<sep_;
            write(args...);
        }
    }

    template<typename ...Tn> inline void write(const LogModifier &f, const Tn&...args) {
        f(*this);
        if(sizeof...(args)) write(args...);
    }

    inline void write() {}

public:
    template<typename T, typename ...Tn> inline Log & print(const T& o, const Tn&...args) {
        std::lock_guard<std::mutex> lg(mu_);
        write(o, args...);
        return *this;
    }

    template<typename ...Tn> inline Log & print(const LogModifier &f, const Tn&...args) {
        std::lock_guard<std::mutex> lg(mu_);
        write(f, args...);
        return *this;
    }

    template<typename ...Tn> inline Log & println(const Tn& ...args) {return print(args...,"\n");}

public:
    template<typename T> friend inline Log & operator <<(Log & log, const T & o) {return log.print(o);}
    friend inline Log & operator <<(Log & log, std::ostream& (*f)(std::ostream&)){return log.print(f);}
};

extern Log stdlog;

inline LogModifier sep(std::string &&s="") {return LogModifier([&](Log &log) {log.setSep(s);});}
