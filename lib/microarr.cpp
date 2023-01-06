#include "microarr.h"
#include <cmath>

// constructors
microarr::microarr() : dims({1}), arr(0), transpose_map({0}) {}



// getters and setters
std::vector<std::size_t> microarr::get_dims() {
    return dims;
}

// unary method operators
microarr microarr::transpose(std::size_t axis1, std::size_t axis2) {
    std::swap(transpose_map[axis1], transpose_map[axis2]);
    std::swap(dims[axis1], dims[axis2]);

    return *this;
}

/// @brief sums along an axis
/// @param axis the axis along which to sum, defaults to `0`
/// @return a microarr with one less axis
microarr microarr::sum(std::size_t axis) {
    std::vector<std::size_t> new_dims(this->dims);
    new_dims.erase(new_dims.begin() + axis);
    
    microarr out(new_dims);
    
    std::vector<std::size_t> idx(new_dims.size());
    
    for (std::size_t i = 0; i < out.arr.size(); i++) {
        idx.clear();
        // generate a new multi-index
        for (std::size_t j = 0; j < new_dims.size(); j++) {
            std::size_t ind = i;
            for (std::size_t d = new_dims.size()-1; d > j; d--) ind /= new_dims[d];
            ind = ind % new_dims[j];
            idx.push_back(ind);
        }
        // sum across that index
        for (std::size_t k = 0; k < this->dims[axis]; k++) {
            // add in the new index
            std::vector<std::size_t> sum_idx(idx);
            sum_idx.insert(sum_idx.begin() + axis, k);

            out.get(idx) += this->get(sum_idx);
        }
        
    } 

    return out;
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

/// @brief supports the 1d and 2d dot products
/// @param lhs left hand side array
/// @param rhs right hand side array
/// @return the dot product of lhs and rhs
microarr dot(const microarr lhs, const microarr rhs) {
    if (lhs.dims.size() <= 2 && rhs.dims.size() <= 2) {
        microarr lhs_use = lhs;
        if (lhs.dims.size() == 1) {
            lhs_use = lhs.reshape(1, lhs.dims[0]);
        }

        microarr rhs_use = rhs;
        if (rhs.dims.size() == 1) {
            rhs_use = rhs.reshape(rhs.dims[0],1);
        }

        assert(lhs_use.dims[1] == rhs_use.dims[0]);
        
        microarr out(lhs_use.dims[0], rhs_use.dims[1]);

        for (std::size_t i = 0; i < lhs_use.dims[0]; i++) {
            for (std::size_t j = 0; j < rhs_use.dims[1]; j++) {
                for (std::size_t k = 0; k < lhs_use.dims[1]; k++) {
                    out.get(i,j) += lhs_use.get(i,k) * rhs_use.get(k,j);
                }
            }
        }
        return out;
        
    } else {
        return microarr();
    }
}

microarr operator+(const microarr lhs, const microarr rhs) {
    assert(lhs.dims == rhs.dims);
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] += rhs.arr[i];

    return out;
}
microarr operator-(const microarr lhs, const microarr rhs) {
    assert(lhs.dims == rhs.dims);
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] -= rhs.arr[i];

    return out;
}
microarr operator*(const microarr lhs, const microarr rhs) {
    assert(lhs.dims == rhs.dims);
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] *= rhs.arr[i];

    return out;
}
microarr operator/(const microarr lhs, const microarr rhs) {
    assert(lhs.dims == rhs.dims);
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] /= rhs.arr[i];

    return out;
}
// scalar-tensor operations
microarr operator+(double lhs, const microarr rhs) { return operator+(rhs,lhs); }
microarr operator-(double lhs, const microarr rhs) { return operator-(rhs,lhs); }
microarr operator*(double lhs, const microarr rhs) { return operator*(rhs,lhs); }
microarr operator/(double lhs, const microarr rhs) { return operator/(rhs,lhs); }
// tensor-scalar operations
microarr operator+(const microarr lhs, double rhs) {
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] += rhs;

    return out;
}
microarr operator-(const microarr lhs, double rhs) {
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] -= rhs;

    return out;
}
microarr operator*(const microarr lhs, double rhs) {
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] *= rhs;

    return out;
}
microarr operator/(const microarr lhs, double rhs) {
    microarr out(lhs);
    for (std::size_t i = 0; i < lhs.arr.size(); i++) out.arr[i] /= rhs;

    return out;
}

