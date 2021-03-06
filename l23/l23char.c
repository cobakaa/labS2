#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

struct tree {
	char fatherVal; // для построения дерева по значению отца
	char val;
	struct tree *son;
	struct tree *brother;
};

bool clean_screen() {
	return printf("\033[2J") && printf("\033[0;0f");
}

struct tree *root;
struct tree *mktree(struct tree *root1, struct tree *subTree, char val, char fatherVal);
void printTree(struct tree *root, int lvl);
bool isExists(const struct tree *root, char fatherVal);
void deleteTree(struct tree * *root, char val, int id);
bool isEmpty(const struct tree *root);
int max_depth(const struct tree *root, int lvl);


int main() {

	root = NULL;

	char val, fatherVal;
	int used_leaf_count = 0, min_depth = INT_MAX;
	char answer = 'y';
	char ch = '\0', c;
	char ans[256];
	clean_screen();

	while (true) {
        printf("\nMenu: \n\t1) Add root/leaf.\n\t2) Print tree.\n\t3) Remove tree node.\n\t4) Max depth.\n\t5) Exit.\n\nYour choice: ");
        if ((ch = getchar()) == EOF) break;
		// char c;
        int cnt = 0;
        while ((c = getchar()) != EOF && c != '\n') cnt++;
        if (cnt != 0) continue;

		switch (ch) {
		case '1': {
			do {
				if (!root) {
                    int cnt;
                    do {
                        printf("Enter value of root: ");
                        scanf("%c", &val);
                        cnt = 0;
                        while ((c = getchar()) != EOF && c != '\n') cnt++;
                    } while (cnt != 0);
                    // while ((c = getchar()) != EOF && c != '\n');
					fatherVal = val;

				} else {
                    int cnt;
                    do {
                        printf("Enter father and value of leaf: ");
                        cnt = 0;
                        scanf("%c", &fatherVal);
                        while ((c = getchar()) != EOF && c != ' ' && c != '\n') cnt++;
                        scanf("%c", &val);
                        while ((c = getchar()) != EOF && c != '\n') cnt++;
                    } while(cnt != 0);
                    // while ((c = getchar()) != EOF && c != '\n');
				}

				if (root && !isExists(root, fatherVal)) {
					printf("No such father.\n");
				} else {
					if (!root || !isExists(root, val)) {
						root = mktree(root, root, val, fatherVal);
						printf("Item (%c) has been added.\n", val);
					} else {
						printf("Item with this value already exists.\n");
					}
				}
                int cnt = 0;
				do {
                    printf("Do you want to add another leaf? (y/n) : ");
                    cnt = 0;
                    scanf("%c", &answer);
                    while ((c = getchar()) != EOF && c != '\n') cnt++;
                } while (!(cnt == 0 && (tolower(answer) == 'n' || tolower(answer) == 'y')));
			} while (answer != 'n');
			break;
		}
		case '2': {
			if (isEmpty(root)) printf("Tree is empty...\n");
			else {
				printf("\n__________TREE__________\n\n");
				printTree(root, 1);
				printf("\n__________TREE__________\n\n");
			}
			break;
		}
		case '3': {
            if (isEmpty(root)) {
                printf("Tree is empty...\n");
                break;
            }
			do {
                int cnt;
                do {
                    printf("Enter value of element that you want to delete: ");
                    cnt = 0;
                    scanf("%c", &val);
                    while ((c = getchar()) != EOF && c != '\n') cnt++;
                } while(cnt != 0);
				if (isExists(root, val)) {
                    deleteTree(&root, val, 0);
                    printf("Item (%c) has been added.\n", val);
                }
				else printf("There is no this node.\n");
				if (root) {
                    int cnt;
                    do {
                        printf("Do you want to add another leaf? (y/n) : ");
                        cnt = 0;
                        scanf("%c", &answer);
                        while ((c = getchar()) != EOF && c != '\n') cnt++;
                    } while (!(cnt == 0 && (tolower(answer) == 'n' || tolower(answer) == 'y')));
                } else (answer = 'n');
                
			} while (answer != 'n');
			break;
		}
		case '4': {

			if (!root) {
				printf("Tree is empty...\n");
				break;
			}
			printf("Max depth: %d", max_depth(root, 1) - 1);
				
			printf("\n");
			break;
		}
		case '5': {
			if (root) {
				deleteTree(&root, root -> val, 1);
			}
			clean_screen();
			return 0;
		}
		default: {
			break;
		}
		
		clean_screen();
		return 0;
		}
	}
}

