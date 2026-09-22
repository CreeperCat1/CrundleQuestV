#include "gameManager.h"
#include <iostream>
#include <string>

gameManager::gameManager():
	dialogueList{ "WELCOME TO CRUNDLE QUEST V - THE CRYSTALS OF GINGLEDOOF!",
	"DO YOU DARE ENTER THE MOUNTAIN CABIN OF PLINTILSAD AND GET THE SPELL OF FINGLEDOOF?", // Vooldizad and Spade
	"WILL YOU GET THE CRYSTALS OF GRINGIFF?", // gringeef
	"AND DEFEAT THE EVIL GLUNBUFF?", // gloomboof
	"BUT FIRST YOU HAVE TO HAVE THE BITS AND THE BUUTS OF GRINGLEDOOF.", // beetz and bootz or boots "it covers his bits and boots"
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
// story is enter mountain cabin and get spell which summons sword
// then get crystals of gringiff which empowers the sword
// then get bits and buuts of gringledoof which is armor
// then defeat evil glunbuff to get crystals of gingledoof (auto kill you unless having bits and buuts of gringledoof)
// evil glunbuff is protecting the crystals of gingledoof
// the end