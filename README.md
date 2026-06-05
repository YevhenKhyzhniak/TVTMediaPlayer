# TVTMediaPlayer

[![CocoaPods Compatible](https://img.shields.io/cocoapods/v/TVTMediaPlayer.svg?style=flat-flat&color=brightgreen)](https://cocoapods.org/pods/TVTMediaPlayer)
[![Platform Support](https://img.shields.io/badge/platform-iOS%2012.0+-blue.svg?style=flat-flat)](https://developer.apple.com/ios/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-flat)](LICENSE)
[![GitHub active](https://img.shields.io/badge/maintained-yes-brightgreen.svg?style=flat-flat)]()

An iOS CocoaPod wrapper library designed to facilitate integration with **TVT (Tongwei Video Technology)** IP cameras, Digital Video Recorders (DVRs), and Network Video Recorders (NVRs). 

`TVTMediaPlayer` bridges the gap between the low-level, high-performance static C/C++ SDKs (`libDVR_NET_SDK.a` and `libMediaPlayer.a`) and modern iOS applications, providing clean Objective-C interfaces that can be seamlessly consumed in both Swift and Objective-C projects.

---

## 📖 Table of Contents

- [Why TVTMediaPlayer?](#-why-tvtmediaplayer)
- [Key Features](#-key-features)
- [Project Architecture](#-project-architecture)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Quick Start Guide](#-quick-start-guide)
  - [1. Initialize and Login](#1-initialize-and-login)
  - [2. Live Stream Playback](#2-live-stream-playback)
  - [3. Capture and Recording](#3-capture-and-recording)
  - [4. Audio & Two-Way Intercom](#4-audio--two-way-intercom)
  - [5. Fisheye Dewarping](#5-fisheye-dewarping)
- [Apple Silicon (M1/M2/M3) Simulator Workaround](#apple-silicon-m1m2m3-simulator-workaround)
- [Contributing](#-contributing)
- [Security](#-security)
- [License](#-license)

---

## ❓ Why TVTMediaPlayer?

Integrating raw video surveillance SDKs in iOS often presents several challenges:
* **Complex Build Environments**: Managing fat static libraries (`.a`) with custom compile flags and header search paths.
* **Architecture Mismatches**: Dealing with simulator compilation errors on ARM64 Apple Silicon Macs.
* **Low-Level Memory & Thread Management**: Safely parsing raw video frames (H.264/H.265) and converting them into renderable UI layers.
* **Device Control Integration**: Binding PTZ (Pan-Tilt-Zoom), audio, recording, and camera-specific actions (like Fisheye calibration) to standard Cocoa touch events.

`TVTMediaPlayer` resolves these by packaging everything into a modular, clean CocoaPod, providing:
1. **Metal & OpenGL Rendering**: Automatic hardware-accelerated video rendering.
2. **Delegate-Driven Touch Interactions**: Standard gestures (tap, double-tap, drag) translated into viewport actions.
3. **Structured API**: Simple interfaces for complex features like live-streaming, playback, intercom, and alarms.

---

## ⚡ Key Features

* **🎥 Live Video Streaming**: Low-latency video playback supporting both Main and Sub streams.
* **⚙️ Hardware H.264 & H.265 Decoding**: Hardware-accelerated decoding using iOS system frameworks.
* **📐 PTZ & Device Control**: Seamless camera pan, tilt, zoom, and preset management.
* **🎙️ Audio & Two-Way Talkback**: High-fidelity audio playback and two-way voice intercom using G.711 / ADPCM decoders.
* **📸 Snapshots & Video Recording**: Local frame capture (to JPEG/PNG) and MP4 video clip recording directly to the iOS sandbox.
* **🐠 Fisheye Dewarping**: Advanced viewport modes (Common, Sphere, Cylinder, Square, 4-Split, VR) for 360-degree fisheye cameras.
* **🚨 Smart Alarms**: Real-time subscriptions for motion detection, perimeter intrusion, face matching, fire point detection, and temperature analysis.

---

## 🏗️ Project Architecture

```
TVTMediaPlayer/
├── TVTMediaPlayer.podspec      # CocoaPods specification
├── SwiftSupport.swift          # Force-enable Swift runtime support
├── LICENSE                     # MIT License
├── README.md                   # Project Documentation
└── libAndHeaders/              # Vendor SDK Binaries & Headers
    ├── MediaPlayer/            # Rendering & Decoding Library
    │   ├── MediaPlayer.h       # Media player Objective-C class
    │   ├── libMediaPlayer.a    # High-performance static library
    │   └── ...
    └── SDK/                    # Connection & Control SDK
        ├── DVR_NET_SDK.h       # Connection SDK functions
        ├── libDVR_NET_SDK.a    # Raw C/C++ static library
        └── ...
```

---

## 📋 Requirements

* **iOS Deployment Target**: iOS 12.0 or later
* **Xcode**: Xcode 12.0 or later
* **Languages**: Swift 5.0+ or Objective-C
* **Hardware**: Tested on real iOS devices (arm64). For Simulators, see the Apple Silicon note below.

---

## 📦 Installation

Add the following line to your project's `Podfile`:

```ruby
pod 'TVTMediaPlayer', :git => 'https://github.com/YevhenKhyzhniak/TVTMediaPlayer.git', :tag => '0.1.0'
```

Then, run:
```bash
pod install
```

---

## 🚀 Quick Start Guide

### 1. Initialize and Login

You need to initialize the underlying network SDK and log into the target DVR/NVR/IP camera.

#### Objective-C
```objc
#import <TVTMediaPlayer/DVR_NET_SDK.h>

// 1. Initialize the SDK
BOOL initSuccess = NET_SDK_Init();
if (initSuccess) {
    NSLog(@"DVR Net SDK Initialized successfully.");
}

// 2. Define device connection details
NET_SDK_DEVICE_IP_INFO loginInfo;
memset(&loginInfo, 0, sizeof(NET_SDK_DEVICE_IP_INFO));
strcpy(loginInfo.szIpAddr, "192.168.1.100");
loginInfo.netPort = 80;
strcpy(loginInfo.szPassword, "admin12345");

// 3. Login to get User ID
LONG userID = NET_SDK_Login(&loginInfo);
if (userID > 0) {
    NSLog(@"Successfully logged in! User ID: %ld", userID);
}
```

#### Swift
```swift
import TVTMediaPlayer

// 1. Initialize SDK
let initSuccess = NET_SDK_Init()
if initSuccess {
    print("DVR Net SDK Initialized successfully.")
}

// 2. Login to Device
var loginInfo = NET_SDK_DEVICE_IP_INFO()
// Configure loginInfo with target IP, Port, Username, and Password
// Call NET_SDK_Login(&loginInfo) to authenticate
```

---

### 2. Live Stream Playback

Render a live feed inside an iOS view using the `MediaPlayer` container.

#### Objective-C
```objc
#import <TVTMediaPlayer/MediaPlayer.h>

// Initialize player with device MAC address
MediaPlayer *player = [[MediaPlayer alloc] init:1 MAC:@"00:1A:2B:3C:4D:5E"];

// Set channel details
[player SetPlayerChannel:0 devName:@"Main_Entrance"];

// Set target frame for the player's view
[player setFrame:self.view.bounds];

// Add player view to parent view hierarchy
UIView *playerView = [player getPlayerView];
[self.view addSubview:playerView];

// Begin decoding incoming stream packets
// Feed packets received via NET_SDK_StartRealPlay callbacks:
// [player OnVideoDate:channel Data:buffer Length:len TimeStamp:ts IFrame:isIFrame ...];
```

#### Swift
```swift
import TVTMediaPlayer

// Initialize player
let player = MediaPlayer(1, mac: "00:1A:2B:3C:4D:5E")

// Configure channel & frame
player?.setPlayerChannel(0, devName: "Main_Entrance")
player?.setFrame(self.view.bounds)

if let playerView = player?.getPlayerView() {
    self.view.addSubview(playerView)
}
```

---

### 3. Capture and Recording

#### Snapshots
```objc
// Set capture destination path
[player SetCapturePath:NSTemporaryDirectory()];

// Capture current frame
[player CaptureBitmap];
```

#### Video Recording
```objc
// Set destination path
[player SetRecordPath:[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"record.mp4"]];

// Toggle Recording
if (![player GetRecordState]) {
    [player StartRecord];
} else {
    [player StopRecord];
}
```

---

### 4. Audio & Two-Way Intercom

Open audio streams or broadcast microphone input to the camera.

```objc
// Play Audio from Stream
[player StartAudio:0]; // 0 for default server type

// Speak into Camera (Talkback)
[player StartTalk:0];

// Stop Intercom
[player StopTalk];
[player StopAudio];
```

---

### 5. Fisheye Dewarping

Dewarp 360-degree panorama inputs dynamically.

```objc
// Enable Fisheye correction engine
[player setFishEyeEnable:YES];

// Select calibration / dewarp model
[player setFishEyeModel:FISH_EYES_SPHERE_FOUR_MODE]; // 4-split screen mode
```

---

## Apple Silicon (M1/M2/M3) Simulator Workaround

Since the vendored binary libraries (`libMediaPlayer.a` and `libDVR_NET_SDK.a`) are compiled as static archives (`arm64` physical architecture and `x86_64` simulator architecture), compiling on an Apple Silicon (M1/M2/M3) Mac targeting the **iOS Simulator (ARM64)** might cause linker issues.

To resolve this, add the following post-install hook to your project's `Podfile` to exclude arm64 simulator builds, forcing Xcode to compile simulator targets using Rosetta 2 translation:

```ruby
post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['EXCLUDED_ARCHS[sdk=iphonesimulator*]'] = 'arm64'
    end
  end
end
```

---

## 🤝 Contributing

Contributions are welcome! Please feel free to open issues, submit pull requests, or send suggestions. For details on code style and the PR submission pipeline, please read [CONTRIBUTING.md](CONTRIBUTING.md).

---

## 🔒 Security

We take security seriously. If you identify any vulnerability, please report it privately according to our security policy. See [SECURITY.md](SECURITY.md) for details.

---

## 📄 License

`TVTMediaPlayer` is available under the **MIT License**. See [LICENSE](LICENSE) for more info.