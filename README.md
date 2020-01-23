# CGLM

[![Build Status](https://travis-ci.org/sinisterchipmunk/cglm-ruby.svg?branch=master)](https://travis-ci.org/sinisterchipmunk/cglm-ruby)

Ruby bindings for [CGLM](https://github.com/recp/cglm), a high performance math library for OpenGL.

[CGLM](https://github.com/recp/cglm) provides support for SIMD on CPUs that support it in order to deliver better performance. This requires the variables to be aligned to 8-, 16- and 32-byte boundaries, but this gem automatically handles this requirement so you don't have to think about that.

[CGLM](https://github.com/recp/cglm) sports the following features:

* general purpose matrix operations (mat4, mat3)
* general purpose vector operations (cross, dot, rotate, proj, angle...)
* affine transforms
* matrix decomposition (extract rotation, scaling factor)
* optimized affine transform matrices (mul, rigid-body inverse)
* camera (lookat)
* projections (ortho, perspective)
* quaternions
* euler angles / yaw-pitch-roll to matrix
* extract euler angles
* frustum (extract view frustum planes, corners...)
* bounding box (AABB in Frustum (culling), crop, merge...)
* project, unproject

(Note: A few other features are available in the original C library, such as optional in-lining of all functions, which don't really translate to Ruby gems -- although such features are used by the code for the gem itself.)

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'cglm'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cglm

## Usage

Include the `CGLM` module, or use the classes it defines directly:

```ruby
include CGLM

a = Vec3.new
b = Vec3.new([1, 0, 0])

proj = Mat4.perspective(fovy: Math::PI / 4, aspect: 640.0 / 480.0)
view = Mat4.rotate(Vec3.new([0, 1, 0], PI_4)
model = Mat4.translate(Vec3.new([34, 57, 36]))

mvp = proj * view * model
```

This gem provides two basic variants for almost every operation. Let's use `Vec3#add` as an example. You can use the intuitive syntax:

```ruby
result = a + b
```

This will work just fine, returning a new `Vec3`. Or, in performance-critical situations, you may wish to directly specify a destination to place the result in:

```ruby
result = Vec3.new
loop do
  # avoid allocating a new Vec3 by reusing result
  a.add(b, result)
end
```

The second syntax is perhaps a little less intuitive, but avoids creation of extra objects (because you specify them yourself), so you can more easily control your memory and garbage collection costs.

There are too many methods to list here, so you are encouraged to check out the [project documentation](https://www.rubydoc.info/github/sinisterchipmunk/cglm-ruby).


## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake test` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/sinisterchipmunk/cglm-ruby.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
