#include <iostream>
#include "kmeans.hpp"
#include "jaroWinkler.hpp"

double str_distance(const std::string& s1, const std::string& s2 ){
    return 1.0 - jaroWinklerDistance(s1, s2);
}

size_t classify(const std::string& str, const data_frame& means){
    size_t k = means.size();
    double best_distance = std::numeric_limits<double>::max();
    size_t best_cluster = 0;
    for (size_t cluster = 0; cluster < k; ++cluster) {
        const double distance = str_distance(str, means[cluster].str());
        if (distance < best_distance) {
            best_distance = distance;
            best_cluster = cluster;
        }
    }
    return best_cluster;
}

size_t average_str_legnth(const std::vector<size_t>& lenghs){
    size_t size = lenghs.size();
    long total = 0;
    for(auto& l: lenghs){
        total += l;
    }
    return (size_t)((double)(total)/(float)(size));
}

double kmeans_diff(const data_frame& means, const data_frame& new_means){
    size_t k = means.size();
    double diff = 0.0;
    for (size_t i = 0 ; i < means.size(); i++) {
        diff += str_distance(means[i].str(), new_means[i].str());
    }
    return diff/(double)(k);
}

void set_centeroids_randomly(const data_frame& data, data_frame& means){
    for (auto& cluster : means) {
        cluster = *select_randomly(data.begin(), data.end());
        //std::cout << "random selected centeroid - "  << cluster.str() << std::endl;
    }
}

data_frame k_means(const data_frame& data,
                  size_t k,
                  size_t number_of_iterations){
    data_frame means(k), optimized_means(k);
    if (data.size() == 0 || k == 0 || number_of_iterations == 0) return means;
    set_centeroids_randomly(data, means);
    double global_diff = std::numeric_limits<double>::max();
    double local_diff = 0.0;
    std::vector<size_t> assignments(data.size());
    for (size_t iteration = 0; iteration < number_of_iterations; ++iteration) {
        std::cout << "Iteration: " << iteration + 1<< std::endl;
        
        // Find assignments.
        for (size_t point = 0; point < data.size(); ++point) {
            assignments[point] = classify(data[point].str(), means);
        }

        // Sum up and count characters for each cluster.
        data_frame new_means(k);
        for (size_t point = 0; point < data.size(); ++point) {
            const auto cluster = assignments[point];
            new_means[cluster].add(data[point].str());
        }

        local_diff = kmeans_diff(means, new_means);
        if (local_diff < DIFF_THRESHOLD) {
            std::cout << "Found optimized centeroid values and stopped early" << std::endl;
            return new_means;
        } else {
            std::cout << "local_diff:" << local_diff << " (global_diff:" << global_diff <<")" << std::endl;
            if (local_diff < global_diff) {
                global_diff = local_diff;
                for (size_t i = 0; i < k; ++i) {
                    optimized_means[i] = new_means[i];
                }
            }
        }
        
        // Update to get new centroids.
        if ((iteration+1) != number_of_iterations && 
                number_of_iterations >= RESAMPLING_ITER*2 && 
                (iteration+1)%RESAMPLING_ITER == 0) {
            std::cout << "Resamping centeroids" << std::endl;
            set_centeroids_randomly(data, means);
        } else {
            for (size_t i = 0; i < k; ++i) {
                if(new_means[i].str().size()){
                    means[i] = new_means[i];
                    std::cout <<"Num." << i << " : " << means[i].str() << " (Size:" << means[i].str().size() << ")"<< std::endl;
                }
                else{
                    std::cout <<"Num." << i << " : ###### Nothing for this cluster! Get a randome centeroid !!! ######" << std::endl;
                    means[i] = *select_randomly(data.begin(), data.end());
                }
            }
        }
    }
    
    std::cout << "Finished finding mean values of K(" << k << ")" << std::endl;
    if (local_diff > global_diff) return optimized_means; 
    return means;
}

void clustering(const data_frame& data,
                const data_frame& kmeans,
                std::vector<std::vector<std::string>>& output ){
    output.clear();
    output = std::vector<std::vector<std::string>>(kmeans.size());

    for (auto& str_k: data) {
        output[classify(str_k.str(), kmeans)].emplace_back(str_k.str());
    }
}

// end of file