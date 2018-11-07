require "test_helper"
require 'fiddle/import'

class CglmSphereTest < Minitest::Test
  def test_dup
    a = CGLM::Sphere.new
    a[0] = 1

    b = a.dup
    assert_equal a, b
    refute_equal a.addr, b.addr
  end
end
