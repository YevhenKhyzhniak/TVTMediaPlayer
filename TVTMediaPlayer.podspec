Pod::Spec.new do |s|
  s.name             = 'TVTMediaPlayer'
  s.version          = '0.1.0'
  s.summary          = 'Library for interaction with TVT cameras'
  s.description      = <<-DESC
                      TVTMediaPlayer is a library that provides functionality for working with TVT cameras.
                      It includes classes for video playback, stream decoding, and device management.
                      DESC
  s.homepage         = 'https://github.com/YevhenKhyzhniak/TVTMediaPlayer'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Yevhen Khyzhniak' => 'yevhenkhyzhniak@icloud.com' }
  s.source           = { :git => 'git@github.com:YevhenKhyzhniak/TVTMediaPlayer.git', :tag => s.version.to_s }

  s.ios.deployment_target = '12.0'
  s.swift_version = '5.0'

  # Headers
  s.source_files = 'libAndHeaders/**/*.h'

  # Public
  s.public_header_files = 'libAndHeaders/**/*.h'

  # Static lib
  s.vendored_libraries = 'libAndHeaders/MediaPlayer/libMediaPlayer.a', 'libAndHeaders/SDK/libDVR_NET_SDK.a'

  s.resources = 'libAndHeaders/MediaPlayer/default.metallib'

  s.frameworks = 'AVFoundation', 'CoreMedia', 'UIKit'

  s.xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }

  s.preserve_paths = 'libAndHeaders/**/*'
  s.header_mappings_dir = 'libAndHeaders'

  s.library = 'c++'
end