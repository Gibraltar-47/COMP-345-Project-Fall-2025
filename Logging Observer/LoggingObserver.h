//
// Created by Malak Sefrioui on 2025-11-03.
//

#include <iostream>
#include <set>
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
        ofstream& outputFileStream;
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

//protected members and methods for the Subject class
//so that only derived classes can directly access them
//without having to implement them again (except for the notify method that NEEDS to be implemented in derived classes)
protected:
    set <LogObserver*> list;
    virtual void addObserver(LogObserver* observer) ;
    virtual void removeObserver(LogObserver* observer);
    virtual void notify(ILoggable subject) =0;

    Subject() = default;
    ~Subject() = default;
};

#endif //GITCLONE345_LOGGINGOBSERVER_H
