require "test_helper"
require 'fiddle/import'

class CglmQuatTest < Minitest::Test
  def test_each
    accum = []
    CGLM::Quat.new([1,2,3,4]).each do |i|
      accum << i
    end
    assert_equal [1, 2, 3, 4], accum
  end

  def test_to_a
    assert_equal [1,2,3,4], CGLM::Quat.new([1,2,3,4]).to_a
  end

  def test_quat # taken from cglm tests
    # 0. test identiy quat
    q4 = Quat.identity
    assert q4.real == Math.cos(0.to_radians * 0.5)
    rot1 = q4.to_mat4
    assert rot1 =~ Mat4.identity

    # 1. test quat to mat and mat to quat
    1_000.times do |i|
      in_quat = Quat.random
      in_rot = in_quat.to_mat4
      out_quat = in_rot.to_quat
      out_rot = out_quat.to_mat4

      # 2. test first quat and generated one for equality
      4.times { |j| in_quat[j] = in_quat[j].abs; out_quat[j] = out_quat[j].abs }
      assert in_quat =~ out_quat

      # 3. test first rotation and second rotation
      assert in_rot =~ out_rot
    end

    # 5. test lookat
    eye = Vec3.random
    q3 = Quat.axis_angle(Vec3.yup, -90.to_radians)
    # now X axis must be forward axis, Z must be right axis
    view1 = Mat4.look(eye, Vec3.xup, Vec3.yup)
    # create view matrix with quaternion
    view2 = q3.look(eye)
    assert view1 =~ view2

    # 6. test quaternion rotation matrix result
    q3 = Quat.random
    rot1 = q3.to_mat4

    # 6.1 test axis and angle of quat
    rot2 = Mat4.rotate(q3.axis, q3.angle)
    assert rot1 =~ rot2

    # 7. test quaternion multiplication (hamilton product),
    #    final rotation = first rotation + second = quat1 * quat2
    q3 = Quat.random
    q4 = Quat.random
    q5 = q3 * q4
    rot1 = Mat4.rotate(q3.axis, q3.angle)
    rot1.rotate! q4.axis, q4.angle
    assert rot1 =~ q5.to_mat4

    # 8. test quaternion for look rotation

    # 8.1 same direction
    # look at from 0, 0, 1 to zero, direction = 0, 0, -1
    q3 = Quat.look(Vec3.new([0, 0, -1]), Vec3.new([0, 0, -1]), Vec3.yup)

    # result must be identity
    assert q3 =~ Quat.identity

    # look at from 0, 0, 1 to zero, direction = 0, 0, -1
    q4 = Quat.look_at(Vec3.zup, Vec3.zero, Vec3.new([0, 0, -1]), Vec3.yup)

    # result must be identity
    assert q4 =~ Quat.identity
    assert q3 =~ q4

    # 8.2 perpendicular
    q3 = Quat.look(Vec3.xup, Vec3.new([0, 0, -1]), Vec3.yup)

    # result must be -90
    q4 = Quat.axis_angle(Vec3.yup, -90.to_radians)
    assert q3 =~ q4

    # 9. test imag, real

    # 9.1 real
    assert_in_delta q4.real, Math.cos(-90.to_radians * 0.5)

    # 9.1 imag
    imag = q4.imag

    # axis = Y_UP * sinf(angle * 0.5), YUP = 0, 1, 0
    axis = Vec3.new([0, Math.sin(-90.to_radians * 0.5) * 1, 0])
    assert imag =~ axis

    # 9.2 axis
    assert q4.axis =~ Vec3.new([0, -1, 0])

    # 10. test rotate vector using quat
    # (0,0,-1) around (1,0,0) must give (0,1,0)
    v1 = Vec3.new([0, 0, -1])
    v2 = Vec3.new([0, 0, -1])
    v1.rotate_axis_angle!(Vec3.new([1,0,0]), 90.to_radians)
    q3 = Quat.axis_angle(Vec3.new([1,0,0]), 90.to_radians)
    q3 *= 1.5
    q3.rotate_vec3(v2, v2)

    # result must be : (0,1,0)
    assert v1 =~ Vec3.new([0, 1, 0])
    assert v1 =~ v2

    # 11. test rotate transform
    rot1 = Mat4.translate Vec3.new([-10, 45, 8])
    rot1.rotate! Vec3.zup, -90.to_radians

    q3 = Quat.axis_angle(Vec3.zup, -90.to_radians)
    rot2 = Mat4.translate Vec3.new([-10, 45, 8])
    q3.rotate_mat4(rot2, rot2)

    # result must be same (almost)
    assert rot1 =~ rot2

    rot1 = Mat4.rotate(Vec3.zup, -90.to_radians)
    rot1.translate! Vec3.new([-10, 45, 8])

    q3 = Quat.axis_angle(Vec3.zup, -90.to_radians)
    rot2 = q3.rotate_mat4 Mat4.identity
    rot2.translate! Vec3.new([-10, 45, 8])
    assert rot1 =~ rot2

    # reverse
    rot1 = Mat4.rotate(Vec3.zup, -90.to_radians)
    q3 = Quat.axis_angle(Vec3.zup, 90.to_radians)
    q3.rotate_mat4 rot1, rot1
    # result must be identity
    assert rot1 =~ Mat4.identity

    # 12. inverse of quat, multiplication must be IDENTITY
    q3 = Quat.rand
    q4 = q3.invert
    q5 = q3 * q4
    assert q5 =~ Quat.identity

    # TODO: add tests for slerp, lerp
  end
end
