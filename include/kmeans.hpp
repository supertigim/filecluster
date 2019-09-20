#pragma once
#include "string_for_kmean.hpp"

// resampling centeroids every 25 iterations
const size_t RESAMPLING_ITER = 25;

// difference threshold to stop k-means process
const double DIFF_THRESHOLD = 0.01;

using data_frame = std::vector<string_for_kmean>;

data_frame k_means(const data_frame& data,size_t k, size_t number_of_iterations);
void clustering(const data_frame& data, const data_frame& kmeans, std::vector<std::vector<std::string>>& output);

// end of file