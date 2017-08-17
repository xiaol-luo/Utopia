#ifndef __SRV_RBTREE_H__
#define __SRV_RBTREE_H__

#ifdef _cplusplus
extern "C" {
#endif

typedef unsigned int uint;
typedef unsigned char u_char;
typedef long long srv_rbtree_key_t;

typedef struct srv_rbtree_node_s srv_rbtree_node_t;
struct srv_rbtree_node_s 
{
	srv_rbtree_key_t       key;
	srv_rbtree_node_t     *left;
	srv_rbtree_node_t     *right;
	srv_rbtree_node_t     *parent;
	u_char                 color;
	void	              *data;
};

typedef struct srv_rbtree_s srv_rbtree_t;

typedef void (*srv_rbtree_insert_pt)(srv_rbtree_node_t *root, srv_rbtree_node_t *node, srv_rbtree_node_t *sentinel);

struct srv_rbtree_s 
{
	srv_rbtree_node_t *root;
	srv_rbtree_node_t *sentinel;
	srv_rbtree_insert_pt insert;
};

#define srv_rbt_red(node)               ((node)->color = 1)
#define srv_rbt_black(node)             ((node)->color = 0)
#define srv_rbt_is_red(node)            ((node)->color)
#define srv_rbt_is_black(node)          (!srv_rbt_is_red(node))
#define srv_rbt_copy_color(n1, n2)      (n1->color = n2->color)

#define srv_rbtree_sentinel_init(node)  srv_rbt_black(node)

#define srv_rbtree_init(tree, s, i) \
	srv_rbtree_sentinel_init(s);	\
	(tree)->root = s;				\
	(tree)->sentinel = s;			\
	(tree)->insert = i;

void srv_rbtree_insert(srv_rbtree_t *tree, srv_rbtree_node_t *node);
void srv_rbtree_delete(srv_rbtree_t *tree, srv_rbtree_node_t *node);
srv_rbtree_node_t * srv_rbtree_min(srv_rbtree_node_t *node, srv_rbtree_node_t *sentinel);

void srv_rbtree_insert_value(srv_rbtree_node_t *root, srv_rbtree_node_t *node, srv_rbtree_node_t *sentinel);

#endif

#ifdef _cplusplus
}
#endif
