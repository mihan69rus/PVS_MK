#include <vector>

int main() {
	std::vector<bool> v; 
	for (auto&& x: v) {
	}
	return 0;
}

// Из-за оптимизации std::vector<bool> реализован не совсем так
// как обычный std::vector. Неконстантная ссылка auto& может быть связана только
// с lvalue объектом, а std::vector<bool> будет давать rvalue. Поэтому в случае
// auto& не будет компилироваться.