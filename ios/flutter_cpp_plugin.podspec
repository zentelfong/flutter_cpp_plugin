#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name             = 'flutter_cpp_plugin'
  s.version          = '0.0.1'
  s.summary          = 'A new flutter cplusplus plugin project.'
  s.description      = <<-DESC
A new flutter cplusplus plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }

  s.header_dir = '../include'
  s.source_files = '../src/libjson/*','../src/*.cc','Classes/**/*','../example/*'
  s.public_header_files = 'Classes/**/*.h','../include/json/*.h','../include/*.h'

  s.dependency 'Flutter'
  
  s.ios.deployment_target = '8.0'

end
