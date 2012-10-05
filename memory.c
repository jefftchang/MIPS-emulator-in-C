#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

/* Pointer to simulator memory */
uint8_t *mem;

/* Called by program loader to initialize memory. */
uint8_t *init_mem() {
  assert (mem == NULL);
  mem = calloc(MEM_SIZE, sizeof(uint8_t)); // allocate zeroed memory
  return mem;
}

/* Returns 1 if memory access is ok, otherwise 0 */
int access_ok(uint32_t mipsaddr, mem_unit_t size) {

  /* TODO YOUR CODE HERE */
  if (mipsaddr % size == 0 && mipsaddr <= 1024*1024 && mipsaddr > 0 && mipsaddr % size == 0) {
    return 1;
  }
  return 0;
}

/* Writes size bytes of value into mips memory at mipsaddr */
void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value) {
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad write=%08x\n", __FUNCTION__, mipsaddr);
    exit(0);
  }

  /* TODO YOUR CODE HERE */
  int k;
  for (k = 0; k < size;k++) {
    *(mipsaddr + mem + k) = (uint8_t)(value & 0xFF);
    value = value >> 8;
  }
}

/* Returns zero-extended value from mips memory */
uint32_t load_mem(uint32_t mipsaddr, mem_unit_t size) {
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad read=%08x\n", __FUNCTION__, mipsaddr);
    exit(0);
  }

  /* TODO YOUR CODE HERE */
  //printf("accessing address: %d\n", mipsaddr);
  if (size == SIZE_BYTE) {
    return *(uint8_t*)(mem + mipsaddr);
  }
  // incomplete stub to let mipscode/simple execute
  // (only handles size == SIZE_WORD correctly)
  // feel free to delete and implement your own way
  return *(uint32_t*)(mem + mipsaddr);
}
