#include "rb_cglm.h"

/*
 * call-seq: affine_mul_rot(m[, dest]) => dest | new Mat4
 *
 * This is similar to #mul but specialized to affine transform.
 *
 * Right Matrix format should be:
 *
 *     R  R  R  0
 *     R  R  R  0
 *     R  R  R  0
 *     0  0  0  1
 *
 * This reduces some multiplications. It should be faster than #mul.
 * if you are not sure about matrix format then DON'T use this! use #mul.
 *
 * * `m` is the second affine Mat4 to multiply `self` against.
 * * `dest` is the out Mat4 to place the result in, and will be allocated if
 *   omitted.
 *
 */
VALUE rb_cglm_affine_mul_rot(int argc, VALUE *argv, VALUE self) {
  VALUE m_v, dest_v;
  rb_scan_args(argc, argv, "11", &m_v, &dest_v);
  if (NIL_P(dest_v)) dest_v = MAT4_NEW(ALLOC_MAT4);

  mat4 *m1 = NULL, *m2 = NULL, *dest = NULL;
  m1 = &VAL2MAT4(self);
  m2 = &VAL2MAT4(m_v);
  dest = &VAL2MAT4(dest_v);
  glm_mul_rot(*m1, *m2, *dest);
  return dest_v;
}

/*
 * call-seq: inv_tr() => self
 *
 * inverse orthonormal rotation + translation matrix (ridgid-body)
 *
 *     X = | R  T |   X' = | R' -R'T |
 *         | 0  1 |        | 0     1 |
 *
 */
VALUE rb_cglm_affine_inv_tr(VALUE mat) {
  mat4 *m = NULL;
  m = &VAL2MAT4(mat);
  glm_inv_tr(*m);
  return mat;
}

/*
 * call-seq: affine_mul(m[, dest]) => dest | new Mat4
 *
 * This is similar to #mul but specialized to affine transform.
 *
 * Right Matrix format should be:
 *
 *     R  R  R  X
 *     R  R  R  Y
 *     R  R  R  Z
 *     0  0  0  W
 *
 * This reduces some multiplications. It should be faster than #mul.
 * if you are not sure about matrix format then DON'T use this! use #mul.
 *
 * * `m` is the second affine Mat4 to multiply `self` against.
 * * `dest` is the out Mat4 to place the result in, and will be allocated if
 *   omitted.
 *
 */
VALUE rb_cglm_affine_mul(int argc, VALUE *argv, VALUE self) {
  VALUE m_v, dest_v;
  rb_scan_args(argc, argv, "11", &m_v, &dest_v);
  if (NIL_P(dest_v)) dest_v = MAT4_NEW(ALLOC_MAT4);
  mat4 *m1 = NULL, *m2 = NULL, *dest = NULL;
  m1 = &VAL2MAT4(self);
  m2 = &VAL2MAT4(m_v);
  dest = &VAL2MAT4(dest_v);
  glm_mul(*m1, *m2, *dest);
  return dest_v;
}

/* call-seq: translate(vec3[, dest]) => dest | new Mat4 */
VALUE rb_cglm_translate(int argc, VALUE *argv, VALUE self) {
  VALUE vec_v, dest_v;
  rb_scan_args(argc, argv, "11", &vec_v, &dest_v);
  if (NIL_P(dest_v)) dest_v = MAT4_NEW(ALLOC_MAT4);
  mat4 *m1 = NULL, *dest = NULL;
  vec3 *vec = NULL;
  m1 = &VAL2MAT4(self);
  vec = &VAL2VEC3(vec_v);
  dest = &VAL2MAT4(dest_v);
  glm_translate_to(*m1, *vec, *dest);
  return dest_v;
}

/* call-seq: translate!(vec3) => self */
VALUE rb_cglm_translate_self(VALUE self, VALUE vec_v) {
  mat4 *m1 = NULL;
  vec3 *vec = NULL;
  m1 = &VAL2MAT4(self);
  vec = &VAL2VEC3(vec_v);
  glm_translate(*m1, *vec);
  return self;
}

/* call-seq: translate_x!(float) => self */
VALUE rb_cglm_translate_x_self(VALUE self, VALUE flt) {
  mat4 *m1 = NULL;
  m1 = &VAL2MAT4(self);
  glm_translate_x(*m1, (float) NUM2DBL(flt));
  return self;
}

/* call-seq: mat4.translate_y!(float) => mat4 */
VALUE rb_cglm_translate_y_self(VALUE self, VALUE flt) {
  mat4 *m1 = NULL;
  m1 = &VAL2MAT4(self);
  glm_translate_y(*m1, (float) NUM2DBL(flt));
  return self;
}

/* call-seq: translate_z!(float) => self */
VALUE rb_cglm_translate_z_self(VALUE self, VALUE flt) {
  mat4 *m1 = NULL;
  m1 = &VAL2MAT4(self);
  glm_translate_z(*m1, (float) NUM2DBL(flt));
  return self;
}

