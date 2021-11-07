#include "App.h"

#include <SDL.h>


App::App(int width, int height) 
	: m_window{ nullptr }
	, m_renderer{ nullptr }
	, m_running{ true }
	, m_width{ width }
	, m_height{ height }
{

}

void App::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
	ReDraw();
}

void App::ReDraw() {
	SDL_RenderPresent(m_renderer);
}

SDL_Window* App::GetWindow() const
{
	return m_window;
}

SDL_Renderer* App::GetRenderer() const
{
	return m_renderer;
}

int App::OnExecute() {
	if (!OnInit()) {
		SDL_Log("%s", SDL_GetError());
		return -1;
	}

	SDL_Event event;
	while (m_running)
	{
		while (SDL_PollEvent(&event)) OnEvent(event);

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

bool App::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	if ((m_window = SDL_CreateWindow(
		"Window", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		m_width, m_height, 
		0)) == nullptr) return false;
	if ((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) return false;

	return m_running;
}

void App::OnEvent(SDL_Event const& event) {
	if (event.type == SDL_QUIT) m_running = false;
}

void App::OnLoop() {
	
}

void App::OnRender() {

}

void App::OnCleanup() {
	SDL_Quit();
}
