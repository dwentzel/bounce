#include "image_data.h"

#include <memory>

bounce::ImageData::ImageData()
{
}

bounce::ImageData::ImageData(ImageData&& other)
: size_(other.size_), width_(other.width_), height_(other.height_), data_(std::move(other.data_))
{
    other.data_ = nullptr;
}

bounce::ImageData::~ImageData() NOEXCEPT
{
    delete [] data_;
}

unsigned int bounce::ImageData::size() const
{
    return size_;
}

void bounce::ImageData::size(unsigned int value)
{
    size_ = value;
}

unsigned int bounce::ImageData::width() const
{
    return width_;
}

void bounce::ImageData::width(unsigned int value)
{
    width_ = value;
}

unsigned int bounce::ImageData::height() const
{
    return height_;
}

void bounce::ImageData::height(unsigned int value)
{
    height_ = value;
}

const std::uint8_t* bounce::ImageData::data() const
{
    return data_;
}

void bounce::ImageData::data(const std::uint8_t* value)
{
    data_ = value;
}
