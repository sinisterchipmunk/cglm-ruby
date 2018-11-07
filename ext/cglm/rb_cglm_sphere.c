#include "rb_cglm.h"

/* call-seq: transform(mat4[, dest]) => dest | new Sphere
 *
 * Transforms this sphere to put it in the space described by `mat4`, and
 * puts the result into `dest`. If `dest` is omitted, a new Sphere is created.
 */
VALUE rb_cglm_sphere_transform(int argc, VALUE *argv, VALUE self) {
  VALUE matrix, dest;
  rb_scan_args(argc, argv, "11", &matrix, &dest);
  if (NIL_P(dest)) dest = rb_funcall(rb_cSphere, rb_intern("new"), 0);
  glm_sphere_transform(VAL2VEC4(self), VAL2MAT4(matrix), VAL2VEC4(dest));
  return dest;
}

/* call-seq: merge(other[, dest]) => dest | new Sphere
 *
 * Merges two spheres (`self` and `other`) and places the result in `dest`. If
 * `dest` is omitted, a new Sphere will be created.
 *
 * Both spheres must be in the same space. For instance, if one is in world
 * space then the other must be in world space and not in local space.
 *
 * * `other` must be a Sphere or a Vec4 with the layout `[x, y, z, radius]`.
 */
VALUE rb_cglm_sphere_merge(int argc, VALUE *argv, VALUE self) {
  VALUE other, dest;
  rb_scan_args(argc, argv, "11", &other, &dest);
  if (NIL_P(dest)) dest = rb_funcall(rb_cSphere, rb_intern("new"), 0);
  glm_sphere_merge(VAL2VEC4(self), VAL2VEC4(other), VAL2VEC4(dest));
  return dest;
}

/* call-seq: intersects_sphere?(other) => true|false
 *
 * Returns true if `self` intersects `other`, false otherwise.
 *
 * * `other` must be a Sphere or a Vec4 with the layout `[x, y, z, radius]`.
 */
VALUE rb_cglm_sphere_intersects_sphere(VALUE self, VALUE other) {
  return glm_sphere_sphere(VAL2VEC4(self), VAL2VEC4(other)) ? Qtrue : Qfalse;
}

/* call-seq: contains_point?(point) => true|false
 *
 * Returns true if `self` contains the specified Vec3, false otherwise.
 */
VALUE rb_cglm_sphere_contains_point(VALUE self, VALUE point) {
  return glm_sphere_point(VAL2VEC4(self), VAL2VEC3(point)) ? Qtrue : Qfalse;
}

void Init_cglm_sphere() {
  rb_define_method(rb_cSphere, "transform",          rb_cglm_sphere_transform,         -1);
  rb_define_method(rb_cSphere, "merge",              rb_cglm_sphere_merge,             -1);
  rb_define_method(rb_cSphere, "intersects_sphere?", rb_cglm_sphere_intersects_sphere,  1);
  rb_define_method(rb_cSphere, "contains_point?",    rb_cglm_sphere_contains_point,     1);
}
