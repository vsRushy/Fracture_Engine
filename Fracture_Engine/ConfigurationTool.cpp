#include "ConfigurationTool.h"

JSON_Wrapper::JSON_Wrapper(const char* file, const char* node)
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

JSON_Wrapper::~JSON_Wrapper()
{
	json_value_free(j_value);
}

JSON_Wrapper& JSON_Wrapper::GetNode(const char* section_name)
{
	j_node_object = json_object_get_object(j_object, section_name);
	return *this;
}

int JSON_Wrapper::GetInt(const char* name)
{
	return (int)json_object_dotget_number(j_node_object, name);
}

uint JSON_Wrapper::GetUint(const char* name)
{
	return (uint)json_object_dotget_number(j_node_object, name);
}

float JSON_Wrapper::GetFloat(const char* name)
{
	return (float)json_object_dotget_number(j_node_object, name);
}

bool JSON_Wrapper::GetBool(const char* name)
{
	return (bool)json_object_dotget_boolean(j_node_object, name);
}

const char* JSON_Wrapper::GetString(const char* name)
{
	return json_object_dotget_string(j_node_object, name);
}

void JSON_Wrapper::SetInt(const char* name, const int& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void JSON_Wrapper::SetUint(const char* name, const uint& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void JSON_Wrapper::SetFloat(const char* name, const float& value)
{
	json_object_set_number(j_node_object, name, (double)value);
}

void JSON_Wrapper::SetBool(const char* name, const bool& value)
{
	json_object_set_boolean(j_node_object, name, value);
}

void JSON_Wrapper::SetString(const char* name, const char* value)
{
	json_object_set_string(j_node_object, name, value);
}
