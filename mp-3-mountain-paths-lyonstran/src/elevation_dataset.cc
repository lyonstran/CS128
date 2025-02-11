#include "elevation_dataset.hpp"



ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) 
    : width_(width), height_(height) {
    std::ifstream file(filename);
    data_ = std::vector<std::vector<int>>(height_, std::vector<int>(width_)); // -> initialize data_ to have size of height and width parameters
    if (!file.is_open()) {
        throw std::runtime_error("couldn't open file");
    }
    size_t checker = 0;
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            int elevation = 0;
            if (!(file >> elevation)) {
                throw std::invalid_argument("bad argument passed");
            }
            data_[i][j] = elevation;
            checker++;
        }
    }
    if (checker != width_ * height_) {
        throw std::invalid_argument("extra/insufficient data found.");
    }
    int minimum = data_[0][0];
    int maximum = data_[0][0];
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (data_[i][j] < minimum) {
                minimum = data_[i][j];
            } 
            if (data_[i][j] > maximum) {
                maximum = data_[i][j];
            }
        }
    }
    min_ele_ = minimum;
    max_ele_ = maximum;
}



size_t ElevationDataset::Width() const { //Returns the “width” of the dataset
    return width_;
}


size_t ElevationDataset::Height() const { //Returns the “height” of the dataset
    return height_;
}


int ElevationDataset::MaxEle() const { //Returns the maximum elevation value observed in the dataset
    return max_ele_;
}


int ElevationDataset::MinEle() const { //Returns the minimum elevation value observed in the dataset
    return min_ele_;
}


int ElevationDataset::DatumAt(size_t row, size_t col) const { //Returns the value recorded for (row, col)
    return data_[row][col];
}


const std::vector<std::vector<int>>& ElevationDataset::GetData() const { //Returns reference to const to data_.
    return data_;
}