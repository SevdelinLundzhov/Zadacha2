//============================================================================
// Name        : SkachashtoTopche.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL2\\SDL.h>
#include <SDL2\\SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

class LTexture
{
public:
	LTexture();

	~LTexture();

	bool loadFromFIle( string path);

	void free();

	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	void setBlendMode( SDL_BlendMode blending );

	void setAlpha( Uint8 alpha );

	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
			                                          SDL_Point* center = NULL,
						                       SDL_RendererFlip flip = SDL_FLIP_NONE );

	int getWidth();
	int getHeight();

private:

	SDL_Texture *mTexture;

	int width;
	int height;
};

bool init();

bool loadMedia();

void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
LTexture ballTexture;

LTexture::LTexture()
{
	mTexture = NULL;
	width = 0;
	height = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFIle(string path)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n",
					                                         path.c_str(), SDL_GetError() );
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );

	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		width = 0;
		height = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center,
		                                                           SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if( clip != NULL )
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return width;
}

int LTexture::getHeight()
{
	return height;
}

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
						                                              SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED |
					                                          SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n",
							                                             IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
		bool success = true;

		if( !ballTexture.loadFromFIle( "src/Ball.png" ) )
	{
		printf( "Failed to load arrow texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	ballTexture.free();

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



int main( int argc, char* args[] ) {

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			double degrees = 0;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_a:
							degrees -= 60;
							break;

							case SDLK_d:
							degrees += 60;
							break;

							case SDLK_q:
							flipType = SDL_FLIP_HORIZONTAL;
							break;

							case SDLK_w:
							flipType = SDL_FLIP_NONE;
							break;

							case SDLK_e:
							flipType = SDL_FLIP_VERTICAL;
							break;
						}
					}
				}

				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				ballTexture.render( ( SCREEN_WIDTH - ballTexture.getWidth() ) / 30,
						                     ( SCREEN_HEIGHT - ballTexture.getHeight() ) / 30,
						                                          NULL, degrees, NULL, flipType );

				SDL_RenderPresent( renderer );
			}
		}
	}

	close();

	return 0;
}
