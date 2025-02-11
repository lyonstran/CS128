#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue();
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  void OptimizedPathsRow(const ElevationDataset& dataset, Path& path, const int& i);
  void ChoosingBestPath(const ElevationDataset& dataset, Path& path, const int& i);
  
  private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kRedlineR = 252;
  static const int kRedLineG = 25;
  static const int kRedLineB = 63;
  static const int kGreenlineR = 31;
  static const int kGreenlineG = 253;
  static const int kGreenlineB = 13; 
};

#endif