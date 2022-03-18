module CGLM
  class Mat4 < MatrixType
    def initialize(initial_values = nil, **args)
      super(**args)
      case initial_values
      when Mat3
        initial_values.to_a.each_with_index { |row, i| self[i] = row }
      when Mat4
        addr[0, self.class.size] = initial_values.addr[0, self.class.size]
      when Array
        initial_values.each_with_index do |row, i|
          self[i] = row
        end
      when nil
      else
        raise ArgumentError, 'initial values should be a Mat4, a Mat3 or an array of Array/Vec3/Vec4'
      end
    end

    def to_a
      4.times.map { |i| self[i].to_a }
    end

    def inspect
      vals = to_a
      longest_val_size = vals.flatten.reduce(0) { |a, v| a < v.to_s.size ? v.to_s.size : a }
      vals.map! { |row| row.map { |val| val.to_s.rjust(longest_val_size) }.join(', ') }
      left = "#<#{self.class}@#{addr.to_i.to_s(16)} ["
      left + vals.join(",\n" + (" " * left.size)) + "]>"
    end

    # Performs multiplication with `other` and returns the result.
    #
    # * `other` is a Mat3 or Vec3.
    def *(other)
      case other
      when Mat4    then mul_mat4(other)
      when Mat3    then mul_mat3(other)
      when Vec3    then mul_vec3(other)
      when Vec4    then mul_vec4(other)
      when Numeric then mul_scalar(other)
      else raise ArgumentError, "Don't know how to multiply Mat4 with object: #{other.inspect}"
      end
    end
  end
end
