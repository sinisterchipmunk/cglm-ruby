module CGLM
  module Plane
    class << self
      # Returns a new Vec4 representing a plane with the given normal (a Vec3)
      # and distance (a number).
      def new(normal, distance)
        return Vec4.new([*normal, distance])
      end
    end
  end
end
