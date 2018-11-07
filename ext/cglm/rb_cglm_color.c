#include "rb_cglm.h"

/* call-seq: luminance => number
 *
 * Averages the RGB color channels into one value
 */
VALUE rb_cglm_color_luminance3(VALUE self) {
  return DBL2NUM(glm_luminance(VAL2VEC3(self)));
}

/* call-seq: luminance => number
 *
 * Averages the RGB color channels into one value and then multiplies the
 * result by the alpha channel.
 */
VALUE rb_cglm_color_luminance4(VALUE self) {
  return DBL2NUM(glm_luminance(VAL2VEC3(self)) * VAL2VEC4(self)[3]);
}

void Init_cglm_color() {
  rb_define_method(rb_cVec3, "luminance", rb_cglm_color_luminance3, 0);
  rb_define_method(rb_cVec4, "luminance", rb_cglm_color_luminance4, 0);
}
