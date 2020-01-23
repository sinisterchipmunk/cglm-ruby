#include "rb_cglm.h"

VALUE rb_cglm_vec3_aref(VALUE self, VALUE index) {
  CHECK_RANGE(index, 0, 2);
  return DBL2NUM(VAL2VEC3(self)[NUM2INT(index)]);
}

VALUE rb_cglm_vec3_aset(VALUE self, VALUE index, VALUE val) {
  CHECK_RANGE(index, 0, 2);
  VAL2VEC3(self)[NUM2INT(index)] = NUM2DBL(val);
  return self;
}

VALUE rb_cglm_vec3_size_bytes(VALUE klass) {
  return SIZET2NUM(vec3_size());
}

VALUE rb_cglm_vec3_alignment_bytes(VALUE klass) {
  return SIZET2NUM(VEC3_ALIGNMENT);
}

VALUE rb_cglm_vec3_xup(VALUE self) {
  VALUE dest = VEC3_NEW(ALLOC_VEC3);
  vec3 yup = GLM_XUP;
  memcpy(&VAL2VEC3(dest), &yup, sizeof(vec3));
  return dest;
}

VALUE rb_cglm_vec3_yup(VALUE self) {
  VALUE dest = VEC3_NEW(ALLOC_VEC3);
  vec3 yup = GLM_YUP;
  memcpy(&VAL2VEC3(dest), &yup, sizeof(vec3));
  return dest;
}

VALUE rb_cglm_vec3_zup(VALUE self) {
  VALUE dest = VEC3_NEW(ALLOC_VEC3);
  vec3 yup = GLM_ZUP;
  memcpy(&VAL2VEC3(dest), &yup, sizeof(vec3));
  return dest;
}

VALUE rb_cglm_vec3_one(VALUE self) {
  VALUE dest = VEC3_NEW(ALLOC_VEC3);
  vec3 yup = GLM_VEC3_ONE;
  memcpy(&VAL2VEC3(dest), &yup, sizeof(vec3));
  return dest;
}

VALUE rb_cglm_vec3_zero(VALUE self) {
  VALUE dest = VEC3_NEW(ALLOC_VEC3);
  vec3 yup = GLM_VEC3_ZERO;
  memcpy(&VAL2VEC3(dest), &yup, sizeof(vec3));
  return dest;
}

VALUE rb_cglm_vec3_zero_self(VALUE self) {
  glm_vec3_zero(VAL2VEC3(self));
  return self;
}

VALUE rb_cglm_vec3_one_self(VALUE self) {
  glm_vec3_one(VAL2VEC3(self));
  return self;
}

VALUE rb_cglm_vec3_dot(VALUE self, VALUE other) {
  return DBL2NUM(glm_vec3_dot(VAL2VEC3(self), VAL2VEC3(self)));
}

