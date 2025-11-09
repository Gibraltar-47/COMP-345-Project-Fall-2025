//
// Created by Malak Sefrioui on 2025-11-03.
//

#include "LoggingObserver.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::ofstream;

//IMPLEMENTATION OF THE SUBJECT CLASS

//ADDING CLASS THAT ARE/DERIVE FROM OBSERVER TO THE SET ATTRIBUTE OF SUBJECT
void Subject::addObserver(Observer *observer) {
    list.insert(observer);
}

//REMOVING THE GIVEN OBSERVER
void Subject::removeObserver(Observer *observer)
{
    list.erase(observer);
}

// METHOD NOTIFY IS NOT IMPLEMENTED IN THIS CLASS BECAUSE
// EACH DERIVED CLASS OF SUBJECT WILL HAVE TO IMPLEMENT THEIR OWN METHOD

//COPY CONSTRUCTOR, ASSIGNMENT OPERATOR AND STREAM INSERTION OPERATOR
Subject::Subject(const Subject &other)
{
    list= other.list;
}

Subject& Subject::operator=(const Subject &other)
{
    if (this!=&other)
    {
        list.clear();
        list = other.list;
    }
    return *this;
}

ostream& operator <<(ostream& out, const Subject& subject)
{
    out<<"This is a Subject Object with the following observers attached :\n";
    for (Observer* observer : subject.list)
    {
        out<<"\t- "<<*observer<<endl;
    }
    return out;
}

//IMPLEMENTATION OF LOGOBSERVER CLASS

LogObserver::LogObserver()
{
    filename = "gamelog.txt";
    outputFileStream.open(filename);
}

LogObserver::LogObserver(const LogObserver& o)
{
    filename = "gamelog.txt";
    outputFileStream.open(filename);
}

LogObserver::~LogObserver()
{
 if (outputFileStream.is_open())
 {
     outputFileStream.close();
 }
}

void LogObserver::update(ILoggable& s)
{
    if (outputFileStream.is_open())
    {
        outputFileStream<<s.stringToLog()<<endl;
    }else
    {
        cout<<filename<< "is not open!"<<endl;
    }
}

LogObserver& LogObserver::operator=(const LogObserver& o)
{
    if (this!=&o){}
    return *this;
}

ostream &operator<<(ostream &out, const Observer &o)
{
    out<<"This is an Observer with the address : "<<&o<<endl;
    return out;
}


//IMPLEMENTATION OF ILOGGABLE
ostream& operator<<(ostream &out, ILoggable &i)
{
    out<<i.stringToLog()<<endl;
    return out;
}
