require 'bundler/setup'
require 'simplecov'
SimpleCov.start
require "cglm"
require "minitest/autorun"

class Minitest::Test
  include CGLM
end
