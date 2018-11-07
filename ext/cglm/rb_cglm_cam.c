#include "rb_cglm.h"

/* call-seq: aspect => Numeric */
VALUE rb_cglm_cam_decomp_aspect(VALUE self) {
  return DBL2NUM(glm_persp_aspect(VAL2MAT4(self)));
}

/* call-seq: fovy => Numeric */
VALUE rb_cglm_cam_decomp_fovy(VALUE self) {
  return DBL2NUM(glm_persp_fovy(VAL2MAT4(self)));
}

/* call-seq: left_and_right => Array */
VALUE rb_cglm_cam_decomp_left_and_right(VALUE self) {
  float left, right;
  glm_persp_decomp_x(VAL2MAT4(self), &left, &right);
  return rb_ary_new_from_args(2, DBL2NUM(left), DBL2NUM(right));
}

/* call-seq: sizes([fovy]) => Hash
 *
 * Returns the sizes of the near and far planes of this perspective
 * projection. The return value has the following format:
 *
 *     { near: [width, height], far: [width, height] }
 *
 * If `fovy` is omitted, it will be decomposed from the current matrix.
 */
VALUE rb_cglm_cam_sizes(int argc, VALUE *argv, VALUE self) {
  VALUE fovy = Qnil;
  if (argc == 0) fovy = rb_cglm_cam_decomp_fovy(self);
  else fovy = argv[0];
  vec4 out;
  glm_persp_sizes(VAL2MAT4(self), NUM2FLT(fovy), out);
  VALUE near = rb_ary_new_from_args(2, DBL2NUM(out[0]), DBL2NUM(out[1]));
  VALUE far  = rb_ary_new_from_args(2, DBL2NUM(out[2]), DBL2NUM(out[3]));
  VALUE dest = rb_hash_new();
  rb_hash_aset(dest, ID2SYM(rb_intern("near")), near);
  rb_hash_aset(dest, ID2SYM(rb_intern("far")), far);
  return dest;
}

/* call-seq: top_and_bottom => Array */
VALUE rb_cglm_cam_decomp_top_and_bottom(VALUE self) {
  float top, bottom;
  glm_persp_decomp_y(VAL2MAT4(self), &top, &bottom);
  return rb_ary_new_from_args(2, DBL2NUM(top), DBL2NUM(bottom));
}

/* call-seq: near_and_far => Array */
VALUE rb_cglm_cam_decomp_near_and_far(VALUE self) {
  float near, far;
  glm_persp_decomp_z(VAL2MAT4(self), &near, &far);
  return rb_ary_new_from_args(2, DBL2NUM(near), DBL2NUM(far));
}

/* call-seq: left => Numeric */
VALUE rb_cglm_cam_decomp_left(VALUE self) {
  float left, right;
  glm_persp_decomp_x(VAL2MAT4(self), &left, &right);
  return DBL2NUM(left);
}

/* call-seq: right => Numeric */
VALUE rb_cglm_cam_decomp_right(VALUE self) {
  float left, right;
  glm_persp_decomp_x(VAL2MAT4(self), &left, &right);
  return DBL2NUM(right);
}

/* call-seq: top => Numeric */
VALUE rb_cglm_cam_decomp_top(VALUE self) {
  float top, bottom;
  glm_persp_decomp_y(VAL2MAT4(self), &top, &bottom);
  return DBL2NUM(top);
}

/* call-seq: bottom => Numeric */
VALUE rb_cglm_cam_decomp_bottom(VALUE self) {
  float top, bottom;
  glm_persp_decomp_y(VAL2MAT4(self), &top, &bottom);
  return DBL2NUM(bottom);
}

/* call-seq: near => Numeric */
VALUE rb_cglm_cam_decomp_near(VALUE self) {
  float near;
  glm_persp_decomp_near(VAL2MAT4(self), &near);
  return DBL2NUM(near);
}

/* call-seq: far => Numeric */
VALUE rb_cglm_cam_decomp_far(VALUE self) {
  float far;
  glm_persp_decomp_far(VAL2MAT4(self), &far);
  return DBL2NUM(far);
}


/*
 * call-seq: frustum() => Hash
 *
 * Decomposes this perspective matrix into a hash containing the 6 frustum
 * values: `:near`, `:far`, `:top`, `:bottom`, `:left`, and `:right`.
 */
