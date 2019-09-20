#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <stdlib.h>
#include "kmeans.hpp"

// Generate data frame from a file
bool generate_data(const std::string& filepath, data_frame& data) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        data.clear();
        std::string line;
        while (getline(file, line)) {
            data.emplace_back(line);
        }
        file.close();
        if(data.size() == 0) return false;
    } else {
        return false;
    }
    std::cout << "Data Size :" << data.size() << std::endl;
    return true;
}

// Generate a result file
void generate_output_file(const data_frame& kmeans,
                        const std::vector<std::vector<std::string>>& clustered_data,
                        const std::string& outputfile) {
    assert(kmeans.size()==clustered_data.size());

    std::ofstream file(outputfile);
    if (file.is_open()) {
        for (size_t i = 0 ; i < kmeans.size(); ++i) {
            file << "#####################################################################################################" << std::endl;
            file << "Num." << i << " - centeroid: " << kmeans[i].str() << std::endl << std::endl;
            long total = 0;
            for (auto& filename: clustered_data[i]) {
                ++total;
                file << filename << std::endl;
            }
            file << "##### End of this(" << i << ") cluster, Total Number: "<< total <<" #####\n" << std::endl;
        }
        file.close();
    }else{
        std::cout << "Failed to write the file, " << outputfile << std::endl;
    }
}

int main(int argc, char* argv[]) {
    namespace po = boost::program_options;
    po::options_description desc("Allowed options"); // Declare the supported options.

    std::string filepath, outputfile;
    int k;
    size_t iter;

    desc.add_options()("help","ex>./filecluster -f f.txt -o o.txt -k 3 -i 200")(
        "filepath,f", po::value<std::string>(&filepath)->required(), "input file (.txt)")(
        "output,o", po::value<std::string>(&outputfile)->required(), "output file (.txt)")(
        "K,k", po::value<int>(&k)->required(), "K factor of K-Means clustering")(
        "iteration,i", po::value<size_t>(&iter)->default_value(200),"number of iteration");

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help") != 0u) {
            std::cout << desc << "\n";
            return EXIT_SUCCESS;
        }
    } catch (po::error& e) {
        std::cerr << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
        return EXIT_FAILURE;
    }

    data_frame data;
    if (generate_data(filepath, data)) {
        std::cout << "K-Means clustering started (K:" << k << ", Iterations:" << iter << ")" << std::endl;
        data_frame kmeans = k_means(data, k, iter);
        std::vector<std::vector<std::string>> clustered_data;
        clustering(data, kmeans, clustered_data);
        generate_output_file(kmeans, clustered_data, outputfile);
        std::cout << "Successfully finished...!!!" << std::endl;
    } else {
        std::cout << "Something wrong in handling the file, " << filepath << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// end of file