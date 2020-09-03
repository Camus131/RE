//#include "Model.h"
//
//#include <iostream>
//
//
//namespace OGE
//{
//	Model::Model(const std::string& model_path)
//	{
//        loadModel(model_path);
//	}
//
//
//    void Model::loadModel(const std::string& model_path)
//    {
//        Assimp::Importer importer;
//        const aiScene* scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//        {
//            std::cout << "模型数据读取失败：" << importer.GetErrorString() << std::endl;
//            return;
//        }
//        
//        directory_ = model_path.substr(0, model_path.find_last_of('/'));
//
//        
//        processNode(scene->mRootNode, scene);
//    }
//
//
//    void Model::processNode(aiNode* node, const aiScene* scene)
//    {
//
//        for (unsigned int i = 0; i < node->mNumMeshes; i++)
//        {
//
//            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//            mesh_vector_.push_back(processMesh(mesh, scene));
//        }
//
//        for (unsigned int i = 0; i < node->mNumChildren; i++)
//        {
//            processNode(node->mChildren[i], scene);
//        }
//    }
//
//
//}