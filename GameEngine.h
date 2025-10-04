//
// Created by abede on 2025-09-28.
//

#ifndef COMP_345_PROJECT_FALL_2025_GAMEENGINE_H
#define COMP_345_PROJECT_FALL_2025_GAMEENGINE_H

#include <string>



class GameEngine {

private:
    std::ifstream file;

    std::string gameState;

public:

	GameEngine();


	void loadMap(std::string mapFileName);
	void validateMap();
	void addPlayer();
	void assignCountries();
	void reinforce();
	void issueOrders();
	void endIssueOrders();
	void executeOrders();
	void endExecuteOrders();
	void win();
	void play();
    void end();




}


#endif //COMP_345_PROJECT_FALL_2025_GAMEENGINE_H