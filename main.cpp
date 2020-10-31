#include <iostream>
#include <glm/glm.hpp>
#include "kdtree.h"
#include "Random.h"
#include "print.h"

int main(void){
	RNG rng;
	Tree tree;

	for(int i=0; i<8; i++){
		glm::vec3 v(rng.uniform(), rng.uniform(), rng.uniform());
		tree.verts.push_back(v);
		print(v);
	}
	printRule();
	
	tree.build();
	printRule();

	for(auto& n : tree.nodes){
		std::cout <<n.size;
		print(n.min, " | ");
		print(n.max);
	}
	printRule();

	for(auto& v : tree.verts) print(v);
	printRule();

	return 0;
}