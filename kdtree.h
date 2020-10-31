#pragma

#include <vector>
#include <glm/glm.hpp>

struct Node{
	glm::vec3 min;
	glm::vec3 max;

	Node* child_R;
	Node* child_L;

	Node(std::vector<glm::vec3>::iterator begin, std::vector<glm::vec3>::iterator end){
		min = glm::vec3( 1e6, 1e6, 1e6);
		max = glm::vec3(-1e6,-1e6,-1e6);

		child_R = nullptr;
		child_L = nullptr;

		for(; begin<end; begin++){
			min = glm::min(min, *begin);
			max = glm::max(max, *begin);
		}
	}
};