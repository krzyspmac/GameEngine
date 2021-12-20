//
//  main.cpp
//  Compiler
//
//  Created by krzysp on 18/12/2021.
//

#include <iostream>
#include "Defs.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

#ifdef MACOS
    std::cout << "Mac!!\n";
#endif
    return 0;
}
