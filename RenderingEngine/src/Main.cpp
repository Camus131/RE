#include "Window/Window.h"
#include "Object/DrawElements.h"

#include <ctime>


using namespace OGE;

int main()
{
	Window window = Window::GetInstance();

	//材质
	SPtr(Material) material = Material::Create();
	SPtr(Image) image = Image::Create("res/textures/container2.png");
	SPtr(Texture2D) diffuse_map = Texture2D::Create(image);
	diffuse_map->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map->SetMipMapEnable(true);
	diffuse_map->SetInternalFormat(Texture2D::Format::RGBA);
	SPtr(Image) image2 = Image::Create("res/textures/container2_specular.png");
	SPtr(Texture2D) specular_map = Texture2D::Create(image2);
	specular_map->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
	specular_map->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
	specular_map->SetMipMapEnable(true);
	specular_map->SetInternalFormat(Texture2D::Format::RGBA);
	material->SetDiffuseMap(diffuse_map);
	material->SetSpecularMap(specular_map);
	material->SetShininess(64.0f);

	SPtr(Material) material2 = Material::Create();
	SPtr(Image) image3 = Image::Create("res/textures/timg.jpg");
	SPtr(Texture2D) diffuse_map2 = Texture2D::Create(image3);
	diffuse_map2->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map2->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map2->SetMipMapEnable(true);
	diffuse_map2->SetInternalFormat(Texture2D::Format::RGB);
	material2->SetDiffuseMap(diffuse_map2);

	//state
	SPtr(PhongState) state = PhongState::Create();
	state->SetMaterial(material);

	SPtr(PhongState) state2 = PhongState::Create();
	state2->SetMaterial(material);
	state2->SetTransparent(0.4f);

	SPtr(PhongState) state3 = PhongState::Create();
	state3->SetMaterial(material2);

	//创建场景
	SPtr(Group) scene = Group::Create();

	SPtr(Cube) cube = Cube::Create();
	cube->SetUvEnable(true);

	SPtr(Group) group = Group::Create();
	group->SetState(state);
	scene->AddChild(group);
	srand((int)time(0));
	for (int i = 0; i < 500; ++i)
	{
		int x = rand() % 90;
		int z = rand() % 90;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(cube);
		group->AddChild(transform);
	}

	SPtr(Group) group2 = Group::Create();
	group2->SetState(state2);
	scene->AddChild(group2);
	for (int i = 0; i < 2500; ++i)
	{
		int x = rand() % 90;
		int z = rand() % 90;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(cube);
		group2->AddChild(transform);
	}

	SPtr(Group) group3 = Group::Create();
	group3->SetState(state3);
	scene->AddChild(group3);
	for (int i = 0; i < 90; ++i)
	{
		for (int j = 0; j < 90; ++j)
		{
			SPtr(Transform) transform = Transform::Create(Matrix::Translate(i, -1.01f, j));
			transform->AddChild(cube);
			group3->AddChild(transform);
		}
	}

	//创建渲染器
	SPtr(Renderer) renderer = Renderer::Create();
	renderer->SetScene(scene);
	window.BindRenderer(renderer);

	//渲染
	window.Run();
}