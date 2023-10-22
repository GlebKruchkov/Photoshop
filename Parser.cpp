#include "Parser.h"

std::queue<std::unique_ptr<BaseFilter>> Parser::Parsing() {
    std::queue<std::unique_ptr<BaseFilter>> filters;
    if (argc_ >= 4) {
        for (size_t it = 3; it < argc_; ++it) {
            if (std::string(argv_[it]) == "-blur") {
                if (it + 1 >= argc_) {
                    throw std::runtime_error("You need to choose blur param");
                }
                ++it;
                double sigma = 0;
                try {
                    sigma = (std::stod(argv_[it]));
                } catch (std::exception& e) {
                    std::cout << "You need to write the correct digit param for the filter : -blur" << std::endl;
                    exit(0);
                }
                filters.push(std::make_unique<Blur>(sigma));
            } else if (std::string(argv_[it]) == "-gs") {
                filters.push(std::make_unique<Grayscale>());
            } else if (std::string(argv_[it]) == "-neg") {
                filters.push(std::make_unique<Negative>());
            } else if (std::string(argv_[it]) == "-sharp") {
                filters.push(std::make_unique<Sharpening>());
            } else if (std::string(argv_[it]) == "-edge") {
                if (it + 1 >= argc_) {
                    throw std::runtime_error("You need to choose -edge param");
                }
                ++it;
                double threshold = 0;
                try {
                    threshold = (std::stod(argv_[it]));
                } catch (std::exception& e) {
                    std::cout << "You need to write the correct digit param for the filter : -edge" << std::endl;
                    exit(0);
                }
                filters.push(std::make_unique<EdgeDetection>(threshold));
            } else if (std::string(argv_[it]) == "-crop") {
                if (it + 2 >= argc_) {
                    throw std::runtime_error("You need to choose two params after -crop");
                }
                std::vector<int> p;
                ++it;
                try {
                    p.push_back(std::stoi(argv_[it]));
                } catch (std::exception& e) {
                    std::cout << "You need to write the correct digit params for the filter : -crop" << std::endl;
                    exit(0);
                }
                ++it;
                try {
                    p.push_back(std::stoi(argv_[it]));
                } catch (std::exception& e) {
                    std::cout << "You need to write the correct digit params for the filter : -crop" << std::endl;
                    exit(0);
                }
                filters.push(std::make_unique<Crop>(p[0], p[1]));
            } else if (std::string(argv_[it]) == "-tape") {
                filters.push(std::make_unique<TapeEffect>());
            } else {
                try {
                    throw std::runtime_error(
                            "You need to choose filters only from the next list.\nList of available "
                            "filters:\n-crop\n-gs\n-neg\n-sharp\n-edge\n-blur\n-tape");
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                    exit(0);
                }
            }
        }
        return filters;
    } else if (argc_ == 1) {
        std::cout
                << "Firstly you need to choose the file, that you wnt to redact.\nSecondly you need to choose the export "
                   "filename.\nLastly you need to choose some filters.\nList of variable "
                   "filters:\n-crop\n-gs\n-neg\n-sharp\n-edge\n-blur\n-tape"
                << std::endl;
        exit(0);
    } else if (argc_ == 2) {
        throw std::runtime_error(
                "You need to choose the export filename.\nThen you can choose filters from the next "
                "list:\n-crop\n-gs\n-neg\n-sharp\n-edge\n-blur\n-tape");
    } else if (argc_ == 3) {
        std::cout << "List of available filters:\n-crop\n-gs\n-neg\n-sharp\n-edge\n-blur\n-tape" << std::endl;
        exit(0);
    }
    return filters;
}
