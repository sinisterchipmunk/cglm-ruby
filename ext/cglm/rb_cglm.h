#ifndef RB_CGLM_H
#define RB_CGLM_H 1

#ifdef __MINGW32__
#include <stdlib.h>
#include <intrin.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#define drand48() (((double)rand()) / RAND_MAX)
#endif // __MINGW32__

#include "ruby.h"
#include <errno.h>

// Based on unit test results I think the FLT_EPSILON that is used for fuzzy
// equality by CGLM may be too strict. This HACK works around the issue.
#include <float.h>
#undef FLT_EPSILON
#define FLT_EPSILON 0.00001

#include "cglm/cglm.h"

#if SIZEOF_VOIDP == SIZEOF_LONG
# define PTR2NUM(x)   (LONG2NUM((long)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULONG(x)))
#else
# define PTR2NUM(x)   (LL2NUM((LONG_LONG)(x)))
# define NUM2PTR(x)   ((void*)(NUM2ULL(x)))
#endif

#define CHECK_RANGE(val, min, max)  \
        if (NUM2INT(val) < min || NUM2INT(val) > max) \
          rb_raise(rb_eRangeError, "index %d out of bounds (%d..%d)", NUM2INT(val), min, max);

void Init_cglm_affine();
void Init_cglm_box();
void Init_cglm_cam();
void Init_cglm_color();
void Init_cglm_ease();
void Init_cglm_euler();
void Init_cglm_frustum();
void Init_cglm_io();
void Init_cglm_mat3();
void Init_cglm_mat4();
void Init_cglm_plane();
void Init_cglm_project();
void Init_cglm_quat();
void Init_cglm_sphere();
void Init_cglm_vec3();
void Init_cglm_vec4();

#define VEC3_ALIGNMENT  8
#define VEC4_ALIGNMENT 16
#define AABB_ALIGNMENT  8
#define QUAT_ALIGNMENT 16
#ifdef __AVX__
#define MAT4_ALIGNMENT 32
#define MAT3_ALIGNMENT 32
#else
#define MAT4_ALIGNMENT 16
#define MAT3_ALIGNMENT 16
#endif
#define PLANE_ALIGNMENT VEC4_ALIGNMENT

extern VALUE rb_cFiddle, rb_cPointer, rb_mCGLM, rb_cCGLMBase, rb_cVectorType,
             rb_cMat4, rb_cVec3, rb_cVec4, rb_cAABB, rb_mEuler, rb_cQuat,
             rb_cFrustum, rb_cMat3, rb_cSphere, rb_cPlane;

typedef struct { vec3 corners[2]; } aabb;
typedef struct { vec4 planes[6];  } frustum;
typedef vec4 quat;
typedef vec4 plane;

inline size_t vec3_size()  { return sizeof(vec3);  }
inline size_t vec4_size()  { return sizeof(vec4);  }
inline size_t aabb_size()  { return sizeof(aabb);  }
inline size_t mat4_size()  { return sizeof(mat4);  }
inline size_t mat3_size()  { return sizeof(mat4);  }
inline size_t quat_size()  { return sizeof(mat4);  }
inline size_t plane_size() { return sizeof(plane); }

#define PTR2FIDDLE(addr, size) rb_funcall(rb_cPointer, rb_intern("new"), 2, PTR2NUM(addr), SIZET2NUM(size))

static inline VALUE CGLM_NEW(VALUE klass, size_t size, void *addr) {
  VALUE kw = rb_hash_new();
  VALUE ptr = PTR2FIDDLE(addr, size);
  rb_hash_aset(kw, ID2SYM(rb_intern("addr")), ptr);
  return rb_funcall(klass, rb_intern("new"), 1, kw);
}

