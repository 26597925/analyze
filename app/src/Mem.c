/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include "Mem.h"
static size_t max_alloc_size= INT_MAX;

void *m_malloc(size_t size)
{
    void *ptr = NULL;

    if (size > (max_alloc_size - 32))
        return NULL;
	
    ptr = malloc(size);
	
    if(!ptr && !size) {
        size = 1;
        ptr= m_malloc(1);
    }

    return ptr;
}

void *m_mallocz(size_t size)
{
    void *ptr = m_malloc(size);
    if (ptr)
        memset(ptr, 0, size);
    return ptr;
}

void *m_realloc(void *ptr, size_t size)
{
    if (size > (max_alloc_size - 32))
        return NULL;
    return realloc(ptr, size + !size);
}

void *m_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    if (!size || nmemb >= INT_MAX / size)
        return NULL;
    return m_realloc(ptr, nmemb * size);
}

void m_freep(void *ptr)
{
    void *val;

    memcpy(&val, ptr, sizeof(val));
    memcpy(ptr, &(void *){ NULL }, sizeof(val));
    free(val);
}