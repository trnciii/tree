#pragma

#include <iostream>
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include "print.h"

struct Tree{

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

	std::vector<glm::vec3> verts;
	std::vector<Node> nodes;

	void build(){addNode(verts.begin(), verts.end());}

	std::vector<glm::vec3> traverse(glm::vec3 p, float r){
		std::vector<glm::vec3> result;
		
		for(glm::vec3 v : verts){
			if(glm::length(p-v) < r) result.push_back(v);
		}

		return result;
	}

	void split(const std::vector<glm::vec3>::iterator begin,
		const std::vector<glm::vec3>::iterator end,
		const int axis)
	{
		std::sort(begin, end, [axis](glm::vec3 a, glm::vec3 b){return a[axis] < b[axis];});	
		std::vector<glm::vec3>::iterator mid =  begin+(end-begin)/2; // split by count

		// print
		std::cout <<"begin " <<&(*begin) <<", mid " <<&(*mid) <<", end " <<&(*end);
		std::cout <<", " <<axis <<std::endl;
		for(auto it=begin; it<end; it++) print(*it);
		std::cout <<std::endl;


		if(1 < mid-begin)addNode(begin, mid);
		if(1 < end-mid)addNode(mid, end);
	};

	void addNode(const std::vector<glm::vec3>::iterator begin,
		const std::vector<glm::vec3>::iterator end){
		Node node(begin, end);
		nodes.push_back(node);
		split(begin, end, node.axis());
	}

};