struct tree *mktree(struct tree * root, struct tree * subTree, char val, char fatherVal) {

	if (!subTree) {
		subTree = (struct tree *)malloc(sizeof(struct tree));

		if (!subTree) {
			printf("No memory.");
			exit(1);
		}

		subTree -> son = NULL;
		subTree -> brother = NULL;
		subTree -> val = val;
		subTree -> fatherVal = fatherVal;

		if (!root) return subTree; // для первого вхождения
		if (root -> val == fatherVal) root -> son = subTree;
		else root -> brother = subTree;

		subTree -> val = val;
		subTree -> fatherVal = fatherVal;

		return root;
	}

	if (subTree -> val == fatherVal) {
		mktree(subTree, subTree -> son, val, fatherVal);
		return root;
	} else {
		if (subTree -> fatherVal == fatherVal) {
			mktree(subTree, subTree -> brother, val, fatherVal);
			return root;
		} else {
			if (subTree -> son) mktree(subTree, subTree -> son, val, fatherVal);
			if (subTree -> brother) mktree(subTree, subTree -> brother, val, fatherVal);
			return root;
		}
	}

	return root;
}

void printTree(struct tree * root, int lvl) {
	if (!root) return;
	printf("%*c\n", 2 * lvl, root -> val);
	if (root -> son) printTree(root -> son, lvl + 1);
	if (root -> brother) {
		root = root -> brother;
		printTree(root, lvl);
	}
}

bool isEmpty(const struct tree * root) {
	return root == NULL;
}

void deleteTree(struct tree **t, char val, int id) { // id: 1 - удалить, 0 - пропустить

	struct tree* tmp = *t;
	struct tree* tmp1;
	struct tree* tmp2;

	if (tmp -> val == val) id = 1;
	if (tmp -> son) {
		if (tmp -> son -> val == val && tmp -> son -> brother) { // swap указателей

			tmp1 = tmp -> son -> brother;
			tmp2 = tmp -> son;
			tmp2 -> brother = NULL;
			tmp -> son = tmp1;

			deleteTree(&tmp2, tmp2 -> val, 1);

		} else deleteTree(&tmp -> son, val, id);
	}
	if (tmp -> brother) {
		if (tmp -> brother -> val == val && tmp -> brother -> brother) { // swap указателей

			tmp1 = tmp -> brother -> brother;
			tmp2 = tmp -> brother;
			tmp2 -> brother = NULL;
			tmp -> brother = tmp1;

			deleteTree(&tmp2, tmp2 -> val, 1);
		} else deleteTree(&tmp -> brother, val, id);

	}

	if (id == 1) {
		free(*t);
		*t = NULL;
	}

	return;
}

bool isExists(const struct tree * root, char val) {

	bool tmp = false;

	if (root -> val == val) {
		tmp = true;
	}
	if (!tmp && root -> son) {
		tmp = isExists(root -> son, val);
	}
	if (!tmp && root -> brother) {
		tmp = isExists(root -> brother, val);
	}

	return tmp;
}

int max_depth(const struct tree *root, int lvl) {
	if (!root) return 0;
	int max_v = 1;
	if (root -> son) {
		max_v = max_depth(root -> son, lvl + 1);
	}
	if (root -> brother) {
		root = root -> brother;
		int b_depth = max_depth(root, lvl);
		max_v = b_depth > max_v ? b_depth : max_v;
	}
	return max_v > lvl ? max_v : lvl;
}