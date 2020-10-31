#include <iostream>
#include <glm/glm.hpp>
#include "kdtree.h"
#include "Random.h"
#include "print.h"

int main(void){
	RNG rng;
	Tree tree;

	std::cout <<"source" <<std::endl;
	for(int i=0; i<8; i++){
		glm::vec3 v(rng.uniform(), rng.uniform(), rng.uniform());
		tree.verts.push_back(v);
		print(v);
	}
	printRule();
	
	std::cout <<"building the tree" <<std::endl;
	tree.build();
	printRule();

	std::cout <<"nodes" <<std::endl;
	for(auto& n : tree.nodes){
		std::cout <<n.size;
		print(n.min, " | ");
		print(n.max);
	}
	printRule();

	std::cout <<"verts" <<std::endl;
	for(auto& v : tree.verts) print(v);
	printRule();

	std::cout <<"traversing" <<std::endl;
	std::vector<glm::vec3> result = tree.traverse(glm::vec3(0.58, 0.74, 0.26), 0.5);
	for(glm::vec3 v : result) print(v);
	printRule();

	return 0;
}