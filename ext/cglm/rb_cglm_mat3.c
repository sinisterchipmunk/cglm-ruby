#include "rb_cglm.h"

/* call-seq: identity([dest]) => dest | new Mat3
 *
 * Sets `dest` to the identity if provided. If omitted, a new Mat4 is created
 * and set to the identity. `dest` or the new Mat3 is returned.
 */
VALUE rb_cglm_mat3_new_identity(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_mat3_identity(VAL2MAT3(dest));
  return dest;
}

/* call-seq: mul_mat3(other[, dest]) => dest | new Mat3
 *
 * Multiplies this Mat3 with `other`, returning the result.
 */
VALUE rb_cglm_mat3_mul_mat3(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_mat3_mul(VAL2MAT3(self), VAL2MAT3(other), VAL2MAT3(dest));
  return dest;
}

/* call-seq: mul_vec3(other[, dest]) => dest | new Vec3
 *
 * Multiplies this Vec3 with `other`, returning the result.
 */
VALUE rb_cglm_mat3_mul_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_mat3_mulv(VAL2MAT3(self), VAL2VEC3(other), VAL2VEC3(dest));
  return dest;
}

/* call-seq: transpose([dest]) => dest | new Mat3
 *
 * Transposes this matrix and places it into `dest`. If `dest` is omitted, a
 * new Mat3 will be allocated.
 */
VALUE rb_cglm_mat3_transpose(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_mat3_transpose_to(VAL2MAT3(self), VAL2MAT3(dest));
  return dest;
}

/* call-seq: transpose! => self
 *
 * Transposes this matrix in-place and returns `self`.
 */
VALUE rb_cglm_mat3_transpose_self(VALUE self) {
  glm_mat3_transpose(VAL2MAT3(self));
  return self;
}

/* call-seq: to_quat([dest]) => dest | new Quat
 *
 * Converts `self` to a Quat. If `dest` is omitted, a new Quat is created.
 */
VALUE rb_cglm_mat3_to_quat(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_mat3_quat(VAL2MAT3(self), VAL2QUAT(dest));
  return dest;
}

/* call-seq: mul_scalar(scalar[, dest]) => dest | new Mat3
 *
 * Multiplies each element in this matrix by the specified scalar amount.
 * Places the result in `dest` and returns it, creating a new Mat3 if `dest`
 * is omitted.
 */
VALUE rb_cglm_mat3_mul_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE scalar, dest;
  rb_scan_args(argc, argv, "11", &scalar, &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_mat3_scale(VAL2MAT3(dest), NUM2FLT(scalar));
  return dest;
}

/* call-seq: mul_scalar!(scalar) => self
 *
 * Multiplies each element in this matrix by the specified scalar amount,
 * modifying `self` in-place and returning it.
 */
VALUE rb_cglm_mat3_mul_scalar_self(VALUE self, VALUE scalar) {
  glm_mat3_scale(VAL2MAT3(self), NUM2FLT(scalar));
  return self;
}

VALUE rb_cglm_mat3_determinant(VALUE self) {
  return glm_mat3_det(VAL2MAT3(self));
}

/* call-seq: inverse([dest]) => dest | new Mat3
 *
 * Places the inverse of `self` into `dest`, creating a new Mat3 if `dest` is
 * omitted. Returns `dest`.
 */
VALUE rb_cglm_mat3_inverse(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_mat3_inv(VAL2MAT3(self), VAL2MAT3(dest));
  return dest;
}

/* call-seq: invert! => self
 *
 * Calcaultes the inverse of `self`, modifies `self` in-place, and returns
 * `self`.
 */
VALUE rb_cglm_mat3_inverse_self(VALUE self) {
  glm_mat3_inv(VAL2MAT3(self), VAL2MAT3(self));
  return self;
}

/* call-seq: swap_col!(col1, col2) => self
 *
 * Swaps two matrix columns and returns `self`.
 */
VALUE rb_cglm_mat3_swap_col_self(VALUE self, VALUE col1, VALUE col2) {
  glm_mat3_swap_col(VAL2MAT3(self), NUM2INT(col1), NUM2INT(col2));
  return self;
}

/* call-seq: swap_row!(row1, row2) => self
 *
 * Swaps two matrix rows and returns `self`.
 */
VALUE rb_cglm_mat3_swap_row_self(VALUE self, VALUE row1, VALUE row2) {
  glm_mat3_swap_row(VAL2MAT3(self), NUM2INT(row1), NUM2INT(row2));
  return self;
}

VALUE rb_cglm_mat3_aref(VALUE self, VALUE index) {
  CHECK_RANGE(index, 0, 2);
  float *addr = (float *) VAL2MAT3(self);
  return VEC3_NEW(addr + (NUM2INT(index) * 3));
}

