//#pragma once
//
//#include "Mesh.h"
//
//#include "assimp/Importer.hpp"
//#include "assimp/scene.h"
//#include "assimp/postprocess.h"
//
//
//namespace OGE
//{
//	class Model
//	{
//	public:
//		Model(const std::string& model_path);
//
//	protected:
//		void loadModel(const std::string& model_path);
//		void processNode(aiNode* node, const aiScene* scene);
//		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
//		std::vector<Texture2D> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& type_name);
//
//	public:
//		std::string						directory_;
//		std::vector<Mesh>				mesh_vector_;
//		std::vector<SPtr(Texture2D)>	tex_vector_;
//	};
//}