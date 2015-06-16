/*
 * name:wenford 
 * email:26597925@qq.com
 *
*/
#include <limits.h>
#include <stdlib.h>
#include<string.h>

void *m_realloc(void *ptr, size_t size);

void *m_malloc(size_t size);

void *m_mallocz(size_t size);

void *m_realloc_array(void *ptr, size_t nmemb, size_t size);

void m_freep(void *ptr);