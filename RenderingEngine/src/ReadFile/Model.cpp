#include "Model.h"

#include <iostream>

#include "Object/DrawElements.h"


namespace OGE
{
	Model::Model(const std::string& model_path)
	{
        scene_ = Group::Create();
        LoadModel(model_path);
	}


    void Model::LoadModel(const std::string& model_path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "模型数据读取失败：" << importer.GetErrorString() << std::endl;
            return;
        }
        
        directory_ = model_path.substr(0, model_path.find_last_of('/'));

        ProcessGroup(scene->mRootNode, scene);
    }


    void Model::ProcessGroup(aiNode* node, const aiScene* scene)
    {
        SPtr(Group) group = Group::Create();
        scene_->AddChild(group);

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            group->AddChild(ProcessMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
            ProcessGroup(node->mChildren[i], scene);
    }


    SPtr(Mesh) Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        Vec3Array pos_array;
        Vec3Array norm_array;
        Vec2Array uv_array;
        pos_array.reserve(mesh->mNumVertices);
        norm_array.reserve(mesh->mNumVertices);
        uv_array.reserve(mesh->mNumVertices);
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            pos_array.emplace_back(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

            if (mesh->HasNormals())
                norm_array.emplace_back(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            if (mesh->mTextureCoords[0])
                uv_array.emplace_back(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        SPtr(DrawingSet) drawing_set = DrawElementsUInt::Create(DrawElementsUInt::TRIANGLES, indices);

        aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];

        SPtr(Texture2D) emission_map = ProcessTexture(aimaterial, aiTextureType_EMISSIVE);
        SPtr(Texture2D) diffuse_map = ProcessTexture(aimaterial, aiTextureType_DIFFUSE);
        SPtr(Texture2D) specular_map = ProcessTexture(aimaterial, aiTextureType_SPECULAR);

        SPtr(Material) material = Material::Create();
        material->SetEmissionMap(emission_map);
        material->SetDiffuseMap(diffuse_map);
        material->SetSpecularMap(specular_map);

        SPtr(PhongState) state = PhongState::Create();
        state->SetMaterial(material);

        SPtr(Mesh) res = Mesh::Create();
        res->SetState(state);
        res->SetDrawingSet(drawing_set);
        res->SetPosArray(pos_array);
        res->SetNormArray(norm_array);
        res->SetUvArray(uv_array);

        return res;
    }


    SPtr(Texture2D) Model::ProcessTexture(aiMaterial* mat, aiTextureType type)
    {
        aiString str;
        mat->GetTexture(type, 0, &str);
        if (str.C_Str() == nullptr)
            return nullptr;

        std::string path = str.C_Str();

        auto iter = texture_map_.find(path);
        if (iter != texture_map_.end())
            return iter->second;

        std::string image_path = directory_ + '/' + path;
        SPtr(Image) image = Image::Create(image_path);
        SPtr(Texture2D) texture = Texture2D::Create(image);
        texture_map_[path] = texture;
        return texture;
    }
}