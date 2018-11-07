#include "rb_cglm.h"

/* call-seq: unproject_i(pos, viewport[, dest]) => dest | new Vec3
 *
 * Maps the specified position into the space represented by this matrix,
 * places it in `dest` or a new Vec3 if `dest` is omitted, and returns it.
 *
 * * NOTE: This method assumes that `self` represents the **inverse** of a
 *   projection matrix. It's faster than calling #unproject assuming you
 *   already have an inverse matrix. If you don't have an inverse, you should
 *   just rely on #unproject (to save the overhead of the extra method call),
 *   but if you have or need the inverse for other computations, you can use
 *   #unproject_i to save yourself the cost of the inversion.
 *
 * * If `self` is an `inverse(projection)` matrix, then the result will be
 *   in view space.
 *
 * * If `self` is an `inverse(projection * view)` matrix, then the result will
 *   be in world space.
 *
 * * If `self` is an `inverse(projection * view * model)` matrix, then the
 *   result will be in object space.
 *
 * * `pos` is a Vec3 specifying the coordinates to unproject.
 *
 * * `viewport` is a Vec4 specifying the dimensions of the viewport in
 *   `[x, y, width, height]` format.
 *
 * * `dest` is the Vec3 to place the results into, and will be created if
 *   omitted.
 */
VALUE rb_cglm_project_unproject_i(int argc, VALUE *argv, VALUE self) {
  VALUE pos, viewport, dest;
  rb_scan_args(argc, argv, "21", &pos, &viewport, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_unprojecti(VAL2VEC3(pos), VAL2MAT4(self), VAL2VEC4(viewport), VAL2VEC3(dest));
  return dest;
}

/* call-seq: unproject(pos, viewport[, dest]) => dest | new Vec3
 *
 * Maps the specified position into the space represented by this matrix,
 * places it in `dest` or a new Vec3 if `dest` is omitted, and returns it.
 *
 * * NOTE: This method must calculate the inverse of the current matrix. If
 *   you already have the inverse handy, you should use #unproject_i for
 *   better performance.
 *
 * * If `self` is a `projection` matrix, then the result will be
 *   in view space.
 *
 * * If `self` is a `projection * view` matrix, then the result will
 *   be in world space.
 *
 * * If `self` is an `projection * view * model` matrix, then the
 *   result will be in object space.
 *
 * * `pos` is a Vec3 specifying the coordinates to unproject.
 *
 * * `viewport` is a Vec4 specifying the dimensions of the viewport in
 *   `[x, y, width, height]` format.
 *
 * * `dest` is the Vec3 to place the results into, and will be created if
 *   omitted.
 */
VALUE rb_cglm_project_unproject(int argc, VALUE *argv, VALUE self) {
  VALUE pos, viewport, dest;
  rb_scan_args(argc, argv, "21", &pos, &viewport, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_unproject(VAL2VEC3(pos), VAL2MAT4(self), VAL2VEC4(viewport), VAL2VEC3(dest));
  return dest;
}

/* call-seq: project(pos, viewport[, dest]) => dest | new Vec3
 *
 * Maps the given object-space coordinates into window coordinates using
 * `self` as the projection matrix.
 *
 * * `pos` is a Vec3 specifying the object-space coordinates.
 *
 * * `viewport` is a Vec4 specifying the dimensions of the viewport in
 *   `[x, y, width, height]` format.
 *
 * * `dest` is the Vec3 to place the results into, and will be created if
 *   omitted.
 */
VALUE rb_cglm_project_project(int argc, VALUE *argv, VALUE self) {
  VALUE pos, viewport, dest;
  rb_scan_args(argc, argv, "21", &pos, &viewport, &dest);
  if (NIL_P(dest)) dest = VEC3_NEW(ALLOC_VEC3);
  glm_project(VAL2VEC3(pos), VAL2MAT4(self), VAL2VEC4(viewport), VAL2VEC3(dest));
  return dest;
}

void Init_cglm_project() {
  rb_define_method(rb_cMat4, "unproject_i", rb_cglm_project_unproject_i, -1);
  rb_define_method(rb_cMat4, "unproject",   rb_cglm_project_unproject,   -1);
  rb_define_method(rb_cMat4, "project",     rb_cglm_project_project,     -1);
}
