#include <list>
#include <map>

#include "Application.h"
#include "ModuleSceneIntro.h"

#include "Component_Mesh.h"

ComponentMesh::ComponentMesh(GameObject* target, Mesh* mesh) : Component(target), mesh(mesh)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{

}

void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::Checkbox("Active", &active);

		std::string n_vertices = std::to_string(mesh->num_vertices);
		ImGui::Text("Number of vertices: "); ImGui::SameLine(); 
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), n_vertices.c_str());

		std::string n_indices = std::to_string(mesh->num_indices);
		ImGui::Text("Number of indices: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), n_indices.c_str());

		std::string n_normals = std::to_string(mesh->num_normals);
		ImGui::Text("Number of normals: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), n_normals.c_str());

		std::string n_uvs = std::to_string(mesh->num_uvs);
		ImGui::Text("Number of normals: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 1.0f), n_uvs.c_str());
	}
}

bool ComponentMesh::Update(float dt)
{
	return true;
}
