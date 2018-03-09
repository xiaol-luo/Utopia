#include "srv_rbtree.h"
#include <cstdlib>

static void srv_rbtree_left_rotate(srv_rbtree_node_t **root, srv_rbtree_node_t *sentinel, srv_rbtree_node_t *node)
{
	srv_rbtree_node_t  *temp;

	temp = node->right;
	node->right = temp->left;

	if (temp->left != sentinel) {
		temp->left->parent = node;
	}

	temp->parent = node->parent;

	if (node == *root) {
		*root = temp;

	} else if (node == node->parent->left) {
		node->parent->left = temp;

	} else {
		node->parent->right = temp;
	}

	temp->left = node;
	node->parent = temp;
}


static void srv_rbtree_right_rotate(srv_rbtree_node_t **root, srv_rbtree_node_t *sentinel, srv_rbtree_node_t *node)
{
	srv_rbtree_node_t  *temp;

	temp = node->left;
	node->left = temp->right;

	if (temp->right != sentinel) {
		temp->right->parent = node;
	}

	temp->parent = node->parent;

	if (node == *root) {
		*root = temp;

	} else if (node == node->parent->right) {
		node->parent->right = temp;

	} else {
		node->parent->left = temp;
	}

	temp->right = node;
	node->parent = temp;
}


void srv_rbtree_insert(srv_rbtree_t *tree, srv_rbtree_node_t *node)
{
    srv_rbtree_node_t  **root, *temp, *sentinel;

    /* a binary tree insert */

    root = (srv_rbtree_node_t **) &tree->root;
    sentinel = tree->sentinel;

    if (*root == sentinel) {
        node->parent = NULL;
        node->left = sentinel;
        node->right = sentinel;
        srv_rbt_black(node);
        *root = node;

        return;
    }

    tree->insert(*root, node, sentinel);

    /* re-balance tree */

    while (node != *root && srv_rbt_is_red(node->parent)) {

        if (node->parent == node->parent->parent->left) {
            temp = node->parent->parent->right;

            if (srv_rbt_is_red(temp)) {
                srv_rbt_black(node->parent);
                srv_rbt_black(temp);
                srv_rbt_red(node->parent->parent);
                node = node->parent->parent;

            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    srv_rbtree_left_rotate(root, sentinel, node);
                }

                srv_rbt_black(node->parent);
                srv_rbt_red(node->parent->parent);
                srv_rbtree_right_rotate(root, sentinel, node->parent->parent);
            }

        } else {
            temp = node->parent->parent->left;

            if (srv_rbt_is_red(temp)) {
                srv_rbt_black(node->parent);
                srv_rbt_black(temp);
                srv_rbt_red(node->parent->parent);
                node = node->parent->parent;

            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    srv_rbtree_right_rotate(root, sentinel, node);
                }

                srv_rbt_black(node->parent);
                srv_rbt_red(node->parent->parent);
                srv_rbtree_left_rotate(root, sentinel, node->parent->parent);
            }
        }
    }

    srv_rbt_black(*root);
}

void srv_rbtree_delete(srv_rbtree_t *tree, srv_rbtree_node_t *node)
{
    uint           red;
    srv_rbtree_node_t  **root, *sentinel, *subst, *temp, *w;

    /* a binary tree delete */

    root = (srv_rbtree_node_t **) &tree->root;
    sentinel = tree->sentinel;

    if (node->left == sentinel) {
        temp = node->right;
        subst = node;

    } else if (node->right == sentinel) {
        temp = node->left;
        subst = node;

    } else {
        subst = srv_rbtree_min(node->right, sentinel);

        if (subst->left != sentinel) {
            temp = subst->left;
        } else {
            temp = subst->right;
        }
    }

    if (subst == *root) {
        *root = temp;
        srv_rbt_black(temp);

        /* DEBUG stuff */
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->key = 0;

        return;
    }

    red = srv_rbt_is_red(subst);

    if (subst == subst->parent->left) {
        subst->parent->left = temp;

    } else {
        subst->parent->right = temp;
    }

    if (subst == node) {

        temp->parent = subst->parent;

    } else {

        if (subst->parent == node) {
            temp->parent = subst;

        } else {
            temp->parent = subst->parent;
        }

        subst->left = node->left;
        subst->right = node->right;
        subst->parent = node->parent;
        srv_rbt_copy_color(subst, node); 

        if (node == *root) {
            *root = subst;

        } else {
            if (node == node->parent->left) {
                node->parent->left = subst;
            } else {
                node->parent->right = subst;
            }
        }

        if (subst->left != sentinel) {
            subst->left->parent = subst;
        }

        if (subst->right != sentinel) {
            subst->right->parent = subst;
        }
    }

    /* DEBUG stuff */
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->key = 0;

    if (red) {
        return;
    }

    /* a delete fixup */

    while (temp != *root && srv_rbt_is_black(temp)) {

        if (temp == temp->parent->left) {
            w = temp->parent->right;

            if (srv_rbt_is_red(w)) {
                srv_rbt_black(w);
                srv_rbt_red(temp->parent);
                srv_rbtree_left_rotate(root, sentinel, temp->parent);
                w = temp->parent->right;
            }

            if (srv_rbt_is_black(w->left) && srv_rbt_is_black(w->right)) {
                srv_rbt_red(w);
                temp = temp->parent;

            } else {
                if (srv_rbt_is_black(w->right)) {
                    srv_rbt_black(w->left);
                    srv_rbt_red(w);
                    srv_rbtree_right_rotate(root, sentinel, w);
                    w = temp->parent->right;
                }

                srv_rbt_copy_color(w, temp->parent);
                srv_rbt_black(temp->parent);
                srv_rbt_black(w->right);
                srv_rbtree_left_rotate(root, sentinel, temp->parent);
                temp = *root;
            }

        } else {
            w = temp->parent->left;

            if (srv_rbt_is_red(w)) {
                srv_rbt_black(w);
                srv_rbt_red(temp->parent);
                srv_rbtree_right_rotate(root, sentinel, temp->parent);
                w = temp->parent->left;
            }

            if (srv_rbt_is_black(w->left) && srv_rbt_is_black(w->right)) {
                srv_rbt_red(w);
                temp = temp->parent;

            } else {
                if (srv_rbt_is_black(w->left)) {
                    srv_rbt_black(w->right);
                    srv_rbt_red(w);
                    srv_rbtree_left_rotate(root, sentinel, w);
                    w = temp->parent->left;
                }

                srv_rbt_copy_color(w, temp->parent);
                srv_rbt_black(temp->parent);
                srv_rbt_black(w->left);
                srv_rbtree_right_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }
    }

    srv_rbt_black(temp);
}

srv_rbtree_node_t * srv_rbtree_min(srv_rbtree_node_t *node, srv_rbtree_node_t *sentinel)
{
	while (node->left != sentinel) {
		node = node->left;
	}

	return node;
}


void srv_rbtree_insert_value(srv_rbtree_node_t *temp, srv_rbtree_node_t *node,
    srv_rbtree_node_t *sentinel)
{
    srv_rbtree_node_t  **p;

    for ( ;; ) {

        p = (node->key < temp->key) ? &temp->left : &temp->right;

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    srv_rbt_red(node);
}

