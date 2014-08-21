#include <string>
#include <iostream>

template<typename T>
class type_descriptor<T>;

template<typename T>
class type_descriptor<T> {
    operator const char *() {
        return  
    }
};

const std::string type_descriptor<char>::value = "char";

int main(void) {
//    std::cout << type_descriptor<char>();
    return 0;
}
