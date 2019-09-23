#ifndef LAP_HPP
#define LAP_HPP

void get_first_neighborhood (const std::vector<uint8_t> *data, 
			     std::vector<std::pair<uint8_t, int>> *clique,
			     const int WIDTH,
			     const int HEIGHT,
			     const int index);

void LAP (std::vector<std::vector<std::pair<uint8_t, int>>> *cliques, 
		      const std::vector<uint8_t> *data, 
		      const int WIDTH, 
		      const int HEIGHT); 

#endif //LAP_HPP
