#include "PanelConsole.h"

PanelConsole::PanelConsole(std::string name, bool active) : Panel(name, active)
{

}

PanelConsole::~PanelConsole()
{

}

bool PanelConsole::Update()
{
	ImGui::Begin("Console");

	for (std::list<std::pair<LOG_TYPE, const char*>>::iterator item = console_logs.begin(); item != console_logs.end(); item++)
	{
		char tmp_str[250];

		switch (item->first)
		{
		case LOG_INFORMATION:
			strcpy(tmp_str, "[Information]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));
			break;
		case LOG_WARNING:
			strcpy(tmp_str, "[Warning]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
			break;
		case LOG_ERROR:
			strcpy(tmp_str, "[Error]: ");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		default:
			break;
		}

		strcat(tmp_str, item->second);
		ImGui::TextUnformatted(tmp_str);
		ImGui::PopStyleColor();
	}

	if (scroll_down_console)
		ImGui::SetScrollHereY(1.0f);

	scroll_down_console = false;
	ImGui::End();

	return true;
}

bool PanelConsole::CleanUp()
{
	for (std::list<std::pair<LOG_TYPE, const char*>>::iterator item = console_logs.begin(); item != console_logs.end(); item++)
	{
		free((void*)item->second); // TOCHECK
	}
	console_logs.clear();

	return true;
}

void PanelConsole::Log(LOG_TYPE type, const char* text_log)
{
	console_logs.push_back(std::make_pair(type, strdup(text_log)));
	scroll_down_console = true;
}
