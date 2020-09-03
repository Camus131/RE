#include "MeshVisitor.h"


namespace OGE
{
	MeshVisitor::MeshVisitor() :
		Visitor()
	{
		name_ = "MeshVisitor";
	}


	void MeshVisitor::Visit(SPtr(ExternalObject) object)
	{
		mesh_ = nullptr;
		vbo_ = nullptr;
		ebo_ = nullptr;
		vao_ = nullptr;
		drawing_call_ = nullptr;
		uniform_list_ = nullptr;
		vertex_shader_code_ = "";
		fragment_shader_code_ = "";
		emission_map_ = nullptr;
		diffuse_map_ = nullptr;
		specular_map_ = nullptr;

		if (object->GetName() != "Mesh")
			return;

		SPtr(Mesh) mesh = SPCast(Mesh)(object);
		if (mesh->SizeOfPosArray() == 0)
			return;

		mesh_ = mesh;

		GenVertexArray();
		GenMaterial();
		GenShaderCode();
	}


	void MeshVisitor::GenVertexArray()
	{
		int pos_array_size = mesh_->SizeOfPosArray();
		int norm_array_size = mesh_->SizeOfNormArray();
		int uv_array_size = mesh_->SizeOfUvArray();
		if (mesh_->GetDrawingSet() == nullptr)
		{
			SPtr(DrawArrays) draw_arrays = DrawArrays::Create(DrawArrays::Mode::TRIANGLES, 0, pos_array_size / sizeof(float));
			mesh_->SetDrawingSet(draw_arrays);
		}
		SPtr(DrawingSet) drawing_set = mesh_->GetDrawingSet();

		vao_ = VAO::Create();
		vao_->Bind();
		vbo_ = VBO::Create(pos_array_size + norm_array_size + uv_array_size);
		if (pos_array_size > 0)
		{
			vbo_->UpdateData(mesh_->GetPosArray());
			vao_->EnableSetAttrib(0, 3, 3 * sizeof(float));
		}
		if (norm_array_size > 0)
		{
			vbo_->UpdateData(mesh_->GetNormArray(), pos_array_size);
			vao_->EnableSetAttrib(1, 3, 3 * sizeof(float), pos_array_size);
		}
		if (uv_array_size > 0)
		{
			vbo_->UpdateData(mesh_->GetUvArray(), norm_array_size);
			vao_->EnableSetAttrib(2, 2, 2 * sizeof(float), norm_array_size);
		}
		if (drawing_set->GetName() == "DrawElementsUByte")
		{
			SPtr(DrawElementsUByte) draw_elements = SPCast(DrawElementsUByte)(drawing_set);
			ebo_ = EBO_UByte::Create(draw_elements->GetIndices());
		}
		else if (drawing_set->GetName() == "DrawElementsUShort")
		{
			SPtr(DrawElementsUShort) draw_elements = SPCast(DrawElementsUShort)(drawing_set);
			ebo_ = EBO_UShort::Create(draw_elements->GetIndices());
		}
		else if (drawing_set->GetName() == "DrawElementsUInt")
		{
			SPtr(DrawElementsUInt) draw_elements = SPCast(DrawElementsUInt)(drawing_set);
			ebo_ = EBO_UInt::Create(draw_elements->GetIndices());
		}
		vao_->UnBind();

		drawing_call_ = DrawingCall::Create(drawing_set);
	}


