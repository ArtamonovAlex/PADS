#include "edx-io.hpp"
#include <string>
using namespace std;

struct node {
	long key, left, right;
};

long find_first_parent_for_left(node* tree, long i, long* parents) {
	while (tree[parents[i]].left != i && parents[i] != 0) {
		i = parents[i];
	}
	return parents[i];
}

long find_first_parent_for_right(node* tree, long i, long* parents) {
	while (tree[parents[i]].right != i && parents[i] != 0) {
		i = parents[i];
	}
	return parents[i];
}

bool check(node* tree, long pos, long pfr, long pfl) {
	if (tree[pos].left) {
		if (tree[tree[pos].left].key >= tree[pos].key) {
			return false;
		}
		else {
			if (pfr) {
				if (tree[pfr].key > tree[tree[pos].left].key) {
					return false;
				}
			}
		}
	}
	if (tree[pos].right) {
		if (tree[tree[pos].right].key <= tree[pos].key)
		{
			return false;
		}
		else {
			if (pfl) {
				if (tree[pfl].key < tree[tree[pos].right].key) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {


	long N;
	io >> N;

	node* tree = new node[N + 1];
	long* parents = new long[N + 1];
	parents[1] = 0;
	for (long i = 1; i < N + 1; i++)
	{
		io >> tree[i].key >> tree[i].left >> tree[i].right;
		if (tree[i].left) {
			parents[tree[i].left] = i;
		}
		if (tree[i].right) {
			parents[tree[i].right] = i;
		}
	}
	string answer = "YES";
	if (N < 2) {
		io << answer;
		return 0;
	}
	else {
		long parent_for_left, parent_for_right;
		for (long i = 1; i < N + 1; i++) {
			parent_for_left = find_first_parent_for_left(tree, i, parents);
			parent_for_right = find_first_parent_for_right(tree, i, parents);
			if (!check(tree, i, parent_for_right, parent_for_left)) {
				io << "NO";
				return 0;
			}
		}
	}

	io << answer;

	return 0;
}