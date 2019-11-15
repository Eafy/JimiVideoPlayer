Pod::Spec.new do |s|
  s.name         = "JimiVideoPlayer"
  s.version      = "1.4.1"
  s.summary      = "Jimi RTMP Video Player SDK for iOS at CocoaPods."

  s.description  = <<-DESC
  Jimi RTMP Video Player SDK for iOS at CocoaPods.
                   DESC

  s.homepage     = "https://github.com/Eafy/JimiVideoPlayer"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "Eafy" => "lizhijian_21@163.com" }
  s.platform     = :ios, "8.0"


  s.source       = { :git => "https://github.com/Eafy/JimiVideoPlayer.git", :tag => "#{s.version}" }

  s.ios.vendored_frameworks = "JimiVideoPlayer.framework"
  s.libraries = "c++"
  s.requires_arc = true

end