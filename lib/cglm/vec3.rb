module CGLM
  class Vec3 < VectorType
    def to_a
      [self[0], self[1], self[2]]
    end

    def inspect
      "#<#{self.class}@#{addr.to_i.to_s(16)} #{to_a.inspect}>"
    end

    def ==(other)
      case other
      when VectorType then equals_vec3(other)
      when Numeric    then equals_scalar(other)
      else false
      end
    end

    def =~(other)
      case other
      when VectorType then equalish_vec3(other)
      when Numeric    then equalish_scalar(other)
      else false
      end
    end

    def +(other)
      case other
      when VectorType then add_vec3(other)
      when Numeric    then add_scalar(other)
      else false
      end
    end

    def -(other)
      case other
      when VectorType then sub_vec3(other)
      when Numeric    then sub_scalar(other)
      else false
      end
    end

    def *(other)
      case other
      when VectorType then mul_vec3(other)
      when Numeric    then mul_scalar(other)
      else false
      end
    end

    def /(other)
      case other
      when VectorType then div_vec3(other)
      when Numeric    then div_scalar(other)
      else false
      end
    end

    def addadd(other, dest)
      case other
      when VectorType then addadd_vec3(other, dest)
      when Numeric    then addadd_scalar(other, dest)
      else false
      end
    end

    def subadd(other, dest)
      case other
      when VectorType then subadd_vec3(other, dest)
      when Numeric    then subadd_scalar(other, dest)
      else false
      end
    end

    def muladd(other, dest)
      case other
      when VectorType then muladd_vec3(other, dest)
      when Numeric    then muladd_scalar(other, dest)
      else false
      end
    end
  end
end
