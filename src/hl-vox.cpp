#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vox_enum.h"

void Init()
{
	SDL_Init( SDL_INIT_AUDIO );
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 1, 1024);
}

void Deinit()
{
	Mix_CloseAudio();
	
	Mix_Quit();
	SDL_Quit();
}

int load(std::string path, Uint16 buffer[])
{
	std::fstream file(path);

	if (file.is_open())
	{
		int len = 0;
		while (file.good())
		{
			std::string line;
			std::getline(file, line);
			
			
			buffer[len] = std::stoi(line);
			len++;
		}

		file.close();
		return len;
	}
	else
	{
		std::cout << "int load(std::string path, Uint16 buffer[] (hl-vox.cpp): Could not open file!\n";
		return -1;
	}
}

void speak(Uint16 vox_code)
{
	std::string fname = "vox/" + std::to_string((int) vox_code);

	Mix_Chunk* clip = Mix_LoadWAV(fname.c_str());
	
	Mix_PlayChannel(-1, clip, 0);
	
	while(Mix_Playing(0)) continue;
	
	Mix_FreeChunk(clip);

	SDL_Delay(100);
}

void speak_async(Uint16 vox_code)
{
		std::string fname = "vox/" + std::to_string((int) vox_code);

	Mix_Chunk* clip = Mix_LoadWAV(fname.c_str());
	
	Mix_PlayChannel(-1, clip, 0);
	
	Mix_FreeChunk(clip);

	SDL_Delay(100);
}

void speak(Uint16 buffer[], int len)
{
	for (int i = 0; i < len; i++)
	{		
		speak(buffer[i]);
	}
}

char* get_args(std::string key, int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (key.compare(argv[i]))
		{
			return argv[i+1];
		}
	}

	return NULL;
}

bool has_args(std::string key, int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (key.data() == argv[i])
		{
			return true;
		}
	}
	
	return false;
}

int main(int argc, char* argv[])
{
	Init();

	if (argc < 2)
	{
		std::cout << "Missing .VOX file!" << std::endl;
		speak(VOX_DEEOO);
		speak(VOX_ACCESS);
		speak(VOX_DENIED);

		Deinit();
		return -1;
	}
	
	Uint16 buffer[VOX_EXT_NUM_LINES];
	
	int len = load(argv[1], buffer);
	speak(buffer, len);

	Deinit();
	return 0;
}