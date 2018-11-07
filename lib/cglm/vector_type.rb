module CGLM
  class VectorType < Base
    def initialize(initial = nil, **args)
      super(**args)
      case initial
      when Array
        initial.each_with_index { |v, i| self[i] = v; break if i >= 3 }
      when Quat, Vec3, Vec4
        size = initial.class.size > self.class.size ? self.class.size : initial.class.size
        addr[0, size] = initial.addr[0, size]
      when nil
      else
        raise ArgumentError, 'initial values must be an Array, Quat, Vec3 or Vec4'
      end
    end
  end
end
