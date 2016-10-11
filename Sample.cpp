#include <iostream>
#include "DisjointSet.h"

using namespace std;

void printElementSets(DisjointSet & s) {
	for (int i = 0; i < s.NumElements(); ++i)
		cout << s.Find(i) << "  ";
	cout << endl;
}

void out(const std::vector<std::vector<int> > &v) {
	printf("\n分组：\n");
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			printf("%d ", v[i][j]);
		}
		putchar('\n');
	}
}

int main() {
	DisjointSet s(10);
	//0  1  2  3  4  5  6  7  8  9
	s.Union(5, 3); //s.Union(s.Find(5),s.Find(3));
	//0  1  2  5  4  5  6  7  8  9
	s.Union(s.Find(1), s.Find(3));
	//0  5  2  5  4  5  6  7  8  9
	s.Union(s.Find(6), s.Find(7));
	//0  5  2  5  4  5  6  6  8  9
	s.Union(s.Find(8), s.Find(9));
	//0  5  2  5  4  5  6  6  8  8
	s.Union(s.Find(6),s.Find(9));
	//0  5  2  5  4  5  6  6  6  6
	s.AddElements(3);
	//0  5  2  5  4  5  6  6  6  6  10  11  12
	s.Union(s.Find(11), s.Find(12));
	//0  5  2  5  4  5  6  6  6  6  10  11  11
	s.Union(s.Find(9), s.Find(10));
	//0  5  2  5  4  5  6  6  6  6  6  11  11
	s.Union(s.Find(7), s.Find(11));
	//0  5  2  5  4  5  6  6  6  6  6  6  6

	printf("%d\n", s.NumSets());
	printElementSets(s);
	
	std::vector<std::vector<int> > v;
	s.GetUnion(v);
	out(v);
	/*
	0
	2
	4
	1 3 5
	6 7 8 9 10 11 12
	*/
	
	return 0;
}
