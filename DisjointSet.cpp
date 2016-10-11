#include "DisjointSet.h"

DisjointSet::DisjointSet()
	:numElts(0), numSets(0) {}

DisjointSet::DisjointSet(const DisjointSet &d) {
	copyAll(d);
}

DisjointSet::DisjointSet(int num) {
	numElts = 0;
	numSets = 0;
	AddElements(num);
}

DisjointSet& DisjointSet::operator=(const DisjointSet &d) {
	if (this != &d)
		copyAll(d);

	return *this;
}

void DisjointSet::AddElements(int num) {
	assert(num >= 0);

	nodes.insert(nodes.end(), num, (Dnode*)(NULL));
	for (int i = numElts; i < numElts + num; i++) {
		nodes[i] = new Dnode();
		nodes[i]->index = i;
	}
	numElts += num;
	numSets += num;
}

int DisjointSet::Find(int elt) {
	assert(elt < numElts);

	Dnode* root = nodes[elt];

	while (root->parent != NULL)
		root = root->parent;

	Dnode* setIter = nodes[elt];
	while (setIter != root) {
		Dnode* parent = setIter->parent;
		setIter->parent = root;
		setIter = parent;
	}

	return root->index;
}

void DisjointSet::Union(int set1, int set2) {
	assert(set1 < numElts && set2 < numElts);

	Dnode* set1_rep = nodes[Find(set1)];
	Dnode* set2_rep = nodes[Find(set2)];

	if (set1_rep == set2_rep)
		return;

	if (set1_rep->rank < set2_rep->rank)
		set1_rep->parent = set2_rep;
	else if (set1_rep->rank > set2_rep->rank)
		set2_rep->parent = set1_rep;
	else {
		set2_rep->parent = set1_rep; // arbitrary, set1_rep->parent = set2->rep
		set1_rep->rank += 1;
	}

	--numSets;
}

int DisjointSet::NumElements() const {
	return numElts;
}

int DisjointSet::NumSets() const {
	return numSets;
}

void DisjointSet::GetFathers(std::vector<int> &fa) {
	fa.resize(numElts);
	for (int i = 0; i < numElts; ++i)
		fa[i] = Find(i);
}

void DisjointSet::GetUnion(std::vector<std::vector<int> > &v) {
	//获得父节点向量
	std::vector<int> fa;
	GetFathers(fa);

	//map[i]：对父节点i重新编号为值map[i]
	std::set<int> ss;
	for (int i = 0; i < numElts; ++i) ss.insert(fa[i]);
	int k = 0;
	std::map<int, int> m;
	for (std::set<int>::iterator it = ss.begin(); it != ss.end(); ++it, ++k)
		m[*it] = k;

	//获得v
	v.resize(numSets);
	for (int i = 0; i < numElts; ++i) {
		v[m[fa[i]]].push_back(i);
	}
}

DisjointSet::~DisjointSet() {
	for (int i = 0; i < numElts; i++)
		delete nodes[i];

	nodes.clear();
}

void DisjointSet::copyAll(const DisjointSet &d) {
	this->numElts = d.numElts;
	this->numSets = d.numSets;

	nodes.resize(numElts);
	for (int i = 0; i < numElts; i++)
		nodes[i] = new Dnode(*d.nodes[i]);

	for (int i = 0; i < numElts; i++)
		if (d.nodes[i]->parent != NULL)
			nodes[i]->parent = nodes[d.nodes[i]->parent->index];
}
