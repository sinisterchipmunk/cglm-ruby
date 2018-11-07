require "test_helper"
require 'fiddle/import'

class CglmAABBTest < Minitest::Test
  def test_dup
    aabb = CGLM::AABB.new
    aabb[0][0] = 1

    other = aabb.dup
    assert_equal aabb, other
    refute_equal aabb.addr, other.addr
  end

  def test_initialize_from_memory_address
    mem = Fiddle::Pointer.malloc(Fiddle::SIZEOF_FLOAT * 6)
    aabb = CGLM::AABB.new(addr: mem)
    assert_equal mem,                              aabb.addr
    assert_equal mem,                              aabb[0].addr
    assert_equal (mem + Fiddle::SIZEOF_FLOAT * 3), aabb[1].addr

    mem[0, Fiddle::SIZEOF_FLOAT * 6] = [0.5, 1.0, 1.5, 2.0, 2.5, 3.0].pack("F6")
    assert_equal 0.5, aabb[0][0]
    assert_equal 1.0, aabb[0][1]
    assert_equal 1.5, aabb[0][2]

    assert_equal 2.0, aabb[1][0]
    assert_equal 2.5, aabb[1][1]
    assert_equal 3.0, aabb[1][2]

    assert_raises(RangeError) { aabb[-1] }
    assert_raises(RangeError) { aabb[2] }
  end
end
