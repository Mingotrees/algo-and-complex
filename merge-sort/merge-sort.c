#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

static Node *createListFromArray(const int arr[], int n);
static Node *copyList(const Node *head);
static void freeList(Node *head);
static void printList(const Node *head);

static Node *sortedMerge(Node *a, Node *b);
static void frontBackSplit(Node *source, Node **frontRef, Node **backRef);
Node *mergeSortTopDown(Node *head);

static int listLength(const Node *head);
static Node *splitRun(Node *head, int size);
static Node *mergeRuns(Node *left, Node *right, Node **tailOut);
Node *mergeSortBottomUp(Node *head);

int main(void) {
	int values[] = {38, 27, 43, 3, 9, 82, 10, 1};
	int n = (int)(sizeof(values) / sizeof(values[0]));

	Node *base = createListFromArray(values, n);
	Node *topDown = copyList(base);
	Node *bottomUp = copyList(base);

	topDown = mergeSortTopDown(topDown);
	bottomUp = mergeSortBottomUp(bottomUp);

	printf("Top-down recursive: ");
	printList(topDown);

	printf("Bottom-up iterative: ");
	printList(bottomUp);

	freeList(base);
	freeList(topDown);
	freeList(bottomUp);

	return 0;
}

Node *mergeSortTopDown(Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}

	Node *a;
	Node *b;

	frontBackSplit(head, &a, &b);
	a = mergeSortTopDown(a);
	b = mergeSortTopDown(b);

	return sortedMerge(a, b);
}

Node *mergeSortBottomUp(Node *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}

	int n = listLength(head);
	Node dummy;
	dummy.next = head;

	for (int width = 1; width < n; width *= 2) {
		Node *curr = dummy.next;
		Node *tail = &dummy;

		while (curr != NULL) {
			Node *left = curr;
			Node *right = splitRun(left, width);
			curr = splitRun(right, width);

			Node *mergedTail = NULL;
			Node *mergedHead = mergeRuns(left, right, &mergedTail);

			tail->next = mergedHead;
			tail = mergedTail;
		}
	}

	return dummy.next;
}

static Node *sortedMerge(Node *a, Node *b) {
	Node dummy;
	Node *tail = &dummy;
	dummy.next = NULL;

	while (a != NULL && b != NULL) {
		if (a->data <= b->data) {
			tail->next = a;
			a = a->next;
		} else {
			tail->next = b;
			b = b->next;
		}
		tail = tail->next;
	}

	tail->next = (a != NULL) ? a : b;
	return dummy.next;
}

static void frontBackSplit(Node *source, Node **frontRef, Node **backRef) {
	Node *slow = source;
	Node *fast = source->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

static int listLength(const Node *head) {
	int len = 0;
	while (head != NULL) {
		len++;
		head = head->next;
	}
	return len;
}

static Node *splitRun(Node *head, int size) {
	if (head == NULL) {
		return NULL;
	}

	for (int i = 1; head->next != NULL && i < size; i++) {
		head = head->next;
	}

	Node *second = head->next;
	head->next = NULL;
	return second;
}

static Node *mergeRuns(Node *left, Node *right, Node **tailOut) {
	Node dummy;
	Node *tail = &dummy;
	dummy.next = NULL;

	while (left != NULL && right != NULL) {
		if (left->data <= right->data) {
			tail->next = left;
			left = left->next;
		} else {
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}

	tail->next = (left != NULL) ? left : right;

	while (tail->next != NULL) {
		tail = tail->next;
	}

	*tailOut = tail;
	return dummy.next;
}

static Node *createListFromArray(const int arr[], int n) {
	Node *head = NULL;
	Node *tail = NULL;

	for (int i = 0; i < n; i++) {
		Node *newNode = (Node *)malloc(sizeof(Node));
		if (newNode == NULL) {
			freeList(head);
			return NULL;
		}

		newNode->data = arr[i];
		newNode->next = NULL;

		if (head == NULL) {
			head = newNode;
			tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	return head;
}

static Node *copyList(const Node *head) {
	Node *copyHead = NULL;
	Node *copyTail = NULL;

	while (head != NULL) {
		Node *newNode = (Node *)malloc(sizeof(Node));
		if (newNode == NULL) {
			freeList(copyHead);
			return NULL;
		}

		newNode->data = head->data;
		newNode->next = NULL;

		if (copyHead == NULL) {
			copyHead = newNode;
			copyTail = newNode;
		} else {
			copyTail->next = newNode;
			copyTail = newNode;
		}

		head = head->next;
	}

	return copyHead;
}

static void freeList(Node *head) {
	while (head != NULL) {
		Node *next = head->next;
		free(head);
		head = next;
	}
}

static void printList(const Node *head) {
	while (head != NULL) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
