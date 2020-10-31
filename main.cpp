#include <iomanip>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "kdtree.h"
#include "Random.h"
#include "print.h"

void split(std::vector<Node>& nodes, const std::vector<glm::vec3>::iterator begin, const std::vector<glm::vec3>::iterator end, const int axis){
	std::sort(begin, end, [axis](glm::vec3 a, glm::vec3 b){return a[axis] < b[axis];});
	
	std::vector<glm::vec3>::iterator mid =  begin+(end-begin)/2; // split by count

	// print
	std::cout <<"begin " <<&(*begin) <<", mid " <<&(*mid) <<", end " <<&(*end);
	std::cout <<", " <<axis <<std::endl;
	for(auto it=begin; it<end; it++) print(*it);
	std::cout <<std::endl;


	if(1 < mid-begin){
		Node right(begin,mid);
		
		nodes.push_back(right);
		split(nodes, begin, mid, right.axis());
	}

	if(1 < end-mid){
		Node left(mid, end);

		nodes.push_back(left);
		split(nodes, mid, end, left.axis());
	}

	return;
}

int main(void){
	RNG rng;
	std::vector<glm::vec3> verts;
	std::vector<Node> nodes;

	for(int i=0; i<8; i++){
		glm::vec3 v(rng.uniform(), rng.uniform(), rng.uniform());
		verts.push_back(v);
		print(v);
	}
	printRule();
	
	Node root(verts.begin(), verts.end());
	nodes.push_back(root);
	split(nodes, verts.begin(), verts.end(), root.axis());
	printRule();

	for(auto& n : nodes){
		std::cout <<n.size;
		print(n.min, " | ");
		print(n.max);
	}
	printRule();

	for(auto& v : verts) print(v);
	printRule();

	return 0;
}