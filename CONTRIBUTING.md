# Contributing to TVTMediaPlayer

Thank you for your interest in contributing to `TVTMediaPlayer`! We welcome contributions of all forms, including bug reports, documentation improvements, feature requests, and code modifications.

Please take a moment to review this document to ensure a smooth contribution process.

---

## 📖 Table of Contents
1. [Code of Conduct](#code-of-conduct)
2. [How Can I Contribute?](#how-can-i-contribute)
   - [Reporting Bugs](#reporting-bugs)
   - [Suggesting Enhancements](#suggesting-enhancements)
   - [Submitting Pull Requests](#submitting-pull-requests)
3. [Local Development Setup](#local-development-setup)
4. [Style Guides & Standards](#style-guides--standards)
   - [Objective-C Style Guide](#objective-c-style-guide)
   - [Swift Style Guide](#swift-style-guide)
5. [Community & Questions](#community--questions)

---

## Code of Conduct

By participating in this project, you agree to abide by our [Code of Conduct](CODE_OF_CONDUCT.md). Please report any violations or inappropriate behavior to [yevhenkhyzhniak@icloud.com].

---

## How Can I Contribute?

### Reporting Bugs

Before submitting a new bug report, please check the existing issues to see if the bug has already been reported. 

If you find a new bug, please open an issue and include:
* **Clear Title**: A concise summary of the issue.
* **Detailed Description**: Explain what you were trying to do and what actually happened.
* **Steps to Reproduce**: Step-by-step instructions to reproduce the bug.
* **System Environment**: iOS version, Xcode version, device model (or simulator details).
* **Logs & Crash Dumps**: If available, stack traces or console output.

### Suggesting Enhancements

We are always looking to improve `TVTMediaPlayer`! To suggest a feature or API enhancement:
1. Open a new feature request issue.
2. Describe the feature, its use case, and how it benefits other developers.
3. Outline any API design proposals or UI mockups.

### Submitting Pull Requests

If you want to contribute code changes:
1. **Fork the repository** and create a branch from `main` (e.g., `feature/add-some-feature` or `fix/resolve-memory-leak`).
2. Implement your changes. Ensure you add relevant unit tests or update the sample/demo project if applicable.
3. Verify your changes don't break Podspec validation:
   ```bash
   pod lib lint --allow-warnings
   ```
4. Commit your changes with clear, descriptive commit messages.
5. Push to your fork and submit a Pull Request (PR) to our repository.
6. In your PR description, explain *what* changed and *why*, and link to any relevant issues.

---

## Local Development Setup

To test and develop `TVTMediaPlayer` locally:
1. Clone the repository:
   ```bash
   git clone https://github.com/YevhenKhyzhniak/TVTMediaPlayer.git
   ```
2. Navigate to the directory and run linting to ensure the environment is correct:
   ```bash
   pod lib lint --allow-warnings
   ```
3. If you want to test the CocoaPod in an example app, add the local path to your test app's `Podfile`:
   ```ruby
   pod 'TVTMediaPlayer', :path => '../TVTMediaPlayer'
   ```

---

## Style Guides & Standards

### Objective-C Style Guide
* **Naming**: Use camelCase for methods and variables. Classes and protocols must use the `TVT` prefix (e.g., `TVTMediaPlayer`) or keep standard SDK style.
* **Formatting**: Use 4 spaces for indentation. Keep bracket formatting clean.
* **Imports**: Group system imports (`#import <Foundation/Foundation.h>`) separate from local headers (`#import "MediaPlayer.h"`).
* **Properties**: Always use attributes explicitly (e.g., `@property (nonatomic, strong) UIView *playerView;`).

### Swift Style Guide
* Follow the official [Swift API Design Guidelines](https://swift.org/documentation/api-design-guidelines/).
* Use capital CamelCase for types and lowercase camelCase for variables/functions.
* Prefer clean, swifty wrapper classes where possible if extending the wrapper API.

---

## Community & Questions

If you have questions or need help integrating the library:
* Open a discussion or issue on GitHub.
* Contact the maintainer: [yevhenkhyzhniak@icloud.com].
