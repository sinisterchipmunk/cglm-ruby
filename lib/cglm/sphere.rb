module CGLM
  # Sphere Representation in cglm: `[center.x, center.y, center.z, radius]`
  #
  # You could use this representation or you can convert it to Vec4 before
  # calling any function.
  class Sphere < Vec4
    def radius
      self[3]
    end
  end
end
