#include "rb_cglm.h"

/* call-seq: angles(mat4[, dest]) => dest or new Vec3
 *
 * Extracts euler angles (in radians) using xyz order.
 */
VALUE rb_cglm_euler_angles(int argc, VALUE *argv, VALUE self) {
  VALUE m, dest;
  rb_scan_args(argc, argv, "11", &m, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_euler_angles(VAL2MAT4(m), VAL2VEC3(dest));
  return dest;
}

/* call-seq: xyz(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in xyz order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_xyz(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_xyz(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: zyx(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in zyx order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_zyx(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_zyx(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: zxy(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in zxy order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_zxy(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_zxy(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: xzy(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in xzy order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_xzy(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_xzy(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: yzx(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in yzx order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_yzx(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_yzx(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: yxz(angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in yxz order. `angles`
 * must be a Vec3 specifying the X, Y and Z angles (in that order).
 */
VALUE rb_cglm_euler_yxz(int argc, VALUE *argv, VALUE self) {
  VALUE angles, dest;
  rb_scan_args(argc, argv, "11", &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_yxz(VAL2VEC3(angles), VAL2MAT4(dest));
  return dest;
}

/* call-seq: by_order(axis, angles[, dest]) => dest or new Mat4
 *
 * Builds a rotation matrix from the specified angles, in the specified order,
 * which can be one of the constants from the Euler module, or computed using
 * #order. `angles` must be a Vec3 specifying the X, Y and Z angles (in that
 * order).
 */
VALUE rb_cglm_euler_by_order(int argc, VALUE *argv, VALUE self) {
  VALUE angles, axis, dest;
  rb_scan_args(argc, argv, "21", &axis, &angles, &dest);
  if (NIL_P(dest)) dest = MAT4_NEW(ALLOC_MAT4);
  glm_euler_by_order(VAL2VEC3(angles), NUM2INT(axis), VAL2MAT4(dest));
  return dest;
}


/* call-seq: order(axis) => Numeric
 *
 * Returns a numeric handle representing the specified axis order. `axis` is
 * an array containing axis indices (0 for X, 1 for Y, 2 for Z).
 *
 * Example:
 *
 *     order([0, 2, 1]) #=> first X, then Z, then Y
 */
VALUE rb_cglm_euler_order(VALUE klass, VALUE order_ary) {
  int order[3] = { NUM2INT(rb_ary_entry(order_ary, 0)),
                   NUM2INT(rb_ary_entry(order_ary, 1)),
                   NUM2INT(rb_ary_entry(order_ary, 2)) };
  return INT2NUM(glm_euler_order(order));
}

void Init_cglm_euler() {
  rb_define_const(rb_mEuler, "XYZ", INT2NUM(GLM_EULER_XYZ));
  rb_define_const(rb_mEuler, "XZY", INT2NUM(GLM_EULER_XZY));
  rb_define_const(rb_mEuler, "YZX", INT2NUM(GLM_EULER_YZX));
  rb_define_const(rb_mEuler, "YXZ", INT2NUM(GLM_EULER_YXZ));
  rb_define_const(rb_mEuler, "ZXY", INT2NUM(GLM_EULER_ZXY));
  rb_define_const(rb_mEuler, "ZYX", INT2NUM(GLM_EULER_ZYX));
  rb_define_singleton_method(rb_mEuler, "order",    rb_cglm_euler_order, 1);
  rb_define_singleton_method(rb_mEuler, "xyz",      rb_cglm_euler_xyz, -1);
  rb_define_singleton_method(rb_mEuler, "zyx",      rb_cglm_euler_zyx, -1);
  rb_define_singleton_method(rb_mEuler, "zxy",      rb_cglm_euler_zxy, -1);
  rb_define_singleton_method(rb_mEuler, "xzy",      rb_cglm_euler_xzy, -1);
  rb_define_singleton_method(rb_mEuler, "yzx",      rb_cglm_euler_yzx, -1);
  rb_define_singleton_method(rb_mEuler, "yxz",      rb_cglm_euler_yxz, -1);
  rb_define_singleton_method(rb_mEuler, "by_order", rb_cglm_euler_by_order, -1);
  rb_define_singleton_method(rb_mEuler, "angles",   rb_cglm_euler_angles, -1);
}
