#include "image_ppm.hpp"
void ImagePPM::RHSHelper(const int* seam) {
  Pixel** pix = new Pixel*[height_ - 1];
  for (int i = 0; i < height_ - 1; ++i) {
    pix[i] = new Pixel[width_];
  }
  for (int col = 0; col < width_; ++col) {
    int nr = 0;
    for (int row = 0; row < height_; ++row) {
      if (row != seam[col]) {
        pix[nr][col] = pixels_[row][col];
      }
    }
  }
  for (int i = 0; i < height_; ++i) {
    delete[] pixels_[i];
  }
  delete[] pixels_;
  
  pixels_ = pix;
  height_--;
}
void ImagePPM::RVSHeper(const int* seam) {
  Pixel** pix = new Pixel*[height_ - 1];
  for (int i = 0; i < height_ - 1; ++i) {
    pix[i] = new Pixel[width_];
  }
  for (int row = 0; row < height_; ++row) {
    int nc = 0;
    for (int col = 0; col < width_; ++col) {
      if (col != seam[row]) {
        pix[row][nc] = pixels_[row][col];
      }
    }
  }
  for (int i = 0; i < width_; ++i) {
    delete[] pixels_[i];
  }
  delete[] pixels_;
  pixels_ = pix;
  width_--;
}
// implement the rest of ImagePPM's functions here
int ImagePPM::GetMaxColorValue() const {
  // Returns the max color value of the image (this is not always 255!)
  return max_color_value_;
}

Pixel ImagePPM::GetPixel(int row, int col) const {
  // Returns the pixel in the image at (row, col). You may assume that row and col will always be within the bounds of the image.
  return pixels_[row][col];
}


std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os.clear();
  os << "P3" << "\n";
  os << image.width_ << " " << image.height_ << "\n";
  os << image.max_color_value_ << "\n";
  for (int h = 0; h < image.height_; ++h) {
    for (int w = 0; w < image.width_; ++w) {
      Pixel p = image.pixels_[h][w];
      os << p.GetRed() << "\n";
      os << p.GetGreen() << "\n";
      os << p.GetBlue() << "\n";
    }
  }
  return os;
}

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}
