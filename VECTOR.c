//当您的向量已满时，将其容量增加到VECTOR_GROWTH_FACTOR * original_capacity
//当用户在不应该有空指针的地方输入一个空指针时，你的程序必须返回VECTOR_ERROR，一个空指针，一个指针为空、大小为0的迭代器，等等，但是它永远不会崩溃。
//我们要求每四行非空行有一行注释。评论必须是有意义的，而且是用英语写的。
//不允许任何内存泄漏。内存泄漏将自动检测和手动筛选，并将导致您的分数下降后的最后期限。
//我们还将对您的LoC(代码行数)施加400的限制。不要超过这个限额，因为超过这个限额的人会被扣分。
//您可以在代码中实现一些帮助函数。但是，不应该从文件中访问辅助函数。我们将手动检查，如果您没有做到这一点，我们将扣分。
#include<stdlib.h>
#include<stdio.h>
#include "vector.h"
#include<string.h>

int vector_init(Vector* vector, size_t capacity, size_t element_size){
    if(capacity<VECTOR_MINIMUM_CAPACITY || element_size<1) return VECTOR_ERROR;
    vector->capacity=capacity;
    vector->element_size=element_size;
    vector->size=0;
    vector->data=malloc(capacity*element_size);
    if(vector->data==NULL) return VECTOR_ERROR;
    //normal operation, just copy
    return VECTOR_SUCCESS;
}//Finished//

int vector_copy(Vector* destination, Vector* source){
    if(vector_init(destination,source->capacity,source->element_size)==VECTOR_ERROR) return VECTOR_ERROR;
    memcpy(destination->data,source->data,source->size*source->element_size);
    return VECTOR_SUCCESS;
}//May source be NULL?

int vector_destroy(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    free(vector->data);
    return VECTOR_SUCCESS;
}//May any other questions?

int vector_push_back(Vector* vector, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    //deal fault parameter
    if(vector->size==vector->capacity){//deal with full condition
        void *p=vector->data;
        void *q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q,p,vector->capacity*vector->element_size);
        free(p);
        vector->data=q;
        vector->capacity*=VECTOR_GROWTH_FACTOR;
    }
    memcpy(vector->data+vector->size*vector->element_size,element,vector->element_size);
    ++vector->size;
    return VECTOR_SUCCESS;
}//直接把指针给它还是别的做法,element=NULL?

int vector_push_front(Vector* vector, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    //deal with fault para
    if(vector->size==vector->capacity){//deal with full condition
        void *p=vector->data;
        void *q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q+vector->element_size,p,vector->capacity*vector->element_size);
        free(p);
        vector->data=q;
        vector->capacity*=VECTOR_GROWTH_FACTOR;
    }
    memcpy(vector->data,element,vector->element_size);
    ++vector->size;
    return VECTOR_SUCCESS;
}//similar to push_back

int vector_insert(Vector* vector, size_t index, void* element){
    if(index>vector->size) return VECTOR_ERROR;
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    //deal para fault
    if(index==0) return vector_push_front(vector,element);
    else if(index==vector->size) return vector_push_back(vector,element);
    else{
        void *p=vector->data,*q;
        if(vector->size==vector->capacity){
            q=malloc((vector->capacity*VECTOR_GROWTH_FACTOR)*vector->element_size);
            vector->capacity*=VECTOR_GROWTH_FACTOR;
        }
        else q=malloc(vector->capacity*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q,p,vector->element_size*index);
        memcpy(q,element,vector->element_size);
        memcpy(q+(index+1)*vector->element_size,p+index*vector->element_size,(vector->size-index)*vector->element_size);
        ++vector->size;
        free(p);
        return VECTOR_SUCCESS;
    }
}

int vector_assign(Vector* vector, size_t index, void* element){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(index>=vector->size) return VECTOR_ERROR;
    if(element==NULL) return VECTOR_ERROR;
    //deal with fault para
    memcpy(vector->data+vector->element_size*index,element,vector->element_size);
    return VECTOR_SUCCESS;
}

