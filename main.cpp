#include <iomanip>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "kdtree.h"
#include "Random.h"

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

	return 0;
}