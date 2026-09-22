#ifndef gameManager_H
#define gameManager_H

#include <string>
#include <array>

class gameManager
{
	public:
		gameManager();
		~gameManager() = default;

		std::string getNextDialogue();
		std::string currentDialogue;

		// remove default class functions
		gameManager(const gameManager&) = delete;
		gameManager& operator=(const gameManager&) = delete;
		gameManager(gameManager&&) = delete;
		gameManager& operator=(gameManager&&) = delete;

	private:
		std::array<std::string, 6> dialogueList;
		int dialogueIndex;
};

#endif