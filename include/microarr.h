#include <vector>
#include <unordered_map>

class microarr {
private:
    std::vector<std::size_t> dims;
    std::vector<double> arr;
    std::vector<std::size_t> transpose_map;
public:
    // constructors
    microarr();

    template<typename... T>
    microarr(T... dimensions) : dims{ dimensions... } {
        std::size_t acc = 1;
        for (std::size_t e : dims) {
            acc *= e;
        }
        
        arr.resize(acc);
        std::fill(arr.begin(), arr.end(), 0);

        for (std::size_t i = 0; i < dims.size(); i++) {
            transpose_map.push_back((std::size_t) i);
        }
    }

    template<typename... T>
    microarr(std::vector<double> vals, T... dimensions) : dims{static_cast<std::size_t>(dimensions)...}, arr(vals) {
        std::size_t acc = 1;
        for (std::size_t e : dims) {
            acc *= e;
        }
        
        assert(vals.size() == acc);

        for (std::size_t i = 0; i < dims.size(); i++) {
            transpose_map.push_back((std::size_t) i);
        }
    }
    
    // getters and setters
    std::vector<std::size_t> get_dims();

    double& get(std::vector<std::size_t> indicies) {
        assert(indicies.size() == dims.size());
        
        std::size_t arr_index = 0;
        for (std::size_t i = 0; i < indicies.size(); i++) {
            std::size_t idx_block = transpose_map[i];
            std::size_t block_index = indicies[idx_block];
            for (std::size_t j = dims.size()-1; j > i; j--) {
                std::size_t idx_dim = transpose_map[j];
                block_index *= dims[idx_dim];
            }
            arr_index += block_index;
        }

        return arr[arr_index];
    }
    
    template<typename... T>
    double& get(T... idx) {
        std::vector<std::size_t> indicies = { static_cast<std::size_t>(idx)... };

        return get(indicies);
    }

    template<typename... T>
    double get(T... idx) const {
        return get(idx...);
    }
    // reshaping functions
    microarr reshape(std::vector<size_t> shape) const {
        // total number of elems
        std::size_t acc = 1;
        for (std::size_t i : shape) {
            acc *= i;
        }

        assert(arr.size() == acc);

        microarr out(this->dims);

        // do a deep copy of the old microarr
        std::vector<std::size_t> idx(this->dims.size());
        for (std::size_t i = 0; i < out.arr.size(); i++) {
            idx.clear();
            // generate a new multi-index
            for (std::size_t j = 0; j < this->dims.size(); j++) {
                std::size_t ind = i;
                for (std::size_t d = this->dims.size()-1; d > j; d--) ind /= this->dims[d];
                ind = ind % this->dims[j];
                idx.push_back(ind);
            }

            out.get(idx) = this->get(idx);
        }

        out.dims = shape;

        // add extra numbers to the transpose map as needed
        for (std::size_t i = out.dims.size() - this->dims.size(); i > 0; i--) {
            std::size_t last = out.transpose_map.back();
            out.transpose_map.push_back(last+1);
        }

        return out;
    }
    template<typename... T>
    microarr reshape(T... shape) const {
        std::vector<std::size_t> s = { static_cast<std::size_t>(shape)... };

        return reshape(s);
    }


    // unary method operators
    microarr transpose(std::size_t axis1 = 0, std::size_t axis2 = 1);
    microarr sum(std::size_t axis = 0);


    // unary operators
    friend microarr exp(microarr&& lhs);
    friend microarr log(microarr&& lhs);

    // tensor-tensor operations
    friend microarr dot(const microarr lhs, const microarr rhs);
    friend microarr operator+(const microarr lhs, const microarr rhs);
    friend microarr operator-(const microarr lhs, const microarr rhs);
    friend microarr operator*(const microarr lhs, const microarr rhs);
    friend microarr operator/(const microarr lhs, const microarr rhs);
    // scalar-tensor operations
    friend microarr operator+(double lhs, const microarr rhs);
    friend microarr operator-(double lhs, const microarr rhs);
    friend microarr operator*(double lhs, const microarr rhs);
    friend microarr operator/(double lhs, const microarr rhs);
    // tensor-scalar operations
    friend microarr operator+(const microarr lhs, double rhs);
    friend microarr operator-(const microarr lhs, double rhs);
    friend microarr operator*(const microarr lhs, double rhs);
    friend microarr operator/(const microarr lhs, double rhs);
};