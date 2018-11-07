require "test_helper"
require 'fiddle/import'

class CGLM::Mat4Test < Minitest::Test
  def test_dup
    a = CGLM::Mat4.new
    a[0][0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end

  def test_init_from_array_of_arrays
    start = [[1,2,3,4], [5,6,7,8], [9,8,7,6], [5,4,3,2]]
    m = CGLM::Mat4.new(start)
    assert_equal start, m.to_a.map { |a| a.to_a }
  end

  def test_memory
    addr = CGLM.alloc(Mat4)
    mat = Mat4.new(addr: addr)
    assert_equal addr, mat.addr
    assert_equal addr, mat.to_ptr
  end

  def test_init_from_array_of_vec3s_and_vec4s
    start = [CGLM::Vec3.new([1,2,3]),
             CGLM::Vec4.new([5,6,7,8]),
             CGLM::Vec3.new([9,8,7]),
             CGLM::Vec4.new([5,4,3,2])]
    m = CGLM::Mat4.new(start)
    assert_equal [[1,2,3,0], [5,6,7,8], [9,8,7,0], [5,4,3,2]],
                 m.to_a.map { |a| a.to_a }
  end

  def test_array_access_and_inspect
    m = CGLM::Mat4.new
    v3 = CGLM::Vec3.new
    v4 = CGLM::Vec4.new

    v3[0] = 1; v3[1] = 2; v3[2] = 3
    v4[0] = 4; v4[1] = 5; v4[2] = 6; v4[3] = 7

    m[0] = v3
    m[1] = v4
    m[2] = [8]
    m[3] = [9, 10, 11, 12, 13]

    assert_equal [1,  2,  3,  0], m.to_a[0]
    assert_equal [4,  5,  6,  7], m.to_a[1]
    assert_equal [8,  0,  0,  0], m.to_a[2]
    assert_equal [9, 10, 11, 12], m.to_a[3]

    # the white space matters
    assert_match         '[ 1.0,  2.0,  3.0,  0.0,
                            4.0,  5.0,  6.0,  7.0,
                            8.0,  0.0,  0.0,  0.0,
                            9.0, 10.0, 11.0, 12.0]',
                  m.inspect
  end

  def test_mat4 # taken from cglm tests
    m1 = Mat4.identity
    m2 = Mat4.identity
    m4 = Mat4.new
    m5 = Mat4.new

    # test identity matrix multiplication
    m3 = m1 * m2
    assert m3 =~ Mat4.identity

    # test random matrices
    m1 = Mat4.random
    m2 = Mat4.random
    m3 = m1 * m2
    4.times do |i|
      4.times do |j|
        4.times do |k|
          m4[i][j] += m1[k][j] * m2[i][k]
        end
      end
    end
    assert m3 =~ m4

    # test pre compiled
    m1.mul_mat4(m2, m3)
    assert m3 =~ m4
    1_000.times do |i|
      Mat4.random m3
      Mat4.random m4
      m3.invert m4
      m4.invert m5
      assert m3.equalish(m5)

      Mat4.random m3
      Mat4.random m4
      m3.invert_fast m4
      m4.invert_fast m5
      assert m3.equalish(m5, 0.0009)
    end

    # test determinant
    assert_equal m1.determinant, m1.det
  end
end
