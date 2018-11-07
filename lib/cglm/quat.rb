module CGLM
  class Quat < Vec4
    def *(other)
      case other
      when Quat then mul_quat(other)
      else Quat.new(super)
      end
    end
  end
end
