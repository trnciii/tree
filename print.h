#pragma once

#include <iostream>
#include "kdtree.h"

void printRule(){std::cout <<"----------  ----------  ----------"<<std::endl;}

void print(const glm::vec3& a, const char* s = "\n"){
	printf("%10.6f %10.6f %10.6f%s", a.x, a.y, a.z, s);
}

void print(const Tree::Node n, const char* s = "\n"){
	printf("%6d | %6d |", n.size, n.next);
	print(n.min, " |");
	print(n.max, s);
}

