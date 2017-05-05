#include <Engine\Game_Objects\GameObject_3D.h>
#include <Engine/Component/RenderComp_3D.h>
#include <Engine/Component/Transform_3D.h>
#include <Engine\Creators\Texture.h>
#include <Engine/Mesh/Mesh_3D.h>
#include <glad\glad.h>
#include <iostream>

glm::mat4 GameObject_3D::get_ParentMatrix()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_ModelMatrix();
}

GameObject_3D::GameObject_3D()
{
	b_RenderStatus = true;
}

GameObject_3D::GameObject_3D(const GameObject_3D & p_NewObject_In) : Game_Object(p_NewObject_In)
{
	for (auto const& pair : p_NewObject_In.mipo_Components)
	{
		if (pair.second->get_Type() == "Mesh_3D")
		{
			auto mesh_3D = static_cast<Mesh_3D*>(pair.second);
			add_Component("Mesh_3D", mesh_3D);
		}
		else if (pair.second->get_Type() == "Transform_3D")
		{
			auto transform_3D = static_cast<Transform_3D*>(pair.second);
			add_Component("Transform_3D", new Transform_3D(*transform_3D));
		}
		else if (pair.second->get_Type() == "RenderComp_3D")
		{
			auto renderComp_3D = static_cast<RenderComp_3D*>(pair.second);
			add_Component("RenderComp_3D", new RenderComp_3D(*renderComp_3D));
		}
	}

	s_PrefabName = p_NewObject_In.s_PrefabName;
}

void GameObject_3D::add_Component(std::string s_Name_In, Component* p_Component_In)
{
	mipo_Components.insert(std::pair<std::string, Component*>(s_Name_In, p_Component_In));

	if (s_Name_In == "RenderComp_3D")
	{
		auto found_Mesh = mipo_Components.find("Mesh_3D");

		if (found_Mesh == mipo_Components.end()) std::cout << "Mesh not found" << "\n";
		else
		{
			auto found_Render = mipo_Components.find("RenderComp_3D")->second;
			static_cast<RenderComp_3D*>(found_Render)->set_Mesh(static_cast<Mesh_3D*>(found_Mesh->second));
		}

	}
}

void GameObject_3D::add_Texture(std::string s_Name_In, Texture* p_Texture_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->add_Texture(s_Name_In, p_Texture_In);
}

void GameObject_3D::update()
{
	if (po_Parent != nullptr)
	{
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->force_Update(); // Update must be forced to update any children
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update(static_cast<GameObject_3D*>(po_Parent)->get_ParentMatrix());
	}
	else
	{
		static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update();
	}
}

void GameObject_3D::render(Shader* p_Shader_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update_Shader(p_Shader_In);
	if (b_RenderStatus) static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->render(GL_TEXTURE_2D, GL_TRIANGLES, p_Shader_In);
}

void GameObject_3D::clean_Up()
{
	//Remove all components
	for (auto const& components : mipo_Components) if (components.first != "Mesh_3D") delete components.second;
	mipo_Components.clear();
}

void GameObject_3D::force_Update()
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->force_Update();
}

void GameObject_3D::set_Position(glm::vec3 v3_Position_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Position(v3_Position_In);
}

void GameObject_3D::set_Scale(glm::vec3 v3_Scale_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Scale(v3_Scale_In);
}

void GameObject_3D::set_Origin(glm::vec3 v3_Origin_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Origin(v3_Origin_In);
}

void GameObject_3D::set_Rotation(glm::quat quat_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->set_Rotation(quat_In);
}

void GameObject_3D::update_Rotation(glm::quat quat_In)
{
	static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->update_Rotation(quat_In);
}

glm::vec3 GameObject_3D::get_Position()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Position();
}

glm::vec3 GameObject_3D::get_Origin()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Origin();
}

glm::quat GameObject_3D::get_Rotation()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Rotation();
}

glm::vec3 GameObject_3D::get_Scale()
{
	return static_cast<Transform_3D*>(mipo_Components.find("Transform_3D")->second)->get_Scale();
}

void GameObject_3D::set_Shininess(float f_Shiny_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->set_Shininess(f_Shiny_In);
}

void GameObject_3D::set_Tiles(glm::vec2 v2_Tiles_In)
{
	static_cast<RenderComp_3D*>(mipo_Components.find("RenderComp_3D")->second)->set_Tiles(v2_Tiles_In);
}

std::string GameObject_3D::get_Type()
{
	return "GameObject_3D";
}


