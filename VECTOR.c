#include<stdlib.h>
#include<stdio.h>
#include "vector.h"
#include<string.h>
/*No problem*/
int vector_init(Vector* vector, size_t capacity, size_t element_size){
    if(capacity<VECTOR_MINIMUM_CAPACITY || element_size<1) return VECTOR_ERROR;
    vector->capacity=capacity;
    vector->element_size=element_size;
    /*no*/
    vector->size=0;
    vector->data=malloc(capacity*element_size);
    if(vector->data==NULL) return VECTOR_ERROR;
    /*normal operation, just copy*/
    return VECTOR_SUCCESS;
}/*Finished*/

int vector_copy(Vector* destination, Vector* source){
    if(vector_init(destination,source->capacity,source->element_size)==VECTOR_ERROR) return VECTOR_ERROR;
    memcpy(destination->data,source->data,source->size*source->element_size);
    return VECTOR_SUCCESS;
}/*May source be NULL?*/

int vector_destroy(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    free(vector->data);
    return VECTOR_SUCCESS;
}/*May any other questions?*/

int vector_push_back(Vector* vector, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    /*deal fault parameter*/
    if(vector->size==vector->capacity){/*deal with full condition*/
        void *p=vector->data;
        void *q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q,p,vector->capacity*vector->element_size);
        /*no*/
        free(p);
        vector->data=q;
        vector->capacity*=VECTOR_GROWTH_FACTOR;
    }
    /*No problem*/
    memcpy((char *)vector->data+vector->size*vector->element_size,element,vector->element_size);
    ++vector->size;
    return VECTOR_SUCCESS;
}/*element=NULL?*/

int vector_push_front(Vector* vector, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    /*deal with fault para*/
    if(vector->size==vector->capacity){/*deal with full condition*/
        void *p=vector->data;
        void *q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy((char *)q+vector->element_size,p,vector->capacity*vector->element_size);
        /*No problem*/
        free(p);
        vector->data=q;
        vector->capacity*=VECTOR_GROWTH_FACTOR;
    }
    /*No problem*/
    memcpy(vector->data,element,vector->element_size);
    ++vector->size;
    return VECTOR_SUCCESS;
}/*similar to push_back*/

int vector_insert(Vector* vector, size_t index, void* element){
    if(index>vector->size) return VECTOR_ERROR;
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    /*deal para fault*/
    if(index==0) return vector_push_front(vector,element);
    else if(index==vector->size) return vector_push_back(vector,element);
    else{
        void *p=vector->data,*q;
        /*No problem*/
        if(vector->size==vector->capacity){
            q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
            vector->capacity*=VECTOR_GROWTH_FACTOR;
        }
        /*No problem*/
        else q=malloc(vector->capacity*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q,p,vector->element_size*index);
        memcpy(q,element,vector->element_size);
        /*No problem*/
        memcpy((char *)q+(index+1)*vector->element_size,(char *)p+index*vector->element_size,(vector->size-index)*vector->element_size);
        ++vector->size;
        free(p);
        return VECTOR_SUCCESS;
        /*No problem*/
    }
}
/*No problem*/
int vector_assign(Vector* vector, size_t index, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(index>=vector->size) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    /*deal with fault para*/
    memcpy((char *)vector->data+vector->element_size*index,element,vector->element_size);
    return VECTOR_SUCCESS;
}
/*No problem*/
int vector_pop_back(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    /*No problem*/
    if(vector->size==0) return VECTOR_ERROR;
    --vector->size;
    return VECTOR_SUCCESS;
}
/*No problem*/
int vector_pop_front(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(vector->size==0) return VECTOR_ERROR;
    memmove((char *)vector->data,(char *)vector->data+vector->element_size,(--vector->size)*vector->element_size);
    /*No problem*/
    return VECTOR_SUCCESS;
}
/*No problem*/
int vector_clear(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    /*No problem*/
    vector->size=0;
    return VECTOR_SUCCESS;
}
/*No problem*/
int vector_erase(Vector* vector, size_t index){
    if(index>=vector->size) return VECTOR_ERROR;
    /*No problem*/
    if(vector->data==NULL) return VECTOR_ERROR;
    if(index==0) return vector_pop_front(vector);
    else if(index==vector->size-1) return vector_pop_back(vector);
    /*No problem*/
    else memmove((char *)vector->data+index*vector->element_size,(char *)vector->data+(index+1)*vector->element_size,(--vector->size-index)*vector->element_size);
    return VECTOR_SUCCESS;
}
/*No problem*/
void* vector_get(Vector* vector, size_t index){
    void *p;
    /*No problem*/
    if(vector->data==NULL) return NULL;
    if(vector->size<=index) return NULL;
    p=malloc(vector->element_size);
    if(p==NULL) return NULL;
    /*No problem*/
    memcpy(p,(char *)vector->data+vector->element_size*index,vector->element_size);
    return p;
}
/*No problem*/
void* vector_front(Vector* vector){
    return vector_get(vector,0);
}/*No problem*/

