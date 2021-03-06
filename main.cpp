#include <iostream>
#include "kdtree.h"
#include <glm/glm.hpp>
#include "Random.h"
#include "print.h"
#include <chrono>

int main(void){
	RNG rng;
	std::vector<glm::vec3> verts;
	Tree tree;

	std::cout <<"source" <<std::endl;
	for(int i=0; i<1000; i++){
		glm::vec3 v(rng.uniform(), rng.uniform(), rng.uniform());
		verts.push_back(v);
	}
	
	std::cout <<"building a tree" <<std::endl;
	tree.copyElements(verts.data(), verts.size());
	tree.build();
	printRule();

	std::cout <<"nodes" <<std::endl;
	{
		// auto nodes = tree.getNodes();
		// for(auto& n : nodes) print(n);
		// printRule();
	}

	glm::vec3 p(0.58, 0.74, 0.26);
	float r = 0.1;

	auto t0 = std::chrono::high_resolution_clock::now();

	std::cout <<"traversing tree" <<std::endl;
	std::vector<Tree::Result> result_tree = tree.searchNN(p, r);
	std::cout <<result_tree.size() <<" | ";

	auto t1 = std::chrono::high_resolution_clock::now();
	std::cout <<std::chrono::duration<double, std::nano>(t1-t0).count() <<" ns" <<std::endl;
	printRule();

	std::cout <<"sort results" <<std::endl;
	std::sort(result_tree.begin(), result_tree.end(), Tree::Result::compareDistance);
	for(auto result : result_tree) print(result);
	printRule();	


	// std::cout <<"traversing all" <<std::endl;
	// std::vector<Tree::Result> result_all = tree.searchNN_checkAll(p, r);
	// std::cout <<result_all.size() <<" | ";

	// auto t2 = std::chrono::high_resolution_clock::now();
	// std::cout <<std::chrono::duration<double, std::nano>(t2-t0).count() <<" ns" <<std::endl;
	// printRule();	

	return 0;
}