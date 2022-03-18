module CGLM
  class Mat3 < MatrixType
    # Performs multiplication with `other` and returns the result.
    #
    # * `other` is a Mat3 or Vec3.
    def *(other)
      case other
      when Mat3    then mul_mat3(other)
      when Vec3    then mul_vec3(other)
      when Numeric then mul_scalar(other)
      else raise ArgumentError, "Don't know how to multiply Mat3 with object: #{other.inspect}"
      end
    end

    def to_a
      3.times.map { |i| self[i].to_a }
    end

    def inspect
      vals = to_a
      longest_val_size = vals.flatten.reduce(0) { |a, v| a < v.to_s.size ? v.to_s.size : a }
      vals.map! { |row| row.map { |val| val.to_s.rjust(longest_val_size) }.join(', ') }
      left = "#<#{self.class}@#{addr.to_i.to_s(16)} ["
      left + vals.join(",\n" + (" " * left.size)) + "]>"
    end

    # Returns a flat array of floats, rather than the 2D array returned by
    # #to_a. Equivalent to `to_a.flatten`, but more efficient.
    def to_flat_a
      addr = self.addr
      addr[0, addr.size].unpack("F*")
    end
  end
end
