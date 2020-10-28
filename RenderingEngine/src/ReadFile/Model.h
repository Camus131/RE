#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Object/Texture2D.h"
#include "Object/Group.h"
#include "Object/Mesh.h"


namespace OGE
{
	class Model
	{
	public:
		Model(const std::string& model_path);

		SPtr(Group) GetNode() const { return scene_; }
		std::string Directory() const { return directory_; }

	protected:
		void LoadModel(const std::string& model_path);
		void ProcessGroup(aiNode* node, const aiScene* scene);
		SPtr(Mesh) ProcessMesh(aiMesh* mesh, const aiScene* scene);
		SPtr(Texture2D) ProcessTexture(aiMaterial* mat, aiTextureType type);

	protected:
		std::string											directory_;

		SPtr(Group)											scene_;

		std::unordered_map<std::string, SPtr(Texture2D)>	texture_map_;
	};
}