#include "StateVisitor.h"


namespace OGE
{
	void StateVisitor::Visit(SPtr(Interviewee) object)
	{
		if (object == nullptr)
			return;

		switch (object->GetName())
		{
		case OGE_PhongState:
			Process(SPtrCast(PhongState, object));
			break;
		case OGE_CustomState:
			Process(SPtrCast(CustomState, object));
			break;
		}
	}


	void StateVisitor::Process(SPtr(PhongState) state)
	{
		//初始化变量
		shader_ = nullptr;
		emission_map_ = nullptr;
		diffuse_map_ = nullptr;
		specular_map_ = nullptr;
		materials_ = UniformList::Create();
		alpha_ = 1.0f - state->GetTransparent();

		SPtr(Material) material = state->GetMaterial();
		SPtr(Texture2D)	emission_map = material->GetEmissionMap();
		SPtr(Texture2D)	diffuse_map = material->GetDiffuseMap();
		SPtr(Texture2D)	specular_map = material->GetSpecularMap();
		std::string	vertex_shader_code = "";
		std::string	fragment_shader_code = "";

		bool EMISSION_MAP = emission_map != nullptr;
		bool DIFFUSE_MAP = diffuse_map != nullptr;
		bool SPECULAR_MAP = specular_map != nullptr;
		bool TEXCOORD = EMISSION_MAP || DIFFUSE_MAP || SPECULAR_MAP;
		bool DIR_LIGHT = lights_[0]->GetName() == OGE_DirLight;
		bool POINT_LIGHT = lights_[0]->GetName() == OGE_PointLight;

		//添加alpha
		materials_->AddUniform(UniformFloat::Create("alpha", alpha_));

		//添加material和texture
		if (EMISSION_MAP)
		{
			materials_->AddUniform(UniformInt::Create("material.emission", 0));
			auto iter = emission_maps_.find(emission_map);
			if (iter != emission_maps_.end())
				emission_map_ = iter->second;
			else
			{
				emission_map_ = Texture2DSource::Create(emission_map);
				emission_maps_[emission_map] = emission_map_;
			}
		}
		else
			materials_->AddUniform(UniformVec3::Create("material.emission", material->GetEmissionColor()));

		if (DIFFUSE_MAP)
		{
			materials_->AddUniform(UniformInt::Create("material.diffuse", 1));
			auto iter = diffuse_maps_.find(diffuse_map);
			if (iter != diffuse_maps_.end())
				diffuse_map_ = iter->second;
			else
			{
				diffuse_map_ = Texture2DSource::Create(diffuse_map);
				diffuse_maps_[diffuse_map] = diffuse_map_;
			}
		}
		else
			materials_->AddUniform(UniformVec3::Create("material.diffuse", material->GetDiffuseColor()));

		if (SPECULAR_MAP)
		{
			materials_->AddUniform(UniformInt::Create("material.specular", 2));
			auto iter = specular_maps_.find(specular_map);
			if (iter != specular_maps_.end())
				specular_map_ = iter->second;
			else
			{
				specular_map_ = Texture2DSource::Create(specular_map);
				specular_maps_[specular_map] = specular_map_;
			}
		}
		else
			materials_->AddUniform(UniformVec3::Create("material.specular", material->GetSpecularColor()));

		materials_->AddUniform(UniformFloat::Create("material.shininess", material->GetShininess()));

		//创建shader
		//vertex shader
		vertex_shader_code +=
			"#version 450 core\n"

			"layout(location = 0) in vec3 aPos;\n"
			"out vec3 Pos;\n"

			"layout(location = 1) in vec3 aNormal;\n"
			"out vec3 Normal;\n";

		if (TEXCOORD)
			vertex_shader_code +=
			"layout(location = 2) in vec2 aTexCoord;\n"
			"out vec2 TexCoord;\n";

		vertex_shader_code +=
			"uniform mat4 model;\n"
			"uniform mat4 normalModel;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"

			"void main()\n"
			"{\n"
			"	Pos = vec3(view * model * vec4(aPos, 1.0f));\n"
			"	Normal = mat3(view) * mat3(normalModel) * aNormal;\n";

		if (TEXCOORD)
			vertex_shader_code +=
			"	TexCoord = aTexCoord;\n";

		vertex_shader_code +=
			"	gl_Position = projection * vec4(Pos, 1.0f);\n"
			"}";

		//fragment shader
		fragment_shader_code +=
			"#version 450 core\n"

			"out vec4 FragColor;\n"

			"in vec3 Pos;\n"
			"in vec3 Normal;\n";

		if (TEXCOORD)
			fragment_shader_code +=
			"in vec2 TexCoord;\n";

		fragment_shader_code +=
			"struct DirLight\n"
			"{\n"
			"	vec3 ambient;\n"
			"	vec3 diffuse;\n"
			"	vec3 specular;\n"
			"	vec3 direction;\n"
			"};\n"

			"struct PointLight\n"
			"{\n"
			"	vec3 ambient;\n"
			"	vec3 diffuse;\n"
			"	vec3 specular;\n"
			"	vec3 position;\n"
			"};\n";

		if (DIR_LIGHT)
			fragment_shader_code +=
			"uniform DirLight dirLight;\n";
		else if (POINT_LIGHT)
			fragment_shader_code +=
			"uniform PointLight pointLight;\n";

		fragment_shader_code +=
			"struct Material\n"
			"{\n";
		if (EMISSION_MAP)
			fragment_shader_code +=
			"	sampler2D emission;\n";
		else
			fragment_shader_code +=
			"	vec3 emission;\n";
		if (DIFFUSE_MAP)
			fragment_shader_code +=
			"	sampler2D diffuse;\n";
		else
			fragment_shader_code +=
			"	vec3 diffuse;\n";
		if (SPECULAR_MAP)
			fragment_shader_code +=
			"	sampler2D specular;\n";
		else
			fragment_shader_code +=
			"	vec3 specular;\n";
		fragment_shader_code +=
			"	float shininess;\n"
			"};\n"
			"uniform Material material;\n"

			"uniform float alpha;\n"

			"vec3 ComputeDirLight(DirLight light, vec3 normal)\n"
			"{\n"
			"	vec3 dir = normalize(light.direction);\n"
			"	float diff = max(dot(normal, -dir), 0.0f);\n"
			"	float spec = pow(max(dot(normalize(-Pos), reflect(dir, normal)), 0.0f), material.shininess);\n";
		if (EMISSION_MAP)
			fragment_shader_code +=
			"	vec3 emission = texture(material.emission, TexCoord).rgb;\n";
		else
			fragment_shader_code +=
			"	vec3 emission = material.emission;\n";
		if (DIFFUSE_MAP)
			fragment_shader_code +=
			"	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n"
			"	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n";
		else
			fragment_shader_code +=
			"	vec3 ambient = light.ambient * material.diffuse;\n"
			"	vec3 diffuse = light.diffuse * diff * material.diffuse;\n";
		if (SPECULAR_MAP)
			fragment_shader_code +=
			"	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;\n";
		else
			fragment_shader_code +=
			"	vec3 specular = light.specular * spec * material.specular;\n";
		fragment_shader_code +=
			"	return (emission + ambient + diffuse + specular);\n"
			"}\n"

			"void main()\n"
			"{\n"
			"	vec3 normal = normalize(Normal);\n";

		if (DIR_LIGHT)
			fragment_shader_code +=
			"	vec3 result = ComputeDirLight(dirLight, normal);\n";
		else if (POINT_LIGHT)
		{
		}

		fragment_shader_code +=
			"	FragColor = vec4(result, alpha);\n"
			"}";

		std::vector<std::string> shaders_code;
		shaders_code.reserve(2);
		shaders_code.emplace_back(vertex_shader_code);
		shaders_code.emplace_back(fragment_shader_code);
		auto iter = shaders_.find(shaders_code);
		if (iter != shaders_.end())
			shader_ = iter->second;
		else
		{
			SPtr(Program) program = Program::Create();
			program->AddShader(Shader::Create(Shader::Type::VERTEX_SHADER, vertex_shader_code));
			program->AddShader(Shader::Create(Shader::Type::FRAGMENT_SHADER, fragment_shader_code));
			shader_ = ShaderSource::Create(program);
			shaders_[shaders_code] = shader_;
		}
	}


	void StateVisitor::Process(SPtr(CustomState) state)
	{

	}
}