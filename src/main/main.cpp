#include <list>
#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <functional>
#include "mlib.h"


int main(){
    vector<int> A(3);
    

    // A.push_back(tp());
    A.push_back(11);

    for(int i = 0; i < A.size(); ++i)
        std::cout << A[i] << " ";

    for(auto c : A)
        std::cout << c << " ";

    std::cout << "\n" << A.size() << " " << A.capacity() <<  "\n";
    return 0;
}