/* call-seq: cross(b[, dest]) => dest | new Vec3 */
VALUE rb_cglm_vec3_cross(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_cross(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: norm2 => Numeric
 *
 * Returns the norm (magnitude) of this vector, squared. Call this rather than
 * `norm ** 2` to avoid an unnecessary square root.
 */
VALUE rb_cglm_vec3_norm2(VALUE self) {
  return DBL2NUM(glm_vec3_norm2(VAL2VEC3(self)));
}

/* call-seq: norm => Numeric
 *
 * Returns the norm (magnitude) of this vector.
 */
VALUE rb_cglm_vec3_norm(VALUE self) {
  return DBL2NUM(glm_vec3_norm(VAL2VEC3(self)));
}

/* call-seq: add_vec3(b[, dest]) => dest | new Vec3
 *
 * Adds `self` and `b` together, placing the result in `dest`. If `dest` is
 * omitted, a new Vec3 is created and returned.
 */
VALUE rb_cglm_vec3_add_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_add(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: add_scalar(b[, dest]) => dest | new Vec3
 *
 * Adds the Numeric `b` to each component of `self`, placing the result in
 * `dest`. If `dest` is omitted, a new Vec3 is created and returned.
 */
VALUE rb_cglm_vec3_add_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_adds(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: sub_vec3(b[, dest]) => dest | new Vec3
 *
 * Subtracts `b` from `self`, placing the result in `dest`. If `dest` is
 * omitted, a new Vec3 is created and returned.
 */
VALUE rb_cglm_vec3_sub_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_sub(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: sub_scalar(b[, dest]) => dest | new Vec3
 *
 * Subtracts the Numeric `b` from each component of `self`, placing the result
 * in `dest`. If `dest` is omitted, a new Vec3 is created and returned.
 */
VALUE rb_cglm_vec3_sub_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_subs(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: add_vec3!(b) => self
 *
 * Adds `self` and `b` together, modifying `self` in-place and returning it.
 */
VALUE rb_cglm_vec3_add_vec3_self(VALUE self, VALUE b) {
  glm_vec3_add(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(self));
  return self;
}

/* call-seq: add_scalar!(b) => self
 *
 * Adds the Numeric `b` to each component of `self`, modifying `self` in-place
 * and returning it.
 */
VALUE rb_cglm_vec3_add_scalar_self(VALUE self, VALUE b) {
  glm_vec3_adds(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(self));
  return self;
}

/* call-seq: sub_vec3!(b) => self
 *
 * Subtracts `b` from `self`, modifying `self` in-place and returning it.
 */
VALUE rb_cglm_vec3_sub_vec3_self(VALUE self, VALUE b) {
  glm_vec3_sub(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(self));
  return self;
}

/* call-seq: sub_scalar!(b) => self
 *
 * Subtracts the Numeric `b` from each component of `self`, modifying `self`
 * in-place and returning it.
 */
VALUE rb_cglm_vec3_sub_scalar_self(VALUE self, VALUE b) {
  glm_vec3_subs(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(self));
  return self;
}

/* call-seq: mul_vec3(b[, dest]) => dest | new Vec3
 *
 * Multiplies two vectors (component-wise multiplication). Places the result
 * in `dest` and returns `dest`. If `dest` is omitted, a new Vec3 is used
 * instead.
 */
VALUE rb_cglm_vec3_mul_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_mul(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: mul_vec3!(b) => self
 *
 * Multiplies two vectors (component-wise multiplication). Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec3_mul_vec3_self(VALUE self, VALUE b) {
  glm_vec3_mul(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(self));
  return self;
}

/* call-seq: mul_scalar(b[, dest]) => dest | new Vec3
 *
 * Multiplies each component in `self` with the scalar `b` and places the
 * result into `dest`. If `dest` is omitted, a new Vec3 is used
 * instead. Returns `dest`.
 */
VALUE rb_cglm_vec3_mul_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_scale(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: mul_scalar!(b) => self
 *
 * Multiplies each component in `self` with the scalar `b`. Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec3_mul_scalar_self(VALUE self, VALUE b) {
  glm_vec3_scale(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(self));
  return self;
}

/* call-seq: resize(b[, dest]) => dest | new Vec3
 *
 * Same as `normalize(self) * b`. Places the result in `dest` and
 * creates a new Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_resize(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_scale_as(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: resize!(b) => self
 *
 * Same as `normalize(self) * b`. Modifies `self` in-place and returns `self`.
 */
VALUE rb_cglm_vec3_resize_self(VALUE self, VALUE b) {
  glm_vec3_scale_as(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(self));
  return self;
}

/* call-seq: div_vec3(b[, dest]) => dest | new Vec3
 *
 * Divides two vectors (component-wise division). Places the result
 * in `dest` and returns `dest`. If `dest` is omitted, a new Vec3 is used
 * instead.
 */
VALUE rb_cglm_vec3_div_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_div(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: div_vec3!(b) => self
 *
 * Divides two vectors (component-wise division). Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec3_div_vec3_self(VALUE self, VALUE b) {
  glm_vec3_div(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(self));
  return self;
}

/* call-seq: div_scalar(b[, dest]) => dest | new Vec3
 *
 * Divides each component in `self` by the scalar `b` and places the
 * result into `dest`. If `dest` is omitted, a new Vec3 is used
 * instead. Returns `dest`.
 */
VALUE rb_cglm_vec3_div_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_divs(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: div_scalar!(b) => self
 *
 * Divides each component in `self` by the scalar `b`. Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec3_div_scalar_self(VALUE self, VALUE b) {
  glm_vec3_divs(VAL2VEC3(self), NUM2FLT(b), VAL2VEC3(self));
  return self;
}

/* call-seq: addadd_vec3(other, dest) => dest
 *
 * Adds `self` to `other` and adds that result to `dest`. Equivalent to
 * `dest += (self + other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec3_addadd_vec3(VALUE self, VALUE other, VALUE dest) {
  glm_vec3_addadd(VAL2VEC3(self), VAL2VEC3(other), VAL2VEC3(dest));
  return dest;
}

/* call-seq: subadd_vec3(other, dest) => dest
 *
 * Subtracts `other` from `self` and adds that result to `dest`. Equivalent to
 * `dest += (self - other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec3_subadd_vec3(VALUE self, VALUE other, VALUE dest) {
  glm_vec3_subadd(VAL2VEC3(self), VAL2VEC3(other), VAL2VEC3(dest));
  return dest;
}

/* call-seq: muladd_vec3(other, dest) => dest
 *
 * Multiplies `self` with `other` and adds that result to `dest`. Equivalent to
 * `dest += (self * other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec3_muladd_vec3(VALUE self, VALUE other, VALUE dest) {
  glm_vec3_muladd(VAL2VEC3(self), VAL2VEC3(other), VAL2VEC3(dest));
  return dest;
}

/* call-seq: muladd_scalar(other, dest) => dest
 *
 * Multiplies `self` with `other` and adds that result to `dest`. Equivalent to
 * `dest += (self * other)`. Returns `dest`.
 *
 * * `other` is a Numeric, not a vector type.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec3_muladd_scalar(VALUE self, VALUE other, VALUE dest) {
  glm_vec3_muladds(VAL2VEC3(self), NUM2FLT(other), VAL2VEC3(dest));
  return dest;
}

/* call-seq: flip_signs([dest]) => dest | new Vec3
 *
 * Flips the sign of each component and places the result into `dest`. Returns
 * `dest`. If `dest` is omitted, a new Vec3 is allocated.
 */
VALUE rb_cglm_vec3_flip_signs(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_flipsign_to(VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: flip_signs! => self
 *
 * Flips the sign of each component, modifying `self` in-place. Returns `self`.
 */
VALUE rb_cglm_vec3_flip_signs_self(VALUE self) {
  glm_vec3_flipsign(VAL2VEC3(self));
  return self;
}

/* call-seq: normalize([dest]) => dest | new Vec3
 *
 * Normalizes `self` and places the result into `dest`. If `dest` is omitted,
 * a new Vec3 is allocated. Returns `dest`.
 */
VALUE rb_cglm_vec3_normalize(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_normalize_to(VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: normalize! => self
 *
 * Normalizes `self` in-place, and returns `self`.
 */
VALUE rb_cglm_vec3_normalize_self(VALUE self) {
  glm_vec3_normalize(VAL2VEC3(self));
  return self;
}

/* call-seq: angle(other) => Numeric
 *
 * Returns the angle between `self` and `other`, in radians.
 */
VALUE rb_cglm_vec3_angle(VALUE self, VALUE other) {
  return DBL2NUM(glm_vec3_angle(VAL2VEC3(self), VAL2VEC3(other)));
}

/* call-seq: rotate_axis_angle(axis, angle[, dest]) => dest | new Vec3
 *
 * Rotates `self` around `axis` (a Vec3) by the specified `angle` (in radians)
 * using Rodrigues' rotation formula. Places the result into `dest` and
 * returns `dest`. Allocates a new Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_rotate_axis_angle(int argc, VALUE *argv, VALUE self) {
  VALUE axis, angle, dest;
  rb_scan_args(argc, argv, "21", &axis, &angle, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  memcpy(&VAL2VEC3(dest), &VAL2VEC3(self), sizeof(vec3));
  glm_vec3_rotate(VAL2VEC3(dest), NUM2FLT(angle), VAL2VEC3(axis));
  return dest;
}

/* call-seq: rotate_axis_angle!(axis, angle) => self
 *
 * Rotates `self` around `axis` (a Vec3) by the specified `angle` (in radians)
 * using Rodrigues' rotation formula. Places the result into `self` and
 * returns `self`.
 */
VALUE rb_cglm_vec3_rotate_axis_angle_self(VALUE self, VALUE axis, VALUE angle) {
  glm_vec3_rotate(VAL2VEC3(self), NUM2FLT(angle), VAL2VEC3(axis));
  return self;
}

/* call-seq: rotate_mat4(mat[, dest]) => dest | new Vec3
 *
 * Rotate `self` by the given rotation or affine matrix. Places the result in
 * `dest` and returns `dest`. Creates and returns a new Vec3 if `dest` is
 * omitted.
 *
 * * `mat` format should be (no perspective):
 *
 *       a  b  c  x
 *       e  f  g  y
 *       i  j  k  z
 *       0  0  0  w
 */
VALUE rb_cglm_vec3_rotate_mat4(int argc, VALUE *argv, VALUE self) {
  VALUE matrix, dest;
  rb_scan_args(argc, argv, "11", &matrix, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_rotate_m4(VAL2MAT4(matrix), VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: rotate_mat4!(mat) => self
 *
 * Rotate `self` by the given rotation or affine matrix. Places the result in
 * `self` and returns `self`.
 *
 * * `mat` format should be (no perspective):
 *
 *       a  b  c  x
 *       e  f  g  y
 *       i  j  k  z
 *       0  0  0  w
 */
VALUE rb_cglm_vec3_rotate_mat4_self(VALUE self, VALUE matrix) {
  glm_vec3_rotate_m4(VAL2MAT4(matrix), VAL2VEC3(self), VAL2VEC3(self));
  return self;
}

/* call-seq: rotate_mat3(mat[, dest]) => dest | new Vec3
 *
 * Rotate `self` by the given rotation matrix. Places the result in
 * `dest` and returns `dest`. Creates and returns a new Vec3 if `dest` is
 * omitted.
 */
VALUE rb_cglm_vec3_rotate_mat3(int argc, VALUE *argv, VALUE self) {
  VALUE matrix, dest;
  rb_scan_args(argc, argv, "11", &matrix, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_rotate_m3(VAL2MAT3(matrix), VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: rotate_mat3!(mat) => self
 *
 * Rotate `self` by the given rotation matrix. Places the result in
 * `self` and returns `self`.
 */
VALUE rb_cglm_vec3_rotate_mat3_self(VALUE self, VALUE matrix) {
  glm_vec3_rotate_m3(VAL2MAT3(matrix), VAL2VEC3(self), VAL2VEC3(self));
  return self;
}

/* call-seq: project(vec[, dest]) => dest | new Vec3
 *
 * Projects `self` onto the given Vec3. Places the result into `dest` and
 * returns `dest`. Creates and returns a new Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_project(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_proj(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: project!(vec) => self
 *
 * Projects `self` onto the given Vec3. Places the result into `self` and
 * returns `self`.
 */
VALUE rb_cglm_vec3_project_self(VALUE self, VALUE b) {
  glm_vec3_proj(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(self));
  return self;
}

/* call-seq: center(vec[, dest]) => dest | new Vec3
 *
 * Finds the center point between `self` and `vec`. Places the result into
 * `dest` and returns `dest`. Creates and returns a new Vec3 if `dest` is
 * omitted.
 */
VALUE rb_cglm_vec3_center(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_center(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: distance2(vec) => Numeric
 *
 * Returns the squared distance between this vector and the specified one.
 */
VALUE rb_cglm_vec3_distance2(VALUE self, VALUE b) {
  return DBL2NUM(glm_vec3_distance2(VAL2VEC3(self), VAL2VEC3(b)));
}

/* call-seq: distance(vec) => Numeric
 *
 * Returns the distance between this vector and the specified one.
 */
VALUE rb_cglm_vec3_distance(VALUE self, VALUE b) {
  return DBL2NUM(glm_vec3_distance(VAL2VEC3(self), VAL2VEC3(b)));
}

/* call-seq: max(vec[, dest]) => dest | new Vec3
 *
 * Finds the higher of each component (x, y, z) between `self` and `vec`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_max(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_maxv(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: min(vec[, dest]) => dest | new Vec3
 *
 * Finds the lower of each component (x, y, z) between `self` and `vec`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_min(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_minv(VAL2VEC3(self), VAL2VEC3(b), VAL2VEC3(dest));
  return dest;
}

/* call-seq: ortho(vec[, dest]) => dest | new Vec3
 *
 * Finds an orthogonal/perpendicular vector to `self`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_ortho(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_ortho(VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: clamp_scalar(min, max[, dest]) => dest | new Vec3
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec3 if `dest` is omitted.
 */
VALUE rb_cglm_vec3_clamp_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE a, b, dest;
  rb_scan_args(argc, argv, "21", &a, &b, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  memcpy(&VAL2VEC3(dest), &VAL2VEC3(self), sizeof(vec3));
  glm_vec3_clamp(VAL2VEC3(dest), NUM2FLT(a), NUM2FLT(b));
  return dest;
}

/* call-seq: clamp_scalar!(min, max) => self
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `self` and returns `self`.
 */
VALUE rb_cglm_vec3_clamp_scalar_self(VALUE self, VALUE a, VALUE b) {
  glm_vec3_clamp(VAL2VEC3(self), NUM2FLT(a), NUM2FLT(b));
  return self;
}

/* call-seq: lerp!(from, to, amount) => self
 *
 * Performs linear interpolation between `from` and `to`, both of which should
 * be Vec3's, by the specified `amount` which should be a number. Modifies
 * `self` in-place and returns `self`.
 */
VALUE rb_cglm_vec3_lerp_self(VALUE self, VALUE from, VALUE to, VALUE amount) {
  glm_vec3_lerp(VAL2VEC3(from), VAL2VEC3(to), NUM2FLT(amount), VAL2VEC3(self));
  return self;
}

/* call-seq: broadcast!(val) => self
 *
 * Sets each member of `self` to the specified Numeric value and returns
 * `self`.
 */
VALUE rb_cglm_vec3_broadcast_self(VALUE self, VALUE val) {
  glm_vec3_broadcast(NUM2FLT(val), VAL2VEC3(self));
  return self;
}

/* call-seq: equals_scalar(val) => true|false
 *
 * Returns true if the given scalar value exactly equals each component of
 * this Vec3, false otherwise.
 */
VALUE rb_cglm_vec3_equals_scalar(VALUE self, VALUE val) {
  return glm_vec3_eq(VAL2VEC3(self), NUM2FLT(val)) ? Qtrue : Qfalse;
}

/* call-seq: equalish_scalar(val[, epsilon]) => true|false
 *
 * Returns true if the given scalar value is very close to each component of
 * this Vec3, false otherwise. Useful for dealing with the loss of precision
 * during floating point arithmetic.
 */
VALUE rb_cglm_vec3_equalish_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE val, eps;
  float epsil = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &val, &eps);
  if (!NIL_P(eps)) epsil = NUM2FLT(eps);
  float s = NUM2FLT(val);
  vec3 *v = &VAL2VEC3(self);
  return fabsf((*v)[0] - s) <= eps &&
         fabsf((*v)[1] - s) <= eps &&
         fabsf((*v)[2] - s) <= eps ? Qtrue : Qfalse;
}

/* call-seq: equals_all => true|false
 *
 * Returns true if each component in this Vec3 has the same exact value.
 */
VALUE rb_cglm_vec3_equals_all(VALUE self) {
  return glm_vec3_eq_all(VAL2VEC3(self)) ? Qtrue : Qfalse;
}

/* call-seq: equals_vec3(other) => true|false
 *
 * Returns true if this vector exactly matches the given one.
 */
VALUE rb_cglm_vec3_equals_vec3(VALUE self, VALUE other) {
  return glm_vec3_eqv(VAL2VEC3(self), VAL2VEC3(other)) ? Qtrue : Qfalse;
}

/* call-seq: equalish_vec3(other[, epsilon]) => true|false
 *
 * Returns true if this vector is very close to equal to the given one. Useful
 * for dealing with the loss of precision during floating point arithmetic.
 */
VALUE rb_cglm_vec3_equalish_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE val, eps;
  float epsil = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &val, &eps);
  if (!NIL_P(eps)) epsil = NUM2FLT(eps);
  vec3 *s = &VAL2VEC3(val);
  vec3 *v = &VAL2VEC3(self);
  return fabsf((*v)[0] - (*s)[0]) <= eps &&
         fabsf((*v)[1] - (*s)[1]) <= eps &&
         fabsf((*v)[2] - (*s)[2]) <= eps ? Qtrue : Qfalse;
}

/* call-seq: highest => Numeric
 *
 * Returns the value of the highest component in this Vec3.
 */
VALUE rb_cglm_vec3_highest(VALUE self) {
  return DBL2NUM(glm_vec3_max(VAL2VEC3(self)));
}

/* call-seq: lowest => Numeric
 *
 * Returns the value of the lowest component in this Vec3.
 */
VALUE rb_cglm_vec3_lowest(VALUE self) {
  return DBL2NUM(glm_vec3_min(VAL2VEC3(self)));
}

/* call-seq: nan? => true|false
 *
 * Returns true if any component in this vector is nan, false otherwise.
 * You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec3_is_nan(VALUE self) {
  return glm_vec3_isnan(VAL2VEC3(self)) ? Qtrue : Qfalse;
}

/* call-seq: inf? => true|false
 *
 * Returns true if any component in this vector is inf, false otherwise.
 * You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec3_is_inf(VALUE self) {
  return glm_vec3_isinf(VAL2VEC3(self)) ? Qtrue : Qfalse;
}

/* call-seq: valid? => true|false
 *
 * Returns true if no component in this vector is NaN or infinite, false
 * otherwise. You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec3_is_valid(VALUE self) {
  return glm_vec3_isvalid(VAL2VEC3(self)) ? Qtrue : Qfalse;
}

/* call-seq: signs([dest]) => dest | new Vec3
 *
 * Places `+1`, `0` or `-1` into each component of `dest` based on whether the
 * corresponding component of this Vec3 is positive, `0`/`NaN`, or negative.
 * If `dest` is omitted, a new Vec3 is created and returned.
 */
VALUE rb_cglm_vec3_signs(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_sign(VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: sqrt([dest]) => dest | new Vec3
 *
 * For each component of this Vec3, places the square root of that component
 * into `dest`. If `dest` is omitted, a new Vec3 is created. Returns `dest`.
 */
VALUE rb_cglm_vec3_sqrt(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3_sqrt(VAL2VEC3(self), VAL2VEC3(dest));
  return dest;
}

/* call-seq: to_vec4([last, dest]) => dest | new Vec4
 *
 * Places the 3 components of this Vec3 into the first 3 components of the
 * `dest` Vec4. Sets the final component to the value of `last`, which
 * defaults to `1`. If `dest` is omitted, a new Vec4 is created.
 */
VALUE rb_cglm_vec3_to_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE last, dest;
  rb_scan_args(argc, argv, "02", &last, &dest);
  if (NIL_P(last)) last = INT2NUM(1);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4(VAL2VEC3(self), NUM2FLT(last), VAL2VEC4(dest));
  return dest;
}

/* call-seq: random([dest]) => dest | new Vec3
 *
 * Fills `dest` or a new Vec3 with random values, and returns it.
 */
VALUE rb_cglm_vec3_new_random(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);

  VAL2VEC3(dest)[0] = drand48();
  VAL2VEC3(dest)[1] = drand48();
  VAL2VEC3(dest)[2] = drand48();

  return dest;
}

void Init_cglm_vec3() {
  rb_define_method(rb_cVec3, "-@",                 rb_cglm_vec3_flip_signs,            -1);
  rb_define_method(rb_cVec3, "[]",                 rb_cglm_vec3_aref,                   1);
  rb_define_method(rb_cVec3, "[]=",                rb_cglm_vec3_aset,                   2);
  rb_define_method(rb_cVec3, "zero!",              rb_cglm_vec3_zero_self,              0);
  rb_define_method(rb_cVec3, "one!",               rb_cglm_vec3_one_self,               0);
  rb_define_method(rb_cVec3, "dot",                rb_cglm_vec3_dot,                    1);
  rb_define_method(rb_cVec3, "cross",              rb_cglm_vec3_cross,                 -1);
  rb_define_method(rb_cVec3, "norm2",              rb_cglm_vec3_norm2,                  0);
  rb_define_method(rb_cVec3, "norm",               rb_cglm_vec3_norm,                   0);
  rb_define_method(rb_cVec3, "add_vec3",           rb_cglm_vec3_add_vec3,              -1);
  rb_define_method(rb_cVec3, "add_scalar",         rb_cglm_vec3_add_scalar,            -1);
  rb_define_method(rb_cVec3, "sub_vec3",           rb_cglm_vec3_sub_vec3,              -1);
  rb_define_method(rb_cVec3, "sub_scalar",         rb_cglm_vec3_sub_scalar,            -1);
  rb_define_method(rb_cVec3, "add_vec3!",          rb_cglm_vec3_add_vec3_self,          1);
  rb_define_method(rb_cVec3, "add_scalar!",        rb_cglm_vec3_add_scalar_self,        1);
  rb_define_method(rb_cVec3, "sub_vec3!",          rb_cglm_vec3_sub_vec3_self,          1);
  rb_define_method(rb_cVec3, "sub_scalar!",        rb_cglm_vec3_sub_scalar_self,        1);
  rb_define_method(rb_cVec3, "mul_vec3",           rb_cglm_vec3_mul_vec3,              -1);
  rb_define_method(rb_cVec3, "mul_vec3!",          rb_cglm_vec3_mul_vec3_self,          1);
  rb_define_method(rb_cVec3, "mul_scalar",         rb_cglm_vec3_mul_scalar,            -1);
  rb_define_method(rb_cVec3, "mul_scalar!",        rb_cglm_vec3_mul_scalar_self,        1);
  rb_define_method(rb_cVec3, "div_vec3",           rb_cglm_vec3_div_vec3,              -1);
  rb_define_method(rb_cVec3, "div_vec3!",          rb_cglm_vec3_div_vec3_self,          1);
  rb_define_method(rb_cVec3, "div_scalar",         rb_cglm_vec3_div_scalar,            -1);
  rb_define_method(rb_cVec3, "div_scalar!",        rb_cglm_vec3_div_scalar_self,        1);
  rb_define_method(rb_cVec3, "resize",             rb_cglm_vec3_resize,                -1);
  rb_define_method(rb_cVec3, "resize!",            rb_cglm_vec3_resize_self,            1);
  rb_define_method(rb_cVec3, "addadd_vec3",        rb_cglm_vec3_addadd_vec3,            2);
  rb_define_method(rb_cVec3, "subadd_vec3",        rb_cglm_vec3_subadd_vec3,            2);
  rb_define_method(rb_cVec3, "muladd_scalar",      rb_cglm_vec3_muladd_scalar,          2);
  rb_define_method(rb_cVec3, "muladd_vec3",        rb_cglm_vec3_muladd_vec3,            2);
  rb_define_method(rb_cVec3, "flip_signs",         rb_cglm_vec3_flip_signs,            -1);
  rb_define_method(rb_cVec3, "flip_signs!",        rb_cglm_vec3_flip_signs_self,        0);
  rb_define_method(rb_cVec3, "normalize",          rb_cglm_vec3_normalize,             -1);
  rb_define_method(rb_cVec3, "normalize!",         rb_cglm_vec3_normalize_self,         0);
  rb_define_method(rb_cVec3, "angle",              rb_cglm_vec3_angle,                  1);
  rb_define_method(rb_cVec3, "rotate_axis_angle",  rb_cglm_vec3_rotate_axis_angle,     -1);
  rb_define_method(rb_cVec3, "rotate_axis_angle!", rb_cglm_vec3_rotate_axis_angle_self, 2);
  rb_define_method(rb_cVec3, "rotate_mat4",        rb_cglm_vec3_rotate_mat4,           -1);
  rb_define_method(rb_cVec3, "rotate_mat4!",       rb_cglm_vec3_rotate_mat4_self,       1);
  rb_define_method(rb_cVec3, "rotate_mat3",        rb_cglm_vec3_rotate_mat3,           -1);
  rb_define_method(rb_cVec3, "rotate_mat3!",       rb_cglm_vec3_rotate_mat3_self,       1);
  rb_define_method(rb_cVec3, "project",            rb_cglm_vec3_project,               -1);
  rb_define_method(rb_cVec3, "project!",           rb_cglm_vec3_project_self,           1);
  rb_define_method(rb_cVec3, "center",             rb_cglm_vec3_center,                -1);
  rb_define_method(rb_cVec3, "distance2",          rb_cglm_vec3_distance2,              1);
  rb_define_method(rb_cVec3, "distance",           rb_cglm_vec3_distance,               1);
  rb_define_method(rb_cVec3, "max",                rb_cglm_vec3_max,                   -1);
  rb_define_method(rb_cVec3, "min",                rb_cglm_vec3_min,                   -1);
  rb_define_method(rb_cVec3, "ortho",              rb_cglm_vec3_ortho,                 -1);
  rb_define_method(rb_cVec3, "clamp_scalar",       rb_cglm_vec3_clamp_scalar,          -1);
  rb_define_method(rb_cVec3, "clamp_scalar!",      rb_cglm_vec3_clamp_scalar_self,      2);
  rb_define_method(rb_cVec3, "lerp!",              rb_cglm_vec3_lerp_self,              3);
  rb_define_method(rb_cVec3, "broadcast!",         rb_cglm_vec3_broadcast_self,         1);
  rb_define_method(rb_cVec3, "equals_scalar",      rb_cglm_vec3_equals_scalar,          1);
  rb_define_method(rb_cVec3, "equalish_scalar",    rb_cglm_vec3_equalish_scalar,       -1);
  rb_define_method(rb_cVec3, "equals_all",         rb_cglm_vec3_equals_all,             0);
  rb_define_method(rb_cVec3, "equals_vec3",        rb_cglm_vec3_equals_vec3,            1);
  rb_define_method(rb_cVec3, "equalish_vec3",      rb_cglm_vec3_equalish_vec3,         -1);
  rb_define_method(rb_cVec3, "highest",            rb_cglm_vec3_highest,                0);
  rb_define_method(rb_cVec3, "lowest",             rb_cglm_vec3_lowest,                 0);
  rb_define_method(rb_cVec3, "nan?",               rb_cglm_vec3_is_nan,                 0);
  rb_define_method(rb_cVec3, "inf?",               rb_cglm_vec3_is_inf,                 0);
  rb_define_method(rb_cVec3, "valid?",             rb_cglm_vec3_is_valid,               0);
  rb_define_method(rb_cVec3, "signs",              rb_cglm_vec3_signs,                 -1);
  rb_define_method(rb_cVec3, "sqrt",               rb_cglm_vec3_sqrt,                  -1);
  rb_define_method(rb_cVec3, "to_vec4",            rb_cglm_vec3_to_vec4,               -1);

  rb_define_alias(rb_cVec3, "invert",     "flip_signs");
  rb_define_alias(rb_cVec3, "invert!",    "flip_signs!");
  rb_define_alias(rb_cVec3, "magnitude",  "norm");
  rb_define_alias(rb_cVec3, "mag",        "norm");
  rb_define_alias(rb_cVec3, "magnitude2", "norm2");
  rb_define_alias(rb_cVec3, "mag2",       "norm2");

  rb_define_singleton_method(rb_cVec3, "random",    rb_cglm_vec3_new_random,     -1);
  rb_define_singleton_method(rb_cVec3, "rand",      rb_cglm_vec3_new_random,     -1);
  rb_define_singleton_method(rb_cVec3, "size",      rb_cglm_vec3_size_bytes,      0);
  rb_define_singleton_method(rb_cVec3, "alignment", rb_cglm_vec3_alignment_bytes, 0);
  rb_define_singleton_method(rb_cVec3, "one",       rb_cglm_vec3_one,             0);
  rb_define_singleton_method(rb_cVec3, "zero",      rb_cglm_vec3_zero,            0);
  rb_define_singleton_method(rb_cVec3, "xup",       rb_cglm_vec3_xup,             0);
  rb_define_singleton_method(rb_cVec3, "yup",       rb_cglm_vec3_yup,             0);
  rb_define_singleton_method(rb_cVec3, "zup",       rb_cglm_vec3_zup,             0);
}
