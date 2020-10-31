#pragma

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include "print.h"

struct Node{
	glm::vec3 min;
	glm::vec3 max;

	uint32_t size;

	Node(const std::vector<glm::vec3>::iterator begin,
		const std::vector<glm::vec3>::iterator end)
	:min(*begin), max(*begin), size(end-begin)
	{
		for(auto it=begin+1; it<end; it++){
			min = glm::min(min, *it);
			max = glm::max(max, *it);
		}
	}

	int axis(){
		glm::vec3 dim = max - min;
		return (dim.y<dim.x && dim.z<dim.x)? 0 : ((dim.z<dim.y)? 1 : 2);
	}
};