#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "LoggingObserver.h"
using namespace std;
//forward declaration
class Command;
class Command: public Subject, public ILoggable{
private:
    string command; //the command
    string effect; //the result of command
public:
//constructors
    Command(Observer* observer, const string& cm);
    Command(const Command& other);
    ~Command() override;
    Command& operator=(const Command& other);
    void saveEffect();
    string getCommand()const;
    string getEffect()const;
    void setEffect(const std::string& eff);
    string stringToLog() override;
    void notify(ILoggable& subject) override;
    friend ostream& operator<<(ostream& os, const Command& cm);
};
//this class is responsible for reading and storing commands
class CommandProcessor{
    protected:
    vector<Command*> commands;
    public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor& other);
    CommandProcessor& operator=(const CommandProcessor& other);
    virtual ~CommandProcessor();
    //methods
    virtual Command* readCommand(); //reading the command from console
    Command* saveCommand(const string& cm);  //saving the command in the vector
    virtual Command* getCommand(string state); //getting the last command
    virtual bool validate(Command* cm, string state);
    vector<Command*> getCommandList() const; //getter for commands vector
    //stream insertion operator
    friend ostream& operator<<(ostream& os, const CommandProcessor& cp);
    vector<Command*> getCommands() const ; //getter for the vector, it is needed for loops in the driver


};
//FileCommandProcessorAdapter extends CommandProcessor to read commands from a file
class FileCommandProcessorAdapter: public CommandProcessor{
private:
    ifstream file; 
    string fileN; 
    
public:
    explicit FileCommandProcessorAdapter(const string& filename);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter() override;
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
    Command* readCommand() override;
    friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& fcp);

};

#endif