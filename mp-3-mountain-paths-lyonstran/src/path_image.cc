#include "path_image.hpp"

void PathImage::OptimizedPathsRow(const ElevationDataset& dataset, Path& path, const int& i) {
    int cur_elev = dataset.DatumAt(path.GetPath().at(i), i);
    int east_elev = dataset.DatumAt(path.GetPath().at(i), i + 1);
    int ascend_east = abs(cur_elev - east_elev);
    unsigned int r_next = path.GetPath().at(i);
    int minimum_ascend = ascend_east;
    if (path.GetPath().at(i) > 0) {
        int ne_elev = dataset.DatumAt(path.GetPath().at(i) - 1, i + 1);
        int ne_ascend = abs(cur_elev - ne_elev);
        if (ne_ascend < minimum_ascend) {
            minimum_ascend = ne_ascend;
            r_next = path.GetPath().at(i) - 1;
        }
    }
    if (path.GetPath().at(i) < dataset.Height() - 1) {
        int se_elev = dataset.DatumAt(path.GetPath().at(i) + 1, i + 1);
        int se_ascend = abs(cur_elev - se_elev);
        if (se_ascend < minimum_ascend) {
            minimum_ascend = se_ascend;
            r_next = path.GetPath().at(i) + 1;
        }
    }
    path.SetLoc(i + 1, r_next);
    path.IncEleChange(minimum_ascend);
}

void PathImage::ChoosingBestPath(const ElevationDataset& dataset, Path& path, const int& i) {
    int cur_elev = dataset.DatumAt(path.GetPath().at(i), i);
    int e_elev = dataset.DatumAt(path.GetPath().at(i), i + 1);
    int ne_elev = dataset.DatumAt(path.GetPath().at(i) - 1, i + 1);
    int se_elev = dataset.DatumAt(path.GetPath().at(i) + 1, i + 1);
    int ascent_se = abs(se_elev - cur_elev);
    int ascent_e = abs(e_elev - cur_elev);
    int ascent_ne = abs(ne_elev - cur_elev);

    if (ascent_e == ascent_se || ascent_e == ascent_ne) {
        path.SetLoc(i + 1, path.GetPath().at(i));
    } else if (ascent_se == ascent_ne) {
        path.SetLoc(i + 1, path.GetPath().at(i) + 1);
    } else if (ascent_se < ascent_e && ascent_se < ascent_ne) {
        path.SetLoc(i + 1, path.GetPath().at(i) + 1);
        path.IncEleChange(ascent_se);
    } else if (ascent_ne < ascent_e && ascent_ne < ascent_se) {
        path.SetLoc(i + 1, path.GetPath().at(i) - 1);
        path.IncEleChange(ascent_ne);
    } else {
        path.SetLoc(i + 1, path.GetPath().at(i));
        path.IncEleChange(ascent_e);
    }
}


PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) : 
    width_(dataset.Width()), height_(dataset.Height()) {
    unsigned int best_r = 0;
    unsigned int min_change = paths_.at(0).EleChange();
    for (size_t i = 0; i < height_; ++i) {
        paths_.push_back(Path(width_, i));
    }
    for (Path& p : paths_) {
        for (size_t i = 0; i < width_ - 1; ++i) {
            
        }
    }
    

    

}
 
size_t PathImage::Width() const {
    return width_;
}
size_t PathImage::Height() const {
    return height_;
}
unsigned int PathImage::MaxColorValue() {
    return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
    return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs(name);
    if (!ofs.is_open()) {
        throw std::runtime_eror("file could not be opened");
    }
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
}