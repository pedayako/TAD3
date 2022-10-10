typedef struct _sllist_ SLList;
typedef struct _slnode_ SLNode;

SLList * sllCreate( void );
int sllDestroy ( SLList *l );
int sllInsertFirst(SLList *l, void *data);
int sllInsertAsLast ( SLList *l, void *data);
void * sllRemoveFirst ( SLList *l );
void * sllGetFirst (SLList *l);
void * sllGetNext( SLList *l);
void * sllQuery( SLList *l, void *key, int (*cmp)(void *, void *));
void * sllRemove( SLList *l, void *key, int (*cmp)(void *, void *));