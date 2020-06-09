#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node {
	struct Node* right;
	struct Node* left;
	char* value;
	int length;
} Node;

typedef struct Tree {
	Node* root;
} Tree;


void checkPtr(void* ptr);
void printTree(Tree* tree, Node* begin);
void pushNode(Tree* tree, char* c, int lenght);
void disposeRecursive(Node* cur);
void dispose(Tree* tree);
Tree* newTree();


void checkPtr(void* ptr) {
	if (ptr == NULL) {
		printf("fatal error ocurred");
		exit(-1);
	}
}

Tree* newTree() {
	Tree* output = malloc(sizeof(Tree));
	checkPtr(output);
	output->root = NULL;
	return output;
}

void pushNode(Tree* tree, char* c, int lenght) {
	Node* cur = tree->root;
	Node* prev = NULL;
	int compareResult;
	while (cur != NULL) {
		prev = cur;
		compareResult = strcmp(c, cur->value);
		if (compareResult > 0) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}
	cur = malloc(sizeof(Node));
	checkPtr(cur);
	cur->left = NULL;
	cur->right = NULL;
	cur->value = c;
	cur->length = lenght;
	if (prev != NULL) {
		if (compareResult > 0) {
			prev->right = cur;
		}
		else {
			prev->left = cur;
		}
	}
	else {
		tree->root = cur;
	}
}

void printTree(Tree* tree, Node* begin) {
	if (tree->root == NULL) {
		return;
	}
	if (begin == NULL) {
		begin = tree->root;
	}
	if (begin->left != NULL) {
		printTree(tree, begin->left);
	}
	if (begin->value[0] == begin->value[begin->length - 1]) {
		printf("%s ", begin->value);
	}
	if (begin->right != NULL) {
		printTree(tree, begin->right);
	}
}

void disposeRecursive(Node* cur) {
	if (cur->left != NULL) {
		disposeRecursive(cur->left);
	}
	if (cur->right != NULL) {
		disposeRecursive(cur->right);
	}
	free(cur->value);
	free(cur);
}

void dispose(Tree* tree) {
	if (tree == NULL) {
		return;
	}
	if (tree->root != NULL) {
		disposeRecursive(tree->root);
	}
	free(tree);
}

char buffer[1000000];

int main() {
	FILE* file = fopen("text.txt", "r");
	Tree* tree = newTree();
	checkPtr(file);
	while (fscanf(file, "%s", buffer) > 0) {
		int length = strlen(buffer);
		char* c = calloc(length + 1, sizeof(char));
		checkPtr(c);
		strcpy(c, buffer);
		pushNode(tree, c, length);
	}
	printTree(tree, NULL);
	dispose(tree);
	fclose(file);
	return 0;
}