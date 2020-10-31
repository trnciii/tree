#pragma

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include "print.h"

struct Tree{

	struct Node{
		glm::vec3 min;
		glm::vec3 max;

		std::vector<glm::vec3>::iterator begin;
		uint32_t size;
		uint32_t next;

		Node(const std::vector<glm::vec3>::iterator b,
			const std::vector<glm::vec3>::iterator e)
		:min(b[0]), max(b[0]), size(e-b), next(0), begin(b)
		{
			for(int i=1; i<size; i++){
				min = glm::min(min, begin[i]);
				max = glm::max(max, begin[i]);
			}
		}

		int axis(){
			glm::vec3 dim = max - min;
			return (dim.y<dim.x && dim.z<dim.x)? 0 : ((dim.z<dim.y)? 1 : 2);
		}

		bool intersect(glm::vec3 p, float r){
			return (min.x - r < p.x && p.x < max.x + r
				&& min.y - r < p.y && p.y < max.y + r
				&& min.z - r < p.z && p.z < max.z + r);
		}
	};

	std::vector<glm::vec3> verts;
	std::vector<Node> nodes;

	void build(){addNode(verts.begin(), verts.end());}

	std::vector<glm::vec3> searchNN(glm::vec3 p, float r){
		std::vector<glm::vec3> result;

		auto node = nodes.begin();
		while(node < nodes.end()){
			if(node->intersect(p, r)){
				if(node->size < 5)
					for(int i=0; i<node->size; i++)
						if(glm::length(node->begin[i] - p) < r)
							result.push_back(node->begin[i]);

				node++;
			}
			else node += node->next;
		}

		return result;
	}

	std::vector<glm::vec3> searchNN_all(glm::vec3 p, float r){
		std::vector<glm::vec3> result;
		
		for(auto v : verts)
			if(glm::length(v-p) < r)
				result.push_back(v);

		return result;
	}


	void split(const std::vector<glm::vec3>::iterator begin,
		const std::vector<glm::vec3>::iterator end,
		const int axis)
	{
		std::sort(begin, end, [axis](glm::vec3 a, glm::vec3 b){return a[axis] < b[axis];});	
		std::vector<glm::vec3>::iterator mid =  begin+(end-begin)/2; // split by count

		uint32_t p0 = nodes.size();
		if(2 < mid-begin)addNode(begin, mid);
		
		uint32_t p1 = nodes.size();
		if(2 < end-mid)addNode(mid, end);

		uint32_t p2 = nodes.size();
	
		nodes[p0].next = p1 - p0;
		nodes[p1].next = p2 - p1;
	};

	void addNode(const std::vector<glm::vec3>::iterator begin,
		const std::vector<glm::vec3>::iterator end){
		Node node(begin, end);
		nodes.push_back(node);
		split(begin, end, node.axis());
	}

};