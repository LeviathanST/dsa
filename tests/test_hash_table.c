#include "../src/hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_hash() {
  ht *p_ht = ht_create(4);

  printf("%u", ht_hash(p_ht, "Bob"));
  ht_clear(p_ht);
}

void test_add() {
  ht *p_ht1 = ht_create(4);

  ht_insert(p_ht1, "Bob", "Name: Bob");
  assert(strcmp((char *)ht_get(p_ht1, "Bob"), "Name: Bob") == 0);
  ht_insert(p_ht1, "Bob", "Name: Alice");
  assert(strcmp((char *)ht_get(p_ht1, "Bob"), "Name: Alice") == 0);
  ht_clear(p_ht1);
}

int main() {
  test_hash();
  test_add();
  return 0;
}
