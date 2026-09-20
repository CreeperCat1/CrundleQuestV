#include "gameManager.h"
#include <iostream>

gameManager::gameManager():
	dialogueList{ "WELCOME TO CRUNDAL QUEST 5: THE CRYSTALS OF GINGLEDOOF!",
	"DO YOU DARE ENTER THE MOUNTAIN CABIN OF PLINTILSAD AND GET THE SPELL OF FINGLEDOOF?",
	"WILL YOU GET THE CRYSTALS OF GRINGIFF?",
	"AND DEFEAT THE EVIL GLUNBUFF?",
	"BUT FIRST YOU HAVE TO HAVE THE BITS AND THE BUUTS OF GRINGLEDOOF.",
	"CRUNDLE QUEST V - THE CRYSTALS OF GINGLEDOOF!"
	},
	dialogueIndex{ 0 },
	currentDialogue{ "" }
{

}

std::string gameManager::getNextDialogue()
{
	if (dialogueIndex < dialogueList.size())
	{
		currentDialogue = dialogueList[dialogueIndex];
		dialogueIndex++;
		return currentDialogue;
	}
	else
	{
		currentDialogue = "THE END";
		std::cout << "end";
		return currentDialogue;
	}
}