	void MeshVisitor::GenShaderCode()
	{
		SPtr(PhongState) phong_state = SPCast(PhongState)(mesh_->GetState());
		SPtr(Material) material = phong_state->GetMaterial();
		std::string name = phong_state->GetLight()->GetName();

		bool NORMAL = mesh_->SizeOfNormArray() > 0;
		bool TEXCOORD = mesh_->SizeOfUvArray() > 0;
		bool EMISSION_MAP = material->GetEmissionMap() != nullptr;
		bool DIFFUSE_MAP = material->GetDiffuseMap() != nullptr;
		bool SPECULAR_MAP = material->GetSpecularMap() != nullptr;
		bool DIR_LIGHT = name == "DirLight";
		bool POINT_LIGHT = name == "PointLight";

		vertex_shader_code_ += 
			"#version 450 core\n"
			"out vec3 Pos;\n";

		if (NORMAL)
			vertex_shader_code_ += 
			"out vec3 Normal;\n";

		if (TEXCOORD)
			vertex_shader_code_ += 
			"out vec2 TexCoord;\n";

		vertex_shader_code_ += 
			"layout(location = 0) in vec3 aPos;\n";

		if (NORMAL)
			vertex_shader_code_ += 
			"layout(location = 1) in vec3 aNormal;\n";

		if (TEXCOORD)
			vertex_shader_code_ += 
			"layout(location = 2) in vec2 aTexCoord;\n";


		vertex_shader_code_ +=
			"uniform mat4 model;\n"
			"uniform mat4 normalModel;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"

			"void main()\n"
			"{\n"
			"	Pos = vec3(view * model * vec4(aPos, 1.0f));\n";

		if (NORMAL)
			vertex_shader_code_ +=
			"	Normal = mat3(view) * mat3(normalModel) * aNormal;\n";

		if (TEXCOORD)
			vertex_shader_code_ +=
			"	TexCoord = aTexCoord;\n";

		vertex_shader_code_ +=
			"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
			"}";


		fragment_shader_code_ +=
			"#version 450 core\n"
			"out vec4 FragColor;\n"
			"in vec3 Pos;\n";

		if (NORMAL)
			fragment_shader_code_ +=
			"in vec3 Normal;\n";

		if (TEXCOORD)
			fragment_shader_code_ +=
			"in vec2 TexCoord;\n";

		fragment_shader_code_ +=
			"struct Material\n"
			"{\n";

		if (EMISSION_MAP)
			fragment_shader_code_ +=
			"	sampler2D emission;\n";
		else
			fragment_shader_code_ +=
			"	vec3 emission;\n";

		if (DIFFUSE_MAP)
			fragment_shader_code_ +=
			"	sampler2D diffuse;\n";
		else
			fragment_shader_code_ +=
			"	vec3 diffuse;\n";

		if (SPECULAR_MAP)
			fragment_shader_code_ +=
			"	sampler2D specular;\n";
		else
			fragment_shader_code_ +=
			"	vec3 specular;\n";

		fragment_shader_code_ +=
			"	float shininess;\n"
			"};\n"

			"struct Light\n"
			"{\n"
			"	vec3 ambient;\n"
			"	vec3 diffuse;\n"
			"	vec3 specular;\n";

		if (DIR_LIGHT)
			fragment_shader_code_ +=
			"	vec3 direction;\n";
		else if (POINT_LIGHT)
			fragment_shader_code_ +=
			"	vec3 position;\n";

		fragment_shader_code_ +=
			"};\n"

			"uniform vec3 viewPos;\n"
			"uniform Material material;\n"
			"uniform Light light;\n"


			"void main()\n"
			"{\n"


			"vec3 result = vec3(0.0f, 0.0f, 0.0f);\n";


		if (TEXCOORD && EMISSION_MAP)
			fragment_shader_code_ +=
			"	vec3 emission = texture(material.emission, TexCoord).rgb;\n";
		else
			fragment_shader_code_ +=
			"	vec3 emission = material.emission;\n";
		fragment_shader_code_ +=
			"	result += emission;\n";



		if (TEXCOORD && DIFFUSE_MAP)
			fragment_shader_code_ +=
			"	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;\n";
		else
			fragment_shader_code_ +=
			"	vec3 ambient = light.ambient * material.diffuse;\n";
		fragment_shader_code_ +=
			"	result += ambient;\n";


		if (NORMAL)
		{
			fragment_shader_code_ +=
				"	vec3 normal = normalize(Normal);\n";


			if (DIR_LIGHT)
				fragment_shader_code_ +=
				"	vec3 lightDir = light.direction;\n";
			else if (POINT_LIGHT)
				fragment_shader_code_ +=
				"	vec3 lightDir = normalize(Pos - light.position);\n";

			fragment_shader_code_ +=
				"	float diff = max(dot(normal, -lightDir), 0.0f);\n";


			if (TEXCOORD && DIFFUSE_MAP)
				fragment_shader_code_ +=
				"	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;\n";
			else
				fragment_shader_code_ +=
				"	vec3 diffuse = light.diffuse * diff * material.diffuse;\n";
			fragment_shader_code_ +=
				"	result += diffuse;\n";

			fragment_shader_code_ +=
				"	vec3 viewDir = normalize(-Pos);\n"
				"	vec3 reflectDir = reflect(lightDir, normal);\n"
				"	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);\n";
			if (TEXCOORD && SPECULAR_MAP)
				fragment_shader_code_ +=
				"	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;\n";
			else
				fragment_shader_code_ +=
				"	vec3 specular = light.specular * spec * material.specular;\n";
			fragment_shader_code_ +=
				"	result += specular;\n";
		}
			
		fragment_shader_code_ +=
			"	FragColor = vec4(result, 1.0);\n"
			"}";
	}


