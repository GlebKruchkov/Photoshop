#include "bmp_reader.h"
#include "Parser.h"
#include "Redactor.h"

int main(int argc, char** argv) {

    std::queue<std::unique_ptr<BaseFilter>> filters_new;
    Parser parse = Parser(argc, argv);
    try {
        filters_new = parse.Parsing();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(0);
    }
    char* input_path = argv[1];
    char* output_path = argv[2];

    Image image(0, 0);

    try {
        image.Read(reinterpret_cast<const char*>(input_path));
    } catch (std::exception& exception) {
        std::cout << exception.what() << '\n';
        return -1;
    }
    Redactor redactor = Redactor(std::move(filters_new), output_path, image);
    redactor.RedactFile();

}
