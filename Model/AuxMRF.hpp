#ifndef AuxMRF_hpp
#define AuxMRF_hpp

#include "Node.hpp"
#include <unordered_set>
#include <utility>
#include <vector>

class AuxMRF {
private:
    // holds the base nodes of the auxiliary MRF
    std::vector<Node> baseNodes;
    // holds the nodes got by augmenting the the clique in the LAP algorithm
    std::vector<Node> augmentingNodes;
    // stores the positions of added nodes to prevent duplicates
    std::unordered_set<size_t> positions;
    size_t channel = 0;

public:
    bool isOverlappingPixel = false;
    
    // Adds a node to this auxiliary MRF's baseNodes set.
    bool addBaseNode(Node node);
    
    // adds a node to this auxiliary MRF's augmentingNodes set
    bool addAugmentingNode(Node node);

    // get vector of base nodes
    std::vector<Node>& getBaseNodes();

    // get vector of augmentingNodes
    std::vector<Node>& getAugmentingNodes();
    
    bool updateBaseNode(size_t position, uint8_t value);
    
    bool updateAugmentingNode(size_t position, uint8_t value);
    
    bool set_channel(size_t channel);
    
    size_t getChannel() { return this->channel; }
        
//    bool operator==(AuxMRF rval) {
//        return this->baseNodes == rval.getBaseNodes() &&
//        this->augmentingNodes == rval.getAugmentingNodes();
//    }
};

#endif /* AuxMRF_hpp */
