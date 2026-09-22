#ifndef LTexture_H
#define LTexture_H

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

// constexpr int screenWidth{ 602 }; - defined globally
inline constexpr int screenWidth{ 602 };

extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

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

		// remove default class functions
		LTexture(const LTexture&) = delete;
		LTexture& operator=(const LTexture&) = delete;
		LTexture(LTexture&&) = delete;
		LTexture& operator=(LTexture&&) = delete;

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

#endif