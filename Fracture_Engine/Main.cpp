#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG(LOG_INFORMATION, "-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG(LOG_INFORMATION, "-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG(LOG_ERROR, "Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				LOG(LOG_INFORMATION, "Started application %s ...", App->GetAppName());
				state = MAIN_UPDATE;
				LOG(LOG_INFORMATION, "-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG(LOG_ERROR, "Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG(LOG_INFORMATION, "-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG(LOG_ERROR, "Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	LOG(LOG_INFORMATION, "Exiting application");

	RELEASE(App);

	return main_return;
}