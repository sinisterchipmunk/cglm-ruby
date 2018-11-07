#define GLM_CUSTOM_CLIPSPACE 1
#include "cglm/types.h"

/* near */
static float CSCOORD_LBN[4] = {-1.0f, -1.0f, -1.0f, 1.0f};
static float CSCOORD_LTN[4] = {-1.0f,  1.0f, -1.0f, 1.0f};
static float CSCOORD_RTN[4] = { 1.0f,  1.0f, -1.0f, 1.0f};
static float CSCOORD_RBN[4] = { 1.0f, -1.0f, -1.0f, 1.0f};

/* far */
static float CSCOORD_LBF[4] = {-1.0f, -1.0f,  1.0f, 1.0f};
static float CSCOORD_LTF[4] = {-1.0f,  1.0f,  1.0f, 1.0f};
static float CSCOORD_RTF[4] = { 1.0f,  1.0f,  1.0f, 1.0f};
static float CSCOORD_RBF[4] = { 1.0f, -1.0f,  1.0f, 1.0f};

#define GLM_CSCOORD_LBN { CSCOORD_LBN[0], CSCOORD_LBN[1], CSCOORD_LBN[2], CSCOORD_LBN[3] }
#define GLM_CSCOORD_LTN { CSCOORD_LTN[0], CSCOORD_LTN[1], CSCOORD_LTN[2], CSCOORD_LTN[3] }
#define GLM_CSCOORD_RTN { CSCOORD_RTN[0], CSCOORD_RTN[1], CSCOORD_RTN[2], CSCOORD_RTN[3] }
#define GLM_CSCOORD_RBN { CSCOORD_RBN[0], CSCOORD_RBN[1], CSCOORD_RBN[2], CSCOORD_RBN[3] }
#define GLM_CSCOORD_LBF { CSCOORD_LBF[0], CSCOORD_LBF[1], CSCOORD_LBF[2], CSCOORD_LBF[3] }
#define GLM_CSCOORD_LTF { CSCOORD_LTF[0], CSCOORD_LTF[1], CSCOORD_LTF[2], CSCOORD_LTF[3] }
#define GLM_CSCOORD_RTF { CSCOORD_RTF[0], CSCOORD_RTF[1], CSCOORD_RTF[2], CSCOORD_RTF[3] }
#define GLM_CSCOORD_RBF { CSCOORD_RBF[0], CSCOORD_RBF[1], CSCOORD_RBF[2], CSCOORD_RBF[3] }

#include "rb_cglm.h"
#define SYMBOL(cstr) ID2SYM(rb_intern(cstr))

/* call-seq: planes(space[, dest]) => dest | new Hash
 *
 * Extracts the 6 view frustum planes into an hash of 6 Vec4's. If `dest` is
 * omitted, a new Hash is allocated.
 *
 * * `space` is the Mat4 representing the space in which the 6 frustum planes
 *   are defined. If it's a `projection` matrix, the result is in view space. If
 *   it's a `(view * projection)` matrix, the result is in world space. If it's
 *   a `(model * view * projection)` matrix, the result is in object space.
 *
 * * `dest` is a Hash containing the following keys: `:left`, `:right`, `:bottom`,
 *   `:top`, `:near`, `:far`. Each value is a Vec4.
 *
 * You probably want to extract planes in world space, so use `(view * projection)`
 * as `space`.
 */
