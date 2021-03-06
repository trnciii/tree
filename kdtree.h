#pragma once

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>

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

	struct Result{
		float distance;
		glm::vec3 position;

		Result(float d, glm::vec3 p):distance(d), position(p){}

		static bool compareDistance(const Result& a, const Result& b){return a.distance < b.distance;}
	};


private:

	std::vector<glm::vec3> verts;
	std::vector<Node> nodes;
	const uint32_t nElements = 1000;

	void split(const std::vector<glm::vec3>::iterator verts_begin,
		const std::vector<glm::vec3>::iterator verts_end,
		const int axis)
	{
		std::sort(verts_begin, verts_end, [axis](glm::vec3 a, glm::vec3 b){return a[axis] < b[axis];});	
		std::vector<glm::vec3>::iterator verts_mid =  verts_begin+(verts_end-verts_begin)/2; // split by count

		uint32_t p0 = nodes.size();
		{
			Node node(verts_begin, verts_mid);
			nodes.push_back(node);
			if(nElements < node.size)split(verts_begin, verts_mid, node.axis());
		}
		
		uint32_t p1 = nodes.size();
		{
			Node node(verts_mid, verts_end);
			nodes.push_back(node);
			if(nElements < node.size)split(verts_mid, verts_end, node.axis());
		}

		uint32_t p2 = nodes.size();
	
		nodes[p0].next = p1 - p0;
		nodes[p1].next = p2 - p1;
	};


public:

	bool build(){
		nodes.clear();

		if(verts.size() < 1) return false;
		
		Node node(verts.begin(), verts.end());
		nodes.push_back(node);
		if(nElements < node.size)split(verts.begin(), verts.end(), node.axis());
		nodes[0].next = nodes.size();
		return true;
	}

	std::vector<Result> searchNN(glm::vec3 p, float r){
		if(!hasTree()) return searchNN_checkAll(p,r);

		std::vector<Result> result;

		auto node = nodes.begin();
		while(node < nodes.end()){
			if(node->intersect(p, r)){
				if(node->size <= nElements)
					for(int i=0; i<node->size; i++){
						float distance = glm::length(node->begin[i] - p);
						if(distance < r)
							result.push_back(Result(distance, node->begin[i]));
					}

				node++;
			}
			else node += node->next;
		}

		return result;
	}

	std::vector<Result> searchNN_checkAll(glm::vec3 p, float r){
		std::vector<Result> result;
		
		for(auto v : verts){
			float distance = glm::length(v-p);
			if(distance < r)
				result.push_back(Result(distance, v));
		}

		return result;
	}

	void copyElements(glm::vec3* const elements, uint32_t size){
		std::vector<glm::vec3> v(elements, elements+size);
		verts.swap(v);
		nodes.clear();
	}

	void addElements(glm::vec3* const elements, uint32_t size){
		std::vector<glm::vec3> v(elements, elements+size);
		verts.reserve(verts.size()+size);
		std::copy(v.begin(), v.end(), back_inserter(verts));
		nodes.clear();
	}

	bool hasTree(){return 0 < nodes.size();}

	std::vector<Node> getNodes(){return nodes;}

	std::vector<glm::vec3> getElements(){return verts;}

};