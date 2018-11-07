#include "rb_cglm.h"

/* call-seq: normalize([dest]) => dest | new Plane
 *
 * Normalizes this plane and places the result in `dest`, or allocates a new
 * Plane if `dest` is omitted.
 */
VALUE rb_cglm_plane_normalize(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = PLANE_NEW(ALLOC_PLANE);
  memcpy(&(VAL2VEC4(self)), &(VAL2VEC4(dest)), sizeof(vec4));
  glm_plane_normalize(VAL2VEC4(dest));
  return dest;
}

/* call-seq: normalize! => self
 *
 * Normalizes this Vec4 (which represents a plane) and returns it.
 */
VALUE rb_cglm_plane_normalize_self(VALUE self) {
  glm_plane_normalize(VAL2VEC4(self));
  return self;
}

VALUE rb_cglm_plane_size_bytes(VALUE klass) { return SIZET2NUM(plane_size()); }

VALUE rb_cglm_plane_alignment_bytes(VALUE klass) { return SIZET2NUM(PLANE_ALIGNMENT); }

void Init_cglm_plane() {
  rb_define_method(rb_cPlane, "normalize",  rb_cglm_plane_normalize,     -1);
  rb_define_method(rb_cPlane, "normalize!", rb_cglm_plane_normalize_self, 0);

  rb_define_singleton_method(rb_cPlane, "size",      rb_cglm_plane_size_bytes,      0);
  rb_define_singleton_method(rb_cPlane, "alignment", rb_cglm_plane_alignment_bytes, 0);
}