void* vector_back(Vector* vector){
    return vector_get(vector,vector->size-1);
}
/*No problem*/
size_t vector_size(const Vector* vector){
    return vector->size;
}/*No problem*/

bool vector_is_empty(const Vector* vector){
    return vector->size==0;
}
/*No problem*/
int vector_resize(Vector* vector, size_t new_size){
    if(vector->data==NULL) return VECTOR_ERROR;
    /*No problem*/
    if(new_size>vector->capacity){
        void *p=vector->data;
        void *q=malloc(((new_size/vector->capacity)+1)*vector->capacity*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        /*No problem*/
        memcpy(q,p,vector->size*vector->element_size);
    }
    vector->size=new_size;
    return VECTOR_SUCCESS;
}
/*No problem*/
Iterator vector_begin(Vector* vector){
    Iterator iter;
    if((vector->data==NULL) || (vector->size==0)){
        iter.pointer=NULL;
        /*No problem*/
        iter.element_size=0;
    }
    /*No problem*/
    else{
        iter.element_size=vector->element_size;
        iter.pointer=vector->data;
    }
    /*No problem*/
    return iter;
}
/*No problem*/
Iterator vector_end(Vector* vector){
    Iterator iter;
    if((vector->data==NULL) || (vector->size==0)){
        /*No problem*/
        iter.pointer=NULL;
        iter.element_size=0;
    }
    /*No problem*/
    else{
        iter.element_size=vector->element_size;
        /*No problem*/
        iter.pointer=(char *)vector->data+(vector->size-1)*vector->element_size;
    }
    return iter;
}
/*No problem*/
Iterator vector_iterator(Vector* vector, size_t index){
    Iterator iter;
    /*No problem*/
    if((vector->data==NULL) || (vector->size>=index)){
        iter.pointer=NULL;
        iter.element_size=0;
    }
    else{
        /*No problem*/
        iter.element_size=vector->element_size;
        iter.pointer=(char *)vector->data+(vector->size-1)*vector->element_size;
    }
    return iter;
}

void* iterator_get(Iterator* iterator){
    /*No problem*/
    void *p;
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return NULL;
    p=malloc(iterator->element_size);
    memcpy(p,iterator->pointer,iterator->element_size);
    /*No problem*/
    return p;
}
void iterator_increment(Iterator* iterator){
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return;
    /*No problem*/
    else{
        /*No problem*/
        char *p;
        p=iterator->pointer;
        p+=iterator->element_size;
        iterator->pointer=p;
        /*No problem*/
    }
}

void iterator_decrement(Iterator* iterator){
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return;
    /*No problem*/
    else{
        char *p;
        /*No problem*/
        p=iterator->pointer;
        p-=iterator->element_size;
        iterator->pointer=p;
    }
    /*No problem*/
}
/*No problem*/
bool iterator_equals(Iterator* first, Iterator* second){
    return((first->pointer==second->pointer) && (first->element_size==second->element_size));
}

void vector_sort(Vector *vector, vector_less_func *less){
    /*No problem*/
    int a,b;
    /*No problem*/
    a=sizeof(vector);
    b=sizeof(less);
    a=a+b;
    b=b+a;
    /*No problem*/
    printf("%d %d\n",a,b);
    return;
}
/*No problem*/
