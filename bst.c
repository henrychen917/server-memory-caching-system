#include <bst.h>

node_t* newNode(uint32_t keyid, char key[32], char value[64], pool_t *pool) {
	node_t* temp = pool_alloc(sizeof(node_t),pool);
	temp->keyid = keyid;
	memcpy(temp->key, key, sizeof(char)*32);
	memcpy(temp->val, value, sizeof(char)*64);
	temp->left = temp->right = NULL;
	return temp;
}


void inorder(node_t *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("id: %" PRIu32 " key: %s val:%s \n", root->keyid, root->key, root->val);
		inorder(root->right);
	}

}


node_t* insert_s(node_t* root, uint32_t keyid, char key[32], char value[64], pool_t *pool)
{
	
	if (root == NULL)
		return newNode(keyid, key, value, pool);
	if (keyid == root->keyid){
		memcpy(root->key, key, sizeof(char)*32);
		memcpy(root->val, value, sizeof(char)*64);
		return root;
	}
	if (keyid < root->keyid)
		root->left = insert_s(root->left, keyid, key, value, pool);
	else
		root->right = insert_s(root->right, keyid, key, value, pool);


	return root;
}

node_t* insert(node_t* root, char key[32], char value[64], pool_t *pool){
	uint32_t seed = 0;
	uint32_t keyid = murmurhash(key, (uint32_t) str_length(key), seed);
	return insert_s(root, keyid, key, value, pool);
}


node_t* minValueNode(node_t* node) {
	node_t* current = node;


	while (current && current->left != NULL)
		current = current->left;

	return current;
}


node_t* deleteNode(node_t* root, uint32_t keyid) {

	if (root == NULL)
		return root;

	if (keyid < root->keyid)
		root->left = deleteNode(root->left, keyid);

	else if (keyid > root->keyid)
		root->right = deleteNode(root->right, keyid);


	else {

		if (root->left == NULL) {
			node_t* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			node_t* temp = root->left;
			free(root);
			return temp;
		}

		node_t* temp = minValueNode(root->right);


		root->keyid = temp->keyid;


		root->right = deleteNode(root->right, temp->keyid);
	}
	return root;
}


node_t* searchNode(node_t* root, uint32_t keyid){

	if (root == NULL)
		return root;

	if (keyid < root->keyid)
		root->left = searchNode(root->left, keyid);

	else if (keyid > root->keyid)
		root->right = searchNode(root->right, keyid);
	else
		return root;

}


