/*
CommandProcessor/CommandProcessing.cpp
CommandProcessor/CommandProcessing.h
#include "CommandProcessing.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//command class implemetation, the command class represents a command entered by the player
//each command has a name and an effect

Command::Command(const string& cm){
    command =cm;
}
//copy constructor, deep copying other command objs
Command::Command(const Command& other){
    command=other.command;
    effect=other.effect;
}
//releasing dynamically allocated memory
Command::~Command(){
   
}
//assignment operator
Command& Command::operator=(const Command& other){
    if(this!=&other){ //avoids self-assignment
        command=other.command;
        effect=other.effect;

    }
    return *this;
}
//storing the given string into effect attribute
void Command:: saveEffect(){
if (command=="loadmap"){
    effect="map loaded successfully";
}
  else if(command=="validatemap"){
    effect="map validated ";
  }
  else if(command=="addplayer"){
    effect="player added ";
  }
  else if(command=="gamestart"){
    effect="game started";
  }
  else if(command=="replay"){
    effect="replaying game";
}
  else if(command=="quit"){
    effect="exiting the game";

}
else {
    effect="invalid command";
}
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
// check if the given command is valid in the current game state
//call saveEffect() if valid to store the message and if invalid store an error message
// returns true if valid, false otherwise
bool CommandProcessor:: validate(Command* cm, string state){
     string cmnd=cm->getCommand();
     bool valid=false;
     if(state=="start"){
        if(cmnd=="loadmap"){
            valid=true;
        }
     }
     else if(state=="maploaded"){
        if(cmnd=="validatemap"){
            valid=true;
        }
     }
     else if(state=="mapvalidated"){
        if(cmnd=="addplayer"){
            valid=true;
        }
        
     }
     else if(state=="playersadded"){
        if(cmnd=="gamestart"){
            valid=true;
        }
     }
     else if(state=="win"){
        if(cmnd=="replay"){
            valid=true;
        }
     }
     else if(cmnd=="quit") valid=true;
     //saving the effect
     if(valid){
        cm->saveEffect();
     }
     else{
        cm->setEffect("invalid command"+cmnd);

     }

return valid;


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
*/