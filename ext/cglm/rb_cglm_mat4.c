#include "rb_cglm.h"

/* call-seq: identity([dest]) => dest | new Mat4
 *
 * Sets `dest` to the identity if provided. If omitted, a new Mat4 is created
 * and set to the identity. `dest` or the new Mat4 is returned.
 */
VALUE rb_cglm_mat4_new_identity(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_mat4_identity(VAL2MAT4(dest));
  return dest;
}

/* call-seq: quat_rotate_at(quat, pivot_point[, dest]) => dest | new Mat4
 *
 * Creates a new transformation matrix using the quaternion at the pivot
 * point. Places the result into `dest`, or creates a new Mat4 if `dest` is
 * omitted. Returns `dest`.
 */
VALUE rb_cglm_mat4_new_rotate_at(int argc, VALUE *argv, VALUE self) {
  VALUE q, pivot, dest;
  rb_scan_args(argc, argv, "21", &q, &pivot, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_quat_rotate_atm(VAL2MAT4(dest), VAL2QUAT(q), VAL2VEC3(pivot));
  return dest;
}

VALUE rb_cglm_mat4_aref(VALUE self, VALUE index) {
  CHECK_RANGE(index, 0, 3);
  float *addr = (float *) VAL2MAT4(self);
  return VEC4_NEW(addr + (NUM2INT(index) * 4));
}

VALUE rb_cglm_mat4_aset(VALUE self, VALUE index, VALUE val) {
  CHECK_RANGE(index, 0, 3);
  if (rb_funcall(val, rb_intern("kind_of?"), 1, rb_cVec4))
    memcpy(&(VAL2MAT4(self)[NUM2INT(index)]), &VAL2VEC4(val), sizeof(vec4));
  else if (rb_funcall(val, rb_intern("kind_of?"), 1, rb_cVec3))
    memcpy(&(VAL2MAT4(self)[NUM2INT(index)]), &VAL2VEC3(val), sizeof(vec3));
  else {
    VALUE row = rb_cglm_mat4_aref(self, index);
    for (int i = 0; i < 4; i++) {
      VALUE v = rb_funcall(val, rb_intern("[]"), 1, INT2NUM(i));
      if (!NIL_P(v)) {
        rb_funcall(row, rb_intern("[]="), 2, INT2NUM(i), v);
      }
    }
  }
  return self;
}

VALUE rb_cglm_mat4_to_mat3(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  if (argc == 0) dest = MAT3_NEW(ALLOC_MAT3);
  else dest = argv[0];
  glm_mat4_pick3(VAL2MAT4(self), VAL2MAT3(dest));
  return dest;
}

VALUE rb_cglm_mat4_to_transposed_mat3(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  if (argc == 0) dest = MAT3_NEW(ALLOC_MAT3);
  dest = argv[0];
  glm_mat4_pick3t(VAL2MAT4(self), VAL2MAT3(dest));
  return dest;
}

VALUE rb_cglm_mat4_mul_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_mat4_mul(VAL2MAT4(self), VAL2MAT4(other), VAL2MAT4(dest));
  return dest;
}

VALUE rb_cglm_mat4_mul_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_mat4_mulv(VAL2MAT4(self), VAL2VEC4(other), VAL2VEC4(dest));
  return dest;
}

VALUE rb_cglm_mat4_mul_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE other, last, dest;
  rb_scan_args(argc, argv, "12", &other, &last, &dest);
  if (NIL_P(last)) last = DBL2NUM(1.0);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_mat4_mulv3(VAL2MAT4(self), VAL2VEC3(other), NUM2FLT(last), VAL2VEC3(dest));
  return dest;
}

VALUE rb_cglm_mat4_to_quat(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_mat4_quat(VAL2MAT4(self), VAL2QUAT(dest));
  return dest;
}

VALUE rb_cglm_mat4_transpose(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_mat4_transpose_to(VAL2MAT4(self), VAL2MAT4(dest));
  return dest;
}

VALUE rb_cglm_mat4_transpose_self(VALUE self) {
  glm_mat4_transpose(VAL2MAT4(self));
  return self;
}

/* call-seq: mul_scalar(scalar[, dest]) => dest | new Mat3
 *
 * Multiplies each element in this matrix by the specified scalar amount.
 * Places the result in `dest` and returns it, creating a new Mat4 if `dest`
 * is omitted.
 */
