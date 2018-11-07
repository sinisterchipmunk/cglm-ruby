#include "rb_cglm.h"

VALUE rb_cglm_vec4_aref(VALUE self, VALUE index) {
  CHECK_RANGE(index, 0, 3);
  return DBL2NUM(VAL2VEC4(self)[NUM2INT(index)]);
}

VALUE rb_cglm_vec4_aset(VALUE self, VALUE index, VALUE val) {
  CHECK_RANGE(index, 0, 3);
  VAL2VEC4(self)[NUM2INT(index)] = NUM2DBL(val);
  return self;
}

VALUE rb_cglm_vec4_size_bytes(VALUE klass) { return SIZET2NUM(vec4_size()); }

VALUE rb_cglm_vec4_alignment_bytes(VALUE klass) { return SIZET2NUM(VEC4_ALIGNMENT); }

/* call-seq: to_vec3([dest]) => dest | new Vec3 */
VALUE rb_cglm_vec4_to_vec3(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_vec3(VAL2VEC4(self), VAL2VEC3(dest));
  return dest;
}

VALUE rb_cglm_vec4_one(VALUE self) {
  VALUE dest = VEC4_NEW(ALLOC_VEC4);
  vec4 one = GLM_VEC4_ONE;
  memcpy(&VAL2VEC4(dest), &one, sizeof(vec4));
  return dest;
}

VALUE rb_cglm_vec4_black(VALUE self) {
  VALUE dest = VEC4_NEW(ALLOC_VEC4);
  vec4 black = GLM_VEC4_BLACK;
  memcpy(&VAL2VEC4(dest), &black, sizeof(vec4));
  return dest;
}

VALUE rb_cglm_vec4_zero(VALUE self) {
  VALUE dest = VEC4_NEW(ALLOC_VEC4);
  vec4 zero = GLM_VEC4_ZERO;
  memcpy(&VAL2VEC4(dest), &zero, sizeof(vec4));
  return dest;
}

VALUE rb_cglm_vec4_copy_to(VALUE self, VALUE other) {
  glm_vec4_copy(VAL2VEC4(self), VAL2VEC4(other));
  return other;
}

/* call-seq: zero! => self
 *
 * Sets all fields in `self` to `0` and returns `self`.
 */
VALUE rb_cglm_vec4_zero_self(VALUE self) {
  glm_vec4_zero(VAL2VEC4(self));
  return self;
}

/* call-seq: one! => self
 *
 * Sets all fields in `self` to `1` and returns `self`.
 */
VALUE rb_cglm_vec4_one_self(VALUE self) {
  glm_vec4_one(VAL2VEC4(self));
  return self;
}

VALUE rb_cglm_vec4_dot(VALUE self, VALUE other) {
  return DBL2NUM(glm_vec4_dot(VAL2VEC4(self), VAL2VEC4(other)));
}

/* call-seq: norm2 => Numeric
 *
 * Returns the norm (magnitude) of this vector, squared. Call this rather than
 * `norm ** 2` to avoid an unnecessary square root.
 */
VALUE rb_cglm_vec4_norm2(VALUE self) {
  return DBL2NUM(glm_vec4_norm2(VAL2VEC4(self)));
}

/* call-seq: norm => Numeric
 *
 * Returns the norm (magnitude) of this vector.
 */
VALUE rb_cglm_vec4_norm(VALUE self) {
  return DBL2NUM(glm_vec4_norm(VAL2VEC4(self)));
}

/* call-seq: add_vec4(b[, dest]) => dest | new Vec4
 *
 * Adds `self` and `b` together, placing the result in `dest`. If `dest` is
 * omitted, a new Vec4 is created and returned.
 */
