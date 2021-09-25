#include <array>
#include <iostream>

template <int N>
constexpr std::array<std::array<int, N-1>, N-1> calc_matrix(const std::array<std::array<int, N>, N>& a, const int row, const int col) {
	std::array<std::array<int, N-1>, N-1> new_a{};
	int t=0;
	int k=0;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (i < row && j < col) {
				t = i;
				k = j;
			} else if (i >= row && j < col) {
				t = i + 1;
				k = j;
			} else if (i < row && j >= col) {
				t = i;
				k = j + 1;
			} else if (i >= row && j >= col) {
				t = i + 1;
				k = j + 1;
			}
			(&std::get<0>((&std::get<0>(new_a))[i]))[j] = a[t][k];
		}
	}
	return new_a;
}

template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
	int result = 0;
	int sign = 1;
	for (auto i = 0; i < N; i++) {
		result += N < 2 ? a[0][0] : sign * a[0][i] * det<N-1>(calc_matrix<N>(a, 0, i));
		sign *= -1;
	}		
	return result;
}

template <>
constexpr int det<1>(const std::array<std::array<int, 1>, 1>& a) {
	return a[0][0];
}

int main() {
	constexpr std::array<std::array<int, 3>, 3> A = {{
		{0, 1, 2}
		,{1, 2, 3}
		,{2, 3, 7}
	}};
  	constexpr int res = det<3>(A);
  	static_assert(res == -2, "wwwwwwww");
}