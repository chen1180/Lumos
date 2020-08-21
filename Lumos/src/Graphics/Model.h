#pragma once
#include "lmpch.h"
#include "MeshFactory.h"
#include "Mesh.h"
#include "Material.h"
#include <cereal/cereal.hpp>

namespace Lumos
{
    namespace Graphics
    {
        class Model
        {
        public:
            Model() = default;
            Model(const std::string& filePath);
            Model(const Ref<Mesh>& mesh, PrimitiveType type);
            Model(PrimitiveType type);

            ~Model() = default;

            const std::vector<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }
            void AddMesh(Ref<Mesh> mesh) { m_Meshes.push_back(mesh); }

            template<typename Archive>
            void save(Archive& archive) const
            {
                auto material = std::unique_ptr<Material>(m_Meshes.front()->GetMaterial().get());
                archive(cereal::make_nvp("PrimitiveType", m_PrimitiveType), cereal::make_nvp("FilePath", m_FilePath), cereal::make_nvp("Material", material));
                material.release();
            }

            template<typename Archive>
            void load(Archive& archive)
            {
                auto material = std::unique_ptr<Graphics::Material>();
                archive(cereal::make_nvp("PrimitiveType", m_PrimitiveType), cereal::make_nvp("FilePath", m_FilePath), cereal::make_nvp("Material", material));
                
                m_Meshes.clear();
                
                if(m_PrimitiveType != PrimitiveType::File)
                {	
                    m_Meshes.push_back(Ref<Mesh>(CreatePrimative(m_PrimitiveType)));
                    m_Meshes.back()->SetMaterial(Ref<Material>(material.get()));
                    material.release();
                }
                else
                {
                    LoadModel(m_FilePath);
                }
            }

            const std::string& GetFilePath() const { return m_FilePath; }
            PrimitiveType GetPrimitiveType() { return m_PrimitiveType; }
            
        private:
            PrimitiveType m_PrimitiveType;
            std::vector<Ref<Mesh>> m_Meshes;
            std::string m_FilePath;

            void LoadOBJ(const std::string& path);
		    void LoadGLTF(const std::string& path);
		    void LoadFBX(const std::string& path);
        public:
        	void LoadModel(const std::string& path);
        };
    }
}