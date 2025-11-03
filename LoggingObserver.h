//
// Created by Malak Sefrioui on 2025-11-03.
//

#include <iostream>
#include <vector>
#include <string>
using std::cout;

#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

class ILoggable{
    public:
        virtual string stringToLog(): =0;
};

class Observer{
    public:
    //pure virtual function that class which will extend Observer will HAVE to override
        virtual Observer():=0;
        virtual void update(const ILoggable& s):=0;
};

class LogObserver : Observer{
    private:
        string filename;
    public:
        //overridden virtual method from parent class
        void update(const ILoggable& s) override;

        //constructors, copy constructors, destructors, assignment operator and stream insertion operator
        LogObserver(string filename);
        LogObserver(): filename("log.txt");
        LogObserver(const LogObserver& o);
        ~LogObserver();
        LogObserver& operator = (const LogObserver& o);
        friend ostream& operator << (ostream& out, const LogObserver& logObserver);
};

class Subject{
public:
    vector <LogObserver*> list;
    virtual void addObserver(LogObserver* observer);
    virtual void removeObserver(LogObserver* observer);
    virtual void notify(ILoggable subject);

    Subject();
    ~Subject();
};

#endif //GITCLONE345_LOGGINGOBSERVER_H
