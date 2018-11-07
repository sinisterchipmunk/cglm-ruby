require 'fiddle'

module CGLM
  class Base
    attr_accessor :addr
    alias to_ptr addr

    def initialize(addr: CGLM.alloc(self.class).tap { |ptr|
      # Init malloc'd values to 0; there is a PR to fiddle for this, then we
      # can delete this code. https://github.com/ruby/fiddle/pull/14
      ptr[0, self.class.size] = "\x00".b * self.class.size
    })
      # Even if addr is present, but points to NULL, this is a problem that
      # will lead to segfaults. If not present, `nil.to_i == 0`.
      raise ArgumentError, 'BUG: object initialized without a backing store?' if addr.to_i == 0
      self.addr = addr
    end

    def copy_to(other)
      size = addr.size > other.addr.size ? other.addr.size : addr.size
      other.addr[0, size] = addr[0, size]
    end

    def dup(other = nil)
      if other
        copy_to other
      else
        super()
      end
    end

    def initialize_dup(other)
      super
      @addr = CGLM.alloc(self.class)
      other.copy_to(self)
    end
  end
end
