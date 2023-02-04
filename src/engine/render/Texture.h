#pragma once

#include "engine/core/Object.h"
#include "engine/core/SharedPtr.h"

#include <string>

class Texture;
using TexturePtr = SharedPtr<Texture>;

class Texture final : public Object
{
public:
    static TexturePtr create(const std::string& image_file, bool save_data_after_loading = false);

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    bool isValid() const { return texture_id_ != 0; }

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getNumChannels() const { return number_channels_; }

    void bind(int slot = 0) const;
    void unbind() const;

private:
    explicit Texture(const std::string& image_file, bool save_data_after_loading = false);
    ~Texture() override;

private:
    unsigned int texture_id_{0};

    unsigned char* data_{nullptr}; // leave it as class member for future using

    int width_{0};
    int height_{0};
    int number_channels_{0};
};
