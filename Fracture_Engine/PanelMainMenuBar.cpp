#include "PanelMainMenuBar.h"
#include "Application.h"
#include "PanelConsole.h"

PanelMainMenuBar::PanelMainMenuBar(std::string name) : Panel(name)
{

}

PanelMainMenuBar::~PanelMainMenuBar()
{

}

bool PanelMainMenuBar::Update()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close"))
			{
				App->CloseApplication();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Create"))
		{
			bool create_empty_game_object = false;
			ImGui::MenuItem("Empty GameObject", NULL, &create_empty_game_object);
			if (create_empty_game_object)
				App->scene_intro->CreateEmptyGameObject("Empty", App->scene_intro->root_game_object);
			
			bool create_cube = false;
			ImGui::MenuItem("Cube", NULL, &create_cube);
			if (create_cube)
				App->scene_intro->CreateEmptyGameObject("Cube", App->scene_intro->root_game_object);

			bool create_sphere = false;
			ImGui::MenuItem("Sphere", NULL, &create_sphere);
			if (create_sphere)
				App->scene_intro->CreateEmptyGameObject("Sphere", App->scene_intro->root_game_object);

			bool create_plane = false;
			ImGui::MenuItem("Plane", NULL, &create_plane);
			if (create_plane)
				App->scene_intro->CreateEmptyGameObject("Plane", App->scene_intro->root_game_object);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Configuration", NULL, &(App->user_interface->panel_configuration->active));
			ImGui::MenuItem("Console", NULL, &(App->user_interface->panel_console->active));
			ImGui::MenuItem("Hierarchy", NULL, &(App->user_interface->panel_hierarchy->active));
			ImGui::MenuItem("Inspector", NULL, &(App->user_interface->panel_inspector->active));
			ImGui::MenuItem("Scene", NULL, &(App->user_interface->panel_scene->active));
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				App->user_interface->panel_about->SetActive(true);
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Webpage"))
			{
				App->RequestBrowser("https://vsrushy.github.io/Fracture_Engine/");
			}
			if (ImGui::MenuItem("GitHub"))
			{
				App->RequestBrowser("https://github.com/vsRushy/Fracture_Engine/");
			}
			if (ImGui::MenuItem("Report a bug"))
			{
				App->RequestBrowser("https://github.com/vsRushy/Fracture_Engine/issues/");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	return true;
}
