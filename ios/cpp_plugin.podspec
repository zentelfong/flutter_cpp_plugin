#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name             = 'flutterCppPlugin'
  s.version          = '0.0.1'
  s.summary          = 'A new flutter cplusplus plugin project.'
  s.description      = <<-DESC
A new flutter cplusplus plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }

  s.source_files = 'Classes/**/*'
  s.public_header_files = 'Classes/**/*.h'

  s.dependency 'Flutter'
  
  s.ios.deployment_target = '8.0'

  s.subspec 'Jsoncpp' do |jsoncpp|
    jsoncpp.public_header_files = '../include/json/*.h'
    jsoncpp.source_files   = '../src/libjson/*'
    jsoncpp.compiler_flags = '-Wno-incomplete-implementation -Wno-missing-prototypes'
  end

  s.subspec 'PluginCore' do |plugincore|
    plugincore.public_header_files = '../include/*.h'
    plugincore.source_files   = '../src/*.cc'
    plugincore.compiler_flags = '-Wno-incomplete-implementation -Wno-missing-prototypes'
  end

end
