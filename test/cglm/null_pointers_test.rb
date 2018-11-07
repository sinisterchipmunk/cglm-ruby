require "test_helper"
require 'fiddle/import'

class CGLM::NullPointersTest < Minitest::Test
  def test_null_pointers
    assert_raises(ArgumentError) { AABB.new(addr: nil) }
    assert_raises(ArgumentError) { Mat3.new(addr: nil) }
    assert_raises(ArgumentError) { Mat4.new(addr: nil) }
    assert_raises(ArgumentError) { Vec3.new(addr: nil) }
    assert_raises(ArgumentError) { Vec4.new(addr: nil) }

    assert_raises(ArgumentError) { AABB.new(addr: Fiddle::Pointer.new(0)) }
    assert_raises(ArgumentError) { Mat3.new(addr: Fiddle::Pointer.new(0)) }
    assert_raises(ArgumentError) { Mat4.new(addr: Fiddle::Pointer.new(0)) }
    assert_raises(ArgumentError) { Vec3.new(addr: Fiddle::Pointer.new(0)) }
    assert_raises(ArgumentError) { Vec4.new(addr: Fiddle::Pointer.new(0)) }
  end
end
