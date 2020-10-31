#include <iomanip>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "kdtree.h"
#include "Random.h"

void printRule(){std::cout <<"----------  ----------  ----------"<<std::endl;}

void print(const glm::vec3& a, const char* s = "\n"){
	printf("%10.6f %10.6f %10.6f%s", a.x, a.y, a.z, s);
}

int main(void){
	RNG rand_local;
	int size = 20;
	std::vector<glm::vec3> verts;

	for(int i=0; i<size; i++){
		glm::vec3 v(rand_local.uniform(), rand_local.uniform(), rand_local.uniform());
		verts.push_back(v);
		print(v);
	}

	printRule();
	Node root(verts.begin(), verts.end());
	print(root.min); // 0.013513   0.118296   0.034841
	print(root.max); // 0.851034   0.995759   0.944129

	return 0;
}