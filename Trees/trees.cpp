struct Node {
	int key;
	Node *left, *right;
};

void postorder(Node *n) {
	if(n) {
		postorder(n->left);
		postorder(n->right);
		cout << n->key << " ";
	}
}

int main() {
	return 0;
}