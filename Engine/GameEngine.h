//
// Created by abede on 2025-09-28.
//

#ifndef COMP_345_PROJECT_FALL_2025_GAMEENGINE_H
#define COMP_345_PROJECT_FALL_2025_GAMEENGINE_H

#include <string>



class GameEngine {

private:


    std::string gameState = "start";

    std::string input;

public:

	GameEngine();

    std::string getGameState();

    void loopEntrance();
	void loadMap();
	void validateMap();
	void addPlayer();
	void assignCountries();

	void issueOrder();
	void endIssueOrders();
	void execOrder();
	void endExecOrders();
	void win();
	void play();
    void end();




};


#endif //COMP_345_PROJECT_FALL_2025_GAMEENGINE_H