VALUE rb_cglm_cam_frustum_decomp(VALUE self) {
  VALUE hash = rb_hash_new();
  float left, top, right, bottom, near, far;
  glm_persp_decomp(VAL2MAT4(self), &near, &far, &top, &bottom, &left, &right);
  rb_hash_aset(hash, ID2SYM(rb_intern("near")),   DBL2NUM(near));
  rb_hash_aset(hash, ID2SYM(rb_intern("far")),    DBL2NUM(far));
  rb_hash_aset(hash, ID2SYM(rb_intern("left")),   DBL2NUM(left));
  rb_hash_aset(hash, ID2SYM(rb_intern("right")),  DBL2NUM(right));
  rb_hash_aset(hash, ID2SYM(rb_intern("bottom")), DBL2NUM(bottom));
  rb_hash_aset(hash, ID2SYM(rb_intern("top")),    DBL2NUM(top));
  return hash;
}

/* call-seq: look(eye, direction[, up, dest]) => dest | new Mat4
 *
 * Convenience wrapper for {look_at} for if you only have direction and not
 * the target position.
 *
 * If `up` is omitted (or nil), it is assumed that you don't care what it is,
 * and one will be computed for you.
 *
 * Note: The `up` vector must not be parallel to the line of sight from the
 *       eye point to the reference point.
 */
