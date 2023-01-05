#include "microarr.h"
#include <iostream>

#define ASSERT_EQ(x, y, acc) acc = (acc && (x==y)); std::cout << x << " == " << y << " (" << acc <<"), ";
#define ASSERT(x, acc) acc = (acc && x);

bool simple_access() {
    bool passed_flag = true;
    // a = [[1,0,1], [0,1,0]]
    std::vector<double> a_internal = {1,0,1 , 0,1,0};
    microarr a(a_internal, 2,3);
    
    std::cout << "a: ";
    ASSERT_EQ(a.get(0,0), 1, passed_flag);
    ASSERT_EQ(a.get(0,1), 0, passed_flag); 
    ASSERT_EQ(a.get(0,2), 1, passed_flag);
    ASSERT_EQ(a.get(1,0), 0, passed_flag);
    ASSERT_EQ(a.get(1,1), 1, passed_flag);
    ASSERT_EQ(a.get(1,2), 0, passed_flag);
    std::cout << std::endl;
    
    // b = [[[1,2],[3,4]],[[5,6],[7,8]],[[9,10],[11,12]]]
    std::vector<double> b_internal = {1,2,3,4,5,6,7,8,9,10,11,12};
    microarr b(b_internal,3,2,2);
    
    std::cout << "b: ";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                ASSERT_EQ(
                    b.get(i,j,k),
                    4*i + 2*j + k + 1,
                    passed_flag
                );
            }
        }
    }

    std::cout << std::endl;

    return passed_flag;
} 

bool write() {
    bool passed_flag = true;
    // a = [[1,0,1], [0,1,0]]
    std::vector<double> a_internal = {1,0,1 , 0,1,0};
    microarr a(a_internal, 2,3);
    ASSERT_EQ(a.get(0,0), 1, passed_flag);
    a.get(0,0) = 1234;
    ASSERT_EQ(a.get(0,0), 1234, passed_flag);
    return passed_flag;
}

int main() {
    bool passed_flag = true;
    
    ASSERT(simple_access(), passed_flag);
    ASSERT(write(), passed_flag);

    return (int) (!passed_flag);
}