VALUE rb_cglm_frustum_singleton_planes(int argc, VALUE *argv, VALUE self) {
  VALUE mat, dest;
  rb_scan_args(argc, argv, "11", &mat, &dest);
  if (NIL_P(dest)) dest = rb_hash_new();
  vec4 planes[6];
  glm_frustum_planes(VAL2MAT4(mat), planes);

  #define HASH_GET_OR_SET(index, name)                     \
    VALUE name = rb_hash_aref(dest, SYMBOL(#name));        \
    if (NIL_P(name)) {                                     \
      name = VEC4_NEW(ALLOC_VEC4);                     \
      rb_hash_aset(dest, SYMBOL(#name), name);             \
    }                                                      \
    memcpy(&VAL2VEC4(name), &planes[index], sizeof(vec4));

    HASH_GET_OR_SET(GLM_LEFT,   left);
    HASH_GET_OR_SET(GLM_RIGHT,  right);
    HASH_GET_OR_SET(GLM_BOTTOM, bottom);
    HASH_GET_OR_SET(GLM_TOP,    top);
    HASH_GET_OR_SET(GLM_NEAR,   near);
    HASH_GET_OR_SET(GLM_FAR,    far);
  #undef HASH_GET_OR_SET

  return dest;
}


/* call-seq: corners(inv_space[, dest]) => dest | new Hash
 *
 * Extracts the view frustum corners using clip-space coordinates.
 *
 * * `inv_space` is the inverse of the Mat4 representing the space in which
 *   the 8 frustum corners are defined. If it's an `(inverse(view * projection))`
 *   matrix, the result is in world space. If it's an `(inverse(model * view * projection))`
 *   matrix, the result is in object space.
 *
 *   * You probably want to extract planes in world space, so use
 *     `(inverse(view * projection))` as `inv_space`.
 *
 * * `dest` is a Hash containing the following keys: `:lbn`, `:ltn`, `:rtn`,
 *   `:rbn`, `:lbf`, `:ltf`, `:rtf`, `:rbf`. Each value is a Vec4.
 *
 *   * The `dest` hash, if created, is ordered such that you can index into
 *     the array of values with the Frustum class constants. For example,
 *     `hash.values[Frustum::RTN]`.
 *
 *   * If you know the index of a near coord, you can get its far coord by
 *     adding 4. For example,
 *     `hash.values[Frustum::RTN + 4] == hash.values[Frustum::RTF]`.
 *
 */
VALUE rb_cglm_frustum_singleton_corners(int argc, VALUE *argv, VALUE self) {
  VALUE mat, dest;
  rb_scan_args(argc, argv, "11", &mat, &dest);
  if (NIL_P(dest)) dest = rb_hash_new();
  vec4 corners[8];
  glm_frustum_corners(VAL2MAT4(mat), corners);

  #define HASH_GET_OR_SET(index, name)                     \
    VALUE name = rb_hash_aref(dest, SYMBOL(#name));        \
    if (NIL_P(name)) {                                     \
      name = VEC4_NEW(ALLOC_VEC4);                     \
      rb_hash_aset(dest, SYMBOL(#name), name);             \
    }                                                      \
    memcpy(&VAL2VEC4(name), &corners[index], sizeof(vec4));

    HASH_GET_OR_SET(GLM_LBN, lbn);
    HASH_GET_OR_SET(GLM_LTN, ltn);
    HASH_GET_OR_SET(GLM_RTN, rtn);
    HASH_GET_OR_SET(GLM_RBN, rbn);
    HASH_GET_OR_SET(GLM_LBF, lbf);
    HASH_GET_OR_SET(GLM_LTF, ltf);
    HASH_GET_OR_SET(GLM_RTF, rtf);
    HASH_GET_OR_SET(GLM_RBF, rbf);
  #undef HASH_GET_OR_SET

  return dest;
}

#define hash_to_corner(corners, corners_v, index, name)     \
  {                                                         \
    VALUE v = rb_hash_aref(corners_v, SYMBOL(name));        \
    if (NIL_P(v)) v = VEC4_NEW(ALLOC_VEC4);             \
    memcpy(&corners[index][0], &VAL2VEC4(v), sizeof(vec4)); \
  }

#define hash_to_corners(corners, corners_v)           \
  hash_to_corner(corners, corners_v, GLM_LBN, "lbn"); \
  hash_to_corner(corners, corners_v, GLM_LTN, "ltn"); \
  hash_to_corner(corners, corners_v, GLM_RTN, "rtn"); \
  hash_to_corner(corners, corners_v, GLM_RBN, "rbn"); \
  hash_to_corner(corners, corners_v, GLM_LBF, "lbf"); \
  hash_to_corner(corners, corners_v, GLM_LTF, "ltf"); \
  hash_to_corner(corners, corners_v, GLM_RTF, "rtf"); \
  hash_to_corner(corners, corners_v, GLM_RBF, "rbf");

/* call-seq: center(corners[, dest]) => dest | new vec4
 *
 * Returns the center of the view frustum described by the hash `corners`,
 * which must follow the format returned by {corners}.
 */
VALUE rb_cglm_frustum_singleton_center(int argc, VALUE *argv, VALUE self) {
  VALUE corners_v, dest;
  rb_scan_args(argc, argv, "11", &corners_v, &dest);
  if (NIL_P(dest)) dest = VEC4_NEW(ALLOC_VEC4);
  vec4 corners[8];
  hash_to_corners(corners, corners_v);
  glm_frustum_center(corners, VAL2VEC4(dest));
  return dest;
}

/* call-seq: aabb(matr, corners[, dest]) => dest | new AABB
 *
 * Finds a bounding box for the frustum defined by `corners` relative to the
 * givn matrix (e.g. a view matrix). Places the result in `dest` and returns
 * `dest`, or a new AABB if `dest` is omitted.
 */
VALUE rb_cglm_frustum_singleton_aabb(int argc, VALUE *argv, VALUE self) {
  VALUE matr, corners_v, dest;
  rb_scan_args(argc, argv, "21", &matr, &corners_v, &dest);
  if (NIL_P(dest)) dest = rb_funcall(rb_cAABB, rb_intern("new"), 0);
  vec4 corners[8];
  hash_to_corners(corners, corners_v);
  glm_frustum_box(corners, VAL2MAT4(matr), VAL2AABB(dest).corners);
  return dest;
}

/* call-seq: corners_at(corners, split, far[, dest]) => dest | new Hash
 *
 * Finds the corners of a plane which lies between the near and far planes of
 * the frustum.
 *
 * This will be helpful if you want to split a frustum, e.g. CSM/PSSM.
 *
 * * `corners` are the 8 corners of the frustum and follow the same format as
 *   is returned by {corners}.
 *
 * * `split` is the distance at which to calculate the 4 corners.
 *
 * * `far` is the far distance of the frustum.
 *
 * * `dest` is a Hash containing :lb, :lt, :rt, and :rb (all of which are
 *   Vec4's). If omitted, one will be created.
 */
VALUE rb_cglm_frustum_singleton_corners_at(int argc, VALUE *argv, VALUE self) {
  VALUE corners_v, split, far, dest;
  rb_scan_args(argc, argv, "31", &corners_v, &split, &far, &dest);
  if (NIL_P(dest)) dest = rb_hash_new();
  vec4 corners[8];
  hash_to_corners(corners, corners_v);
  vec4 plane_corners[4];
  glm_frustum_corners_at(corners, NUM2FLT(split), NUM2FLT(far), plane_corners);

  #define HASH_GET_OR_SET(index, name)                     \
    VALUE name = rb_hash_aref(dest, SYMBOL(#name));        \
    if (NIL_P(name)) {                                     \
      name = VEC4_NEW(ALLOC_VEC4);                     \
      rb_hash_aset(dest, SYMBOL(#name), name);             \
    }                                                      \
    memcpy(&VAL2VEC4(name), &plane_corners[index], sizeof(vec4));

    HASH_GET_OR_SET(0, lb);
    HASH_GET_OR_SET(1, lt);
    HASH_GET_OR_SET(2, rt);
    HASH_GET_OR_SET(3, rb);
  #undef HASH_GET_OR_SET

  return dest;
}

/* call-seq: planes([dest]) => dest | new Hash
 *
 * Same as calling {planes} with `self.matrix` as the first argument.
 */
VALUE rb_cglm_frustum_planes(int argc, VALUE *argv, VALUE self) {
  VALUE mat = rb_ivar_get(self, rb_intern("@matrix"));
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  return rb_funcall(rb_cFrustum, rb_intern("planes"), 2, mat, dest);
}

/* call-seq: corners([dest]) => dest | new Hash
 *
 * Same as calling {corners} with `self.matrix.inverse` as the first argument.
 */
VALUE rb_cglm_frustum_corners(int argc, VALUE *argv, VALUE self) {
  VALUE mat = rb_funcall(rb_ivar_get(self, rb_intern("@matrix")), rb_intern("inverse"), 0);
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  return rb_funcall(rb_cFrustum, rb_intern("corners"), 2, mat, dest);
}

/* call-seq: center([dest]) => dest | new Hash
 *
 * Same as calling {center} with #corners as the first argument.
 */
VALUE rb_cglm_frustum_center(int argc, VALUE *argv, VALUE self) {
  VALUE corners = rb_funcall(self, rb_intern("corners"), 0);
  VALUE dest;
  rb_scan_args(argc, argv, "01", &dest);
  return rb_funcall(rb_cFrustum, rb_intern("center"), 2, corners, dest);
}

/* call-seq: to_aabb(matr[, dest]) => dest | new AABB
 *
 * Same as calling {aabb} with #corners as the first argument.
 */
VALUE rb_cglm_frustum_to_aabb(int argc, VALUE *argv, VALUE self) {
  VALUE corners = rb_funcall(self, rb_intern("corners"), 0);
  VALUE split, far, dest;
  rb_scan_args(argc, argv, "21", &split, &far, &dest);
  return rb_funcall(rb_cFrustum, rb_intern("aabb"), 4, corners, split, far, dest);
}

/* call-seq: corners_at(split, far[, dest]) => dest | new Hash
 *
 * Same as calling {corners_at} with #corners as the first argument.
 */
VALUE rb_cglm_frustum_corners_at(int argc, VALUE *argv, VALUE self) {
  VALUE corners = rb_funcall(self, rb_intern("corners"), 0);
  VALUE split, far, dest;
  rb_scan_args(argc, argv, "21", &split, &far, &dest);
  return rb_funcall(rb_cFrustum, rb_intern("corners_at"), 4, corners, split, far, dest);
}

void Init_cglm_frustum() {
  /* left  bottom near */ rb_define_const(rb_cFrustum, "LBN",                 GLM_LBN);
  /* left  top    near */ rb_define_const(rb_cFrustum, "LTN",                 GLM_LTN);
  /* right top    near */ rb_define_const(rb_cFrustum, "RTN",                 GLM_RTN);
  /* right bottom near */ rb_define_const(rb_cFrustum, "RBN",                 GLM_RBN);
  /* left  bottom far  */ rb_define_const(rb_cFrustum, "LBF",                 GLM_LBF);
  /* left  top    far  */ rb_define_const(rb_cFrustum, "LTF",                 GLM_LTF);
  /* right top    far  */ rb_define_const(rb_cFrustum, "RTF",                 GLM_RTF);
  /* right bottom far  */ rb_define_const(rb_cFrustum, "RBF",                 GLM_RBF);
                          rb_define_const(rb_cFrustum, "LEFT",                GLM_LEFT);
                          rb_define_const(rb_cFrustum, "RIGHT",               GLM_RIGHT);
                          rb_define_const(rb_cFrustum, "BOTTOM",              GLM_BOTTOM);
                          rb_define_const(rb_cFrustum, "TOP",                 GLM_TOP);
                          rb_define_const(rb_cFrustum, "NEAR",                GLM_NEAR);
                          rb_define_const(rb_cFrustum, "FAR",                 GLM_FAR);
  /* left  bottom near */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_LBN", VEC4_NEW(CSCOORD_LBN));
  /* left  top    near */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_LTN", VEC4_NEW(CSCOORD_LTN));
  /* right top    near */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_RTN", VEC4_NEW(CSCOORD_RTN));
  /* right bottom near */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_RBN", VEC4_NEW(CSCOORD_RBN));
  /* left  bottom far  */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_LBF", VEC4_NEW(CSCOORD_LBF));
  /* left  top    far  */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_LTF", VEC4_NEW(CSCOORD_LTF));
  /* right top    far  */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_RTF", VEC4_NEW(CSCOORD_RTF));
  /* right bottom far  */ rb_define_const(rb_cFrustum, "CLIPSPACE_COORD_RBF", VEC4_NEW(CSCOORD_RBF));

  rb_define_method(rb_cFrustum, "planes",     rb_cglm_frustum_planes,  -1);
  rb_define_method(rb_cFrustum, "corners",    rb_cglm_frustum_corners, -1);
  rb_define_method(rb_cFrustum, "center",     rb_cglm_frustum_center,  -1);
  rb_define_method(rb_cFrustum, "aabb",       rb_cglm_frustum_to_aabb, -1);
  rb_define_method(rb_cFrustum, "corners_at", rb_cglm_frustum_to_aabb, -1);

  rb_define_singleton_method(rb_cFrustum, "planes",     rb_cglm_frustum_singleton_planes,     -1);
  rb_define_singleton_method(rb_cFrustum, "corners",    rb_cglm_frustum_singleton_corners,    -1);
  rb_define_singleton_method(rb_cFrustum, "to_aabb",    rb_cglm_frustum_singleton_aabb,       -1);
  rb_define_singleton_method(rb_cFrustum, "corners_at", rb_cglm_frustum_singleton_corners_at, -1);
}
