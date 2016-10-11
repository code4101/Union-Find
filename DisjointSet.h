#include <vector>
#include <cassert>
#include <set>
#include <map>

//并查集类，在参考资料基础上增加了功能
//参考资料：https://github.com/angusb/Union-Find
class DisjointSet {
public:
	DisjointSet();
	DisjointSet(const DisjointSet &d);
	DisjointSet(int num);
	DisjointSet &operator=(const DisjointSet &d);
	~DisjointSet();

	void AddElements(int num);  // REQ: num >= 0
	void Union(int set1, int set2);
	int Find(int element);
	int NumElements() const;
	int NumSets() const;
	
	//获得所有节点的父节点
	void GetFathers(std::vector<int> &fa);

	//返回并查集中每个集合的元素
	//如5个元素的父节点依次是：0 1 2 3 2
	//则返回：
	// (0) (1) (2,4) (3)
	void GetUnion(std::vector<std::vector<int> > &v);

private:
	void copyAll(const DisjointSet &d);

	struct Dnode {
		int index;      // index of the elment the node represents
		int rank;
		Dnode* parent;

		Dnode() {
			parent = NULL;
			index = -1;
			rank = 0;
		}
	};

	int numElts;
	int numSets;
	std::vector<Dnode*> nodes;
};
