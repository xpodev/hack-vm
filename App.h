#pragma once
#include "SDL_link.h"

#include <SDL_events.h>

// C++ doesn't like the old 'typedef struct SDL_Renderer SDL_Renderer', probably because it's C, so we redeclare it here
struct SDL_Renderer;


class App {
public:
	App(int width, int height);


public:
	void Clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);

	void ReDraw();

public:
	// getters

	SDL_Window* GetWindow() const;

	SDL_Renderer* GetRenderer() const;

public:
	// events

	virtual int OnExecute();

	virtual bool OnInit();

	virtual void OnEvent(SDL_Event const& event);

	virtual void OnLoop();

	virtual void OnRender();

	virtual void OnCleanup();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_running;
	int m_width, m_height;
};
