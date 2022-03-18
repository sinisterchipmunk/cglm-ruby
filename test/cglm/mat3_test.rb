require "test_helper"
require 'fiddle/import'

class CGLM::Mat3Test < Minitest::Test
  def test_dup
    a = CGLM::Mat3.new
    a[0][0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end

  def test_memory
    addr = CGLM.alloc(Mat3)
    mat = Mat3.new(addr: addr)
    assert_equal addr, mat.addr
    assert_equal addr, mat.to_ptr
  end

  def test_to_flat_a
    assert_equal [1,0,0, 0,1,0, 0,0,1], Mat3.identity.to_flat_a
  end

  def test_size
    # Don't want to put a tight constraint on the expected size of a mat3 due
    # to alignment, architecture, etc. Let's be satisfied with "smaller than
    # mat4".
    assert Mat3.size < Mat4.size, 'Expected mat3 to be smaller than mat4'
  end

  def test_mat3 # taken from cglm tests
    m1 = Mat3.identity
    m2 = Mat3.identity
    m4 = Mat3.new

    # test identity matrix multiplication
    m3 = m1 * m2
    assert m3 =~ Mat3.identity

    # test random matrices
    m1 = Mat3.random
    m2 = Mat3.random
    m3 = m1 * m2
    3.times do |i|
      3.times do |j|
        3.times do |k|
          m4[i][j] += m1[k][j] * m2[i][k]
        end
      end
    end
    assert m3 =~ m4

    1_000.times do |i|
      m3 = Mat3.random
      m4 = Mat3.random

      # test inverse precise
      m3.invert(m4)
      m5 = m4.invert
      assert m3 =~ m5
    end
  end
end