static inline void *__aligned_alloc(size_t align, size_t size) {
  void *mem = NULL;
#ifdef __MINGW32__
  mem = _aligned_malloc(size, align);
  int err = 0;
  if (!mem) err = ENOMEM;
#else
  int err = posix_memalign(&mem, align, size);
#endif
  switch(err) {
    case EINVAL:
      rb_raise(rb_eRuntimeError, "Alignment %zu was not a power of two, or was not a multiple of sizeof(void *) == %zu", align, sizeof(void *));
    case ENOMEM:
      rb_raise(rb_eRuntimeError, "Insufficient memory");
  }
  return mem;
}

#define ALIGNED_ALLOC(align, size) __aligned_alloc(align, size)

#define VEC3_NEW(addr)  CGLM_NEW(rb_cVec3,  vec3_size(),  addr)
#define VEC4_NEW(addr)  CGLM_NEW(rb_cVec4,  vec4_size(),  addr)
#define MAT4_NEW(addr)  CGLM_NEW(rb_cMat4,  mat4_size(),  addr)
#define MAT3_NEW(addr)  CGLM_NEW(rb_cMat3,  mat3_size(),  addr)
#define AABB_NEW(addr)  CGLM_NEW(rb_cAABB,  aabb_size(),  addr)
#define QUAT_NEW(addr)  CGLM_NEW(rb_cQuat,  quat_size(),  addr)
#define PLANE_NEW(addr) CGLM_NEW(rb_cPlane, plane_size(), addr);

#define ALLOC_VEC3  ALIGNED_ALLOC(VEC3_ALIGNMENT,  sizeof(vec3))
#define ALLOC_VEC4  ALIGNED_ALLOC(VEC4_ALIGNMENT,  sizeof(vec4))
#define ALLOC_AABB  ALIGNED_ALLOC(AABB_ALIGNMENT,  sizeof(aabb))
#define ALLOC_QUAT  ALIGNED_ALLOC(QUAT_ALIGNMENT,  sizeof(quat))
#define ALLOC_MAT4  ALIGNED_ALLOC(MAT4_ALIGNMENT,  sizeof(mat4))
#define ALLOC_MAT3  ALIGNED_ALLOC(MAT3_ALIGNMENT,  sizeof(mat3))
#define ALLOC_PLANE ALIGNED_ALLOC(PLANE_ALIGNMENT, sizeof(plane))

// #define VAL2ADDR(val) NUM2PTR(rb_funcall(rb_ivar_get(val, rb_intern("@addr")), rb_intern("to_i"), 0))

static inline void *VAL2ADDR(VALUE val, size_t min_size) {
  VALUE addr = rb_funcall(val, rb_intern("addr"), 0);
  VALUE size = rb_funcall(addr, rb_intern("size"), 0);
  if (min_size > NUM2SIZET(size))
    rb_raise(rb_eArgError, "memory store (size %zu) is not large enough to be converted into the requested type (size %zu)", NUM2SIZET(size), min_size);
  return NUM2PTR(rb_funcall(addr, rb_intern("to_i"), 0));
}

#define VAL2VEC3(val)    (*((vec3    *)(VAL2ADDR(val, sizeof(vec3)    ))))
#define VAL2VEC4(val)    (*((vec4    *)(VAL2ADDR(val, sizeof(vec4)    ))))
#define VAL2MAT4(val)    (*((mat4    *)(VAL2ADDR(val, sizeof(mat4)    ))))
#define VAL2MAT3(val)    (*((mat3    *)(VAL2ADDR(val, sizeof(mat3)    ))))
#define VAL2AABB(val)    (*((aabb    *)(VAL2ADDR(val, sizeof(aabb)    ))))
#define VAL2QUAT(val)    (*((quat    *)(VAL2ADDR(val, sizeof(quat)    ))))
#define VAL2FRUSTUM(val) (*((frustum *)(VAL2ADDR(val, sizeof(frustum) ))))
#define VAL2PLANE(val)   (*((plane   *)(VAL2ADDR(val, sizeof(plane)   ))))

#define NUM2FLT(val) ((float) NUM2DBL(val))

#endif /* CGLM_H */
