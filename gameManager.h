#ifndef gameManager_H
#define gameManager_H

#include <string>
#include <array>

class gameManager
{
	public:
		gameManager();
		std::string getNextDialogue();
		std::string currentDialogue;

	private:
		std::array<std::string, 6> dialogueList;
		int dialogueIndex;
};

#endif