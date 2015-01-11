
#ifndef CONTAINER_H
# define CONTAINER_H

# include "object.h"
# include "iterator.h"

typedef struct Container_s Container;

typedef Iterator* (*iter_t)(Container* self);
typedef size_t (*len_t)(Container* self);
typedef Object* (*getitem_t)(Container* self, ...);
typedef void (*setitem_t)(Container* self, ...);
typedef void (*pushback_t)(Container *list, Object *new);
typedef void (*pushfront_t)(Container *list, Object *new);
typedef void (*popback_t)(Container *list);
typedef void (*popfront_t)(Container *list);

struct Container_s {
    Class base;
    len_t       __len__;
    iter_t      __begin__;
    iter_t      __end__;
    getitem_t   __getitem__;
    setitem_t   __setitem__;
    pushback_t  __pushback__;
    pushfront_t __pushfront__;
    popback_t   __popback__;
    popfront_t  __popfront__;
};

# define len(c)                 (((Container*) c)->__len__(c))
# define begin(c)               (((Container*) c)->__begin__(c))
# define end(c)                 (((Container*) c)->__end__(c))
# define getitem(c, ...)        (((Container*) c)->__getitem__(c, __VA_ARGS__))
# define setitem(c, ...)        (((Container*) c)->__setitem__(c, __VA_ARGS__))
# define pushback(c, o)         (((Container*) c)->__pushback__(c, o))
# define pushfront(c, o)        (((Container*) c)->__pushfront__(c, o))
# define popback(c)             (((Container*) c)->__popback__(c))
# define popfront(c)            (((Container*) c)->__popfront__(c))

#endif

