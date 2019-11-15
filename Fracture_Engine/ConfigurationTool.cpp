#include "ConfigurationTool.h"

ConfigurationTool::ConfigurationTool(const char* file, const char* node)
{
	j_value = json_parse_file(file);

	if (j_value == NULL)
	{
		LOG(LOG_ERROR, "Couldn't find the JSON file %s.", file);
		j_value = json_value_init_object();
	}
	else
	{
		LOG(LOG_INFORMATION, "Loaded correctly the JSON file %s.", file);
	}

	j_object = json_value_get_object(j_value);
	j_node_object = json_object_get_object(j_object, node);
}

ConfigurationTool::~ConfigurationTool()
{
	json_value_free(j_value);
}

void ConfigurationTool::SetNode(const char* section_name)
{
	j_node_object = json_object_get_object(j_object, section_name);
}

int ConfigurationTool::GetInt(const char* name)
{
	return (int)json_object_dotget_number(j_node_object, name);
}

uint ConfigurationTool::GetUint(const char* name)
{
	return (uint)json_object_dotget_number(j_node_object, name);
}

float ConfigurationTool::GetFloat(const char* name)
{
	return (float)json_object_dotget_number(j_node_object, name);
}

bool ConfigurationTool::GetBool(const char* name)
{
	return (bool)json_object_dotget_boolean(j_node_object, name);
}

const char* ConfigurationTool::GetString(const char* name)
{
	return json_object_dotget_string(j_node_object, name);
}

void ConfigurationTool::SetInt(const char* name, const int& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void ConfigurationTool::SetUint(const char* name, const uint& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void ConfigurationTool::SetFloat(const char* name, const float& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void ConfigurationTool::SetBool(const char* name, const bool& value)
{
	json_object_set_boolean(j_node_object, name, value);
}

void ConfigurationTool::SetString(const char* name, const char* value)
{
	json_object_set_string(j_node_object, name, value);
}
