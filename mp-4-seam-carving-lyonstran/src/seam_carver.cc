#include "seam_carver.hpp"
#include "image_ppm.hpp"
// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel pixel_up = Pixel();
  if (row == 0) {
    pixel_up = image_.GetPixel(image_.GetHeight() - 1, col);
  } else {
    pixel_up = image_.GetPixel(row - 1, col);
  }
  Pixel pixel_down = Pixel();
  if (row == image_.GetHeight() - 1) {
    pixel_down = image_.GetPixel(0, col);
  } else {
    pixel_down = image_.GetPixel(row + 1, col);
  }
  Pixel pixel_r = Pixel();
  if (col == image_.GetWidth() - 1) {
    pixel_r = image_.GetPixel(row, 0);
  } else {
    pixel_r = image_.GetPixel(row, col + 1);
  }
  Pixel pixel_l = Pixel();
  if (col == 0) {
    pixel_l = image_.GetPixel(row, image_.GetWidth() - 1);
  } else {
    pixel_l = image_.GetPixel(row, col - 1);
  }
  int col_red = pixel_l.GetRed() - pixel_r.GetRed();  // differences in col
  int col_gre = pixel_l.GetGreen() - pixel_r.GetGreen();
  int col_blu = pixel_l.GetBlue() - pixel_r.GetBlue();

  int row_red = pixel_up.GetRed() - pixel_down.GetRed();  // differences by row
  int row_gre = pixel_up.GetGreen() - pixel_down.GetGreen();
  int row_blu = pixel_up.GetBlue() - pixel_down.GetBlue();
  return (col_red * col_red + col_gre * col_gre + col_blu * col_blu) +
         (row_red * row_red + row_gre * row_gre + row_blu * row_blu);
}

void SeamCarver::CostAndEnergies(int** energies,
                                 int** cost,
                                 const int& width,
                                 const int& height,
                                 bool vert_status) const {
  for (int row = 0; row < height; ++row) {
    energies[row] = new int[width];
    cost[row] = new int[width];
    for (int col = 0; col < width; ++col) {
      energies[row][col] = GetEnergy(row, col);
      if ((vert_status && row == height - 1) ||
          (!vert_status && col == width - 1)) {
        cost[row][col] = energies[row][col];
      }
    }
  }
  // switch between hor and vert seam() -> vert_status
}
int* SeamCarver::SeamCalculator(int** cost, const int& x, const int& y, bool vert_status) const {
  int* seam = new int[x];
  int starting_i = 0;
  int min = cost[0][0];
  if (vert_status) {
    for (int i = 1; i < y; ++i) {
      if (cost[i][0] < min) {
        min = cost[i][0];
        starting_i = i;
      }
    }
  } else {
    for (int j = 1; j < y; ++j) {
      if (cost[0][j] < min) {
        min = cost[0][j];
        starting_i = j;
      }
    }
  }

  seam[0] = starting_i;
  for (int i = 1; i < x; ++i) {
    int prev = seam[i - 1];
    int pick[3] = {prev, prev, prev};
    if (prev > 0) pick[0] = prev - 1;
    if (prev < y - 1) pick[2] = prev + 1;

    int min_i = 0;
    int least_e = 0;
    if (vert_status) {
      least_e = cost[pick[0]][i];
      for (int j = 1; j < 3; ++j) {
        int energy = cost[pick[j]][i];
        if (energy < least_e) {
          least_e = energy;
          min_i = j;
        }
      }
    } else {
      least_e = cost[i][pick[0]];
      for (int j = 1; j < 3; ++j) {
        int energy = cost[i][pick[j]];
        if (energy < least_e) {
          least_e = energy;
          min_i = j;
        }
      }
    }

    seam[i] = pick[min_i];
  }
  return seam;
}
int* SeamCarver::GetHorizontalSeam() const {
  int w = GetWidth();
  int h = GetHeight();
  int** arr_cost = new int*[h];
  int** arr_energy = new int*[h];

  // make function tht takes care of energies and cost values:
  CostAndEnergies(arr_energy, arr_cost, w, h, false);
  // seam
  int* seam = SeamCalculator(arr_cost, w, h, false);
  for (int i = 0; i < h; ++i) {
    delete[] arr_energy[i];
    delete[] arr_cost[i];
  }
  delete[] arr_energy;
  delete[] arr_cost;
  return seam;
}
int* SeamCarver::GetVerticalSeam() const {
  int w = GetWidth();
  int h = GetHeight();
  int** arr_cost = new int*[h];
  int** arr_energy = new int*[h];

  // make function tht takes care of energies and cost values:
  CostAndEnergies(arr_energy, arr_cost, w, h, true);
  // seam
  int* seam = SeamCalculator(arr_cost, w, h, true);
  for (int i = 0; i < h; ++i) {
    delete[] arr_energy[i];
    delete[] arr_cost[i];
  }
  delete[] arr_energy;
  delete[] arr_cost;
  return seam;
}
void SeamCarver::RemoveHorizontalSeam() {
  // finish later
  int* seam = GetHorizontalSeam();
  image_.RHSHelper(seam);
  height_ = image_.GetHeight();
  delete[] seam;
}
void SeamCarver::RemoveVerticalSeam() {
  // finish later;
  int* seam = GetVerticalSeam();
  image_.RVSHeper(seam);
  width_ = image_.GetWidth();
  delete[] seam;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
