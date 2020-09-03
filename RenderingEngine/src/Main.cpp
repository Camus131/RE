#include "Window/Window.h"


using namespace OGE;

int main()
{
	Window window = Window::GetInstance();

	SPtr(Mesh) box = Mesh::CreateBox();

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
	SPtr(PhongState) state = PhongState::Create();
	state->SetMaterial(material);
	box->SetState(state);

	std::vector<SPtr(Mesh)> scene;
	scene.emplace_back(box);

	SPtr(Renderer) renderer = Renderer::Create();
	renderer->SetScene(scene);
	
	window.BindRenderer(renderer);

	window.Run();
}