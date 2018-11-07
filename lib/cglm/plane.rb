module CGLM
  class Plane < Vec4
    # Returns a new Vec4 representing a plane with the given normal (a Vec3)
    # and distance (a number).
    def initialize(normal, distance)
      super [*normal, distance]
    end
  end
end
