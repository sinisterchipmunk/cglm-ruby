require "test_helper"
require 'fiddle/import'

class CglmVec4Test < Minitest::Test
  def test_dup
    a = CGLM::Vec4.new
    a[0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end

  def test_vec4 # taken from cglm
    assert Vec4.zero == Vec4.new
    assert Vec4.one  == Vec4.new([1, 1, 1, 1])

    # adds, subs, div, divs, mul
    v = Vec4.one + Vec4.one
    assert v =~ Vec4.new.broadcast!(2)
    v += 10
    assert v =~ Vec4.new.broadcast!(12)

    v -= Vec4.one
    assert v =~ Vec4.new.broadcast!(11)

    v -= 1
    assert v =~ Vec4.new.broadcast!(10)

    v1 = Vec4.new.broadcast! 2
    v /= v1
    assert v =~ Vec4.new.broadcast!(5)

    v /= 0.5
    assert v =~ Vec4.new.broadcast!(10)

    v *= v1
    assert v =~ Vec4.new.broadcast!(20)

    v *= 0.5
    assert v =~ Vec4.new.broadcast!(10)

    v1 = v.normalize
    v1 *= 0.8
    v *= 0.8
    assert v =~ v1

    # addadd, subadd, muladd
    v.one!

    v = v.addadd Vec4.one, Vec4.one
    assert v =~ Vec4.new.broadcast!(3)

    v = v.subadd Vec4.one, Vec4.zero
    assert v =~ Vec4.new.broadcast!(4)

    v1.broadcast! 2
    v2 = Vec4.new.broadcast! 3
    v1.muladd v2, v
    assert v =~ Vec4.new.broadcast!(10)

    # min, max
    v1 = Vec4.rand
    v2 = Vec4.rand

    v3 = v1.max v2
    4.times { |i| assert v3[i] >= v1[i] && v3[i] >= v2[i] }

    v3 = v1.min v2
    4.times { |i| assert v3[i] <= v1[i] && v3[i] <= v2[i] }

    # clamp
    v3.clamp! 0.1, 0.8
    4.times { |i| assert v3[i] >= 0.0999 && v3[i] <= 0.80001 }
  end

  def test_initialize_from_memory_address
    mem = Fiddle::Pointer.malloc(Fiddle::SIZEOF_FLOAT * 4)
    mem[                     0, Fiddle::SIZEOF_FLOAT] = [0.5].pack('F')
    mem[  Fiddle::SIZEOF_FLOAT, Fiddle::SIZEOF_FLOAT] = [1.0].pack('F')
    mem[2*Fiddle::SIZEOF_FLOAT, Fiddle::SIZEOF_FLOAT] = [1.5].pack('F')
    mem[3*Fiddle::SIZEOF_FLOAT, Fiddle::SIZEOF_FLOAT] = [2.0].pack('F')

    vec = CGLM::Vec4.new(addr: mem)
    assert_equal mem, vec.to_ptr
    assert_equal mem, vec.addr
    assert_equal 0.5, vec[0]
    assert_equal 1.0, vec[1]
    assert_equal 1.5, vec[2]
    assert_equal 2.0, vec[3]
  end

  def test_array_access
    vec = CGLM::Vec4.new
    vec[0] = 0.5
    vec[1] = 1.0
    vec[2] = 1.5
    vec[3] = 2.0
    assert_equal 0.5, vec[0]
    assert_equal 1.0, vec[1]
    assert_equal 1.5, vec[2]
    assert_equal 2.0, vec[3]
    assert_raises(RangeError) { vec[-1] }
    assert_raises(RangeError) { vec[ 4] }
    assert_raises(RangeError) { vec[-1] = 0 }
    assert_raises(RangeError) { vec[ 4] = 0 }
  end
end
