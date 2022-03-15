#include "rb_cglm.h"

/* call-seq: identity([dest]) => dest | new Quat */
VALUE rb_cglm_quat_new_identity(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_identity(VAL2QUAT(dest));
  return dest;
}

/* call-seq: axis_angle(axis, angle[, dest]) => dest | new Quat */
VALUE rb_cglm_quat_new_axis_angle(int argc, VALUE *argv, VALUE self) {
  VALUE axis, angle, dest;
  rb_scan_args(argc, argv, "21", &axis, &angle, &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quatv(VAL2QUAT(dest), NUM2FLT(angle), VAL2VEC3(axis));
  return dest;
}

/* call-seq: copy_to(dest) => dest */
VALUE rb_cglm_quat_copy_to(VALUE self, VALUE dest) {
  glm_quat_copy(VAL2QUAT(self), VAL2QUAT(dest));
  return dest;
}

/* call-seq: normalize([dest]) => dest */
VALUE rb_cglm_quat_normalize(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_normalize_to(VAL2QUAT(self), VAL2QUAT(dest));
  return dest;
}

/* call-seq: normalize! => self */
VALUE rb_cglm_quat_normalize_self(VALUE self) {
  glm_quat_normalize(VAL2QUAT(self));
  return self;
}

/* call-seq: conjugate([dest]) => dest | new Quat */
VALUE rb_cglm_quat_conjugate(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_conjugate(VAL2QUAT(self), VAL2QUAT(dest));
  return dest;
}

/* call-seq: invert([dest]) => dest | new Quat */
VALUE rb_cglm_quat_invert(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_inv(VAL2QUAT(self), VAL2QUAT(dest));
  return dest;
}

/* call-seq: invert! => self */
VALUE rb_cglm_quat_invert_self(VALUE self) {
  glm_quat_inv(VAL2QUAT(self), VAL2QUAT(self));
  return self;
}

/* call-seq: real => Numeric
 *
 * Returns the real part of the quaternion.
 */
VALUE rb_cglm_quat_real(VALUE self) {
  return DBL2NUM(glm_quat_real(VAL2QUAT(self)));
}

/* call-seq: imag([dest]) => dest | new Vec3
 *
 * Returns the imaginary part of the quaternion in `dest`.
 */
VALUE rb_cglm_quat_imag(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_quat_imag(VAL2QUAT(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: imagn([dest]) => dest | new Vec3
 *
 * Returns the imaginary part of the quaternion in `dest`, normalized.
 */
VALUE rb_cglm_quat_imagn(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_quat_imagn(VAL2QUAT(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: imaglen => Numeric
 *
 * Returns the length of the imaginary part of the quaternion.
 */
VALUE rb_cglm_quat_imaglen(VALUE self) {
  return DBL2NUM(glm_quat_imaglen(VAL2QUAT(self)));
}

/* call-seq: angle => Numeric
 *
 * Returns the angle of the quaternion.
 */
VALUE rb_cglm_quat_angle(VALUE self) {
  return DBL2NUM(glm_quat_angle(VAL2QUAT(self)));
}

/* call-seq: axis([dest]) => dest | new Vec3
 *
 * Returns the axis of the quaternion in `dest`.
 */
VALUE rb_cglm_quat_axis(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_quat_axis(VAL2QUAT(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: mul_quat(other[, dest]) => dest | new Quat
 *
 * Multiplies `self` by `other` and stores the result in `dest`. If `dest`
 * is omitted, a new Quat is created. `dest` or the new Quat is returned.
 */
VALUE rb_cglm_quat_mul_quat(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_mul(VAL2QUAT(self), VAL2QUAT(other), VAL2QUAT(dest));
  return dest;
}

/* call-seq: mul_quat!(other) => self
 *
 * Multiplies `self` by `other`. Modifies `self` in-place and returns `self`.
 */
VALUE rb_cglm_quat_mul_quat_self(VALUE self, VALUE other) {
  quat dest;
  glm_quat_mul(VAL2QUAT(self), VAL2QUAT(other), dest);
  memcpy(&VAL2QUAT(self), &dest, sizeof(quat));
  return self;
}

/* call-seq: to_mat4([dest]) => dest | new Mat4
 *
 * Converts this quaternion into a Mat4. Places the result into `dest` or
 * creates a new Mat4.
 */
VALUE rb_cglm_quat_to_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_quat_mat4(VAL2QUAT(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: to_transposed_mat4([dest]) => dest | new Mat4
 *
 * Converts this quaternion into a transposed Mat4. Places the result into
 * `dest` or creates a new Mat4.
 */
VALUE rb_cglm_quat_to_mat4t(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_quat_mat4t(VAL2QUAT(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: to_mat3([dest]) => dest | new Mat3
 *
 * Converts this quaternion into a Mat3. Places the result into `dest` or
 * creates a new Mat3.
 */
VALUE rb_cglm_quat_to_mat3(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_quat_mat3(VAL2QUAT(self), VAL2MAT3(dest));
  return dest;
}

/* call-seq: to_transposed_mat3([dest]) => dest | new Mat3
 *
 * Converts this quaternion into a transposed Mat3. Places the result into
 * `dest` or creates a new Mat3.
 */
VALUE rb_cglm_quat_to_mat3t(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = MAT3_NEW(ALLOC_MAT3);
  glm_quat_mat3t(VAL2QUAT(self), VAL2MAT3(dest));
  return dest;
}

/* call-seq: lerp!(from, to, amount) => self */
VALUE rb_cglm_quat_lerp_self(VALUE self, VALUE from, VALUE to, VALUE amount) {
  glm_quat_lerp(VAL2QUAT(from), VAL2QUAT(to), NUM2FLT(amount), VAL2QUAT(self));
  return self;
}

/* call-seq: slerp!(from, to, amount) => self */
VALUE rb_cglm_quat_slerp_self(VALUE self, VALUE from, VALUE to, VALUE amount) {
  glm_quat_slerp(VAL2QUAT(from), VAL2QUAT(to), NUM2FLT(amount), VAL2QUAT(self));
  return self;
}

/* call-seq: look(position[, dest]) => dest | new Mat4
 *
 * Creates a view matrix, stored in `dest`, using this quaternion as the
 * camera orientation. Returns `dest`. Creates a new Mat4 if `dest` is
 * omitted.
 */
VALUE rb_cglm_quat_look(int argc, VALUE *argv, VALUE self) {
  VALUE position, dest;
  rb_scan_args(argc, argv, "11", &position, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_quat_look(VAL2VEC3(position), VAL2QUAT(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: look(dir, fwd, up[, dest]) => dest | new Quat
 *
 * Creates a rotation quaternion that has the specified orientation. Places
 * the result in `dest`, or creates a new Quat if `dest` was omitted. Returns
 * `dest`.
 *
 * * `dir` is the direction to look (a Vec3).
 *
 * * `fwd` is the forward vector (a Vec3).
 *
 * * `up` is the up vector (a Vec3).
 */
VALUE rb_cglm_quat_new_look(int argc, VALUE *argv, VALUE self) {
  VALUE dir, fwd, up, dest;
  rb_scan_args(argc, argv, "31", &dir, &fwd, &up, &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_for(VAL2VEC3(dir), VAL2VEC3(fwd), VAL2VEC3(up), VAL2QUAT(dest));
  return dest;
}

/* call-seq: look_at(position, target, fwd, up[, dest]) => dest | new Quat
 *
 * Creates a rotation quaternion that has the specified orientation. Places
 * the result in `dest`, or creates a new Quat if `dest` was omitted. Returns
 * `dest`.
 *
 * * `position` is the current position to look from (a Vec3).
 *
 * * `target` is the position to look toward (a Vec3).
 *
 * * `fwd` is the forward vector (a Vec3).
 *
 * * `up` is the up vector (a Vec3).
 */
VALUE rb_cglm_quat_new_look_at(int argc, VALUE *argv, VALUE self) {
  VALUE position, target, fwd, up, dest;
  rb_scan_args(argc, argv, "41", &position, &target, &fwd, &up, &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);
  glm_quat_forp(VAL2VEC3(position), VAL2VEC3(target), VAL2VEC3(fwd), VAL2VEC3(up), VAL2QUAT(dest));
  return dest;
}

/* call-seq: rotate_vec3(vec[, dest]) => dest | new Vec3
 *
 * Rotates the given Vec3 by this quaternion. Returns the result in `dest`,
 * or a new Vec3 if `dest` was omitted.
 */
VALUE rb_cglm_quat_rotate_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE vec, dest;
  rb_scan_args(argc, argv, "11", &vec, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_quat_rotatev(VAL2QUAT(self), VAL2VEC3(vec), VAL2VEC3(dest));
  return dest;
}

/* call-seq: rotate_mat4(vec[, dest]) => dest | new Mat4
 *
 * Rotates the given Mat4 by this quaternion. Returns the result in `dest`,
 * or a new Mat4 if `dest` was omitted.
 */
VALUE rb_cglm_quat_rotate_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE mat, dest;
  rb_scan_args(argc, argv, "11", &mat, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_quat_rotate(VAL2MAT4(mat), VAL2QUAT(self), VAL2MAT4(dest));
  return dest;
}

/* call-seq: pivot_mat4(mat, pivot_point[, dest]) => dest | new Mat4
 *
 * Rotates the given transform matrix using this quaternion at the pivot
 * point (a Vec3). Places the resultant Mat4 into `dest`, or creates a new
 * Mat4 if `dest` is omitted. Returns `dest`.
 */
VALUE rb_cglm_quat_pivot_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE mat, pivot, dest;
  rb_scan_args(argc, argv, "21", &mat, &pivot, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  memcpy(&VAL2MAT4(dest), &VAL2MAT4(mat), sizeof(mat4));
  glm_quat_rotate_at(VAL2MAT4(dest), VAL2QUAT(self), VAL2VEC3(pivot));
  return dest;
}

/* call-seq: random([dest]) => dest | new Quat
 *
 * Fills `dest` or a new Quat with a random orientation, and returns it.
 */
VALUE rb_cglm_quat_new_random(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = QUAT_NEW(ALLOC_QUAT);

  glm_quat(VAL2QUAT(dest), drand48(), drand48(), drand48(), drand48());
  glm_quat_normalize(VAL2QUAT(dest));

  return dest;
}

void Init_cglm_quat() {
  rb_define_method(rb_cQuat, "copy_to",            rb_cglm_quat_copy_to,        1);
  rb_define_method(rb_cQuat, "normalize",          rb_cglm_quat_normalize,     -1);
  rb_define_method(rb_cQuat, "normalize!",         rb_cglm_quat_normalize_self, 0);
  rb_define_method(rb_cQuat, "conjugate",          rb_cglm_quat_conjugate,     -1);
  rb_define_method(rb_cQuat, "invert",             rb_cglm_quat_invert,        -1);
  rb_define_method(rb_cQuat, "invert!",            rb_cglm_quat_invert_self,    0);
  rb_define_method(rb_cQuat, "real",               rb_cglm_quat_real,           0);
  rb_define_method(rb_cQuat, "imag",               rb_cglm_quat_imag,          -1);
  rb_define_method(rb_cQuat, "imagn",              rb_cglm_quat_imagn,         -1);
  rb_define_method(rb_cQuat, "imaglen",            rb_cglm_quat_imaglen,        0);
  rb_define_method(rb_cQuat, "angle",              rb_cglm_quat_angle,          0);
  rb_define_method(rb_cQuat, "axis",               rb_cglm_quat_axis,          -1);
  rb_define_method(rb_cQuat, "mul_quat",           rb_cglm_quat_mul_quat,      -1);
  rb_define_method(rb_cQuat, "mul_quat!",          rb_cglm_quat_mul_quat_self,  1);
  rb_define_method(rb_cQuat, "to_mat4",            rb_cglm_quat_to_mat4,       -1);
  rb_define_method(rb_cQuat, "to_transposed_mat4", rb_cglm_quat_to_mat4t,      -1);
  rb_define_method(rb_cQuat, "to_mat3",            rb_cglm_quat_to_mat3,       -1);
  rb_define_method(rb_cQuat, "to_transposed_mat3", rb_cglm_quat_to_mat3t,      -1);
  rb_define_method(rb_cQuat, "lerp!",              rb_cglm_quat_lerp_self,      3);
  rb_define_method(rb_cQuat, "slerp!",             rb_cglm_quat_slerp_self,     3);
  rb_define_method(rb_cQuat, "look",               rb_cglm_quat_look,          -1);
  rb_define_method(rb_cQuat, "rotate_vec3",        rb_cglm_quat_rotate_vec3,   -1);
  rb_define_method(rb_cQuat, "rotate_mat4",        rb_cglm_quat_rotate_mat4,   -1);
  rb_define_method(rb_cQuat, "pivot_mat4",         rb_cglm_quat_pivot_mat4,    -1);

  rb_define_singleton_method(rb_cQuat, "random",     rb_cglm_quat_new_random,     -1);
  rb_define_singleton_method(rb_cQuat, "rand",       rb_cglm_quat_new_random,     -1);
  rb_define_singleton_method(rb_cQuat, "identity",   rb_cglm_quat_new_identity,   -1);
  rb_define_singleton_method(rb_cQuat, "axis_angle", rb_cglm_quat_new_axis_angle, -1);
  rb_define_singleton_method(rb_cQuat, "look",       rb_cglm_quat_new_look,       -1);
  rb_define_singleton_method(rb_cQuat, "look_at",    rb_cglm_quat_new_look_at,    -1);
}
