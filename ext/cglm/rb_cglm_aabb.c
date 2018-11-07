#include "rb_cglm.h"

/* call-seq: transform(mat4[, dest]) => dest | new AABB
 *
 * Applies transform to an axis-aligned bounding box, placing the result in
 * `dest` and allocating it if necessary.
 */
VALUE rb_cglm_aabb_transform(int argc, VALUE *argv, VALUE self) {
  VALUE matr, dest;
  rb_scan_args(argc, argv, "11", &matr, &dest);
  if (NIL_P(dest)) dest = AABB_NEW(ALLOC_AABB);
  mat4 *m;
  aabb *a, *b;
  m = &VAL2MAT4(matr);
  a = &VAL2AABB(self);
  b = &VAL2AABB(dest);
  glm_aabb_transform(a->corners, *m, a->corners);
  return dest;
}

/* call-seq: merge(other[, dest]) => dest | new AABB
 *
 * Merges two axis-aligned bounding boxes, storing the result in `dest`. If
 * `dest` is omitted, a new AABB is created. Returns `dest`.
 *
 * Both boxes must be in the same space.
 */
VALUE rb_cglm_aabb_merge(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = AABB_NEW(ALLOC_AABB);
  aabb *a, *b, *out;
  a = &VAL2AABB(self);
  b = &VAL2AABB(other);
  out = &VAL2AABB(dest);
  glm_aabb_merge(a->corners, b->corners, out->corners);
  return dest;
}

/* call-seq: crop(crop[, dest]) => dest | new AABB
 *
 * Crops this AABB by `crop`, placing the result in `dest` or creating a new
 * one. Returns `dest`.
 *
 * This could be useful for gettng an AABB which fits with view frustum and
 * object bounding boxes. In this case you crop view frustum box with object's
 * box.
 */
VALUE rb_cglm_aabb_crop(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = AABB_NEW(ALLOC_AABB);
  aabb *a, *b, *out;
  a = &VAL2AABB(self);
  b = &VAL2AABB(other);
  out = &VAL2AABB(dest);
  glm_aabb_crop(a->corners, b->corners, out->corners);
  return dest;
}

/* call-seq: crop_until(crop, clamp[, dest]) => dest | new AABB
 *
 * Crops this AABB by `crop`, placing the result in `dest` or creating a new
 * one. Returns `dest`. If the result would be smaller than `clamp`, it is
 * restricted to the extents of `clamp` instead.
 *
 * This could be useful for gettng a bbox which fits with view frustum and
 * object bounding boxes. In this case you crop view frustum box with objects
 * box.
 */
VALUE rb_cglm_aabb_crop_until(int argc, VALUE *argv, VALUE self) {
  VALUE other, clamp, dest;
  rb_scan_args(argc, argv, "21", &other, &clamp, &dest);
  if (NIL_P(dest)) dest = AABB_NEW(ALLOC_AABB);
  aabb *a, *b, *c, *out;
  a = &VAL2AABB(self);
  b = &VAL2AABB(other);
  c = &VAL2AABB(clamp);
  out = &VAL2AABB(dest);
  glm_aabb_crop_until(a->corners, b->corners, c->corners, out->corners);
  return dest;
}

/* call-seq: intersects_frustum?(frustum) => true|false
 * 
 * Returns true if this AABB intersects the given Frustum, false otherwise.
 */
VALUE rb_cglm_aabb_intersect_frustum(VALUE self, VALUE frstm) {
  aabb *a;
  frustum *f;
  a = &VAL2AABB(self);
  f = &VAL2FRUSTUM(frstm);
  return glm_aabb_frustum(a->corners, f->planes) ? Qtrue : Qfalse;
}

/* call-seq: invalidate => self
 *
 * Invalidates the AABB min and max values.
 */
VALUE rb_cglm_aabb_invalidate_self(VALUE self) {
  aabb *a;
  a = &VAL2AABB(self);
  glm_aabb_invalidate(a->corners);
  return self;
}

/* call-seq: valid? => true|false
 *
 * Returns true if this AABB is valid, false otherwise.
 */
VALUE rb_cglm_aabb_is_valid(VALUE self) {
  aabb *a;
  a = &VAL2AABB(self);
  glm_aabb_isvalid(a->corners);
  return self;
}

/* call-seq: size => number
 * 
 * Returns the length of the diagonal line between the corners of this AABB.
 */
VALUE rb_cglm_aabb_size(VALUE self) {
  aabb *a;
  a = &VAL2AABB(self);
  return DBL2NUM(glm_aabb_size(a->corners));
}

/* call-seq: radius => number
 * 
 * Returns the radius of a sphere which surrounds this AABB.
 */
VALUE rb_cglm_aabb_radius(VALUE self) {
  aabb *a;
  a = &VAL2AABB(self);
  return DBL2NUM(glm_aabb_radius(a->corners));
}

/* call-seq: center([dest]) => dest | new Vec3
 * 
 * Computes the center point of the AABB and places it into the Vec3 `dest`,
 * creating a new one if `dest` is omitted.
 */
VALUE rb_cglm_aabb_center(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  aabb *a;
  vec3 *b;
  a = &VAL2AABB(self);
  b = &VAL2VEC3(dest);
  glm_aabb_center(a->corners, *b);
  return dest;
}

/* call-seq: intersects_aabb?(aabb) => true|false
 * 
 * Returns true if the two AABB's overlap, false otherwise.
 */
