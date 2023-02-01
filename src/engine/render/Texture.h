#pragma once

#include <string>

class Texture
{
public:
    explicit Texture(const std::string& image_file, bool save_data_after_loading = false);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    bool isValid() const { return texture_id_ != 0; }

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getNumberChannels() const { return number_channels_; }

    void bind(int slot = 0) const;
    void unbind() const;

private:
    void swap(Texture& other);

private:
    unsigned int texture_id_{0};

    unsigned char* data_{nullptr}; // leave it as class member for future using

    int width_{0};
    int height_{0};
    int number_channels_{0};
};
