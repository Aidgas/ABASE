
#include "ah_api_common.h"

struct PAGE_FRAGMENT* __new_Page_Fragment()
{
    struct PAGE_FRAGMENT *result = (struct PAGE_FRAGMENT *) calloc( sizeof(struct PAGE_FRAGMENT), 1 );
    result->data_list = NULL;
    return result;
}

void free_Page_Fragment(struct PAGE_FRAGMENT *pf)
{
    if(pf == NULL)
    {
        printf("_free_Page_Fragment is NULL\n");
        return;
    }

    free(pf);
    pf = NULL;
}