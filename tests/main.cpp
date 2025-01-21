#include <iostream>
#include <string>

#include "constants.h"
#include "fits.h"
#include "utils.h"

int main(void) {
    std::cout << "start" << std::endl;

    Fits fits_file("../../../2024.12.07_IC434_v1.0.fit", std::ios_base::binary | std::ios_base::in);

    if (!fits_file.is_open()) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return -15;
    }

    fits_file.read_header();

    size_t i = 0;
    for (auto k : fits_file.headers.at(0)) {
        std::cout << &k << "    " << &(fits_file.headers.at(0).data()[i]) << "    " << k.second << std::endl;
        ++i;
    }

    std::cout << "" << std::endl;

    fits_file.close();

    std::cout << fits_file.size << std::endl;
    std::cout << fits_file.nblocks << std::endl;

    std::cout << "end" << std::endl;


    return 0;
}
