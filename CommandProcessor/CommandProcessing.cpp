#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


/*command class implemetation, the command class represents a command entered by the player
each command has a name and an effect */
Command::Command(Observer *observer,const string& cm){
   command =cm;
   Subject::addObserver(observer);
    effect="";
}

//copy constructor shallow copy
Command::Command(const Command& other) : Subject(other) {
    command=other.command;
    effect=other.effect;
}
//releasing dynamically allocated memory
Command::~Command()= default;

void Command::notify(ILoggable& subject)
{
        Subject::observer_->update(subject);
}

string Command::stringToLog()
{
    string str="A command's effect has been saved!\nCommand : \n"+command+"\nEffect : \n"+effect+"\n";
    return str;
}

//assignment operator
Command& Command::operator=(const Command& other){
    if(this!=&other){ //avoids self-assignment
        command=other.command;
        effect=other.effect;
        Subject::addObserver(observer_);
    }
    return *this;
}
//storing the given string into effect attribute
void Command:: saveEffect(){
        //checks if the command starts with "loadmap" starting from position 0 in the string
    if (command.rfind("loadmap",0)==0){
            //if the command is longer than 8 chars it means the name of the map is provided
            if(command.length()>8){
                string mName=command.substr(8); //skip "loadmap "
                effect="map "+mName+" loaded successfully";
            } else{
                effect="missing map name";
            }
        }else if(command=="validatemap"){
            effect="map validated ";
          }else if(command.rfind("addplayer",0)==0){
                if(command.length()>10){
                    string playerN=command.substr(10); //skip "addplayer "
                    effect="player "+playerN+" added ";
                }
                else{
                    effect="missing player name";
                }
            }else if(command=="gamestart"){
                effect="game started";
                }else if(command=="replay"){
                    effect="replaying game";
                    }else if(command=="quit")
                    {
                        effect="exiting the game";
                    }else {
                        effect="invalid command";
                    }
    notify(*this);
}
//returns the command string
string Command::getCommand()const{
    return command;
}

//returns the effect string
string Command::getEffect() const{
    return effect;
}
void Command::setEffect(const string& eff) {
    effect = eff;
}
//printing the command in a readable format
ostream& operator<<(ostream& os, const Command& cm){
os<<"Command: "<<cm.command<<", Effect: "<<cm.effect;
return os;
}
//command processor class implementation

CommandProcessor::CommandProcessor(Observer* observer){
    Subject::addObserver(observer);
}

//copy constructor, deep copying other command processor objs
CommandProcessor::CommandProcessor(const CommandProcessor& other) : Subject(other) {
    for(auto cm:other.commands){
        commands.push_back(new Command(*cm));
    }
}
//destructor, releasing dynamically allocated memory
CommandProcessor::~CommandProcessor(){
    for(auto cm:commands){
        delete cm; //deleting each command object in the vector
    }
    commands.clear(); //clear the vector
}

void CommandProcessor::notify(ILoggable& subject)
{
    Subject::observer_->update(*this);
}

string CommandProcessor::stringToLog()
{
    string str = "A new command has been saved!:\n"+commands.back()->getCommand()+"\n\n";
    return str;
}

//assignment operator
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other){
    if (this!=&other){ //avoiding self assignment
        for(auto cm:commands){ //deleting existing command objects
            delete cm;
        }
        commands.clear();
        //copy command objects from other
        for(auto cm:other.commands){
            commands.push_back(new Command(*cm));
        }
    }
    return *this;
}

//reads command from console
Command* CommandProcessor::readCommand(){
    string input;
    cout<<"Enter command: ";
    getline(cin, input); //reads the entire line including spaces
    Command* com = saveCommand(input); // stores the new command
    return com;
}

//returns the most recently added command
Command* CommandProcessor::getCommand(string state){
    Command* com =readCommand();
    if (validate(com, state))
    {
        return com;
    }

    cout<<"The command is invalid! Re-enter command!"<<std::endl;
    return nullptr;
}

//saves a new command object into the commands vector
Command* CommandProcessor ::saveCommand(string cm){
    Command *command = new Command(Subject::observer_, cm);
    commands.push_back(command); //creates and add new command object to the vector
    notify(*this);
    return command;
}

/* check if the given command is valid in the current game state
call saveEffect() if valid to store the message and if invalid store an error message
 returns true if valid, false otherwise */
bool CommandProcessor:: validate(Command* cm, string state){
    if (!cm) return false; // defensive: avoid crash if caller forgets to check
     string cmnd=cm->getCommand();
     bool valid=false;
     if(state=="start"&& cmnd.rfind("loadmap",0)==0){
         valid=true;
        cm->setEffect("map loaded successfully");
     }
     else if(state=="maploaded"&& cmnd=="validatemap"){
         valid=true;
        cm->setEffect("map validated");
     }
     else if((state=="mapvalidated"||state=="playersadded")&&cmnd.rfind("addplayer",0)==0){
        valid=true;
        string playerN=cmnd.substr(10); //skip "addplayer "
        cm->setEffect("player "+playerN+" added ");


     }
     else if(state=="playersadded"&& cmnd=="gamestart"){
        valid=true;
        cm->setEffect("game started");

     }
     else if(state=="win"&&cmnd=="replay"){
        valid=true;
        cm->setEffect("replaying game");

     }
     else if(cmnd=="quit"){
        valid=true;
        cm->setEffect("exiting the game...");
     }
     //saving the effect
     if(!valid){
        cm->setEffect("invalid command "+cmnd);
     }

    return valid;


}

vector<Command*> CommandProcessor::getCommandList() const
{
    return commands;
}

//file command processor adapter class implementation
//constructor that opens the given file to reads commands from it
FileCommandProcessorAdapter::FileCommandProcessorAdapter(Observer* observer, const string& filename) :
    CommandProcessor(observer)
{
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "Cannot open the file " << filename << endl; //error message if failed to open
    }
}

//copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other):CommandProcessor(other){

}
//using the base class assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other){
   CommandProcessor::operator=(other);
    return *this;

}
//closes file when object is destroyed
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    if(file.is_open()){
        file.close();
    }
}



//reads command from the file
Command* FileCommandProcessorAdapter::readCommand(){
    string line;
    //if the file is open and has a next line, read from it
    if(file.is_open() && getline(file, line)){
        Command* comm = saveCommand(line); //store the read command
        return comm;
    }
    return nullptr;
}

Command* FileCommandProcessorAdapter::getCommand(string state)
{
    Command* com = readCommand();
    if (!com) {
        // end of file OR file couldn't be read -> signal caller
        return nullptr;
    }

    if (validate(com, state)) {
        return com;
    }

    cout << "The command is invalid! Re-enter command!" << std::endl;
    return nullptr;
}


void FileCommandProcessorAdapter ::notify(ILoggable& subject)
{
    Subject::observer_->update(*this);
}

string FileCommandProcessorAdapter ::stringToLog()
{
    string str = "A new command has been saved!:\n"+commands.back()->getCommand()+"\n\n";
    return str;
}
