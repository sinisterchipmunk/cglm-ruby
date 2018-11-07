module CGLM
  class Frustum
    attr_accessor :matrix

    def initialize(matrix = Mat4.identity)
      @matrix = matrix
    end
  end
end
