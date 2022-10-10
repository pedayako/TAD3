#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

#define TRUE 1
#define FALSE 0

struct _sllist_{
    SLNode *first;
    SLNode *cur; //current
};
struct _slnode_{
    void * data;
    struct _slnode_ *next;
};

SLList * sllCreate( void ) {
    SLList *list;
    list = (SLList * ) malloc(sizeof(SLList));
    if ( list != NULL ) {
        list->first = NULL;
        return list;
    }
    return NULL;
}
int sllDestroy ( SLList *l ){
    if ( l != NULL ) {
        if ( l->first == NULL ) {
            free (l);
            return TRUE;
        }
    }
    return FALSE;
}
int sllInsertFirst(SLList *l, void *data){
    SLNode * newnode;
    
    if ( l != NULL) {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if ( newnode != NULL) {
            newnode->data = data;
            newnode->next = l->first;
            l->first = newnode;
            return TRUE;
        }
    }
    return FALSE;
}
int sllInsertAsLast ( SLList *l, void *data){
    SLNode *newnode; SLNode *last;
    if ( l != NULL ) {
        newnode = ( SLNode *) malloc(sizeof(SLNode));
        if ( newnode != NULL) {
            newnode->data = data;
            newnode->next = NULL;
            if( l->first == NULL) {
                l->first = newnode;
            } else {
                // achar o ultimo – last
                last = l->first;
                while (last->next != NULL) { // last não for o ultimo
                    last = last->next;
                }
                last->next = newnode;
            }
            return TRUE;
        }
    }
    return FALSE;
}
void * sllRemoveFirst ( SLList *l ){
    SLNode *first; void *data;
    
    if ( l != NULL) {
        if ( l->first != NULL ) { //Se a lista não esta vazia
            first = l->first;
            data = first->data;
            l->first = first->next;
            free(first);
            return data;
        }
    }
    return NULL;
}
void * sllGetFirst( SLList *l){
    if ( l!= NULL ) {
        l->cur = l->first;
        if ( l->cur != NULL ) {
            return l->cur->data;
        }
    } else {
        return NULL;
    }
}
void * sllGetNext( SLList *l){
    if ( l != NULL ) {
         l->cur = l->cur->next;
        if ( l->cur != NULL ) {
            return l->cur->data;
        }
    }
    return NULL;
}
void * sllQuery( SLList *l, void *key, int (*cmp)(void *, void *)){
    SLNode *spec;
    if ( l != NULL ) {
        if ( l->first != NULL ) {
            spec = l->first;
            int stat = cmp(spec->data, key);
            while ( stat != TRUE && spec->next != NULL){
                spec= spec->next;
                stat = cmp(spec->data, key);
            }
            if ( stat == TRUE ) {
                return spec->data;
            }
        }
    }
    return NULL;
}
void * sllRemove( SLList *l, void *key, int (*cmp)(void *, void *)){
    SLNode *spec, *prev;
    if ( l != NULL ) {
        if ( l->first != NULL ) {
            spec = l->first; prev = NULL;
            int stat = cmp(spec->data, key);
            
            while ( stat != TRUE && spec->next != NULL) {
                prev = spec;
                spec= spec->next;
                stat = cmp(spec->data, key);
            }
            if ( stat == TRUE ) { // achar
                void * data;
                data = spec->data;
                if (l->first == spec ) {
                    l->first = spec->next;
                } else {
                    prev->next = spec->next;
                }
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}