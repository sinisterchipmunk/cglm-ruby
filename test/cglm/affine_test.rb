require "test_helper"

class CglmAffineTest < Minitest::Test
  def test_from_scale
    s = Mat4.scale(Vec3.new([0.1, 0.2, 0.3]))
    Mat4.scale(Vec3.new([0.1, 0.2, 0.3]), s2 = Mat4.new)
    assert_in_delta 0.1, s[0][0]
    assert_in_delta 0.2, s[1][1]
    assert_in_delta 0.3, s[2][2]
    assert s =~ s2
  end

  def test_from_rotation
    q = Quat.axis_angle(Vec3.new([0, 1, 0]), Math::PI)
    r1 = q.to_mat4
    r2 = Mat4.rotate(Vec3.new([0, 1, 0]), Math::PI)
    q.to_mat4(r3 = Mat4.new)
    Mat4.rotate(Vec3.new([0, 1, 0]), Math::PI, r4 = Mat4.new)
    assert r1 =~ r2
    assert r1 =~ r3
    assert r1 =~ r4
  end

  def test_from_translation
    t = Mat4.translate(Vec3.new([0.1, 0.2, 0.3]))
    Mat4.translate(Vec3.new([0.1, 0.2, 0.3]), t2 = Mat4.new)
    assert_in_delta 0.1, t.to_flat_a[12]
    assert_in_delta 0.2, t.to_flat_a[13]
    assert_in_delta 0.3, t.to_flat_a[14]
    assert_in_delta 1.0, t.to_flat_a[15]
    assert t =~ t2
  end

  def test_cglm_tests # taken from cglm tests
    # test translate is postmultiplied
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))

    t3 = t1 * t2 # R * T

    t1.translate! Vec3.new([34, 57, 36])
    assert t1 =~ t3

    # test rotate is postmultiplied
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))
    t3 = t2 * t1 # T * R

    t2.rotate! Vec3.yup, PI_4
    assert t2 =~ t3

    # test scale is postmultiplied
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))
    t4 = Mat4.scale(Vec3.new([3, 5, 6]))

    t3 = t2 * t1 # T * R
    t5 = t3 * t4 # T * R * S

    t3.scale! Vec3.new([3, 5, 6])
    assert t3 =~ t5

    # test translate_x
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([34, 0, 0]))

    t3 = t1 * t2 # R * T
    t1.translate_x! 34
    assert t1 =~ t3

    # test translate_y
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([0, 57, 0]))

    t3 = t1 * t2 # R * T
    t1.translate_y! 57
    assert t1 =~ t3

    # test translate_z
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([0, 0, 36]))

    t3 = t1 * t2 # R * T
    t1.translate_z! 36
    assert t1 =~ t3

    # test rotate_x
    t1 = Mat4.rotate(Vec3.new([1, 0, 0]), PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))

    t3 = t2 * t1 # T * R

    t2 = t2.rotate_x PI_4
    assert t2 =~ t3

    # test rotate_y
    t1 = Mat4.rotate(Vec3.new([0, 1, 0]), PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))

    t3 = t2 * t1 # T * R

    t2 = t2.rotate_y PI_4
    assert t2 =~ t3

    # test rotate_z
    t1 = Mat4.rotate(Vec3.new([0, 0, 1]), PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))

    t3 = t2 * t1 # T * R

    t2 = t2.rotate_z PI_4
    assert t2 =~ t3

    # test rotate
    t1 = Mat4.rotate(Vec3.new([0, 0, 1]), PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))

    t3 = t2 * t1 # T * R
    t2.rotate!(Vec3.new([0, 0, 1]), PI_4)

    assert t3 =~ t2

    # test scale_uni
    t1 = Mat4.rotate(Vec3.yup, PI_4)
    t2 = Mat4.translate(Vec3.new([34, 57, 36]))
    t4 = Mat4.scale(Vec3.new([3, 3, 3]))

    t3 = t2 * t1 # T * R
    t5 = t3 * t4 # T * R * S

    t3.scale! 3
    assert t3 =~ t5, [t3, t5].inspect
  end
end
