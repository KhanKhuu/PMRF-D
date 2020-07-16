#include "./AuxMRF.hpp"
#include <unordered_set>

// Adds a node to this auxiliary MRF's baseNodes set.
bool AuxMRF::addBaseNode(Node node) {
    
    // add the node if it is not already in the auxiliary MRF
    if (positions.find(node.position) == positions.end()) {
        baseNodes.push_back(node);
        positions.emplace(node.position);
        return true;
    }

    return false;
}
 
// adds a node to this auxiliary MRF's augmentingNodes set
bool AuxMRF::addAugmentingNode(Node node) {
    
    // add the node if it is not already in the auxiliary MRF
    if (positions.find(node.position) == positions.end()) {
        augmentingNodes.push_back(node);
        positions.emplace(node.position);
        return true;
    }
    
    return false;
}


// get vector of base nodes
std::vector<Node>& AuxMRF::getBaseNodes() {
    return baseNodes;
}

// get vector of augmentingNodes
std::vector<Node>& AuxMRF::getAugmentingNodes() {
    return augmentingNodes;
}

bool AuxMRF::set_channel(size_t channel) {
    this->channel = channel;
    return true;
}