	void MeshVisitor::GenMaterial()
	{
		uniform_list_ = UniformList::Create();
		Matrix model = mesh_->GetModelMatrix();
		model.MakeInverse();
		Matrix normal_model = Matrix::Transpose(model);
		uniform_list_->AddUniform(UniformMat::Create("model", model));
		uniform_list_->AddUniform(UniformMat::Create("normalModel", normal_model));

		SPtr(State) state = mesh_->GetState();
		if (state->GetName() == "PhongState")
		{
			SPtr(PhongState) phong_state = SPCast(PhongState)(state);
			SPtr(Material) material = phong_state->GetMaterial();

			if (material->GetEmissionMap() != nullptr)
			{
				emission_map_ = material->GetEmissionMap();
				uniform_list_->AddUniform(UniformInt::Create("material.emission", 0));
			}
			else
				uniform_list_->AddUniform(UniformVec3::Create("material.emission", material->GetEmissionColor()));
			
			if (material->GetDiffuseMap() != nullptr)
			{
				diffuse_map_ = material->GetDiffuseMap();
				uniform_list_->AddUniform(UniformInt::Create("material.diffuse", 1));
			}
			else
				uniform_list_->AddUniform(UniformVec3::Create("material.diffuse", material->GetDiffuseColor()));

			if (material->GetSpecularMap() != nullptr)
			{
				specular_map_ = material->GetSpecularMap();
				uniform_list_->AddUniform(UniformInt::Create("material.specular", 2));
			}
			else
				uniform_list_->AddUniform(UniformVec3::Create("material.specular", material->GetSpecularColor()));

			uniform_list_->AddUniform(UniformFloat::Create("material.shininess", material->GetShininess()));


			SPtr(Light) light = phong_state->GetLight();
			uniform_list_->AddUniform(UniformVec3::Create("light.ambient", light->GetAmbient()));
			uniform_list_->AddUniform(UniformVec3::Create("light.diffuse", light->GetDiffuse()));
			uniform_list_->AddUniform(UniformVec3::Create("light.specular", light->GetSpecular()));
			if (light->GetName() == "DirLight")
			{
				SPtr(DirLight) dir_light = SPCast(DirLight)(light);
				uniform_list_->AddUniform(UniformVec3::Create("light.direction", dir_light->GetDir()));
			}
			else if (light->GetName() == "PointLight")
			{
				SPtr(PointLight) point_light = SPCast(PointLight)(light);
				uniform_list_->AddUniform(UniformVec3::Create("light.position", point_light->GetPosition()));
			}
		}
		else if (state->GetName() == "CustomState")
		{
			//...
		}
	}
}