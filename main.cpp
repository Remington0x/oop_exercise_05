#include <algorithm>
#include "stack.hpp"
#include "triangle.hpp"

int main() {
	size_t n;
	auto Print = [](const TStackNode< TTriangle<int> > & sq) {
		std::cout << sq << std::endl;
	};
	std::cout << "Input number of triangles in stack" << std::endl;
	std::cin >> n;
	int cordX, cordY, side;
	TStack< TTriangle<int> > st;
	for (size_t i = 0; i < n; ++i) {
		size_t n;
		std::cout << "Input index to insert a triangle" << std::endl;
		std::cin >> n;
		std::cout << "Input triangle as follows: x y a" << std::endl;
		std::cout << "x, y is a left bottom corner cords" << std::endl;
		std::cout << "a is triangle side" << std::endl;
		std::cin >> cordX >> cordY >> side;
		try {
			TStack< TTriangle<int> >::iterator it = st.begin();
			while (n--) {
				++it;
			}
			st.Insert(it, TTriangle<int>(std::pair<int, int>(cordX, cordY), side));
		} catch (std::runtime_error & exception) {
			std::cout << exception.what() << std::endl;
		}
	}
	std::cout << "Your input:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	std::cout << "Input index to erase from stack" << std::endl;
	std::cin >> n;
	try {
		TStack< TTriangle<int> >::iterator it = st.begin();
		while (n > 1) {
			++it;
			--n;
		}
		st.Erase(it);
	} catch (std::runtime_error & exception) {
		std::cout << exception.what() << std::endl;
	}
	std::cout << "After erase:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	int minimalSquare;
	std::cout << "Input minimal square" << std::endl;
	std::cin >> minimalSquare;
	auto MatchSqaure = [minimalSquare](const TStackNode< TTriangle<int> > & sq) {
		return !(CalcSquare(sq.Data) < minimalSquare);
	};
	std::cout << "Number of figures with square greater or equal, than " << minimalSquare << ": ";
	std::cout << std::count_if(st.begin(), st.end(), MatchSqaure) << std::endl;
	return 0;
}
