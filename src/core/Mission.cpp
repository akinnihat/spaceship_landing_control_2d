#include "Mission.h"

const int SCREEN_WIDTH = 768;    
const int SCREEN_HEIGHT = 1024;	 
bool restart_flag = true;

Mission::Mission()
{

}

Mission::~Mission()
{
	ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	SDL_DestroyRenderer(m_Renderer);
    m_Renderer = NULL;

    SDL_DestroyWindow(m_Window);
    m_Window = NULL;
   
    SDL_Quit();
}

void Mission::start()
{
	// Main Loop
	while(restart_flag)
	{	
		bool visuals_ok = initVisuals();
		int vis_init_cnt{10};

		while(!visuals_ok)
		{
			if (vis_init_cnt == 0) { exit(0); } 
			visuals_ok = initVisuals();
			printf("Visuals couldn't been initialized.\n");
			vis_init_cnt--;
		}
		m_PIDControllerHorizontal.setPIDParameters(4.2, 2.2, 3.2);

		SDL_Texture* ground_texture = IMG_LoadTexture(m_Renderer, "imgs/ground.png");
		initEnvironment(9.81, ground_texture);

		SDL_Texture* spaceship_texture = IMG_LoadTexture(m_Renderer, "imgs/spaceship.png");
		initSpaceship(spaceship_texture);

		runMission();
	}

}

void Mission::initSpaceship(SDL_Texture *texture)
{
	SDL_Event e;
	bool quit_flag = false;
	while (!quit_flag)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&m_MouseX, &m_MouseY);
				SDL_RenderDrawPoint(m_Renderer, m_MouseX, m_MouseY);
				SDL_RenderPresent(m_Renderer);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				m_Spaceship.spawnSpaceship(m_MouseX, m_MouseY, texture);
				quit_flag = true;
				break;
			}
			printf("X: %d\nY: %d\n", m_MouseX, m_MouseY);
		}
	}
}

void Mission::initEnvironment(float gravity, SDL_Texture *texture)
{
	m_Environment.createEnvironment(gravity, texture);
	m_TargetFlag = IMG_LoadTexture(m_Renderer, "imgs/flag.png");
}

bool Mission::initVisuals()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
		m_Window = SDL_CreateWindow("Spaceship Mission", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
		if (m_Window == NULL)
		{
			printf("Window could not be created. Error: %s\n", SDL_GetError());
			success = false;
		} 
		else
		{
			// Create renderer
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_Renderer == NULL)
			{
				printf("Renderer could not be created. Error: %s\n", SDL_GetError());
			}
		}  	
	}

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
	ImGui_ImplSDLRenderer2_Init(m_Renderer);

	return success;
}

void Mission::updateSpaceship(double dt)
{
	
	SDL_Rect spaceship_rect = { m_Spaceship.getX(), m_Spaceship.getY(), 50, 50 };
	SDL_RenderCopy(m_Renderer, m_Spaceship.getTexture(), NULL, &spaceship_rect);

	SDL_Rect ground_rect = { 0, SCREEN_HEIGHT-50, SCREEN_WIDTH, 50 };
	SDL_RenderCopy(m_Renderer, m_Environment.getTexture(), NULL, &ground_rect);

	SDL_Rect flag_rect = { (SCREEN_WIDTH/2)-50, SCREEN_HEIGHT-100, 50, 50};
	SDL_RenderCopy(m_Renderer, m_TargetFlag, NULL, &flag_rect);
	
	float target = (SCREEN_WIDTH/2)-50;
	float error = target - m_Spaceship.getX();

	double pid_out = m_PIDControllerHorizontal.calculatePID(error, dt);

	float dh = 0.5*m_Environment.getEffectingGravity()*dt*dt;   // dh = (g*t^2)/2

	if (m_Spaceship.getY() >= SCREEN_HEIGHT-100) { m_Spaceship.setState(State::LANDED); }

	if (m_Spaceship.getState() == State::LANDED)
	{
		printf("\n\nSpaceship landed succesfully. Press ESC to exit. \n\n");
	}
	else 
	{ 
		m_Spaceship.move(pid_out, dh);  
		printf("Error: %f \ndx: %f \n", error, pid_out); 
	}
}

void Mission::runMission()
{
	Uint32 timer_start = SDL_GetTicks();
	double dt;

	static float slider_p_value = 0.0f;
	static float slider_i_value = 0.0f;
	static float slider_d_value = 0.0f;
 	bool restart_button = false;
	while(true)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
			switch(e.type)
			{
				case SDL_QUIT:
					exit(0);
					break;

				case SDL_KEYDOWN:
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						exit(0);
						break;					
					}
					//if (e.key.keysym.scancode == SDL_SCANCODE_A) { m_Spaceship.move(-4, 0); }
					//if (e.key.keysym.scancode == SDL_SCANCODE_D) { m_Spaceship.move(4, 0); }
			}
		}

		ImGui_ImplSDL2_NewFrame();
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Control Panel");
		ImGui::SliderFloat("P", &slider_p_value, 0.0f, 5.0f);  // to be implemented
		ImGui::SliderFloat("I", &slider_i_value, 0.0f, 5.0f);  // to be implemented
		ImGui::SliderFloat("D", &slider_d_value, 0.0f, 5.0f);  // to be implemented
		if (ImGui::Button("Restart")) 
		{ 
			// To be implemented
			restart_button = true;
			restart_flag = true; 
			// printf("RESTART\n");
			// SDL_RenderClear(m_Renderer);
			// ImGui_ImplSDL2_Shutdown();
    		// ImGui::DestroyContext();
			// SDL_DestroyRenderer(m_Renderer);
			// m_Renderer = NULL;

			// SDL_DestroyWindow(m_Window);
			// m_Window = NULL;
   
    		//SDL_Quit();
		}
		//if (ImGui::Button("Quit")) { restart_flag = false; }
		ImGui::End();    

		SDL_Delay(12);
	
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);
		SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);

		Uint32 timer_end = SDL_GetTicks();
		dt = ( timer_end - timer_start ) / 1000.0f;
		updateSpaceship(dt);

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(m_Renderer);
		
		if (restart_button) { break; }
	}
}

void Mission::initFlag()
{

}