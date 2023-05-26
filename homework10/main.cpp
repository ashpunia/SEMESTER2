#include <cstdlib>
#include <cmath>
#include <vector>
#include <iterator>
#include <iostream>

#include "image.h"
#include "priority_queue.h"
using namespace std;
// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
//double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
        exit(1);
    }
    
    // open the input image
    Image<Color> input;
    if (!input.Load(argv[1])) {
        std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
        exit(1);
    }
    
    // a place to write the distance values
    Image<DistancePixel> distance_image;
    distance_image.Allocate(input.Width(),input.Height());
    
    // calculate the distance field (each function returns the maximum distance value)
    double max_distance = 0;
    if (std::string(argv[3]) == std::string("naive_method")) {
        max_distance = NaiveDistanceFieldMethod(input,distance_image);
    }
    else if (std::string(argv[3]) == std::string("improved_method")) {
        max_distance = ImprovedDistanceFieldMethod(input,distance_image);
    }
    
    else if (std::string(argv[3]) == std::string("pq_with_map")) {
        max_distance = 0;
        //max_distance = FastMarchingMethod(input,distance_image);
    }
    
    else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
        // EXTRA CREDIT: implement FastMarchingMethod with a hash table
    } else {
        std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
        exit(1);
    }
    
    // convert distance values to a visualization
    Image<Color> output;
    output.Allocate(input.Width(),input.Height());
    for (int i = 0; i < input.Width(); i++) {
        for (int j = 0; j < input.Height(); j++) {
            double v = distance_image.GetPixel(i,j).getValue();
            if (std::string(argv[4]) == std::string("greyscale")) {
                output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
            } else if (std::string(argv[4]) == std::string("grey_bands")) {
                output.SetPixel(i,j,GreyBands(v,max_distance,4));
            } else if (std::string(argv[4]) == std::string("rainbow")) {
                output.SetPixel(i,j,Rainbow(v,max_distance));
            } else {
                // EXTRA CREDIT: create other visualizations
                std::cerr << "ERROR: Unknown visualization style" << std::endl;
                exit(0);
            }
        }
    }
    // save output
    if (!output.Save(argv[2])) {
        std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
        exit(1);
    }
    return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // loop over the pixels in the input image
    for (int i = 0; i < w; i++)  {
        for (int j = 0; j < h; j++) {
            double closest = -1;
            // loop over all other pixels in the input image
            for (int i2 = 0; i2 < w; i2++)  {
                for (int j2 = 0; j2 < h; j2++) {
                    const Color& c = input.GetPixel(i2,j2);
                    // skip all pixels that are not black
                    if (!c.isBlack()) continue;
                    // calculate the distance between the two pixels
                    double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
                    // store the closest distance to a black pixel
                    if (closest < 0 || distance < closest) {
                        closest = distance;
                    }
                }
            }
            assert (closest >= 0);
            answer = std::max(answer,closest);
            // save the data to the distance image
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(closest);
        }
    }
    return answer;
}
// ===========================================================================================
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int width = input.Width();
  int height = input.Height();
  // return the maximum distance value
  double answer = 0;
  // store all the black pixels in a vector
  std::vector<std::pair<int,int>> black_pixels;
  for (int i = 0; i < width; i++)  {
      for (int j = 0; j < height; j++) {
          const Color& c = input.GetPixel(i,j);
          if (c.isBlack())
            black_pixels.push_back(std::make_pair(i,j));
      }
  }
  // loop over all other pixels in the input image
  for (int i = 0; i < width; i++)  {
      for (int j = 0; j < height; j++) {
          double closest = -1;
          for (unsigned int m = 0; m < black_pixels.size(); m++) {
              int tmpX = black_pixels[m].first;
              int tmpY = black_pixels[m].second;
              double distance = sqrt((i - tmpX)*(i - tmpX) + (j - tmpY)*(j - tmpY));
              // store the closest distance to a black pixel
              if (closest < 0 || distance < closest) {
                  closest = distance;
              }
          }
          assert (closest >= 0);
          answer = std::max(answer,closest);
          // save the data to the distance image
          DistancePixel& p = distance_image.GetPixel(i,j);
          p.setValue(closest);
      }
  }
  return answer;
}
// ==========================================================================================
// double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
//   return 0;
// }
// ===================================================================================================
Color Rainbow(double distance, double max_distance) {
    Color answer;
    if (distance < 0.001) {
        // black
        answer.r = 0; answer.g = 0; answer.b = 0;
    } else if (distance < 0.2*max_distance) {
        // blue -> cyan
        double tmp = distance * 5.0 / max_distance;
        answer.r = 0;
        answer.g = tmp*255;
        answer.b = 255;
    } else if (distance < 0.4*max_distance) {
        // cyan -> green
        double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
        answer.r = 0;
        answer.g = 255;
        answer.b = (1-tmp*tmp)*255;
    } else if (distance < 0.6*max_distance) {
        // green -> yellow
        double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
        answer.r = sqrt(tmp)*255;
        answer.g = 255;
        answer.b = 0;
    } else if (distance < 0.8*max_distance) {
        // yellow -> red
        double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = (1-tmp*tmp)*255;
        answer.b = 0;
    } else if (distance < max_distance) {
        // red -> white
        double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = tmp*255;
        answer.b = tmp*255;
    } else {
        // white
        answer.r = answer.g = answer.b = 255;
    }  
    return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
    Color answer;
    if (distance < 0.001) {
        // red
        answer.r = 255; answer.g = 0; answer.b = 0;
    } else {
        // shades of grey
        answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
    }  
    return answer;
}

// ===================================================================================================