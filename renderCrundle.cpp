#include "gameManager.h"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

constexpr int screenWidth{ 602 };
constexpr int screenHeight{ 968 };

class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile(std::string path);

		#if defined(SDL_TTF_MAJOR_VERSION)
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		#endif

		void destroy();

		void render(float x, float y);

		int getWidth();
		int getHeight();
		bool isLoaded();

		//remove default class functions
		LTexture(const LTexture&) = delete;
		LTexture& operator=(const LTexture&) = delete;
		LTexture(LTexture&&) = delete;
		LTexture& operator=(LTexture&&) = delete;

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
TTF_Font* gFont{ nullptr };
LTexture gTextTexture;
LTexture gPngTexture;

std::string textToDisplay{ "WELCOME" };

LTexture::LTexture():
	mTexture{ nullptr },
	mWidth{ 0 },
	mHeight{ 0 }
{

}

LTexture::~LTexture()
{
	destroy();
}

bool LTexture::loadFromFile(std::string path)
{
	destroy();

	if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr)
	{
		SDL_Log("Failed to load image: %s, Error: %s", path.c_str(), SDL_GetError());
	}
	else
	{
		if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr)
		{
			SDL_Log("Failed to create texture: %s, Error: %s", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_DestroySurface(loadedSurface);
	}

	return mTexture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	destroy();

	if (SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), 0, textColor); textSurface == nullptr)
	{
		SDL_Log("Failed to load text surface: %s, Error: %s", textureText.c_str(), SDL_GetError());
	}
	else
	{
		if (mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); mTexture == nullptr)
		{
			SDL_Log("Failed to create text texture: %s, Error: %s", textureText.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_DestroySurface(textSurface);
	}

	return mTexture != nullptr;
}
#endif

void LTexture::destroy()
{
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;

	mWidth = 0;
	mHeight = 0;
}

void LTexture::render(float x, float y)
{
	SDL_FRect dstRect{ x, y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

	SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::isLoaded()
{
	return mTexture != nullptr;
}


bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == false)
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
	else
	{
		SDL_Color textColor{ 0xFF, 0xFF, 0xFF, 0xFF };
		if (gTextTexture.loadFromRenderedText(textToDisplay, textColor) == false)
		{
			return false;
		}
	}

	if (gPngTexture.loadFromFile("art.png") == false)
	{
		return false;
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

	TTF_Quit();
	SDL_Quit();
}

int main()
{
	if (init() == false)
	{
		return 1;
	}
	else
	{
		if (loadMedia() == false)
		{
			return 2;
		}
		else
		{
			bool quit = false;

			SDL_Event e;
			SDL_zero(e);

			gameManager manager;

			while (quit == false)
			{
				while (SDL_PollEvent(&e) == true)
				{
					if (e.type == SDL_EVENT_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_EVENT_KEY_DOWN)
					{
						textToDisplay = manager.getNextDialogue();

						if (loadMedia() == false)
						{
							return 2;
						}
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				gPngTexture.render(0.f, 0.f);
				gTextTexture.render(20.f, 800.f);

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}