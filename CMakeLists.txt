add_executable(
        image_processor
        image_processor.cpp
        Parser.cpp Parser.h bmp_reader.cpp bmp_reader.h Base_filter.h Crop.cpp Crop.h Grayscale.cpp Grayscale.h Negative.cpp Negative.h Sharpening.cpp Sharpening.h EdgeDetection.cpp EdgeDetection.h Blur.cpp Blur.h Tape_effect.cpp Tape_effect.h Redactor.cpp Redactor.h)
