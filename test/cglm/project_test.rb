require "test_helper"

class CglmProjectionTest < Minitest::Test
  def test_project # taken from cglm
    viewport = Vec4.new([0, 0, 800, 600])
    pos = Vec3.new([13, 45, 0.74])

    model = Mat4.translate Vec3.new([0, 0, -10])
    view = Mat4.look_at(Vec3.zero, pos, Vec3.yup)

    proj = Mat4.perspective aspect: 0.5
    mvp = proj * view * model

    projected = mvp.project(pos, viewport)
    unprojected = mvp.unproject(projected, viewport)

    # unprojected of projected error must be same as original one
    assert pos.equalish_vec3(unprojected, 0.01)
  end
end
