#include "Engine.h" 
#include <iostream> 

int main()
{
	Solas::InitializeMemory();

	Solas::Engine::Instance().Initialize();
	Solas::Engine::Instance().Register();

	Solas::g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;
	while (!quit)
	{
		Solas::Engine::Instance().Update();

		if (Solas::g_inputSystem.GetKeyState(Solas::key_escape) == Solas::InputSystem::State::Pressed) quit = true;

		Solas::g_renderer.BeginFrame();
		Solas::g_renderer.EndFrame();
	}

	Solas::Engine::Instance().Shutdown();
}