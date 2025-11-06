#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
/*command class implemetation, the command class represents a command entered by the player
each command has a name and an effect */
Command::Command(const string& cm){
    command =new string(cm);
    effect=new string("");
}
//copy constructor, deep copying other command objs
Command::Command(const Command& other){
    command=new string (*other.command);
    effect=new string(*other.effect);
}
//releasing dynamically allocated memory
Command::~Command(){
    delete command;
    delete effect;
}
//assignment operator
Command& Command::operator=(const Command& other){
    if(this!=&other){ //avoids self-assignment
        *command=*other.command;
        *effect=*other.effect;

    }
    return *this;
}
//storing the given string into effect attribute
void Command:: saveEffect(const string& ef){
    *effect=ef;
}
//returns the command string
string Command::getCommand()const{
    return *command;
}
//returns the effect string
string Command::getEffect() const{
    return *effect;
}
//printing the command in a readable format
ostream& operator<<(ostream& os, const Command& cm){
os<<"Command: "<<*cm.command<<"| Effect: "<<*cm.effect;
return os;
}
//command processor class implementation
//default constructor
CommandProcessor::CommandProcessor(){}
//copy constructor, deep copying other command processor objs
CommandProcessor::CommandProcessor(const CommandProcessor& other){
    for(auto cm:other.commands){
        commands.push_back(new Command(*cm));
    }
}
//destructor, releasing dynamically allocated memory
CommandProcessor::~CommandProcessor(){
    for(auto cm:commands){
        delete cm; //deleteing each command object in the vector
    }
    commands.clear(); //clear the vector
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
void CommandProcessor::readCommand(){
    string input;
    cout<<"Enter command: ";
    getline(cin, input); //reads the entire line including spaces
    saveCommand(input); // stores the new command

}
//saves a new command object into the commands vector
void CommandProcessor ::saveCommand(const string& cm){
    commands.push_back(new Command(cm)); //creates and add new command object to the vector
}
//returns the most recently added command
Command* CommandProcessor::getCommand(){
    if(!commands.empty())
    {
         return commands.back(); //returning the last command object
    }
    return nullptr;
}
bool CommandProcessor:: validate(Command* cm){
    //IMPLEMENTATION...

}

//file command processor adapter class implementation
//constructor that opens the given file to reads commands from it
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filename){
    file.open(filename);
    if(!file.is_open()){
        cerr<<"Cannot open the file "<<filename<<endl; //error message if failed to open
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
void FileCommandProcessorAdapter::readCommand(){
    string line;
    //if the file is open and has a next line, read from it
    if(file.is_open() && getline(file, line)){
        saveCommand(line); //store the read command
}
}