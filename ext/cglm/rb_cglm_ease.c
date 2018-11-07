#include "rb_cglm.h"

VALUE rb_cglm_ease_linear(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_linear(NUM2FLT(val)));
}

VALUE rb_cglm_ease_sine_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_sine_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_sine_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_sine_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_sine_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_sine_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quad_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quad_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quad_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quad_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quad_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quad_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_cubic_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_cubic_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_cubic_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_cubic_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_cubic_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_cubic_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quart_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quart_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quart_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quart_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quart_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quart_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quint_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quint_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quint_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quint_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_quint_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_quint_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_exp_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_exp_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_exp_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_exp_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_exp_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_exp_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_circ_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_circ_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_circ_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_circ_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_circ_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_circ_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_back_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_back_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_back_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_back_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_back_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_back_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_elast_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_elast_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_elast_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_elast_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_elast_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_elast_inout(NUM2FLT(val)));
}

VALUE rb_cglm_ease_bounce_out(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_bounce_out(NUM2FLT(val)));
}

VALUE rb_cglm_ease_bounce_in(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_bounce_in(NUM2FLT(val)));
}

VALUE rb_cglm_ease_bounce_inout(VALUE self, VALUE val) {
  return DBL2NUM(glm_ease_bounce_inout(NUM2FLT(val)));
}

void Init_cglm_ease() {
  VALUE rb_mEasing = rb_define_module_under(rb_mCGLM, "Easing");
  rb_define_method(rb_mEasing, "linear",       rb_cglm_ease_linear,       1);
  rb_define_method(rb_mEasing, "sine_in",      rb_cglm_ease_sine_in,      1);
  rb_define_method(rb_mEasing, "sine_out",     rb_cglm_ease_sine_out,     1);
  rb_define_method(rb_mEasing, "sine_inout",   rb_cglm_ease_sine_inout,   1);
  rb_define_method(rb_mEasing, "quad_in",      rb_cglm_ease_quad_in,      1);
  rb_define_method(rb_mEasing, "quad_out",     rb_cglm_ease_quad_out,     1);
  rb_define_method(rb_mEasing, "quad_inout",   rb_cglm_ease_quad_inout,   1);
  rb_define_method(rb_mEasing, "cubic_in",     rb_cglm_ease_cubic_in,     1);
  rb_define_method(rb_mEasing, "cubic_out",    rb_cglm_ease_cubic_out,    1);
  rb_define_method(rb_mEasing, "cubic_inout",  rb_cglm_ease_cubic_inout,  1);
  rb_define_method(rb_mEasing, "quart_in",     rb_cglm_ease_quart_in,     1);
  rb_define_method(rb_mEasing, "quart_out",    rb_cglm_ease_quart_out,    1);
  rb_define_method(rb_mEasing, "quart_inout",  rb_cglm_ease_quart_inout,  1);
  rb_define_method(rb_mEasing, "quint_in",     rb_cglm_ease_quint_in,     1);
  rb_define_method(rb_mEasing, "quint_out",    rb_cglm_ease_quint_out,    1);
  rb_define_method(rb_mEasing, "quint_inout",  rb_cglm_ease_quint_inout,  1);
  rb_define_method(rb_mEasing, "exp_in",       rb_cglm_ease_exp_in,       1);
  rb_define_method(rb_mEasing, "exp_out",      rb_cglm_ease_exp_out,      1);
  rb_define_method(rb_mEasing, "exp_inout",    rb_cglm_ease_exp_inout,    1);
  rb_define_method(rb_mEasing, "circ_in",      rb_cglm_ease_circ_in,      1);
  rb_define_method(rb_mEasing, "circ_out",     rb_cglm_ease_circ_out,     1);
  rb_define_method(rb_mEasing, "circ_inout",   rb_cglm_ease_circ_inout,   1);
  rb_define_method(rb_mEasing, "back_in",      rb_cglm_ease_back_in,      1);
  rb_define_method(rb_mEasing, "back_out",     rb_cglm_ease_back_out,     1);
  rb_define_method(rb_mEasing, "back_inout",   rb_cglm_ease_back_inout,   1);
  rb_define_method(rb_mEasing, "elast_in",     rb_cglm_ease_elast_in,     1);
  rb_define_method(rb_mEasing, "elast_out",    rb_cglm_ease_elast_out,    1);
  rb_define_method(rb_mEasing, "elast_inout",  rb_cglm_ease_elast_inout,  1);
  rb_define_method(rb_mEasing, "bounce_out",   rb_cglm_ease_bounce_out,   1);
  rb_define_method(rb_mEasing, "bounce_in",    rb_cglm_ease_bounce_in,    1);
  rb_define_method(rb_mEasing, "bounce_inout", rb_cglm_ease_bounce_inout, 1);
}
