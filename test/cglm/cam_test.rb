require "test_helper"
require 'fiddle/import'

class CglmCamTest < Minitest::Test
  def test_frustum
    mat = CGLM::Mat4.frustum(left: 1, right: 2, bottom: 3, top: 4, near: 5, far: 6)
    assert_kind_of(CGLM::Mat4, mat)

    other = CGLM::Mat4.frustum(mat, left: 1, right: 2, bottom: 3, top: 4, near: 5, far: 6)
    assert_same(mat, other)

    assert_equal({left: 1, right: 2, bottom: 3, top: 4, near: 5, far: 6}, other.frustum)
  end

  def test_perspective
    o = CGLM::Mat4.perspective(fovy: 1.0472, aspect: 640.0 / 480.0)
    assert_in_delta 0.15396049618721008, o.sizes[:near][0]
    assert_in_delta 0.11547037214040756, o.sizes[:near][1]
    assert_in_delta 153.96060180664062, o.sizes[:far][0]
    assert_in_delta 115.47044372558594, o.sizes[:far][1]
  end

  def test_ortho
    mat = CGLM::Mat4.ortho(left: 1, right: 2, bottom: 3, top: 4, near: 5, far: 6)
    assert_kind_of(CGLM::Mat4, mat)

    other = CGLM::Mat4.ortho(mat, left: 1, right: 2, bottom: 3, top: 4, near: 5, far: 6)
    assert_same(mat, other)
  end

  def test_ortho_aabb
    aabb = CGLM::AABB.new

    mat = CGLM::Mat4.ortho_aabb(aabb)
    assert_kind_of(CGLM::Mat4, mat)

    other = CGLM::Mat4.ortho_aabb(aabb, mat, padding: 1)
    other = CGLM::Mat4.ortho_aabb(aabb, mat, padding: 1, padding_z: 2)
    other = CGLM::Mat4.ortho_aabb(aabb, mat, padding_z: 2)
    assert_same(mat, other)
  end

  def test_camera_lookat # taken from cglm tests
    eye = Vec3.new([0.024, 14.6, 67.04])
    dir = Vec3.new([0, 0, -1])
    up = Vec3.new([0, 1, 0])
    center = eye + dir
    view1 = Mat4.look_at(eye, center, up)
    view2 = Mat4.look(eye, dir, up)
    assert_equal view1, view2
  end

  def test_camera_decomp # taken from cglm tests
    aspect = 0.782
    fovy   = 49.984 * CGLM::PI / 180.0
    near   = 0.1
    far    = 100.0
    proj = Mat4.perspective(fovy: fovy, aspect: aspect, near: near, far: far)
    assert_in_delta aspect,  proj.aspect
    assert_in_delta fovy,    proj.fovy
    sizes = proj.sizes(fovy)
    proj2 = Mat4.frustum(left:   sizes[:near][0] * -0.5, right: sizes[:near][0] * 0.5,
                         bottom: sizes[:near][1] * -0.5, top:   sizes[:near][1] * 0.5,
                         near:   near,                   far:   far)
    assert proj =~ proj2
  end
end
