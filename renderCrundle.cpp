#include "LTexture.h"
#include "gameManager.h"
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

// constexpr int screenWidth{ 602 }; defined in LTexture.h
constexpr int screenHeight{ 968 };
constexpr int screenFPS{ 5 };

bool init();
bool loadMedia();
bool loadText();
bool loadAudio();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
TTF_Font* gFont{ nullptr };
LTexture gTextTexture;
LTexture gPngTexture;

MIX_Mixer* gMixer{ nullptr };
MIX_Track* gMusicTrack{ nullptr };

std::string textToDisplay{ "PRESS ANY KEY TO START" };

float timer{ 255 };
int frameCounter{ 0 };

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false)
	{
		return false;
	}
	else
	{
		if (SDL_CreateWindowAndRenderer("Crundal Quest 5: The Crystals of Gingledoof", screenWidth, screenHeight, 0, &gWindow, &gRenderer) == false)
		{
			return false;
		}
		else
		{
			if (TTF_Init() == false)
			{
				return false;
			}

			if (MIX_Init() == false)
			{
				return false;
			}
			else
			{
				if (gMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr); gMixer == nullptr)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool loadMedia()
{
	std::string fontPath{ "terminal.ttf" };
	if (gFont = TTF_OpenFont(fontPath.c_str(), 15); gFont == nullptr)
	{
		return false;
	}

	if (gPngTexture.loadFromFile("art.png") == false)
	{
		return false;
	}

	return true;
}

bool loadText()
{
	SDL_Color textColor{ 0xFF, 0xFF, 0xFF, 0xFF };
	if (gTextTexture.loadFromRenderedText(textToDisplay, textColor) == false)
	{
		return false;
	}

	return true;
}

bool loadAudio()
{
	if (MIX_Audio* musicAudio = MIX_LoadAudio(gMixer, "title.mp3", false); musicAudio == nullptr)
	{
		return false;
	}
	else
	{
		if (gMusicTrack = MIX_CreateTrack(gMixer); gMusicTrack == nullptr)
		{
			return false;
		}
		else
		{
			MIX_SetTrackAudio(gMusicTrack, musicAudio);
		}

		MIX_DestroyAudio(musicAudio);
	}

	return true;
}

void close()
{
	gTextTexture.destroy();

	TTF_CloseFont(gFont);
	gFont = nullptr;

	gPngTexture.destroy();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	MIX_DestroyTrack(gMusicTrack);
	gMusicTrack = nullptr;

	MIX_DestroyMixer(gMixer);
	gMixer = nullptr;

	TTF_Quit();
	SDL_Quit();
	MIX_Quit();
}

int main()
{
	if (!init() || !loadMedia() || !loadText() || !loadAudio())
	{
		return 1;
	}
	else
	{
		bool quit = false;

		SDL_Event e;
		SDL_zero(e);

		constexpr Uint64 nsPerFrame = 1000000000 / screenFPS;

		gameManager manager;

		while (quit == false)
		{
			Uint64 frameStart = SDL_GetTicksNS();

			while (SDL_PollEvent(&e) == true)
			{
				if (e.type == SDL_EVENT_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_EVENT_KEY_DOWN)
				{
					textToDisplay = manager.getNextDialogue();

					if (!loadText())
					{
						return 1;
					}
				}
			}

			if (MIX_TrackPlaying(gMusicTrack) == false)
			{
				SDL_PropertiesID props = SDL_CreateProperties();
				SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
				MIX_PlayTrack(gMusicTrack, props);
				SDL_DestroyProperties(props);
			}

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			gPngTexture.render(0.f, 0.f);
			gTextTexture.render(20.f, 800.f);

			if (timer >= 0)
			{
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, static_cast<Uint8>(timer));
				SDL_RenderFillRect(gRenderer, nullptr);
				timer -= 5;
			}

			SDL_RenderPresent(gRenderer);

			Uint64 frameTime = SDL_GetTicksNS() - frameStart;
			if (frameTime < nsPerFrame)
			{
				SDL_DelayNS(nsPerFrame - frameTime);
			}
			frameCounter++;
			std::cout << frameCounter << " frame" << std::endl;
		}
	}

	close();

	return 0;
}