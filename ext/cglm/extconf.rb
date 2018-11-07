require "mkmf"
require 'fileutils'
require 'rubygems/package'
require 'zlib'

CGLM_VERSION = '0.4.9'
cglm_source_url = "https://github.com/recp/cglm/archive/v#{CGLM_VERSION}.tar.gz"
cglm_tar_gz = File.expand_path("cglm-#{CGLM_VERSION}.tar.gz", __dir__)
cglm_dir = File.expand_path("cglm-#{CGLM_VERSION}", __dir__)

# fetch cglm unless it's already on the file system
unless File.exist?(cglm_tar_gz)
  require 'open-uri'
  # save tarfile
  open(cglm_tar_gz, 'wb') do |file|
    file << open(cglm_source_url, 'rb').read
  end

  # extract tarfile
  FileUtils.rm_rf cglm_dir if File.directory?(cglm_dir)
  FileUtils.mkdir_p cglm_dir
  tar_extract = Gem::Package::TarReader.new(Zlib::GzipReader.open(cglm_tar_gz))
  tar_extract.rewind # The extract has to be rewinded after every iteration
  tar_extract.each do |entry|
    full_path = File.expand_path(entry.full_name, __dir__)
    if entry.directory?
      FileUtils.mkdir_p full_path
    else
      FileUtils.mkdir_p File.dirname(full_path)
      File.open(full_path, 'wb') { |file| file << entry.read }
    end
  end
  tar_extract.close
end

$INCFLAGS << " -I#{cglm_dir}/include"

require 'fiddle'
%w(
  SIZEOF_VOIDP SIZEOF_CHAR SIZEOF_SHORT SIZEOF_INT SIZEOF_LONG SIZEOF_LONG_LONG
  SIZEOF_FLOAT SIZEOF_DOUBLE SIZEOF_SIZE_T SIZEOF_SSIZE_T SIZEOF_PTRDIFF_T
  SIZEOF_INTPTR_T SIZEOF_UINTPTR_T
).each do |const_name|
  if Fiddle.constants.include?(const_name.to_sym)
    $CFLAGS << " -DHAVE_#{const_name}=1 -D#{const_name}=#{Fiddle.const_get(const_name.to_sym)}"
  end
end

create_makefile("cglm/cglm")
