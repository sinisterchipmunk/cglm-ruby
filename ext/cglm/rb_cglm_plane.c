#include "rb_cglm.h"

/* call-seq: normalize([dest]) => dest | new Vec4
 *
 * Normalizes this plane and places the result in `dest`, or allocates a new
 * Vec4 if `dest` is omitted.
 */
VALUE rb_cglm_plane_normalize(int argc, VALUE *argv, VALUE self) {
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
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

void Init_cglm_plane() {
  rb_define_method(rb_cVec4, "normalize",  rb_cglm_plane_normalize,     -1);
  rb_define_method(rb_cVec4, "normalize!", rb_cglm_plane_normalize_self, 0);
}