VALUE rb_cglm_aabb_intersect_aabb(VALUE self, VALUE other) {
  aabb *a, *b;
  a = &VAL2AABB(self);
  b = &VAL2AABB(other);
  return glm_aabb_aabb(a->corners, b->corners) ? Qtrue : Qfalse;
}

/* call-seq: intersects_sphere?(vec4) => true|false
 * 
 * Returns true if the sphere described by the given Vec4 intersects this
 * AABB, false otherwise.
 */
VALUE rb_cglm_aabb_intersect_sphere(VALUE self, VALUE sphere) {
  aabb *a;
  vec4 *b;
  a = &VAL2AABB(self);
  b = &VAL2VEC4(sphere);
  return glm_aabb_sphere(a->corners, *b) ? Qtrue : Qfalse;
}

/* call-seq: contains_point?(vec3) => true|false
 * 
 * Returns true if this AABB contains the specified point (inclusive), false
 * otherwise.
 */
VALUE rb_cglm_aabb_contains_point(VALUE self, VALUE point) {
  aabb *a;
  vec3 *b;
  a = &VAL2AABB(self);
  b = &VAL2VEC3(point);
  return glm_aabb_point(a->corners, *b) ? Qtrue : Qfalse;
}

/* call-seq: contains_aabb?(aabb) => true|false
 * 
 * Returns true if this AABB contains the specified AABB, false otherwise.
 */
VALUE rb_cglm_aabb_contains_aabb(VALUE self, VALUE other) {
  aabb *a, *b;
  a = &VAL2AABB(self);
  b = &VAL2AABB(other);
  return glm_aabb_contains(a->corners, b->corners) ? Qtrue : Qfalse;
}

VALUE rb_cglm_aabb_aref(VALUE self, VALUE corner_index) {
  CHECK_RANGE(corner_index, 0, 1);
  return VEC3_NEW(VAL2AABB(self).corners[NUM2INT(corner_index)]);
}

VALUE rb_cglm_aabb_aset(VALUE self, VALUE index, VALUE val) {
  CHECK_RANGE(index, 0, 1);
  memcpy(VAL2AABB(self).corners[NUM2INT(index)], VAL2VEC3(val), sizeof(vec3));
  return self;
}

VALUE rb_cglm_aabb_size_bytes(VALUE klass) { return SIZET2NUM(aabb_size()); }

VALUE rb_cglm_aabb_alignment_bytes(VALUE klass) { return SIZET2NUM(AABB_ALIGNMENT); }

VALUE rb_cglm_aabb_equals_aabb(VALUE self, VALUE other) {
  if (memcmp(&VAL2AABB(self), &VAL2AABB(other), sizeof(aabb))) return Qfalse;
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
VALUE rb_cglm_aabb_equalish_aabb(int argc, VALUE *argv, VALUE self) {
  VALUE other, epsilon;
  float feps = FLT_EPSILON;
  rb_scan_args(argc, argv, "11", &other, &epsilon);
  if (!NIL_P(epsilon)) feps = NUM2FLT(epsilon);
  aabb *a = &VAL2AABB(self);
  aabb *b = &VAL2AABB(other);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      if (fabsf((*a).corners[i][j] - (*b).corners[i][j]) > feps)
        return Qfalse;
    }
  }
  return Qtrue;
}

void Init_cglm_box() {
  rb_define_method(rb_cAABB, "==",                  rb_cglm_aabb_equals_aabb,       1);
  rb_define_method(rb_cAABB, "equalish",            rb_cglm_aabb_equalish_aabb,    -1);
  rb_define_method(rb_cAABB, "transform",           rb_cglm_aabb_transform,        -1);
  rb_define_method(rb_cAABB, "merge",               rb_cglm_aabb_merge,            -1);
  rb_define_method(rb_cAABB, "crop",                rb_cglm_aabb_crop,             -1);
  rb_define_method(rb_cAABB, "crop_until",          rb_cglm_aabb_crop_until,       -1);
  rb_define_method(rb_cAABB, "intersects_frustum?", rb_cglm_aabb_intersect_frustum, 1);
  rb_define_method(rb_cAABB, "invalidate!",         rb_cglm_aabb_invalidate_self,   0);
  rb_define_method(rb_cAABB, "valid?",              rb_cglm_aabb_is_valid,          0);
  rb_define_method(rb_cAABB, "size",                rb_cglm_aabb_size,              0);
  rb_define_method(rb_cAABB, "radius",              rb_cglm_aabb_radius,            0);
  rb_define_method(rb_cAABB, "center",              rb_cglm_aabb_center,           -1);
  rb_define_method(rb_cAABB, "intersects_aabb?",    rb_cglm_aabb_intersect_aabb,    1);
  rb_define_method(rb_cAABB, "intersects_sphere?",  rb_cglm_aabb_intersect_sphere,  1);
  rb_define_method(rb_cAABB, "contains_point?",     rb_cglm_aabb_contains_point,    1);
  rb_define_method(rb_cAABB, "contains_aabb?",      rb_cglm_aabb_contains_aabb,     1);
  rb_define_method(rb_cAABB, "[]",                  rb_cglm_aabb_aref,              1);
  rb_define_method(rb_cAABB, "[]=",                 rb_cglm_aabb_aset,              2);

  rb_define_alias(rb_cAABB, "=~", "equalish");

  rb_define_singleton_method(rb_cAABB, "size",      rb_cglm_aabb_size_bytes,      0);
  rb_define_singleton_method(rb_cAABB, "alignment", rb_cglm_aabb_alignment_bytes, 0);
}