VALUE rb_cglm_vec4_add_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_add(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: add_scalar(b[, dest]) => dest | new Vec4
 *
 * Adds the Numeric `b` to each component of `self`, placing the result in
 * `dest`. If `dest` is omitted, a new Vec4 is created and returned.
 */
VALUE rb_cglm_vec4_add_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_adds(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: sub_vec4(b[, dest]) => dest | new Vec4
 *
 * Subtracts `b` from `self`, placing the result in `dest`. If `dest` is
 * omitted, a new Vec4 is created and returned.
 */
VALUE rb_cglm_vec4_sub_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_sub(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: sub_scalar(b[, dest]) => dest | new Vec4
 *
 * Subtracts the Numeric `b` from each component of `self`, placing the result
 * in `dest`. If `dest` is omitted, a new Vec4 is created and returned.
 */
VALUE rb_cglm_vec4_sub_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_subs(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: add_vec4!(b) => self
 *
 * Adds `self` and `b` together, modifying `self` in-place and returning it.
 */
VALUE rb_cglm_vec4_add_vec4_self(VALUE self, VALUE b) {
  glm_vec4_add(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(self));
  return self;
}

/* call-seq: add_scalar!(b) => self
 *
 * Adds the Numeric `b` to each component of `self`, modifying `self` in-place
 * and returning it.
 */
VALUE rb_cglm_vec4_add_scalar_self(VALUE self, VALUE b) {
  glm_vec4_adds(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(self));
  return self;
}

/* call-seq: sub_vec4!(b) => self
 *
 * Subtracts `b` from `self`, modifying `self` in-place and returning it.
 */
VALUE rb_cglm_vec4_sub_vec4_self(VALUE self, VALUE b) {
  glm_vec4_sub(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(self));
  return self;
}

/* call-seq: sub_scalar!(b) => self
 *
 * Subtracts the Numeric `b` from each component of `self`, modifying `self`
 * in-place and returning it.
 */
VALUE rb_cglm_vec4_sub_scalar_self(VALUE self, VALUE b) {
  glm_vec4_subs(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(self));
  return self;
}

/* call-seq: mul_vec4(b[, dest]) => dest | new Vec4
 *
 * Multiplies two vectors (component-wise multiplication). Places the result
 * in `dest` and returns `dest`. If `dest` is omitted, a new Vec4 is used
 * instead.
 */
VALUE rb_cglm_vec4_mul_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_mul(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: mul_vec4!(b) => self
 *
 * Multiplies two vectors (component-wise multiplication). Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec4_mul_vec4_self(VALUE self, VALUE b) {
  glm_vec4_mul(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(self));
  return self;
}

/* call-seq: mul_scalar(b[, dest]) => dest | new Vec4
 *
 * Multiplies each component in `self` with the scalar `b` and places the
 * result into `dest`. If `dest` is omitted, a new Vec4 is used
 * instead. Returns `dest`.
 */
VALUE rb_cglm_vec4_mul_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_scale(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: mul_scalar!(b) => self
 *
 * Multiplies each component in `self` with the scalar `b`. Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec4_mul_scalar_self(VALUE self, VALUE b) {
  glm_vec4_scale(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(self));
  return self;
}

/* call-seq: resize(b[, dest]) => dest | new Vec4
 *
 * Same as `normalize(self) * b`. Places the result in `dest` and
 * creates a new Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_vec4_resize(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_scale_as(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: resize!(b) => self
 *
 * Same as `normalize(self) * b`. Modifies `self` in-place and returns `self`.
 */
VALUE rb_cglm_vec4_resize_self(VALUE self, VALUE b) {
  glm_vec4_scale_as(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(self));
  return self;
}

/* call-seq: div_vec4(b[, dest]) => dest | new Vec4
 *
 * Divides two vectors (component-wise division). Places the result
 * in `dest` and returns `dest`. If `dest` is omitted, a new Vec4 is used
 * instead.
 */
VALUE rb_cglm_vec4_div_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_div(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: div_vec4!(b) => self
 *
 * Divides two vectors (component-wise division). Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec4_div_vec4_self(VALUE self, VALUE b) {
  glm_vec4_div(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(self));
  return self;
}

/* call-seq: div_scalar(b[, dest]) => dest | new Vec4
 *
 * Divides each component in `self` by the scalar `b` and places the
 * result into `dest`. If `dest` is omitted, a new Vec4 is used
 * instead. Returns `dest`.
 */
VALUE rb_cglm_vec4_div_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_divs(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: div_scalar!(b) => self
 *
 * Divides each component in `self` by the scalar `b`. Modifies `self`
 * in-place and returns `self`.
 */
VALUE rb_cglm_vec4_div_scalar_self(VALUE self, VALUE b) {
  glm_vec4_divs(VAL2VEC4(self), NUM2FLT(b), VAL2VEC4(self));
  return self;
}

/* call-seq: addadd_vec4(other, dest) => dest
 *
 * Adds `self` to `other` and adds that result to `dest`. Equivalent to
 * `dest += (self + other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec4_addadd_vec4(VALUE self, VALUE other, VALUE dest) {
  glm_vec4_addadd(VAL2VEC4(self), VAL2VEC4(other), VAL2VEC4(dest));
  return dest;
}

/* call-seq: subadd_vec4(other, dest) => dest
 *
 * Subtracts `other` from `self` and adds that result to `dest`. Equivalent to
 * `dest += (self - other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec4_subadd_vec4(VALUE self, VALUE other, VALUE dest) {
  glm_vec4_subadd(VAL2VEC4(self), VAL2VEC4(other), VAL2VEC4(dest));
  return dest;
}

/* call-seq: muladd_vec4(other, dest) => dest
 *
 * Multiplies `self` with `other` and adds that result to `dest`. Equivalent to
 * `dest += (self * other)`. Returns `dest`.
 *
 * * `dest` is not optional for this method, as it is for most others.
 */
VALUE rb_cglm_vec4_muladd_vec4(VALUE self, VALUE other, VALUE dest) {
  glm_vec4_muladd(VAL2VEC4(self), VAL2VEC4(other), VAL2VEC4(dest));
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
VALUE rb_cglm_vec4_muladd_scalar(VALUE self, VALUE other, VALUE dest) {
  glm_vec4_muladds(VAL2VEC4(self), NUM2FLT(other), VAL2VEC4(dest));
  return dest;
}

/* call-seq: flip_signs([dest]) => dest | new Vec4
 *
 * Flips the sign of each component and places the result into `dest`. Returns
 * `dest`. If `dest` is omitted, a new Vec4 is allocated.
 */
VALUE rb_cglm_vec4_flip_signs(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_flipsign_to(VAL2VEC4(self), VAL2VEC4(dest));
  return dest;
}

/* call-seq: flip_signs! => self
 *
 * Flips the sign of each component, modifying `self` in-place. Returns `self`.
 */
VALUE rb_cglm_vec4_flip_signs_self(VALUE self) {
  glm_vec4_flipsign(VAL2VEC4(self));
  return self;
}

/* call-seq: distance(vec) => Numeric
 *
 * Returns the distance between this vector and the specified one.
 */
VALUE rb_cglm_vec4_distance(VALUE self, VALUE b) {
  return DBL2NUM(glm_vec4_distance(VAL2VEC4(self), VAL2VEC4(b)));
}

/* call-seq: max(vec[, dest]) => dest | new Vec4
 *
 * Finds the higher of each component (x, y, z) between `self` and `vec`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_vec4_max(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_maxv(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: min(vec[, dest]) => dest | new Vec4
 *
 * Finds the lower of each component (x, y, z) between `self` and `vec`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_vec4_min(int argc, VALUE *argv, VALUE self) {
  VALUE b, dest;
  rb_scan_args(argc, argv, "11", &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_minv(VAL2VEC4(self), VAL2VEC4(b), VAL2VEC4(dest));
  return dest;
}

/* call-seq: clamp_scalar(min, max[, dest]) => dest | new Vec4
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_vec4_clamp_scalar(int argc, VALUE *argv, VALUE self) {
  VALUE a, b, dest;
  rb_scan_args(argc, argv, "21", &a, &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  memcpy(&VAL2VEC4(dest), &VAL2VEC4(self), sizeof(vec4));
  glm_vec4_clamp(VAL2VEC4(dest), NUM2FLT(a), NUM2FLT(b));
  return dest;
}

/* call-seq: clamp_scalar!(min, max) => self
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `self` and returns `self`.
 */
VALUE rb_cglm_vec4_clamp_scalar_self(VALUE self, VALUE a, VALUE b) {
  glm_vec4_clamp(VAL2VEC4(self), NUM2FLT(a), NUM2FLT(b));
  return self;
}

/* call-seq: clamp_vec4(min, max[, dest]) => dest | new Vec4
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `dest` and returns `dest`. Creates and returns a new
 * Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_vec4_clamp_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE a, b, dest;
  rb_scan_args(argc, argv, "21", &a, &b, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  memcpy(&VAL2VEC4(dest), &VAL2VEC4(self), sizeof(vec4));
  vec4 *s = &VAL2VEC4(dest);
  vec4 *low = &VAL2VEC4(a);
  vec4 *high = &VAL2VEC4(b);
  for (int i = 0; i < 4; i++) {
    (*s)[i] = (*low)[i] > (*high)[i] ? (*low)[i] : (*high)[i];
  }
  return dest;
}

/* call-seq: clamp_vec4!(min, max) => self
 *
 * Clamps each component in `self` to the range given by `min` and `max`.
 * Places the result into `self` and returns `self`.
 */
VALUE rb_cglm_vec4_clamp_vec4_self(VALUE self, VALUE a, VALUE b) {
  vec4 *s = &VAL2VEC4(self);
  vec4 *low = &VAL2VEC4(a);
  vec4 *high = &VAL2VEC4(b);
  for (int i = 0; i < 4; i++) {
    (*s)[i] = (*low)[i] > (*high)[i] ? (*low)[i] : (*high)[i];
  }
  return self;
}

/* call-seq: lerp!(from, to, amount) => self
 *
 * Performs linear interpolation between `from` and `to`, both of which should
 * be Vec4's, by the specified `amount` which should be a number. Modifies
 * `self` in-place and returns `self`.
 */
VALUE rb_cglm_vec4_lerp_self(VALUE self, VALUE from, VALUE to, VALUE amount) {
  glm_vec4_lerp(VAL2VEC4(from), VAL2VEC4(to), NUM2FLT(amount), VAL2VEC4(self));
  return self;
}

/* call-seq: broadcast!(val) => self
 *
 * Sets each member of `self` to the specified Numeric value and returns
 * `self`.
 */
VALUE rb_cglm_vec4_broadcast_self(VALUE self, VALUE val) {
  glm_vec4_broadcast(NUM2FLT(val), VAL2VEC4(self));
  return self;
}

/* call-seq: equals_scalar(val) => true|false
 *
 * Returns true if the given scalar value exactly equals each component of
 * this Vec4, false otherwise.
 */
VALUE rb_cglm_vec4_equals_scalar(VALUE self, VALUE val) {
  return glm_vec4_eq(VAL2VEC4(self), NUM2FLT(val)) ? Qtrue : Qfalse;
}

/* call-seq: equalish_scalar(val[, epsilon]) => true|false
 *
 * Returns true if the given scalar value is very close to each component of
 * this Vec4, false otherwise. Useful for dealing with the loss of precision
 * during floating point arithmetic.
 */
VALUE rb_cglm_vec4_equalish_scalar(int argc, VALUE *argv, VALUE self) {
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
 * Returns true if each component in this Vec4 has the same exact value.
 */
VALUE rb_cglm_vec4_equals_all(VALUE self) {
  return glm_vec4_eq_all(VAL2VEC4(self)) ? Qtrue : Qfalse;
}

/* call-seq: equals_vec4(other) => true|false
 *
 * Returns true if this vector exactly matches the given one.
 */
VALUE rb_cglm_vec4_equals_vec4(VALUE self, VALUE other) {
  return glm_vec4_eqv(VAL2VEC4(self), VAL2VEC4(other)) ? Qtrue : Qfalse;
}

/* call-seq: equalish_vec4(other[, epsilon]) => true|false
 *
 * Returns true if this vector is very close to equal to the given one. Useful
 * for dealing with the loss of precision during floating point arithmetic.
 */
VALUE rb_cglm_vec4_equalish_vec4(int argc, VALUE *argv, VALUE self) {
  VALUE val, eps;
  float epsil = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &val, &eps);
  if (!NIL_P(eps)) epsil = NUM2FLT(eps);
  vec4 *s = &VAL2VEC4(val);
  vec4 *v = &VAL2VEC4(self);
  return fabsf((*v)[0] - (*s)[0]) <= eps &&
         fabsf((*v)[1] - (*s)[1]) <= eps &&
         fabsf((*v)[2] - (*s)[2]) <= eps &&
         fabsf((*v)[3] - (*s)[3]) <= eps ? Qtrue : Qfalse;
}

/* call-seq: highest => Numeric
 *
 * Returns the value of the highest component in this Vec4.
 */
VALUE rb_cglm_vec4_highest(VALUE self) {
  return DBL2NUM(glm_vec4_max(VAL2VEC4(self)));
}

/* call-seq: lowest => Numeric
 *
 * Returns the value of the lowest component in this Vec4.
 */
VALUE rb_cglm_vec4_lowest(VALUE self) {
  return DBL2NUM(glm_vec4_min(VAL2VEC4(self)));
}

/* call-seq: nan? => true|false
 *
 * Returns true if any component in this vector is nan, false otherwise.
 * You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec4_is_nan(VALUE self) {
  return glm_vec4_isnan(VAL2VEC4(self)) ? Qtrue : Qfalse;
}

/* call-seq: inf? => true|false
 *
 * Returns true if any component in this vector is inf, false otherwise.
 * You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec4_is_inf(VALUE self) {
  return glm_vec4_isinf(VAL2VEC4(self)) ? Qtrue : Qfalse;
}

/* call-seq: valid? => true|false
 *
 * Returns true if no component in this vector is NaN or infinite, false
 * otherwise. You should only use this in DEBUG mode or very critical asserts.
 */
VALUE rb_cglm_vec4_is_valid(VALUE self) {
  return glm_vec4_isvalid(VAL2VEC4(self)) ? Qtrue : Qfalse;
}

/* call-seq: signs([dest]) => dest | new Vec4
 *
 * Places `+1`, `0` or `-1` into each component of `dest` based on whether the
 * corresponding component of this Vec4 is positive, `0`/`NaN`, or negative.
 * If `dest` is omitted, a new Vec4 is created and returned.
 */
VALUE rb_cglm_vec4_signs(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_sign(VAL2VEC4(self), VAL2VEC4(dest));
  return dest;
}

/* call-seq: sqrt([dest]) => dest | new Vec4
 *
 * For each component of this Vec4, places the square root of that component
 * into `dest`. If `dest` is omitted, a new Vec4 is created. Returns `dest`.
 */
VALUE rb_cglm_vec4_sqrt(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_sqrt(VAL2VEC4(self), VAL2VEC4(dest));
  return dest;
}

/* call-seq: random([dest]) => dest | new Vec4
 *
 * Fills `dest` or a new Vec4 with random values, and returns it.
 */
VALUE rb_cglm_vec4_new_random(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);

  VAL2VEC4(dest)[0] = drand48();
  VAL2VEC4(dest)[1] = drand48();
  VAL2VEC4(dest)[2] = drand48();
  VAL2VEC4(dest)[3] = drand48();

  return dest;
}

/* call-seq: normalize([dest]) => dest | new Vec4
 */
VALUE rb_cglm_vec4_normalize(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  glm_vec4_normalize_to(VAL2VEC4(self), VAL2VEC4(dest));
  return dest;
}

/* call-seq: normalize! => self
 */
VALUE rb_cglm_vec4_normalize_self(VALUE self) {
  glm_vec4_normalize(VAL2VEC4(self));
  return self;
}

void Init_cglm_vec4() {
  rb_define_method(rb_cVec4, "[]",                 rb_cglm_vec4_aref,                   1);
  rb_define_method(rb_cVec4, "[]=",                rb_cglm_vec4_aset,                   2);
  rb_define_method(rb_cVec4, "to_vec3",            rb_cglm_vec4_to_vec3,               -1);
  rb_define_method(rb_cVec4, "copy_to",            rb_cglm_vec4_copy_to,                1);
  rb_define_method(rb_cVec4, "zero!",              rb_cglm_vec4_zero_self,              0);
  rb_define_method(rb_cVec4, "one!",               rb_cglm_vec4_one_self,               0);
  rb_define_method(rb_cVec4, "dot",                rb_cglm_vec4_dot,                    1);
  rb_define_method(rb_cVec4, "norm2",              rb_cglm_vec4_norm2,                  0);
  rb_define_method(rb_cVec4, "norm",               rb_cglm_vec4_norm,                   0);
  rb_define_method(rb_cVec4, "add_vec4",           rb_cglm_vec4_add_vec4,              -1);
  rb_define_method(rb_cVec4, "add_scalar",         rb_cglm_vec4_add_scalar,            -1);
  rb_define_method(rb_cVec4, "sub_vec4",           rb_cglm_vec4_sub_vec4,              -1);
  rb_define_method(rb_cVec4, "sub_scalar",         rb_cglm_vec4_sub_scalar,            -1);
  rb_define_method(rb_cVec4, "add_vec4!",          rb_cglm_vec4_add_vec4_self,          1);
  rb_define_method(rb_cVec4, "add_scalar!",        rb_cglm_vec4_add_scalar_self,        1);
  rb_define_method(rb_cVec4, "sub_vec4!",          rb_cglm_vec4_sub_vec4_self,          1);
  rb_define_method(rb_cVec4, "sub_scalar!",        rb_cglm_vec4_sub_scalar_self,        1);
  rb_define_method(rb_cVec4, "mul_vec4",           rb_cglm_vec4_mul_vec4,              -1);
  rb_define_method(rb_cVec4, "mul_vec4!",          rb_cglm_vec4_mul_vec4_self,          1);
  rb_define_method(rb_cVec4, "mul_scalar",         rb_cglm_vec4_mul_scalar,            -1);
  rb_define_method(rb_cVec4, "mul_scalar!",        rb_cglm_vec4_mul_scalar_self,        1);
  rb_define_method(rb_cVec4, "div_vec4",           rb_cglm_vec4_div_vec4,              -1);
  rb_define_method(rb_cVec4, "div_vec4!",          rb_cglm_vec4_div_vec4_self,          1);
  rb_define_method(rb_cVec4, "div_scalar",         rb_cglm_vec4_div_scalar,            -1);
  rb_define_method(rb_cVec4, "div_scalar!",        rb_cglm_vec4_div_scalar_self,        1);
  rb_define_method(rb_cVec4, "resize",             rb_cglm_vec4_resize,                -1);
  rb_define_method(rb_cVec4, "resize!",            rb_cglm_vec4_resize_self,            1);
  rb_define_method(rb_cVec4, "addadd_vec4",        rb_cglm_vec4_addadd_vec4,            2);
  rb_define_method(rb_cVec4, "subadd_vec4",        rb_cglm_vec4_subadd_vec4,            2);
  rb_define_method(rb_cVec4, "muladd_scalar",      rb_cglm_vec4_muladd_scalar,          2);
  rb_define_method(rb_cVec4, "muladd_vec4",        rb_cglm_vec4_muladd_vec4,            2);
  rb_define_method(rb_cVec4, "flip_signs",         rb_cglm_vec4_flip_signs,            -1);
  rb_define_method(rb_cVec4, "flip_signs!",        rb_cglm_vec4_flip_signs_self,        0);
  rb_define_method(rb_cVec4, "distance",           rb_cglm_vec4_distance,               1);
  rb_define_method(rb_cVec4, "max",                rb_cglm_vec4_max,                   -1);
  rb_define_method(rb_cVec4, "min",                rb_cglm_vec4_min,                   -1);
  rb_define_method(rb_cVec4, "clamp_scalar",       rb_cglm_vec4_clamp_scalar,          -1);
  rb_define_method(rb_cVec4, "clamp_scalar!",      rb_cglm_vec4_clamp_scalar_self,      2);
  rb_define_method(rb_cVec4, "clamp_vec4",         rb_cglm_vec4_clamp_vec4,            -1);
  rb_define_method(rb_cVec4, "clamp_vec4!",        rb_cglm_vec4_clamp_vec4_self,        2);
  rb_define_method(rb_cVec4, "lerp!",              rb_cglm_vec4_lerp_self,              3);
  rb_define_method(rb_cVec4, "broadcast!",         rb_cglm_vec4_broadcast_self,         1);
  rb_define_method(rb_cVec4, "equals_scalar",      rb_cglm_vec4_equals_scalar,          1);
  rb_define_method(rb_cVec4, "equalish_scalar",    rb_cglm_vec4_equalish_scalar,       -1);
  rb_define_method(rb_cVec4, "equals_all",         rb_cglm_vec4_equals_all,             0);
  rb_define_method(rb_cVec4, "equals_vec4",        rb_cglm_vec4_equals_vec4,            1);
  rb_define_method(rb_cVec4, "equalish_vec4",      rb_cglm_vec4_equalish_vec4,         -1);
  rb_define_method(rb_cVec4, "highest",            rb_cglm_vec4_highest,                0);
  rb_define_method(rb_cVec4, "lowest",             rb_cglm_vec4_lowest,                 0);
  rb_define_method(rb_cVec4, "nan?",               rb_cglm_vec4_is_nan,                 0);
  rb_define_method(rb_cVec4, "inf?",               rb_cglm_vec4_is_inf,                 0);
  rb_define_method(rb_cVec4, "valid?",             rb_cglm_vec4_is_valid,               0);
  rb_define_method(rb_cVec4, "signs",              rb_cglm_vec4_signs,                 -1);
  rb_define_method(rb_cVec4, "sqrt",               rb_cglm_vec4_sqrt,                  -1);
  rb_define_method(rb_cVec4, "normalize",          rb_cglm_vec4_normalize,             -1);
  rb_define_method(rb_cVec4, "normalize!",         rb_cglm_vec4_normalize_self,         0);

  rb_define_alias(rb_cVec4, "invert",     "flip_signs");
  rb_define_alias(rb_cVec4, "invert!",    "flip_signs!");
  rb_define_alias(rb_cVec4, "magnitude",  "norm");
  rb_define_alias(rb_cVec4, "mag",        "norm");

  rb_define_singleton_method(rb_cVec4, "random",    rb_cglm_vec4_new_random,     -1);
  rb_define_singleton_method(rb_cVec4, "rand",      rb_cglm_vec4_new_random,     -1);
  rb_define_singleton_method(rb_cVec4, "size",      rb_cglm_vec4_size_bytes,      0);
  rb_define_singleton_method(rb_cVec4, "alignment", rb_cglm_vec4_alignment_bytes, 0);
  rb_define_singleton_method(rb_cVec4, "one",       rb_cglm_vec4_one,             0);
  rb_define_singleton_method(rb_cVec4, "black",     rb_cglm_vec4_black,           0);
  rb_define_singleton_method(rb_cVec4, "zero",      rb_cglm_vec4_zero,            0);
}
