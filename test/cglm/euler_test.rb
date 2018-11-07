require "test_helper"
require 'fiddle/import'

class CglmEulerTest < Minitest::Test
  def test_euler # taken from cglm tests
    in_angles = Vec3.new([-45.to_radians, # X angle
                           88.to_radians, # Y angle
                           18.to_radians  # Z angle
                         ])

    rot1 = CGLM::Euler.xyz(in_angles)

    # extract angles
    out_angles = CGLM::Euler.angles(rot1)

    # angles must be equal in that range
    assert in_angles =~ out_angles

    # matrices must be equal
    rot2 = CGLM::Euler.xyz(out_angles)
    assert rot1 =~ rot2

    # change range
    in_angles[0] = -145.0.to_radians  # X angle
    in_angles[1] =  818.0.to_radians  # Y angle
    in_angles[2] =  181.0.to_radians  # Z angle

    rot1 = CGLM::Euler.xyz(in_angles)
    out_angles = CGLM::Euler.angles(rot1)

    # angles may not be equal but matrices MUST!

    # matrices must be equal
    rot2 = CGLM::Euler.xyz(out_angles)
    assert rot1 =~ rot2
  end
end
