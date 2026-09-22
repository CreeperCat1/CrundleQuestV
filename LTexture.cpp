#include "LTexture.h"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

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

	if (SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), 0, textColor, screenWidth - 20); textSurface == nullptr)
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