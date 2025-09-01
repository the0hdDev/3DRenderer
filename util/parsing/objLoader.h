#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>

namespace util {
    std::vector<float> load_model_from_file(const char* filename, glm::mat4& preTransform);
}