VALUE rb_cglm_mat4_mul_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE scalar, dest;
  rb_scan_args(argc, argv, "11", &scalar, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  memcpy(&VAL2MAT4(self), &VAL2MAT4(dest), sizeof(mat4));
  glm_mat4_scale(VAL2MAT4(dest), NUM2FLT(scalar));
  return dest;
}

/* call-seq: mul_scalar!(scalar) => self
 *
 * Multiplies each element in this matrix by the specified scalar amount,
 * modifying `self` in-place and returning it.
 */
VALUE rb_cglm_mat4_mul_scalar_self(VALUE self, VALUE scalar) {
  glm_mat4_scale(VAL2MAT4(self), NUM2FLT(scalar));
  return self;
}

/* call-seq: determinant => Numeric
 */
VALUE rb_cglm_mat4_determinant(VALUE self) {
  return DBL2NUM(glm_mat4_det(VAL2MAT4(self)));
}

/* call-seq: invert([dest]) => dest | new Mat4
 *
 * Computes the inverse of this matrix and stores it in `dest`, creating a
 * new Mat4 if `dest` is omitted. Returns `dest`.
 */
VALUE rb_cglm_mat4_invert(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_mat4_inv(VAL2MAT4(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: invert! => self
 *
 * Computes the inverse of this matrix in-place and returns `self`.
 */
VALUE rb_cglm_mat4_invert_self(int argc, VALUE *argv, VALUE self) {
  glm_mat4_inv(VAL2MAT4(self), VAL2MAT4(self));
  return self;
}

/* call-seq: invert_fast([dest]) => dest | new Mat4
 *
 * Computes the inverse of this matrix and stores it in `dest`, creating a
 * new Mat4 if `dest` is omitted. Returns `dest`.
 *
 * * NOTE: This method uses reciprocal approximation without extra corrections,
 *   e.g Newton-Raphson. This should work faster than normal, but will be less
 *   precise.
 */
VALUE rb_cglm_mat4_invert_fast(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_mat4_inv_fast(VAL2MAT4(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: invert_fast!([dest]) => dest | new Mat4
 *
 * Computes the inverse of this matrix in-place and returns `self`.
 *
 * * NOTE: This method uses reciprocal approximation without extra corrections,
 *   e.g Newton-Raphson. This should work faster than normal, but will be less
 *   precise.
 */
VALUE rb_cglm_mat4_invert_fast_self(int argc, VALUE *argv, VALUE self) {
  glm_mat4_inv_fast(VAL2MAT4(self), VAL2MAT4(self));
  return self;
}

/* call-seq: swap_col!(col1, col2) => self
 *
 * Swaps two matrix columns and returns `self`.
 */
VALUE rb_cglm_mat4_swap_col_self(VALUE self, VALUE col1, VALUE col2) {
  glm_mat4_swap_col(VAL2MAT4(self), NUM2INT(col1), NUM2INT(col2));
  return self;
}

/* call-seq: swap_row!(row1, row2) => self
 *
 * Swaps two matrix rows and returns `self`.
 */
VALUE rb_cglm_mat4_swap_row_self(VALUE self, VALUE row1, VALUE row2) {
  glm_mat4_swap_row(VAL2MAT4(self), NUM2INT(row1), NUM2INT(row2));
  return self;
}

VALUE rb_cglm_mat4_size_bytes(VALUE klass) { return SIZET2NUM(mat4_size()); }

VALUE rb_cglm_mat4_alignment_bytes(VALUE klass) { return SIZET2NUM(MAT4_ALIGNMENT); }

VALUE rb_cglm_mat4_equal(VALUE self, VALUE other) {
  if (memcmp(&VAL2MAT4(self), &VAL2MAT4(other), sizeof(mat4))) return Qfalse;
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
VALUE rb_cglm_mat4_equalish(int argc, VALUE *argv, VALUE self) {
  VALUE other, epsilon;
  float feps = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &other, &epsilon);
  if (!NIL_P(epsilon)) feps = NUM2FLT(epsilon);
  mat4 *a = &VAL2MAT4(self);
  mat4 *b = &VAL2MAT4(other);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fabsf((*a)[i][j] - (*b)[i][j]) > feps)
        return Qfalse;
    }
  }
  return Qtrue;
}

/* call-seq: random([dest]) => dest | new Mat4
 *
 * Fills `dest` or a new Mat4 with a random translation and rotation, and
 * returns it.
 */
VALUE rb_cglm_mat4_new_random(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);

  glm_mat4_copy(GLM_MAT4_IDENTITY, VAL2MAT4(dest));
  
  /* random position */
  VAL2MAT4(dest)[3][0] = drand48();
  VAL2MAT4(dest)[3][1] = drand48();
  VAL2MAT4(dest)[3][2] = drand48();
  
  /* random rotatation around random axis with random angle */
  glm_rotate(VAL2MAT4(dest), drand48(), (vec3){drand48(), drand48(), drand48()});
  
  /* random scale */
  /* glm_scale(dest, (vec3){drand48(), drand48(), drand48()}); */

  return dest;
}

void Init_cglm_mat4() {
  rb_define_method(rb_cMat4, "equalish",           rb_cglm_mat4_equalish,           -1);
  rb_define_method(rb_cMat4, "==",                 rb_cglm_mat4_equal,               1);
  rb_define_method(rb_cMat4, "[]",                 rb_cglm_mat4_aref,                1);
  rb_define_method(rb_cMat4, "[]=",                rb_cglm_mat4_aset,                2);
  rb_define_method(rb_cMat4, "to_mat3",            rb_cglm_mat4_to_mat3,            -1);
  rb_define_method(rb_cMat4, "to_transposed_mat3", rb_cglm_mat4_to_transposed_mat3, -1);
  rb_define_method(rb_cMat4, "to_quat",            rb_cglm_mat4_to_quat,            -1);
  rb_define_method(rb_cMat4, "mul_mat4",           rb_cglm_mat4_mul_mat4,           -1);
  rb_define_method(rb_cMat4, "mul_vec4",           rb_cglm_mat4_mul_vec4,           -1);
  rb_define_method(rb_cMat4, "mul_vec3",           rb_cglm_mat4_mul_vec3,           -1);
  rb_define_method(rb_cMat4, "mul_scalar",         rb_cglm_mat4_mul_scalar,         -1);
  rb_define_method(rb_cMat4, "mul_scalar!",        rb_cglm_mat4_mul_scalar_self,     0);
  rb_define_method(rb_cMat4, "transpose",          rb_cglm_mat4_transpose,          -1);
  rb_define_method(rb_cMat4, "transpose!",         rb_cglm_mat4_transpose_self,      0);
  rb_define_method(rb_cMat4, "determinant",        rb_cglm_mat4_determinant,         0);
  rb_define_method(rb_cMat4, "invert",             rb_cglm_mat4_invert,             -1);
  rb_define_method(rb_cMat4, "invert_fast",        rb_cglm_mat4_invert_fast,        -1);
  rb_define_method(rb_cMat4, "invert!",            rb_cglm_mat4_invert_self,         0);
  rb_define_method(rb_cMat4, "invert_fast!",       rb_cglm_mat4_invert_fast_self,    0);
  rb_define_method(rb_cMat4, "swap_col!",          rb_cglm_mat4_swap_col_self,       2);
  rb_define_method(rb_cMat4, "swap_row!",          rb_cglm_mat4_swap_row_self,       2);

  rb_define_alias(rb_cMat4, "det",  "determinant");
  rb_define_alias(rb_cMat4, "=~",   "equalish");

  rb_define_singleton_method(rb_cMat4, "random",         rb_cglm_mat4_new_random,     -1);
  rb_define_singleton_method(rb_cMat4, "rand",           rb_cglm_mat4_new_random,     -1);
  rb_define_singleton_method(rb_cMat4, "identity",       rb_cglm_mat4_new_identity,   -1);
  rb_define_singleton_method(rb_cMat4, "quat_rotate_at", rb_cglm_mat4_new_rotate_at,  -1);
  rb_define_singleton_method(rb_cMat4, "size",           rb_cglm_mat4_size_bytes,      0);
  rb_define_singleton_method(rb_cMat4, "alignment",      rb_cglm_mat4_alignment_bytes, 0);
}
