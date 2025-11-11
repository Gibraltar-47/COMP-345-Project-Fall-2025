//
// Created by Malak on 2025-11-10.
//

#include "LoggingObserver.h"
#include "../CommandProcessor/CommandProcessing.h"
#include <iostream>

using std::cout;

void  testLoggingObserver()
{
    LogObserver* logObserver = new LogObserver();
    Command* command = new Command(logObserver, "loadmap");

    cout<<"TESTING LOGGING OBSERVER"<<endl;
    cout<<"=============================="<<endl;
    command->notify(*command);
    cout<<"COMMAND NOTIFYING THE LOG OBSERVER AS A CLASS INHERITING SUBJECT"<<endl;
}
