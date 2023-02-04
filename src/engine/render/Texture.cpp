#include "Texture.h"

// clang-format off
#include "glad/glad.h"
// clang-format on

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <functional>
#include <iostream>

Texture::Texture(const std::string& image_file, bool save_data_after_loading)
{
    stbi_set_flip_vertically_on_load(true);
    data_ = stbi_load(image_file.c_str(), &width_, &height_, &number_channels_, 4);

    if (!data_)
    {
        std::cout << "Cannot load image file" << std::endl;
        return;
    }

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (!save_data_after_loading)
    {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

Texture::~Texture()
{
    if (texture_id_)
        glDeleteTextures(1, &texture_id_);
    if (data_)
    {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

void Texture::bind(int slot) const
{
    assert(slot >= 0 && slot < 32);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

TexturePtr Texture::create(const std::string& image_file, bool save_data_after_loading)
{
    return TexturePtr(new Texture(image_file, save_data_after_loading));
}