int vector_pop_back(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(vector->size==0) return VECTOR_ERROR;
    --vector->size;
    return VECTOR_SUCCESS;
}

int vector_pop_front(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    if(vector->size==0) return VECTOR_ERROR;
    memmove(vector->data,vector->data+vector->element_size,(--vector->size)*vector->element_size);
    return VECTOR_SUCCESS;
}

int vector_clear(Vector* vector){
    if(vector->data==VECTOR_UNINITIALIZED) return VECTOR_ERROR;
    vector->size=0;
    return VECTOR_SUCCESS;
}

int vector_erase(Vector* vector, size_t index){
    if(index>=vector->size) return VECTOR_ERROR;
    if(vector->data==NULL) return VECTOR_ERROR;
    if(index==0) return vector_pop_front(vector);
    else if(index==vector->size-1) return vector_pop_back(vector);
    else memmove(vector->data+index*vector->element_size,vector->data+(index+1)*vector->element_size,(--vector->size-index)*vector->element_size);
    return VECTOR_SUCCESS;
}

void* vector_get(Vector* vector, size_t index){
    if(vector->data==NULL) return NULL;
    if(vector->size<=index) return NULL;
    void *p=malloc(vector->element_size);
    if(p==NULL) return NULL;
    memcpy(p,vector->data+vector->element_size*index,vector->element_size);
    return p;
}

void* vector_front(Vector* vector){
    return vector_get(vector,0);
}

void* vector_back(Vector* vector){
    return vector_get(vector,vector->size-1);
}

size_t vector_size(const Vector* vector){
    return vector->size;
}

bool vector_is_empty(const Vector* vector){
    return vector->size==0;
}

int vector_resize(Vector* vector, size_t new_size){
    if(vector->data==NULL) return VECTOR_ERROR;
    if(new_size>vector->capacity){
        void *p=vector->data;
        void *q=malloc(((new_size/vector->capacity)+1)*vector->capacity*vector->element_size);
        if(q==NULL) return VECTOR_ERROR;
        memcpy(q,p,vector->size*vector->element_size);
    }
    vector->size=new_size;
    return VECTOR_SUCCESS;
}

Iterator vector_begin(Vector* vector){
    Iterator iter;
    if((vector->data==NULL) || (vector->size==0)){
        iter.pointer=NULL;
        iter.element_size=0;
    }
    else{
        iter.element_size=vector->element_size;
        iter.pointer=vector->data;
    }
    return iter;
}

Iterator vector_end(Vector* vector){
    Iterator iter;
    if((vector->data==NULL) || (vector->size==0)){
        iter.pointer=NULL;
        iter.element_size=0;
    }
    else{
        iter.element_size=vector->element_size;
        iter.pointer=vector->data+(vector->size-1)*vector->element_size;
    }
    return iter;
}

Iterator vector_iterator(Vector* vector, size_t index){
    Iterator iter;
    if((vector->data==NULL) || (vector->size>=index)){
        iter.pointer=NULL;
        iter.element_size=0;
    }
    else{
        iter.element_size=vector->element_size;
        iter.pointer=vector->data+(vector->size-1)*vector->element_size;
    }
    return iter;
}

void* iterator_get(Iterator* iterator){
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return NULL;
    void *p=malloc(iterator->element_size);
    memcpy(p,iterator->pointer,iterator->element_size);
    return p;
}
void iterator_increment(Iterator* iterator){
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return;
    else iterator->pointer+=iterator->element_size;
}

void iterator_decrement(Iterator* iterator){
    if((iterator->pointer==NULL) || (iterator->element_size==0)) return;
    else iterator->pointer-=iterator->element_size;
}

bool iterator_equals(Iterator* first, Iterator* second){
    return((first->pointer==second->pointer) && (first->element_size==second->element_size));
}

int main(){
    return 0;
}
