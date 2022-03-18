module CGLM
  class MatrixType < Base
    # Returns a flat array of floats, rather than the 2D array returned by
    # #to_a. Equivalent to `to_a.flatten`, but more efficient.
    def to_flat_a
      addr = self.addr
      addr[0, addr.size].unpack("F*")
    end
  end
end
