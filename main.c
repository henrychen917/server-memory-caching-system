#include <main.h>

int main(void) {
	//printf("hello world");
    
    pool_t *pool = pool_init(default_size);
    node_t *root = diskInit(pool);
	char key[32] = "";
	char value[64] = "";
    inorder(root);
/*
	scanf("%s", key);
	scanf("%s", value);
	

	insert(root, key, value, pool);
	scanf("%s", key);
	scanf("%s", value);

	insert(root, key, value, pool);
	scanf("%s", key);
	scanf("%s", value);

	insert(root, key, value, pool);
	scanf("%s", key);
	scanf("%s", value);

	scanf("%s", key);
	scanf("%s", value);
	insert(root, key, value, pool);
	inorder(root);
    diskSaveAll(root);

*/
	return 0;
}


