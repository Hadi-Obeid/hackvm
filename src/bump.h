#define ALIGN 16
#define POOL_SIZE 1024

size_t align_up(size_t n, size_t a);
void *bump_alloc(size_t size); 
void bump_reset(void);
size_t bump_remaining(void);
