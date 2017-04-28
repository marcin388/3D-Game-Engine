#include <Engine\Lighting\Point_Light.h>
#include <glad\glad.h>
#include <Engine\Creators\Shader.h>


Point_Light::Point_Light(glm::vec3 v3_Ambient_In, glm::vec3 v3_Diffuse_In, glm::vec3 v3_Specular_In, float f_Constant_In, float f_Linear_In, float f_Quadratic_In, unsigned int i_ID_In) : Light(v3_Ambient_In, v3_Diffuse_In, v3_Specular_In)
{
	f_Constant = f_Constant_In;
	f_Linear = f_Linear_In;
	f_Quadratic = f_Quadratic_In;
	i_ID = i_ID_In;
}

void Point_Light::set_Constant(float f_Constant_In)
{
	f_Constant = f_Constant_In;
}

void Point_Light::set_Linear(float f_Linear_In)
{
	f_Linear = f_Linear_In;
}

void Point_Light::set_Quadratic(float f_Quadratic_In)
{
	f_Quadratic = f_Quadratic_In;
}

void Point_Light::update_Shader(Shader* p_Shader_In)
{
	std::string point_Light = "point_Light[" + std::to_string(i_ID) + "]";

	std::string pos = point_Light + ".position";
	GLint posLoc = glGetUniformLocation(p_Shader_In->get_Program(), pos.c_str());
	glUniform3f(posLoc, get_Position().x, get_Position().y, get_Position().z);

	std::string amb = point_Light + ".ambient";
	GLint ambientLoc = glGetUniformLocation(p_Shader_In->get_Program(), amb.c_str());
	glUniform3f(ambientLoc, v3_Ambient.x, v3_Ambient.y, v3_Ambient.z);

	std::string diff = point_Light + ".diffuse";
	GLint diffuseLoc = glGetUniformLocation(p_Shader_In->get_Program(), diff.c_str());
	glUniform3f(diffuseLoc, v3_Diffuse.x, v3_Diffuse.y, v3_Diffuse.z);

	std::string spec = point_Light + ".specular";
	GLint specularLoc = glGetUniformLocation(p_Shader_In->get_Program(), spec.c_str());
	glUniform3f(specularLoc, v3_Specular.x, v3_Specular.y, v3_Specular.z);

	std::string cons = point_Light + ".constant";
	GLint constantLoc = glGetUniformLocation(p_Shader_In->get_Program(), cons.c_str());
	glUniform1f(constantLoc, f_Constant);

	std::string lin = point_Light + ".linear";
	GLint linearLoc = glGetUniformLocation(p_Shader_In->get_Program(), lin.c_str());
	glUniform1f(linearLoc, f_Linear);

	std::string quad = point_Light + ".quadratic";
	GLint quadraticLoc = glGetUniformLocation(p_Shader_In->get_Program(), quad.c_str());
	glUniform1f(quadraticLoc, f_Quadratic);
}