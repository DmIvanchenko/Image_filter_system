/*
 * ImageResult.h
 *
 *  Created on: 2022-05-04
 *      Author: ImageIt
 */

#ifndef IMAGERESULT_H_
#define IMAGERESULT_H_
#include <memory>
#include <vips/vips8>

namespace backend {

class ImageResult {
public:
    ImageResult();
    virtual ~ImageResult();
    int width;
    int height;
    VipsBandFormat band_format;
    int bands;
    std::size_t size;
    std::shared_ptr<char []> data;
};

} /* namespace backend */

#endif /* IMAGERESULT_H_ */
