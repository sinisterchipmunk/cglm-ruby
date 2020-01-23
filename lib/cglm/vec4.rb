module CGLM
  class Vec4 < VectorType
    def size
      4
    end

    def inspect
      "#<#{self.class}@#{addr.to_i.to_s(16)} #{to_a.inspect}>"
    end

    def ==(other)
      case other
      when VectorType then equals_vec4(other)
      when Numeric    then equals_scalar(other)
      else false
      end
    end

    # Returns true if the given value is very close to this Vec4. If `other`
    # is a scalar (number), each component in this vector must be very close
    # to the scalar. If it's a vector, it must be a Vec4 and each component
    # of this Vec4 must be very close to the corresponding component of
    # `other`. See #equalish_vec4 and #equalish_scalar.
    def =~(other)
      case other
      when VectorType then equalish_vec4(other)
      when Numeric    then equalish_scalar(other)
      else false
      end
    end

    def +(other)
      case other
      when VectorType then add_vec4(other)
      when Numeric    then add_scalar(other)
      else false
      end
    end

    def -(other)
      case other
      when VectorType then sub_vec4(other)
      when Numeric    then sub_scalar(other)
      else false
      end
    end

    def *(other)
      case other
      when VectorType then mul_vec4(other)
      when Numeric    then mul_scalar(other)
      else false
      end
    end

    def /(other)
      case other
      when VectorType then div_vec4(other)
      when Numeric    then div_scalar(other)
      else false
      end
    end

    def addadd(other, dest)
      case other
      when VectorType then addadd_vec4(other, dest)
      when Numeric    then addadd_scalar(other, dest)
      else false
      end
    end

    def subadd(other, dest)
      case other
      when VectorType then subadd_vec4(other, dest)
      when Numeric    then subadd_scalar(other, dest)
      else false
      end
    end

    def muladd(other, dest)
      case other
      when VectorType then muladd_vec4(other, dest)
      when Numeric    then muladd_scalar(other, dest)
      else false
      end
    end

    def clamp(min, max, *extra)
      case min
      when VectorType then clamp_vec4(min, max, *extra)
      when Numeric    then clamp_scalar(min, max, *extra)
      else raise ArgumentError, 'need Vec4 or'
      end
    end

    def clamp!(min, max)
      case min
      when VectorType then clamp_vec4!(min, max)
      when Numeric    then clamp_scalar!(min, max)
      else raise ArgumentError, 'need Vec4 or Scalar'
      end
    end
  end
end
