/* Idea for implementation:
 * We have a value then we want to save it as a item of a list. YES, that is an
 * array.
 *
 * When retreiving value of a specified item, we want O(1) average time access
 * using an index (No loop through elements), just get it by known index.
 *
 * How can we know the index of the item we want?
 * By using hash function (Mechanism to hash is our)
 * key -> element index in array
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

typedef struct Node ht_node;
struct Node {
  const char *key;
  void *data;
};
typedef struct HashTable ht;

struct HashTable {
  unsigned int size;
  ht_node **nodes;
};

ht *ht_create(unsigned int size);
void ht_clear(ht *ht);

unsigned int ht_hash(ht *ht, const char *key);
/* Remove a key by set its data to NULL pointer
 * */
void ht_insert(ht *ht, const char *key, void *data);
void *ht_get(ht *ht, const char *key);
#endif
