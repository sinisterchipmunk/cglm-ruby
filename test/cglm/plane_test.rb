require "test_helper"
require 'fiddle/import'

class CglmPlaneTest < Minitest::Test
  def test_dup
    a = CGLM::Plane.new([0, 1, 0], 1)
    a[0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end

  def test_initialize
    plane = CGLM::Plane.new([0, 1, 0], 1)
    assert_kind_of CGLM::Vec4, plane
  end
end
