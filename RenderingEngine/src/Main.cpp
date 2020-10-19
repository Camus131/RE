#include "Window/Window.h"
#include "Object/DrawElements.h"

#include <ctime>


using namespace OGE;

int main()
{
	Window window = Window::GetInstance();

	//创建state
	SPtr(PhongState) state = PhongState::Create();
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
	state->SetMaterial(material);

	SPtr(PhongState) state2 = PhongState::Create();
	SPtr(Material) material2 = Material::Create();
	SPtr(Image) image3 = Image::Create("res/textures/timg.jpg");
	SPtr(Texture2D) diffuse_map2 = Texture2D::Create(image3);
	diffuse_map2->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map2->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map2->SetMipMapEnable(true);
	diffuse_map2->SetInternalFormat(Texture2D::Format::RGB);
	material2->SetDiffuseMap(diffuse_map2);
	state2->SetMaterial(material2);

	//创建场景
	SPtr(Group) scene = Group::Create();
	scene->SetState(state);

#if 1
	SPtr(Group) group = Group::Create();
	group->SetState(state2);
	scene->AddChild(group);

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			SPtr(Cube) cube2 = Cube::Create();
			cube2->SetUvEnable(true);
			SPtr(Transform) transform = Transform::Create(Matrix::Translate(i, -1.01f, j));
			transform->AddChild(cube2);
			group->AddChild(transform);
		}
	}

	srand((int)time(0));
	for (int i = 0; i < 5000; ++i)
	{
		SPtr(Cube) cube = Cube::Create();
		cube->SetUvEnable(true);
		int x = rand() % 100;
		int z = rand() % 100;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(cube);
		scene->AddChild(transform);
	}
#else
	SPtr(Group) group = Group::Create();
	group->SetState(state2);
	scene->AddChild(group);

	SPtr(Cube) cube2 = Cube::Create();
	cube2->SetUvEnable(true);
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			SPtr(Transform) transform = Transform::Create(Matrix::Translate(i, -1.01f, j));
			transform->AddChild(cube2);
			group->AddChild(transform);
		}
	}

	SPtr(Cube) cube = Cube::Create();
	cube->SetUvEnable(true);
	srand((int)time(0));
	for (int i = 0; i < 5000; ++i)
	{
		int x = rand() % 100;
		int z = rand() % 100;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(cube);
		scene->AddChild(transform);
	}
#endif

	//创建渲染器
	SPtr(Renderer) renderer = Renderer::Create();
	renderer->SetScene(scene);
	window.BindRenderer(renderer);

	//渲染
	window.Run();
}