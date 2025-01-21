#include <string>

template <typename T>
T from_string(const std::string& cadena) {
    std::istringstream iss(cadena);
    T valor;
    if (!(iss >> valor)) {
        throw std::invalid_argument("Error al convertir la cadena: formato inválido.");
    }
    return valor;
}
