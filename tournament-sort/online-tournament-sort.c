#include <limits.h>
#include <stdio.h>

#define LEAF_COUNT 4
#define TREE_SIZE ((2 * LEAF_COUNT) - 1)

typedef struct {
	int arr[LEAF_COUNT];
	int count;
} ArrayList;

static void initTree(int values[], int tree[]);
static void updateFromLeaf(int values[], int tree[], int leafIndex);
static int winnerIndex(int tree[]);
void onlineTournamentSort4(ArrayList *list);

int main(void) {
	ArrayList data = {{9, 2, 7, 1}, 4};

	onlineTournamentSort4(&data);

	for (int i = 0; i < data.count; i++) {
		printf("%d ", data.arr[i]);
	}
	printf("\n");

	return 0;
}

void onlineTournamentSort4(ArrayList *list) {
	if (list == NULL || list->count <= 0) {
		return;
	}

	if (list->count > LEAF_COUNT) {
		list->count = LEAF_COUNT;
	}

	int input[LEAF_COUNT];
	int values[LEAF_COUNT];
	int tree[TREE_SIZE];

	for (int i = 0; i < LEAF_COUNT; i++) {
		input[i] = (i < list->count) ? list->arr[i] : INT_MAX;
		values[i] = INT_MAX;
	}

	initTree(values, tree);

	// Online phase: insert one element at a time and repair only its path.
	for (int i = 0; i < list->count; i++) {
		values[i] = input[i];
		updateFromLeaf(values, tree, i);
	}

	// Extraction phase: repeatedly remove current winner.
	for (int out = 0; out < list->count; out++) {
		int wIdx = winnerIndex(tree);
		list->arr[out] = values[wIdx];
		values[wIdx] = INT_MAX;
		updateFromLeaf(values, tree, wIdx);
	}
}

static void initTree(int values[], int tree[]) {
	int leafStart = LEAF_COUNT - 1;

	for (int i = 0; i < LEAF_COUNT; i++) {
		tree[leafStart + i] = i;
	}

	for (int i = leafStart - 1; i >= 0; i--) {
		int left = tree[(2 * i) + 1];
		int right = tree[(2 * i) + 2];
		tree[i] = (values[left] <= values[right]) ? left : right;
	}
}

static void updateFromLeaf(int values[], int tree[], int leafIndex) {
	int node = (LEAF_COUNT - 1) + leafIndex;
	tree[node] = leafIndex;

	while (node > 0) {
		int parent = (node - 1) / 2;
		int left = tree[(2 * parent) + 1];
		int right = tree[(2 * parent) + 2];
		tree[parent] = (values[left] <= values[right]) ? left : right;
		node = parent;
	}
}

static int winnerIndex(int tree[]) {
	return tree[0];
}
