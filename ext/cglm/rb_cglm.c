#include "rb_cglm.h"

VALUE rb_cFiddle     = Qnil,
      rb_cPointer    = Qnil,
      rb_mCGLM       = Qnil,
      rb_cCGLMBase   = Qnil,
      rb_cVectorType = Qnil,
      rb_cMat3       = Qnil,
      rb_cMat4       = Qnil,
      rb_cVec3       = Qnil,
      rb_cVec4       = Qnil,
      rb_cAABB       = Qnil,
      rb_mEuler      = Qnil,
      rb_cQuat       = Qnil,
      rb_cFrustum    = Qnil,
      rb_cSphere     = Qnil;

VALUE rb_cglm_alloc_type(VALUE self, VALUE klass) {
  VALUE rsize  = rb_funcall(klass, rb_intern("size"), 0);
  VALUE ralign = rb_funcall(klass, rb_intern("alignment"), 0);
  size_t size  = NUM2SIZET(rsize);
  size_t align = NUM2SIZET(ralign);
  void *addr = ALIGNED_ALLOC(align, size);
  if (!addr)
    rb_raise(rb_eRuntimeError, "could not allocate %zu bytes with %zu alignment", size, align);
  return rb_funcall(rb_cPointer, rb_intern("new"), 2, PTR2NUM(addr), rsize);
}

void Init_cglm(void) {
  rb_cFiddle     = rb_const_get(rb_cObject, rb_intern("Fiddle"));
  rb_cPointer    = rb_const_get(rb_cFiddle, rb_intern("Pointer"));
  rb_mCGLM       = rb_define_module("CGLM");
  rb_mEuler      = rb_define_module_under(rb_mCGLM, "Euler");
  rb_cCGLMBase   = rb_define_class_under(rb_mCGLM, "Base",       rb_cObject);
  rb_cMat3       = rb_define_class_under(rb_mCGLM, "Mat3",       rb_cCGLMBase);
  rb_cMat4       = rb_define_class_under(rb_mCGLM, "Mat4",       rb_cCGLMBase);
  rb_cCGLMBase   = rb_define_class_under(rb_mCGLM, "Base",       rb_cObject);
  rb_cVectorType = rb_define_class_under(rb_mCGLM, "VectorType", rb_cCGLMBase);
  rb_cAABB       = rb_define_class_under(rb_mCGLM, "AABB",       rb_cCGLMBase);
  rb_cVec3       = rb_define_class_under(rb_mCGLM, "Vec3",       rb_cVectorType);
  rb_cVec4       = rb_define_class_under(rb_mCGLM, "Vec4",       rb_cVectorType);
  rb_cFrustum    = rb_define_class_under(rb_mCGLM, "Frustum",    rb_cObject);
  rb_cSphere     = rb_define_class_under(rb_mCGLM, "Sphere",     rb_cVec4);
  rb_cQuat       = rb_define_class_under(rb_mCGLM, "Quat",       rb_cVec4);

  rb_define_const(rb_mCGLM, "E" ,              DBL2NUM(GLM_E));
  rb_define_const(rb_mCGLM, "LOG2E",           DBL2NUM(GLM_LOG2E));
  rb_define_const(rb_mCGLM, "LOG10E",          DBL2NUM(GLM_LOG10E));
  rb_define_const(rb_mCGLM, "LN2",             DBL2NUM(GLM_LN2));
  rb_define_const(rb_mCGLM, "LN10",            DBL2NUM(GLM_LN10));
  rb_define_const(rb_mCGLM, "PI",              DBL2NUM(GLM_PI));
  rb_define_const(rb_mCGLM, "PI_2",            DBL2NUM(GLM_PI_2));
  rb_define_const(rb_mCGLM, "PI_4",            DBL2NUM(GLM_PI_4));
  rb_define_const(rb_mCGLM, "ONE_OVER_PI",     DBL2NUM(GLM_1_PI));
  rb_define_const(rb_mCGLM, "TWO_OVER_PI",     DBL2NUM(GLM_2_PI));
  rb_define_const(rb_mCGLM, "TWO_OVER_SQRTPI", DBL2NUM(GLM_2_SQRTPI));
  rb_define_const(rb_mCGLM, "SQRT2",           DBL2NUM(GLM_SQRT2));
  rb_define_const(rb_mCGLM, "SQRT1_2",         DBL2NUM(GLM_SQRT1_2));

  rb_define_singleton_method(rb_mCGLM, "alloc", rb_cglm_alloc_type, 1);

  Init_cglm_affine();
  Init_cglm_box();
  Init_cglm_cam();
  Init_cglm_color();
  Init_cglm_ease();
  Init_cglm_euler();
  Init_cglm_frustum();
  Init_cglm_mat3();
  Init_cglm_mat4();
  Init_cglm_plane();
  Init_cglm_project();
  Init_cglm_quat();
  Init_cglm_sphere();
  Init_cglm_vec3();
  Init_cglm_vec4();
}
