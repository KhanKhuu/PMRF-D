#include "Node.hpp"

Node::Node(uint8_t value, size_t position) {
    this->value = value;
    this->position = position;
}

// used for comparisons where only position is needed
Node::Node(size_t position) {
    this->position = position;
    this->value = 0;
}

//bool Node::operator==(Node rval) {
//    return this->position == rval.position &&
//    this->value == rval.value;
//}
