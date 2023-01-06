#include "microarr.h"
#include <iostream>

#define TITLE(str) std::cout << std::endl << "[TEST: " << str << "]" << std::endl;
#define ASSERT_EQ(x, y, acc) acc = (acc && (x==y)); std::cout << x << " == " << y << " (" << acc <<"), ";
#define ASSERT(x, acc) acc = (acc && x);

bool sum() {
    TITLE("sum");
    bool passed_flag = true;

    // 2x2 array
    std::vector<double> a_internal = {1,0,1 , 0,1,0};
    microarr a(a_internal, 2,3);

    microarr b = a.sum(0);

    ASSERT_EQ(b.get(0), 1, passed_flag);
    ASSERT_EQ(b.get(1), 1, passed_flag);
    ASSERT_EQ(b.get(2), 1, passed_flag);

    microarr c = a.sum(1);

    ASSERT_EQ(c.get(0), 2, passed_flag);
    ASSERT_EQ(c.get(1), 1, passed_flag);


    return passed_flag;
}

bool sum_redundant_dims() {
    TITLE("sum_redundant_dims");
    bool passed_flag = true;
    
    // redundant dimensions
    std::vector<double> a_internal = {1,0,1 , 0,1,0};
    microarr a(a_internal, 2,3,1,1,1);

    microarr b = a.sum(0);

    ASSERT_EQ(b.get(0,0,0,0), 1, passed_flag);
    ASSERT_EQ(b.get(1,0,0,0), 1, passed_flag);
    ASSERT_EQ(b.get(2,0,0,0), 1, passed_flag);

    microarr c = a.sum(1);

    ASSERT_EQ(c.get(0,0,0,0), 2, passed_flag);
    ASSERT_EQ(c.get(1,0,0,0), 1, passed_flag);

    return passed_flag;
}

bool transpose() {
    TITLE("transpose");
    bool passed_flag = true;

    std::vector<double> a_internal = {1,0,1 , 0,1,0};
    microarr a(a_internal, 2,3);

    a = a.transpose();

    ASSERT_EQ(a.get(0,0), 1, passed_flag);
    ASSERT_EQ(a.get(0,1), 0, passed_flag);
    ASSERT_EQ(a.get(1,0), 0, passed_flag);
    ASSERT_EQ(a.get(1,1), 1, passed_flag);
    ASSERT_EQ(a.get(2,0), 1, passed_flag);
    ASSERT_EQ(a.get(2,1), 0, passed_flag);

    return passed_flag;
}

int main() {
    bool passed_flag = true;

    ASSERT(sum(), passed_flag);
    ASSERT(sum_redundant_dims(), passed_flag);
    ASSERT(transpose(), passed_flag);

    return (int) (!passed_flag);
}