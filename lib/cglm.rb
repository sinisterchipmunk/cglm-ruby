require "cglm/version"

class Numeric
  def to_radians
    self * Math::PI / 180.0
  end

  def to_degrees
    self * 180.0 / Math::PI
  end
end

module CGLM
  require 'cglm/base'
  require 'cglm/vector_type'
  require 'cglm/aabb'
  require 'cglm/vec3'
  require 'cglm/vec4'
  require 'cglm/mat3'
  require 'cglm/mat4'
  require 'cglm/quat'
  require 'cglm/frustum'
  require 'cglm/plane'
end

require "cglm/cglm"
