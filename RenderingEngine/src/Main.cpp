#include "Window/Window.h"
#include "Object/DrawElements.h"
#include "ReadFile/Model.h"

#include <ctime>


using namespace OGE;

int main()
{
	SPtr(Group) scene = Group::Create();

	SPtr(Material) material = Material::Create();
	SPtr(Image) image3 = Image::Create("res/textures/timg.jpg");
	SPtr(Texture2D) diffuse_map = Texture2D::Create(image3);
	diffuse_map->SetFilterMode(Texture::FilterChance::MIN_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map->SetFilterMode(Texture::FilterChance::MAG_FILTER, Texture::FilterMode::LINEAR);
	diffuse_map->SetMipMapEnable(true);
	diffuse_map->SetInternalFormat(Texture2D::Format::RGB);
	material->SetDiffuseMap(diffuse_map);

	SPtr(PhongState) state = PhongState::Create();
	state->SetMaterial(material);

	SPtr(Group) group = Group::Create();
	group->SetState(state);
	scene->AddChild(group);

#if 1
	//优化版
	SPtr(Cube) cube = Cube::Create();
	cube->SetUvEnable(true);
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			SPtr(Transform) transform = Transform::Create(Matrix::Translate(i, -1.0f, j));
			transform->AddChild(cube);
			group->AddChild(transform);
		}
	};

	Model model("res/models/backpack/nanosuit.obj");
	for (int i = 0; i < 20; ++i)
	{
		int x = rand() % 100;
		int z = rand() % 100;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(model.GetNode());
		scene->AddChild(transform);
	}
#else
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			SPtr(Cube) cube = Cube::Create();
			cube->SetUvEnable(true);
			SPtr(Transform) transform = Transform::Create(Matrix::Translate(i, -1.0f, j));
			transform->AddChild(cube);
			group->AddChild(transform);
		}
	};

	for (int i = 0; i < 20; ++i)
	{
		Model model("res/models/backpack/nanosuit.obj");
		int x = rand() % 100;
		int z = rand() % 100;
		SPtr(Transform) transform = Transform::Create(Matrix::Translate(x, 0.0f, z));
		transform->AddChild(model.GetNode());
		scene->AddChild(transform);
	}
#endif

	//创建渲染器
	SPtr(Renderer) renderer = Renderer::Create();
	renderer->SetScene(scene);

	Window window = Window::GetInstance();
	window.BindRenderer(renderer);

	//渲染
	window.Run();
}