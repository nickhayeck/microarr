#include "microarr.h"
#include <cmath>

// constructors
microarr::microarr() : dims({1}), arr(0), transpose_map({0}), is_transposed(false) {}



// getters and setters
std::vector<int> microarr::get_dims() {
    return dims;
}

// unary method operators
microarr microarr::transpose(int axis1, int axis2) {
    std::swap(transpose_map[axis1], transpose_map[axis2]);
    std::swap(dims[axis1], dims[axis2]);

    return *this;
}

// unary operators
microarr exp(microarr&& lhs) {
    microarr out((microarr&&) lhs);
    for (std::size_t i = 0; i < out.arr.size(); i++) {
        out.arr[i] = std::exp(out.arr[i]);
    }

    return out;
}
microarr log(microarr&& lhs) {
    microarr out((microarr&&) lhs);
    for (std::size_t i = 0; i < out.arr.size(); i++) {
        out.arr[i] = std::log(out.arr[i]);
    }

    return out;
}

// tensor-tensor operations
microarr dot(const microarr lhs, const microarr rhs, int axis);
microarr operator+(const microarr lhs, const microarr rhs);
microarr operator-(const microarr lhs, const microarr rhs);
microarr operator*(const microarr lhs, const microarr rhs);
microarr operator/(const microarr lhs, const microarr rhs);
// scalar-tensor operations
microarr dot(double lhs, const microarr rhs, int axis);
microarr operator+(double lhs, const microarr rhs);
microarr operator-(double lhs, const microarr rhs);
microarr operator*(double lhs, const microarr rhs);
microarr operator/(double lhs, const microarr rhs);
// tensor-scalar operations
microarr dot(const microarr lhs, double rhs, int axis);
microarr operator+(const microarr lhs, double rhs);
microarr operator-(const microarr lhs, double rhs);
microarr operator*(const microarr lhs, double rhs);
microarr operator/(const microarr lhs, double rhs);

