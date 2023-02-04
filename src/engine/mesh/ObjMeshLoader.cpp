#include "ObjMeshLoader.h"

#include "engine/utils/StringUtils.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace
{

enum class Token
{
    Undefined,

    Comment,
    Name,
    Position,
    TextureCoords,
    Normal,
    Surface,
    Face,
};

Token get_token(std::stringstream& line);

} // namespace

ObjMeshLoader::ObjMeshLoader(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
        return;

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream line_stream(line);

        switch (get_token(line_stream))
        {
        case Token::Undefined: std::cout << "Undefined token in line: " << line << std::endl; break;
        case Token::Comment: break;
        case Token::Name: handle_name_token(line_stream); break;
        case Token::Position: handle_position_token(line_stream); break;
        case Token::TextureCoords: handle_texture_coords_token(line_stream); break;
        case Token::Normal: handle_normal_token(line_stream); break;
        case Token::Surface: handle_surface_token(line_stream); break;
        case Token::Face: handle_face_token(line_stream); break;
        }
    }

    for (auto obj_vertex : obj_vertices_)
    {
        Vertex vertex{};
        vertex.position = positions_[obj_vertex.position_index];
        vertex.normal = normals_[obj_vertex.normals_index];
        vertex.texture_coords = texture_coords_[obj_vertex.texture_coords_index];
        vertices_.push_back(vertex);
    }

    for (auto & face : faces_)
    {
        for (unsigned int vertex_index : face.vertex_indices)
        {
            indices_.push_back(vertex_index);
        }
    }

    create_mesh();

    is_loaded_ = true;
}

void ObjMeshLoader::create_mesh()
{
    auto vertex_array = VertexArray::create();
    vertex_array->bind();
    auto index_buffer = IndexBuffer::create(&indices_[0], indices_.size());
    auto vertex_buffer = VertexBuffer::create(&vertices_[0], vertices_.size() * sizeof(Vertex));
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texture coordinates
    layout.push<float>(3); // normals
    vertex_array->addBuffer(vertex_buffer, layout);
    vertex_array->unbind();
    vertex_buffer->unbind();
    index_buffer->unbind();

    mesh_ = Mesh::create(vertex_array, index_buffer, vertex_buffer);
}

void ObjMeshLoader::handle_name_token(std::stringstream& line)
{
    line >> name_;
}

void ObjMeshLoader::handle_position_token(std::stringstream& line)
{
    glm::vec3 position{};
    line >> position.x;
    line >> position.y;
    line >> position.z;
    positions_.push_back(position);
}

void ObjMeshLoader::handle_texture_coords_token(std::stringstream& line)
{
    glm::vec2 texture_coords{};
    line >> texture_coords.x;
    line >> texture_coords.y;
    texture_coords_.push_back(texture_coords);
}

void ObjMeshLoader::handle_normal_token(std::stringstream& line)
{
    glm::vec3 normal{};
    line >> normal.x;
    line >> normal.y;
    line >> normal.z;
    normals_.push_back(normal);
}

void ObjMeshLoader::handle_surface_token(std::stringstream& line)
{
    // TODO support multiple surfaces in the .obj file
    std::cout << "Token 's' ignored" << std::endl;
}

void ObjMeshLoader::handle_face_token(std::stringstream& line)
{
    std::string str;

    Face face{};

    int current_vertex = 0;
    while (line >> str)
    {
        if (current_vertex >= 3)
        {
            std::cout << "Only triangulated meshes are supported" << std::endl;
            return;
        }

        std::vector<std::string> indices_strings = String::splitString(str, '/');

        if (indices_strings.size() != 3)
        {
            // TODO support not .obj with no normals or texture coords
            std::cout << "Invalid indices count" << std::endl;
            return;
        }

        int indices[3];

        for (int i = 0; i < 3; i++)
        {
            if (indices_strings[i].empty())
            {
                indices[i] = -1;
            }
            else
            {
                try
                {
                    indices[i] = std::stoi(indices_strings[i]);
                }
                catch(std::exception& e)
                {
                    std::cout << "Invalid index" << std::endl;
                    return;
                }
            }
        }

        ObjVertex obj_vertex{};
        // obj file vertex's indices starts with 1, not with 0
        obj_vertex.position_index = indices[0] - 1;
        obj_vertex.texture_coords_index = indices[1] - 1;
        obj_vertex.normals_index = indices[2] - 1;

        face.vertex_indices[current_vertex] = create_or_get_vertex_index(obj_vertex);
        current_vertex++;
    }

    faces_.push_back(face);
}

unsigned int ObjMeshLoader::create_or_get_vertex_index(const ObjMeshLoader::ObjVertex& obj_vertex)
{
    // check for this vertex in vector
    for (int i = 0; i < obj_vertices_.size(); i++)
    {
        if (obj_vertices_[i] == obj_vertex)
            return i;
    }

    obj_vertices_.push_back(obj_vertex);
    return (int)obj_vertices_.size() - 1;
}

namespace
{

Token get_token(std::stringstream& line)
{
    std::string token_string;
    line >> token_string;

    if (token_string == "#")
        return Token::Comment;
    if (token_string == "o")
        return Token::Name;
    if (token_string == "v")
        return Token::Position;
    if (token_string == "vn")
        return Token::Normal;
    if (token_string == "vt")
        return Token::TextureCoords;
    if (token_string == "s")
        return Token::Surface;
    if (token_string == "f")
        return Token::Face;

    return Token::Undefined;
}

} // namespace
