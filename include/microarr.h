#include <vector>
#include <unordered_map>

class microarr {
    friend microarr exp(microarr&& lhs);
    friend microarr log(microarr&& lhs);

private:
    std::vector<int> dims;
    std::vector<double> arr;
    std::vector<int> transpose_map;
    bool is_transposed;
public:
    // constructors
    microarr();
    
    template<typename... T>
    microarr(T... dimensions) : dims{ dimensions... }, is_transposed(false) {
        std::size_t acc = 1;
        for (int e : dims) {
            acc *= e;
        }
        
        arr.reserve(acc);

        for (std::size_t i = 0; i < dims.size(); i++) {
            transpose_map.push_back((int) i);
        }
    }

    template<typename... T>
    microarr(std::vector<double> vals, T... dimensions) : dims{dimensions...}, arr(vals), is_transposed(false) {
        std::size_t acc = 1;
        for (int e : dims) {
            acc *= e;
        }
        
        assert(vals.size() == acc);

        for (std::size_t i = 0; i < dims.size(); i++) {
            transpose_map.push_back((int) i);
        }
    }
    // ensure copy and move constructors exist
    microarr(microarr& lottadim) = default;
    microarr(microarr&& lottadim) = default;
    
    // getters and setters
    std::vector<int> get_dims();
    
    template<typename... T>
    double& get(T... idx) {
        std::vector<std::size_t> indicies = { static_cast<std::size_t>(idx)... };
        assert(indicies.size() == dims.size());
        
        std::size_t arr_index = 0;
        for (std::size_t i = 0; i < indicies.size(); i++) {
            int idx_block = transpose_map[i];
            std::size_t block_index = indicies[idx_block];
            for (std::size_t j = dims.size()-1; j > i; j--) {
                block_index *= dims[j];
            }
            arr_index += block_index;
        }

        return arr[arr_index];
    }

    template<typename... T>
    double get(T... idx) const {
        return get(idx...);
    }

    // unary method operators
    microarr transpose(int axis1 = 0, int axis2 = 1);
    microarr sum(int axis = 0);
};

// unary operators
microarr exp(microarr&& lhs);
microarr log(microarr&& lhs);

// tensor-tensor operations
microarr dot(const microarr lhs, const microarr rhs, int axis = 0);
microarr operator+(const microarr lhs, const microarr rhs);
microarr operator-(const microarr lhs, const microarr rhs);
microarr operator*(const microarr lhs, const microarr rhs);
microarr operator/(const microarr lhs, const microarr rhs);
// scalar-tensor operations
microarr dot(double lhs, const microarr rhs, int axis = 0);
microarr operator+(double lhs, const microarr rhs);
microarr operator-(double lhs, const microarr rhs);
microarr operator*(double lhs, const microarr rhs);
microarr operator/(double lhs, const microarr rhs);
// tensor-scalar operations
microarr dot(const microarr lhs, double rhs, int axis = 0);
microarr operator+(const microarr lhs, double rhs);
microarr operator-(const microarr lhs, double rhs);
microarr operator*(const microarr lhs, double rhs);
microarr operator/(const microarr lhs, double rhs);
