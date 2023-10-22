#include "Redactor.h"

void Redactor::RedactFile() {
    while (!filters_new_.empty()) {
        filters_new_.front()->Do(image_);
        filters_new_.pop();
    }
    image_.Export(output_path_);
}