VALUE rb_cglm_cam_look(int argc, VALUE *argv, VALUE self) {
  VALUE dest, eye, dir, up;
  rb_scan_args(argc, argv, "31", &eye, &dir, &up, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  if (NIL_P(up))
    glm_look_anyup(VAL2VEC3(eye), VAL2VEC3(dir), VAL2MAT4(dest));
  else
    glm_look(VAL2VEC3(eye), VAL2VEC3(dir), VAL2VEC3(up), VAL2MAT4(dest));
  return dest;
}

/* call-seq: look_at(eye, target_position, up[, dest]) => dest | new Mat4
 *
 * Sets up a view matrix.
 *
 * NOTE: The `up` vector must not be parallel to the line of sight from the
 *       eye point to the reference point.
 */
VALUE rb_cglm_cam_look_at(int argc, VALUE *argv, VALUE self) {
  VALUE dest, eye, center, up;
  rb_scan_args(argc, argv, "31", &eye, &center, &up, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_lookat(VAL2VEC3(eye), VAL2VEC3(center), VAL2VEC3(up), VAL2MAT4(dest));
  return dest;
}

/* call-seq: perspective_resize!(aspect) => self
 *
 * Resizes this perspective matrix by the given aspect ratio (`width / height`).
 * This makes it very easy to resize the projective matrix when the window or
 * viewport is changed.
 */
VALUE rb_cglm_cam_perspective_resize_self(VALUE self, VALUE aspect) {
  glm_perspective_resize(NUM2FLT(aspect), VAL2MAT4(self));
  return self;
}

/* call-seq: perspective([dest], fovy: PI/4, aspect:, near: 0.1, far: 100.0) => dest | new Mat4
 *
 * Sets up a perspective projection matrix.
 */
VALUE rb_cglm_cam_perspective(int argc, VALUE *argv, VALUE self) {
  static ID kwargs_ids[4];
  if (!kwargs_ids[0]) {
    kwargs_ids[0] = rb_intern_const("aspect");
    kwargs_ids[1] = rb_intern_const("fovy");
    kwargs_ids[2] = rb_intern_const("near");
    kwargs_ids[3] = rb_intern_const("far");
  };
  VALUE dest, kwargs[4], opts;
  rb_scan_args(argc, argv, "01:", &dest, &opts);
  rb_get_kwargs(opts, kwargs_ids, 1, 3, kwargs);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  if (RB_TYPE_P(kwargs[1], T_UNDEF)) kwargs[1] = DBL2NUM(GLM_PI_4f);
  if (RB_TYPE_P(kwargs[2], T_UNDEF)) kwargs[2] = DBL2NUM(0.1);
  if (RB_TYPE_P(kwargs[3], T_UNDEF)) kwargs[3] = DBL2NUM(100.0);
  glm_perspective(NUM2FLT(kwargs[1]),
                  NUM2FLT(kwargs[0]),
                  NUM2FLT(kwargs[2]),
                  NUM2FLT(kwargs[3]),
                  VAL2MAT4(dest));
  return dest;
}

/* call-seq: ortho_cube(aspect, size[, dest]) => dest | new Mat4
 *
 * Sets up a new cubed orthographic projection matrix (it has the same size in
 * all dimensions).
 */
VALUE rb_cglm_cam_ortho_cube(int argc, VALUE *argv, VALUE self) {
  VALUE aspect, size, dest;
  rb_scan_args(argc, argv, "21", &aspect, &size, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_ortho_default_s(NUM2FLT(aspect), NUM2FLT(size), VAL2MAT4(dest));
  return dest;
}

/* call-seq: ortho_unit(aspect[, dest]) => dest | new Mat4
 *
 * Sets up a unit orthographic projection matrix.
 */
VALUE rb_cglm_cam_ortho_unit(int argc, VALUE *argv, VALUE self) {
  VALUE aspect, dest;
  rb_scan_args(argc, argv, "11", &aspect, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_ortho_default(NUM2FLT(aspect), VAL2MAT4(dest));
  return dest;
}

/* call-seq: ortho_aabb(aabb[, dest], padding: 0, padding_z: 0) => dest | new Mat4
 *
 * Sets up an orthographic projection matrix using the given bounding box.
 *
 * If `dest` is omitted, a new Mat4 will be allocated and returned. Otherwise,
 * the result will be placed into `dest` and returned.
 *
 * If `padding` is present and `padding_z` is omitted, then the entire projection
 * will have the same padding (including near/far values). If both are present,
 * the near/far values will use `padding_z` while all other values will be
 * padded with `padding`.
 */
VALUE rb_cglm_cam_ortho_aabb(int argc, VALUE *argv, VALUE self) {
  VALUE boxv, dest, opts;
  static ID kwargs_ids[2];
  if (!kwargs_ids[0]) {
    kwargs_ids[0] = rb_intern_const("padding");
    kwargs_ids[1] = rb_intern_const("padding_z");
  }
  VALUE kwargs[2];
  rb_scan_args(argc, argv, "11:", &boxv, &dest, &opts);
  rb_get_kwargs(opts, kwargs_ids, 0, 2, kwargs);
  aabb box = VAL2AABB(boxv);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  if (RB_TYPE_P(kwargs[0], T_UNDEF)) {
    if (RB_TYPE_P(kwargs[1], T_UNDEF)) {
      glm_ortho_aabb(box.corners, VAL2MAT4(dest));
    } else {
      glm_ortho_aabb_pz(box.corners, NUM2FLT(kwargs[1]), VAL2MAT4(dest));
    }
  }
  else{
    if (RB_TYPE_P(kwargs[1], T_UNDEF)) {
      glm_ortho_aabb_p(box.corners, NUM2FLT(kwargs[0]), VAL2MAT4(dest));
    } else {
      float padding  = NUM2FLT(kwargs[0]);
      float paddingz = NUM2FLT(kwargs[1]);
      glm_ortho(box.corners[0][0] - padding,     box.corners[1][0] + padding,
                box.corners[0][1] - padding,     box.corners[1][1] + padding,
              -(box.corners[1][2] + paddingz), -(box.corners[0][2] - paddingz),
                VAL2MAT4(dest));
    }
  }
  return dest;
}

/* call-seq: ortho([dest], left:, right:, bottom:, top:, near:, far:) => dest | new Mat4
 *
 * Sets up an orthographic projection matrix. `dest` is a Mat4. If it is
 * omitted, it is created.
 *
 * * `left` is the viewport left
 * * `right` is the viewport right
 * * `bottom` is the viewport bottom
 * * `top` is the viewport top
 * * `near` is the near clipping plane
 * * `far` is the far clipping plane
 * * `dest` is the result matrix
 *
 */
VALUE rb_cglm_cam_ortho(int argc, VALUE *argv, VALUE klass) {
  static ID kwargs_ids[6];
  if (!kwargs_ids[0]) {
    kwargs_ids[0] = rb_intern_const("left");
    kwargs_ids[1] = rb_intern_const("right");
    kwargs_ids[2] = rb_intern_const("bottom");
    kwargs_ids[3] = rb_intern_const("top");
    kwargs_ids[4] = rb_intern_const("near");
    kwargs_ids[5] = rb_intern_const("far");
  };
  VALUE dest, kwargs[6], opts;
  rb_scan_args(argc, argv, "01:", &dest, &opts);
  rb_get_kwargs(opts, kwargs_ids, 6, 0, kwargs);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_ortho(NUM2FLT(kwargs[0]),
            NUM2FLT(kwargs[1]),
            NUM2FLT(kwargs[2]),
            NUM2FLT(kwargs[3]),
            NUM2FLT(kwargs[4]),
            NUM2FLT(kwargs[5]),
            VAL2MAT4(dest));
  return dest;
}

/* call-seq: frustum([dest], left:, right:, bottom:, top:, near:, far:) => dest | new Mat4
 *
 * Sets up a perspective projection matrix. `dest` is a Mat4. If it is
 * omitted, it is created.
 *
 * * `left` is the viewport left
 * * `right` is the viewport right
 * * `bottom` is the viewport bottom
 * * `top` is the viewport top
 * * `near` is the near clipping plane
 * * `far` is the far clipping plane
 * * `dest` is the result matrix
 *
 */
VALUE rb_cglm_cam_frustum(int argc, VALUE *argv, VALUE klass) {
  static ID kwargs_ids[6];
  if (!kwargs_ids[0]) {
    kwargs_ids[0] = rb_intern_const("left");
    kwargs_ids[1] = rb_intern_const("right");
    kwargs_ids[2] = rb_intern_const("bottom");
    kwargs_ids[3] = rb_intern_const("top");
    kwargs_ids[4] = rb_intern_const("near");
    kwargs_ids[5] = rb_intern_const("far");
  };
  VALUE dest, kwargs[6], opts;
  rb_scan_args(argc, argv, "01:", &dest, &opts);
  rb_get_kwargs(opts, kwargs_ids, 6, 0, kwargs);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_frustum(NUM2FLT(kwargs[0]),
              NUM2FLT(kwargs[1]),
              NUM2FLT(kwargs[2]),
              NUM2FLT(kwargs[3]),
              NUM2FLT(kwargs[4]),
              NUM2FLT(kwargs[5]),
              VAL2MAT4(dest));
  return dest;
}

void Init_cglm_cam() {
  rb_define_method(rb_cMat4, "perspective_resize!",    rb_cglm_cam_perspective_resize_self,       1);
  rb_define_method(rb_cMat4, "frustum",                rb_cglm_cam_frustum_decomp,                0);
  rb_define_method(rb_cMat4, "left_and_right",         rb_cglm_cam_decomp_left_and_right,         0);
  rb_define_method(rb_cMat4, "top_and_bottom",         rb_cglm_cam_decomp_top_and_bottom,         0);
  rb_define_method(rb_cMat4, "near_and_far",           rb_cglm_cam_decomp_near_and_far,           0);
  rb_define_method(rb_cMat4, "left",                   rb_cglm_cam_decomp_left,                   0);
  rb_define_method(rb_cMat4, "right",                  rb_cglm_cam_decomp_right,                  0);
  rb_define_method(rb_cMat4, "top",                    rb_cglm_cam_decomp_top,                    0);
  rb_define_method(rb_cMat4, "bottom",                 rb_cglm_cam_decomp_bottom,                 0);
  rb_define_method(rb_cMat4, "near",                   rb_cglm_cam_decomp_near,                   0);
  rb_define_method(rb_cMat4, "far",                    rb_cglm_cam_decomp_far,                    0);
  rb_define_method(rb_cMat4, "fovy",                   rb_cglm_cam_decomp_fovy,                   0);
  rb_define_method(rb_cMat4, "aspect",                 rb_cglm_cam_decomp_aspect,                 0);
  rb_define_method(rb_cMat4, "sizes",                  rb_cglm_cam_sizes,                        -1);

  rb_define_singleton_method(rb_cMat4, "frustum",     rb_cglm_cam_frustum,     -1);
  rb_define_singleton_method(rb_cMat4, "ortho",       rb_cglm_cam_ortho,       -1);
  rb_define_singleton_method(rb_cMat4, "ortho_aabb",  rb_cglm_cam_ortho_aabb,  -1);
  rb_define_singleton_method(rb_cMat4, "ortho_unit",  rb_cglm_cam_ortho_unit,  -1);
  rb_define_singleton_method(rb_cMat4, "ortho_cube",  rb_cglm_cam_ortho_cube,  -1);
  rb_define_singleton_method(rb_cMat4, "perspective", rb_cglm_cam_perspective, -1);
  rb_define_singleton_method(rb_cMat4, "look_at",     rb_cglm_cam_look_at,     -1);
  rb_define_singleton_method(rb_cMat4, "look",        rb_cglm_cam_look,        -1);
}
