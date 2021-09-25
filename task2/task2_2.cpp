#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <utility>
#include <tuple>

struct Printer {
	std::string str() {
		std::string result;
		std::getline(buffer, result);
		return result;
	}

	Printer& format(std::string str) { 
		this->buffer << str;
		return  *this;
	}

	Printer& format(int value) {
		this->buffer << std::to_string(value);
		return  *this;
	}

	template<typename T>
	Printer& format(std::vector<T>& vec) {
		this->write(" [ ", " ] ", vec);
		return  *this;
	}

	template<typename T>
	Printer& format(std::set<T>& set_of_elems) {
		this->write(" [ ", " ] ", set_of_elems);
		return  *this;
	}

	template<typename... T>
	Printer& format(std::tuple<T... >& tup) {
		this->buffer << "( ";
		std::apply([&](auto& ...x){(..., this->write_tuple(x));}, tup);
		this->buffer.seekp(-2, std::ios_base::end);
		this->buffer << " )";
		return  *this;
	}

	template<typename T>
	Printer& format(std::pair<T, T>& pair_of_elems) {
		this->buffer << "( ";
		this->buffer << Printer().format(pair_of_elems.first).str();
		this->buffer << ", ";
		this->buffer << Printer().format(pair_of_elems.second).str();
		this->buffer << " )";
		return  *this;
	}
	
private:
	template<typename T>
	void write_tuple(T x) {
		this->buffer << Printer().format(x).str();
		this->buffer << ", ";		
	}
	template<typename T>
	void write(const std::string first, const std::string second, T& obj) {
		this->buffer << first;
		for (auto& elem : obj) {
			this->buffer << Printer().format(elem).str();
			this->buffer << ", ";
		}
		this->buffer.seekp(-2, std::ios_base::end);
		this->buffer << second;
	}
	std::stringstream buffer;
};

template<typename T>

std::string format(const T& t) {
	return Printer().format(t).str();
}

int main() {
	std::tuple<std::string, int, int> t = {"xyz", 1, 2};
	std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
	std::string s1 = Printer().format(" vector: ").format(v).str();
	std::cout << s1 << std::endl;
	// " vector: [ (1, 4), (5, 6) ]"
	std::string s2 = Printer().format(t).format(" ! ").format(0).str();
	std::cout << s2 << std::endl;
	// "( xyz, 1, 2 ) ! 0"
}