/* call-seq: translate(vec3) => new Mat4 */
VALUE rb_cglm_translate_new(VALUE klass, VALUE vec_v) {
  VALUE dest = MAT4_NEW(ALLOC_MAT4);
  glm_translate_make(VAL2MAT4(dest), VAL2VEC3(vec_v));
  return dest;
}

/* call-seq: scale(vec3) => new Mat4 */
VALUE rb_cglm_scale_new(VALUE klass, VALUE vec_v) {
  VALUE dest = MAT4_NEW(ALLOC_MAT4);
  glm_scale_make(VAL2MAT4(dest), VAL2VEC3(vec_v));
  return dest;
}

/* call-seq: rotate(axis, angle) => new Mat4 */
VALUE rb_cglm_rotate_new(VALUE klass, VALUE axis, VALUE angle) {
  VALUE dest = MAT4_NEW(ALLOC_MAT4);
  glm_rotate_make(VAL2MAT4(dest), (float) NUM2DBL(angle), VAL2VEC3(axis));
  return dest;
}

/* call-seq: scale(vec3|float[, dest]) => dest | new Mat4 */
VALUE rb_cglm_scale(int argc, VALUE *argv, VALUE self) {
  VALUE factor, dest;
  rb_scan_args(argc, argv, "11", &factor, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);

  if (RB_FLOAT_TYPE_P(factor) || RB_INTEGER_TYPE_P(factor)) {
    memcpy(&VAL2MAT4(dest), &VAL2MAT4(self), sizeof(mat4));
    glm_scale_uni(VAL2MAT4(dest), (float) NUM2DBL(factor));
  } else {
    glm_scale_to(VAL2MAT4(self), VAL2VEC3(factor), VAL2MAT4(dest));
  }

  return dest;
}

/* call-seq: scale!(vec3|float) => self */
VALUE rb_cglm_scale_self(VALUE self, VALUE factor) {
  mat4 *m1 = NULL;
  m1 = &VAL2MAT4(self);
  if (RB_FLOAT_TYPE_P(factor) || RB_INTEGER_TYPE_P(factor)) {
    glm_scale_uni(*m1, (float) NUM2DBL(factor));
  } else {
    vec3 *vec = NULL;
    vec = &VAL2VEC3(factor);
    glm_scale(*m1, *vec);
  }
  return self;
}

