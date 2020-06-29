#ifndef Node_hpp
#define Node_hpp

#include <cstdint>
#include <cstdio>

class Node {
public:
    uint8_t value;
    size_t position;
    
    Node(uint8_t value, size_t position);
    Node(size_t position);
//    bool operator==(const Node n);
};

#endif /* Node_hpp */