VALUE rb_cglm_mat3_aset(VALUE self, VALUE index, VALUE val) {
  CHECK_RANGE(index, 0, 2);
  if (rb_funcall(val, rb_intern("kind_of?"), 1, rb_cVec4))
    memcpy(&(VAL2MAT4(self)[NUM2INT(index)]), &VAL2VEC4(val), sizeof(vec3));
  else if (rb_funcall(val, rb_intern("kind_of?"), 1, rb_cVec3))
    memcpy(&(VAL2MAT4(self)[NUM2INT(index)]), &VAL2VEC3(val), sizeof(vec3));
  else {
    VALUE row = rb_cglm_mat3_aref(self, index);
    for (int i = 0; i < 3; i++) {
      VALUE v = rb_funcall(val, rb_intern("[]"), 1, INT2NUM(i));
      if (!NIL_P(v)) {
        rb_funcall(row, rb_intern("[]="), 2, INT2NUM(i), v);
      }
    }
  }
  return self;
}

VALUE rb_cglm_mat3_to_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  if (argc == 0) dest = MAT4_NEW(ALLOC_MAT4);
  dest = argv[0];
  glm_mat4_ins3(VAL2MAT3(self), VAL2MAT4(dest));
  return dest;
}

VALUE rb_cglm_mat3_size_bytes(VALUE klass) { return SIZET2NUM(mat3_size()); }

VALUE rb_cglm_mat3_alignment_bytes(VALUE klass) { return SIZET2NUM(MAT3_ALIGNMENT); }

VALUE rb_cglm_mat3_equal(VALUE self, VALUE other) {
  if (memcmp(&VAL2MAT3(self), &VAL2MAT3(other), sizeof(mat3))) return Qfalse;
  return Qtrue;
}

/* call-seq: a =~ b => true|false
 *
 * Returns true if each member of `a` is very close to, but not necessarily
 * exactly equal to, each corresponding member of `b`. This is useful in many
 * circumstances because imprecision introduced by floating point calculations
 * can lead to two expressions which are otherwise mathematically equivalent
 * returning false.
 */
VALUE rb_cglm_mat3_equalish(int argc, VALUE *argv, VALUE self) {
  VALUE other, epsilon;
  float feps = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &other, &epsilon);
  if (!NIL_P(epsilon)) feps = NUM2FLT(epsilon);
  mat3 *a = &VAL2MAT3(self);
  mat3 *b = &VAL2MAT3(other);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (fabsf((*a)[i][j] - (*b)[i][j]) > feps)
        return Qfalse;
    }
  }
  return Qtrue;
}

/* call-seq: random([dest]) => dest | new Mat3
 *
 * Fills `dest` or a new Mat3 with a random rotation about a random axis with
 * a random angle, and returns it.
 */
VALUE rb_cglm_mat3_new_random(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);

  mat4 m4;
  glm_rotate_make(m4, drand48(), (vec3){drand48(), drand48(), drand48()});
  glm_mat4_pick3(m4, VAL2MAT3(dest));

  return dest;
}

void Init_cglm_mat3() {
  rb_define_method(rb_cMat3, "equalish",    rb_cglm_mat3_equalish,       -1);
  rb_define_method(rb_cMat3, "==",          rb_cglm_mat3_equal,           1);
  rb_define_method(rb_cMat3, "[]",          rb_cglm_mat3_aref,            1);
  rb_define_method(rb_cMat3, "[]=",         rb_cglm_mat3_aset,            2);
  rb_define_method(rb_cMat3, "mul_mat3",    rb_cglm_mat3_mul_mat3,       -1);
  rb_define_method(rb_cMat3, "mul_vec3",    rb_cglm_mat3_mul_vec3,       -1);
  rb_define_method(rb_cMat3, "mul_scalar",  rb_cglm_mat3_mul_scalar,     -1);
  rb_define_method(rb_cMat3, "mul_scalar!", rb_cglm_mat3_mul_scalar_self, 1);
  rb_define_method(rb_cMat3, "transpose",   rb_cglm_mat3_transpose,      -1);
  rb_define_method(rb_cMat3, "transpose!",  rb_cglm_mat3_transpose_self,  0);
  rb_define_method(rb_cMat3, "to_quat",     rb_cglm_mat3_to_quat,        -1);
  rb_define_method(rb_cMat3, "determinant", rb_cglm_mat3_determinant,     0);
  rb_define_method(rb_cMat3, "invert",      rb_cglm_mat3_inverse,        -1);
  rb_define_method(rb_cMat3, "invert!",     rb_cglm_mat3_inverse_self,    0);
  rb_define_method(rb_cMat3, "swap_col!",   rb_cglm_mat3_swap_col_self,   2);
  rb_define_method(rb_cMat3, "swap_row!",   rb_cglm_mat3_swap_row_self,   2);
  rb_define_method(rb_cMat3, "to_mat4",     rb_cglm_mat3_to_mat4,        -1);

  rb_define_alias(rb_cMat3, "=~",   "equalish");
  rb_define_alias(rb_cMat3, "det",  "determinant");

  rb_define_singleton_method(rb_cMat3, "identity",  rb_cglm_mat3_new_identity,   -1);
  rb_define_singleton_method(rb_cMat3, "size",      rb_cglm_mat3_size_bytes,      0);
  rb_define_singleton_method(rb_cMat3, "alignment", rb_cglm_mat3_alignment_bytes, 0);
  rb_define_singleton_method(rb_cMat3, "random",    rb_cglm_mat3_new_random,     -1);
  rb_define_singleton_method(rb_cMat3, "rand",      rb_cglm_mat3_new_random,     -1);
}
