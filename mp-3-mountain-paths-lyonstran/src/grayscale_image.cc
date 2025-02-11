#include "grayscale_image.hpp"
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    // image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
    height_ = dataset.Height();
    width_ = dataset.Width();
    
    int smallest_ele = dataset.MinEle();
    int largest_ele = dataset.MaxEle();

    std::cout << smallest_ele << std::endl;
    std::cout << largest_ele << std::endl;

    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> cur_row;
        for (size_t j = 0; j < width_; ++j) {
            int cur_ele = dataset.DatumAt(i, j); //good
            int shade_gray = 0.0;
            if (largest_ele == smallest_ele) {
                std::cout << "on the if" << std::endl;
                std::cout << "value of shade_gray: "<< shade_gray << std::endl;
                std::cout << "value of cur_ele: " << cur_ele << std::endl;
                Color k(shade_gray, shade_gray, shade_gray);
                cur_row.push_back(k);
                std::cout << "val for pixel " << i << ", " << j << ": " << k.Red() << " " << k.Green() << " " << k.Blue() << " " << std::endl;
            } else {
                std::cout << "on the else" << std::endl;
                shade_gray = 
                    (int)std::round(((double)cur_ele - (double)smallest_ele) / ((double)largest_ele - (double)smallest_ele) * kMaxColorValue); //this is the problem
                std::cout << "updated shade_gray: " << shade_gray << std::endl;
                std::cout << "value of cur_ele: "<< cur_ele << std::endl;
                Color c(shade_gray, shade_gray, shade_gray);
                cur_row.push_back(c);
                std::cout << "val for pixel " << i << ", " << j << ": " << c.Red() << " " << c.Green() << " " << c.Blue() << " " << std::endl;
            }
        }
        image_.push_back(cur_row);
    }
    //potentially problematic
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width_, size_t height) : width_(width_), height_(height) {
    ElevationDataset e(filename, width_, height_); //look into throwing error here later
    const std::vector<std::vector<int>>& dataset = e.GetData();
    int minimum = dataset[0][0];
    int maximum = dataset[0][0];
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (dataset[i][j] < minimum) {
                minimum = dataset[i][j];
            }
            if (dataset[i][j] > maximum) {
                maximum = dataset[i][j];
            }
        }
    }
    image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> cur_row;
        for (size_t j = 0; j < width_; ++j) {
            int cur_ele = dataset[i][j];
            int shade_gray = 0.0;
            if (minimum == maximum) {
                Color k(shade_gray, shade_gray, shade_gray);
                cur_row.push_back(k);
                std::cout << "val for pixel " << i << ", " << j << ": " << k.Red() << " " << k.Green() << " " << k.Blue() << " " << std::endl;
            } else {
                shade_gray = (int)std::round(((double)cur_ele - (double)minimum) / ((double)maximum - (double)minimum) * kMaxColorValue);
                Color c(shade_gray, shade_gray, shade_gray);
                cur_row.push_back(c);
                std::cout << "val for pixel " << i << ", " << j << ": " << c.Red() << " " << c.Green() << " " << c.Blue() << " " << std::endl;
            }
        }
        image_.push_back(cur_row);
    } 
}

size_t GrayscaleImage::Width() const {
    return width_;
}

size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_[row][col]; //potentially wrong
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    //Writes out image_ in plain PPM format; filename is name.
    std::ofstream ofs(name);
    // if (!ofs.is_open()) {
    //     throw std::invalid_argument("bad file");
    // }
    ofs << "P3" << "\n" << width_ << " " << height_ << "\n" << kMaxColorValue << "\n";
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            const Color& c = ColorAt((int)i, (int)j);
            std::string c_values = std::to_string(c.Red()) + " " +  std::to_string(c.Green()) + " " + std::to_string(c.Blue()) + " ";
            ofs << c_values;
        }
        ofs << "\n";
    }
}