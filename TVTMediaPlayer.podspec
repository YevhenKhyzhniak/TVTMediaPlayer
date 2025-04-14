Pod::Spec.new do |s|
  # ... (keep name, version, summary, etc.) ...
  s.homepage         = 'https://github.com/YevhenKhyzhniak/TVTMediaPlayer'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Yevhen Khyzhniak' => 'yevhenkhyzhniak@icloud.com' }
  s.source           = { :git => 'git@github.com:YevhenKhyzhniak/TVTMediaPlayer.git', :tag => s.version.to_s }

  s.ios.deployment_target = '12.0'
  s.swift_version = '5.0' # Keep this if you plan Swift interaction

  # --- Changes Start Here ---

  # Define the location of the module map
  s.module_map = 'libAndHeaders/module.modulemap'

  # Source files should now point ONLY to the module map if no pod sources need compilation
  # If you had .m files, you'd add them here too.
  # s.source_files = 'libAndHeaders/module.modulemap'
  # Let's explicitly keep preserve_paths to ensure headers are copied correctly for the module map to find them
  s.preserve_paths = 'libAndHeaders/**/*' # Make sure headers are available

  # Remove public_header_files and header_mappings_dir as module map handles exposure
  # s.public_header_files = 'libAndHeaders/**/*.h' # REMOVE or comment out
  # s.header_mappings_dir = 'libAndHeaders'     # REMOVE or comment out

  # --- Changes End Here ---

  # Static lib
  s.vendored_libraries = 'libAndHeaders/MediaPlayer/libMediaPlayer.a', 'libAndHeaders/SDK/libDVR_NET_SDK.a'

  s.resources = 'libAndHeaders/MediaPlayer/default.metallib'

  s.frameworks = 'AVFoundation', 'CoreMedia', 'UIKit'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }
  s.library = 'c++'
end