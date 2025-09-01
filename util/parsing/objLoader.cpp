//
// Created by Theo Wimber on 01.09.25.
//
#include "objLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "objLoaderBackend.h"

std::vector<float> util::load_model_from_file(const char *filename, glm::mat4 &preTransform) {
     std::vector<float> vertex_data;
     tinyobj::attrib_t attributes;
     std::vector<tinyobj::shape_t> shapes;
     std::vector<tinyobj::material_t> materials;
     std::string warning, error;

     if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filename)) {
         std::cout << warning << error << '\n';
     }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices ) {
            glm::vec4 pos = {
                attributes.vertices[3 * index.vertex_index],
                attributes.vertices[3 * index.vertex_index + 1],
                attributes.vertices[3 * index.vertex_index + 2],
                1
            };
            pos = preTransform * pos;

            glm::vec3 normal = {
                attributes.normals[3 * index.normal_index],
                attributes.vertices[3 * index.normal_index + 1],
                attributes.vertices[3 * index.normal_index + 2]
            };

            normal = glm::normalize(glm::mat3(preTransform) * normal);

            glm::vec2 texCoords = {
                attributes.texcoords[3 * index.texcoord_index],
                attributes.texcoords[3 * index.texcoord_index + 1]
            };


            vertex_data.push_back(pos.x);
            vertex_data.push_back(pos.y);
            vertex_data.push_back(pos.z);
            vertex_data.push_back(texCoords.x);
            vertex_data.push_back(texCoords.y);
            vertex_data.push_back(normal.x);
            vertex_data.push_back(normal.y);
            vertex_data.push_back(normal.z);

        }
    }

     return vertex_data;
}
