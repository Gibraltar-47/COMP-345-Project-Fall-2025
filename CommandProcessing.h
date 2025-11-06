#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//forward declaration
class Command;
class Command{
private:
    string command; //the command
    string effect; //the result of command
public:
//constructors
    Command();
    Command(const string& cm);
    Command(const Command& other);
    ~Command();
    Command& operator=(const Command& other);
    void saveEffect();
    string getCommand()const;
    string getEffect()const;
    void setEffect(const std::string& eff);
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
    virtual void readCommand(); //reading the command from either console or a file
    void saveCommand(const string& cm); 
    virtual Command* getCommand();
    virtual bool validate(Command* cm, string state);
    const vector<Command*>& getCommandList() const; //getter for commands vector
    //stream insertion operator
    friend ostream& operator<<(ostream& os, const CommandProcessor& cp);



};
//FileCommandProcessorAdapter extends CommandProcessor to read commands from a file
class FileCommandProcessorAdapter: public CommandProcessor{
private:
    ifstream file; 
    string fileN; 
    
public:
    FileCommandProcessorAdapter(const string& filename);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
    void readCommand() override;
    friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& fcp);

};

#endif
