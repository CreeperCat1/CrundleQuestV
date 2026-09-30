#ifndef gameManager_H
#define gameManager_H

#include <string>
#include <vector>

class gameManager
{
	public:
		gameManager();
		~gameManager() = default;

		std::string getNextDialogue();

		// remove default class functions
		gameManager(const gameManager&) = delete;
		gameManager& operator=(const gameManager&) = delete;
		gameManager(gameManager&&) = delete;
		gameManager& operator=(gameManager&&) = delete;

	private:
		const std::vector<std::string> dialogueList;
		int dialogueIndex;
		std::string currentDialogue;
};

#endif