/* call-seq: rotate_x(float[, dest]) => dest | new Mat4 */
VALUE rb_cglm_rotate_x(int argc, VALUE *argv, VALUE self) {
  VALUE angle, dest;
  rb_scan_args(argc, argv, "11", &angle, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  mat4 *m1, *m2;
  m1 = &VAL2MAT4(self);
  m2 = &VAL2MAT4(dest);
  glm_rotate_x(*m1, (float) NUM2DBL(angle), *m2);
  return dest;
}

/* call-seq: rotate_y(float[, dest]) => dest | new Mat4 */
VALUE rb_cglm_rotate_y(int argc, VALUE *argv, VALUE self) {
  VALUE angle, dest;
  rb_scan_args(argc, argv, "11", &angle, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  mat4 *m1, *m2;
  m1 = &VAL2MAT4(self);
  m2 = &VAL2MAT4(dest);
  glm_rotate_y(*m1, (float) NUM2DBL(angle), *m2);
  return dest;
}

/* call-seq: rotate_z(float[, dest]) => dest | new Mat4 */
VALUE rb_cglm_rotate_z(int argc, VALUE *argv, VALUE self) {
  VALUE angle, dest;
  rb_scan_args(argc, argv, "11", &angle, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  mat4 *m1, *m2;
  m1 = &VAL2MAT4(self);
  m2 = &VAL2MAT4(dest);
  glm_rotate_z(*m1, (float) NUM2DBL(angle), *m2);
  return dest;
}

/* call-seq: rotate!(axis, angle) => self */
VALUE rb_cglm_rotate_self(VALUE self, VALUE axis, VALUE angle) {
  mat4 *mat;
  vec3 *vec;
  mat = &VAL2MAT4(self);
  vec = &VAL2VEC3(axis);
  glm_rotate(*mat, (float) NUM2DBL(angle), *vec);
  return self;
}

/* call-seq: rotate_at!(pivot_point, axis, angle) => self */
VALUE rb_cglm_rotate_self_at(VALUE self, VALUE pivot, VALUE axis, VALUE angle) {
  mat4 *m;
  vec3 *v1, *v2;
  m = &VAL2MAT4(self);
  v1 = &VAL2VEC3(pivot);
  v2 = &VAL2VEC3(axis);
  glm_rotate_at(*m, *v1, (float) NUM2DBL(angle), *v2);
  return self;
}

/* call-seq: axis_angle_rotate_at(pivot_point, axis, angle) => new Mat4 */
VALUE rb_cglm_rotate_at_new(VALUE klass, VALUE pivot, VALUE axis, VALUE angle) {
  VALUE self = MAT4_NEW(ALLOC_MAT4);
  mat4 *m;
  vec3 *v1, *v2;
  m = &VAL2MAT4(self);
  v1 = &VAL2VEC3(pivot);
  v2 = &VAL2VEC3(axis);
  glm_rotate_atm(*m, *v1, (float) NUM2DBL(angle), *v2);
  return self;
}

/* call-seq: decompose_scale(vec3) => vec3 */
VALUE rb_cglm_decompose_scale(VALUE self, VALUE out) {
  mat4 *m;
  vec3 *v;
  m = &VAL2MAT4(self);
  v = &VAL2VEC3(self);
  glm_decompose_scalev(*m, *v);
  return out;
}

/* call-seq: uniform_scale? => true|false */
VALUE rb_cglm_is_uniform_scale(VALUE self) {
  mat4 *m;
  m = &VAL2MAT4(self);
  return glm_uniscaled(*m) ? Qtrue : Qfalse;
}

/* call-seq: decompose_rs(r, s) => self
 * 
 * Decomposes `self` into a rotation Mat4 `r` and scale Vec3 `s`.
 */
VALUE rb_cglm_decompose_rs(VALUE self, VALUE rot, VALUE scale) {
  mat4 *m, *r;
  vec3 *s;
  m = &VAL2MAT4(self);
  r = &VAL2MAT4(rot);
  s = &VAL2VEC3(scale);
  glm_decompose_rs(*m, *r, *s);
  return self;
}

/* call-seq: decompose(t, r, s) => self
 * 
 * Decomposes `self` into a translation Vec4 `t`, rotation Mat4 `r` and scale
 * Vec3 `s`.
 */
VALUE rb_cglm_decompose(VALUE self, VALUE trans, VALUE rot, VALUE scale) {
  mat4 *m, *r;
  vec3 *s;
  vec4 *t;
  m = &VAL2MAT4(self);
  t = &VAL2VEC4(trans);
  r = &VAL2MAT4(rot);
  s = &VAL2VEC3(scale);
  glm_decompose(*m, *t, *r, *s);
  return self;
}

void Init_cglm_affine() {
  rb_define_method(rb_cMat4, "affine_inv_tr",  rb_cglm_affine_inv_tr,    0);
  rb_define_method(rb_cMat4, "affine_mul_rot", rb_cglm_affine_mul_rot,  -1);
  rb_define_method(rb_cMat4, "affine_mul",     rb_cglm_affine_mul,      -1);
  rb_define_method(rb_cMat4, "translate_to",   rb_cglm_translate,       -1);
  rb_define_method(rb_cMat4, "translate!",     rb_cglm_translate_self,   1);
  rb_define_method(rb_cMat4, "translate_x!",   rb_cglm_translate_x_self, 1);
  rb_define_method(rb_cMat4, "translate_y!",   rb_cglm_translate_y_self, 1);
  rb_define_method(rb_cMat4, "translate_z!",   rb_cglm_translate_z_self, 1);
  rb_define_method(rb_cMat4, "scale",          rb_cglm_scale,           -1);
  rb_define_method(rb_cMat4, "scale!",         rb_cglm_scale_self,       1);
  rb_define_method(rb_cMat4, "rotate_x",       rb_cglm_rotate_x,        -1);
  rb_define_method(rb_cMat4, "rotate_y",       rb_cglm_rotate_y,        -1);
  rb_define_method(rb_cMat4, "rotate_z",       rb_cglm_rotate_z,        -1);
  rb_define_method(rb_cMat4, "rotate!",        rb_cglm_rotate_self,      2);
  rb_define_method(rb_cMat4, "rotate_at!",     rb_cglm_rotate_self_at,   3);
  rb_define_method(rb_cMat4, "decompose_scale",rb_cglm_decompose_scale,  1);
  rb_define_method(rb_cMat4, "uniform_scale?", rb_cglm_is_uniform_scale, 0);
  rb_define_method(rb_cMat4, "decompose_rs",   rb_cglm_decompose_rs,     2);
  rb_define_method(rb_cMat4, "decompose",      rb_cglm_decompose,        3);

  rb_define_singleton_method(rb_cMat4, "translate",            rb_cglm_translate_new, 1);
  rb_define_singleton_method(rb_cMat4, "scale",                rb_cglm_scale_new,     1);
  rb_define_singleton_method(rb_cMat4, "rotate",               rb_cglm_rotate_new,    2);
  rb_define_singleton_method(rb_cMat4, "axis_angle_rotate_at", rb_cglm_rotate_at_new, 3);
}
