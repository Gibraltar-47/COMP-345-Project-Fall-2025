
#include "CommandProcessing.h"
#include <iostream>
using namespace std;
void testManualCommands(){
    //testing some manual commands
    cout<<"Manual command test:\n";
    Command c1("loadmap worldmap.txt");
    c1.saveEffect();
    cout<<c1.getCommand()<<" -> "<<c1.getEffect()<<endl;
    Command c2("addplayer Alice");
    c2.saveEffect();
    cout<<c2.getCommand()<<" -> "<<c2.getEffect()<<endl;
    Command c3("invalid");
    c3.saveEffect();
    cout<<c3.getCommand()<<" -> "<<c3.getEffect()<<endl;

    
}
void testCommandProcessor(){
    cout<<"Command Processor test\n";
    CommandProcessor cp;
    string state="start";
    while(true){
        cp.readCommand();
        Command* cmd=cp.getCommand(); //getting the last command entered
        if(!cmd) continue;
        bool valid=cp.validate(cmd,state);
        cout<<*cmd<<", Valid?"<<(valid?" Yes":" No")<<endl;
        //updating the state based on the rules
        string c=cmd->getCommand();
        /* using the find method to search for the substring inside a string and using"==0" to make sure the substring"loadmap" 
        appears at the very beginning of the command str. for example: "loadmap map.txt"*/
        if(state=="start"&& c.rfind("loadmap")==0) state="maploaded";
        else if(state=="maploaded"&&c=="validatemap") state="mapvalidated";
        else if((state=="mapvalidated"||state=="playersadded")&& c.rfind("addplayer",0)==0) state="playersadded";
        else if(state=="playersadded"&& c=="gamestart") state="assignreinforcement";
        else if(state=="win"&& c=="replay") state="start";
        else if(c=="quit"){
            cout<<"Exiting..."<<endl;
            break;
        }
        cout<<"Current state: "<<state<<endl;


    }

   

}
void testFileCommandProcessorAdapter(){
    cout<<"Testing File Command Processor Adapter\n";
    FileCommandProcessorAdapter fcp("Commands.txt");
    string fState="start";
    while(true){
        fcp.readCommand();
        Command* fCmnd=fcp.getCommand(); 
        if(!fCmnd) break; //end of file reached
        bool valid=fcp.validate(fCmnd,fState);
        cout<<*fCmnd<<", Valid?"<<(valid?" Yes":" No")<<endl;
        string c=fCmnd->getCommand();
        if(fState=="start"&& c.rfind("loadmap",0)==0) fState="maploaded";
        else if(fState=="maploaded"&&c=="validatemap") fState="mapvalidated";
        else if(fState=="mapvalidated"&& c.rfind("addplayer",0)==0) fState="playersadded";
        else if(fState=="playersadded"&& c=="gamestart") fState="assignreinforcement";
        else if(fState=="win"&& c=="replay") fState="start";
        else if(c=="quit"){
            cout<<"Exiting..."<<endl;
            break;
        }
        cout<<"Current state: "<<fState<<endl;

    }
  


}
int main(){
    testManualCommands();
    testCommandProcessor();
    testFileCommandProcessorAdapter();
    return 0;
}