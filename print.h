#pragma once

void printRule(){std::cout <<"----------  ----------  ----------"<<std::endl;}

void print(const glm::vec3& a, const char* s = "\n"){
	printf("%10.6f %10.6f %10.6f%s", a.x, a.y, a.z, s);
}