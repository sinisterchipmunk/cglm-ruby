require "test_helper"
require 'fiddle/import'

class CglmVec3Test < Minitest::Test
  def test_dup
    a = CGLM::Vec3.new
    a[0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end

  def test_initialize_from_memory_address
    mem = Fiddle::Pointer.malloc(Fiddle::SIZEOF_FLOAT * 3)
    mem[                     0, Fiddle::SIZEOF_FLOAT] = [0.5].pack('F')
    mem[  Fiddle::SIZEOF_FLOAT, Fiddle::SIZEOF_FLOAT] = [1.0].pack('F')
    mem[2*Fiddle::SIZEOF_FLOAT, Fiddle::SIZEOF_FLOAT] = [1.5].pack('F')

    vec = CGLM::Vec3.new(addr: mem)
    assert_equal mem, vec.addr
    assert_equal 0.5, vec[0]
    assert_equal 1.0, vec[1]
    assert_equal 1.5, vec[2]
  end

  def test_inspect
    vec = CGLM::Vec3.new
    vec[0] = 0.5
    vec[1] = 1.0
    vec[2] = 1.5
    assert_match '0.5, 1.0, 1.5', vec.inspect
  end

  def test_array_access
    vec = CGLM::Vec3.new
    vec[0] = 0.5
    vec[1] = 1.0
    vec[2] = 1.5
    assert_equal 0.5, vec[0]
    assert_equal 1.0, vec[1]
    assert_equal 1.5, vec[2]
    assert_raises(RangeError) { vec[-1] }
    assert_raises(RangeError) { vec[ 3] }
    assert_raises(RangeError) { vec[-1] = 0 }
    assert_raises(RangeError) { vec[ 3] = 0 }
  end

  def test_vec3 # taken from cglm
    # test zero
    v = Vec3.zero
    assert Vec3.zero =~ v

    # test one
    v = Vec3.one
    assert Vec3.one =~ v

    # adds, subs, div, divs, mul
    v = v + Vec3.one
    assert v =~ 2

    v = v + 10
    assert v =~ 12

    v = v - Vec3.one
    assert v =~ 11

    v = v - 1
    assert v =~ 10

    v1 = Vec3.new.broadcast! 2
    v = v / v1
    assert v =~ 5

    v = v / 0.5
    assert v =~ 10

    v = v * v1
    assert v =~ 20

    v = v * 0.5
    assert v =~ 10

    v1 = v.normalize
    v1 = v1 * 0.8
    v = v.resize 0.8
    assert v1 =~ v

    # addadd, subadd, muladd
    v = Vec3.one

    Vec3.one.addadd Vec3.one, v
    assert v =~ 3

    Vec3.one.subadd Vec3.zero, v
    assert v =~ 4

    v1.broadcast! 2
    v2 = Vec3.new.broadcast! 3
    v1.muladd v2, v
    assert v =~ 10

    # rotate
    v = Vec3.yup

    rot1 = Mat4.rotate(Vec3.xup, 90.to_radians)
    v1 = rot1 * v
    rot1m3 = rot1.to_mat3
    v2 = rot1m3 * v

    assert v1 =~ v2
    assert v1 =~ Vec3.zup
  end
end
