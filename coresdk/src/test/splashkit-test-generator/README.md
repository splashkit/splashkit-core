# SplashKit Test Generator and Runner

A testing framework for generating and running tests across multiple programming languages for the SplashKit SDK.

## Supported Languages

- C++
- Python
- Pascal
- Rust
- C#

## Prerequisites

Before using the test generator and runner, ensure you have the following installed:

- Ruby (for running the generator and test runner)
- SplashKit SDK
- Language-specific requirements:
  - C++: g++ compiler and Catch2 testing framework
  - Python: Python 3.x and pytest
  - Pascal: Free Pascal Compiler (FPC) and FPCUnit
  - Rust: Rust compiler and Cargo
  - C#: .NET SDK

## Installation Instructions

1. Clone this repository
2. Install the required dependencies:

## Usage

### Test Generator

Generate tests from API specification:

ruby main.rb path/to/api.json

### Test Runner

You can run tests either by using command-line arguments or by editing main.rb directly.

#### Command Line Usage

Run all tests for a language
ruby main.rb -l cpp

Run specific test group
ruby main.rb -l cpp -g animations

Run single test
ruby main.rb -l cpp -g animations -t animation_count

#### File Usage

ruby main.rb --run-tests

Run all tests for a language in run_tests:

TestRunner.run_all_tests(:cpp)
TestRunner.run_all_tests(:python)
TestRunner.run_all_tests(:pascal)
TestRunner.run_all_tests(:rust)
TestRunner.run_all_tests(:csharp)

Run specific test group:

TestRunner.run_single_file(:cpp, 'animations')

Run single test:

TestRunner.run_specific_test(:cpp, 'animations', 'animation_count')

## Test Types

### Sequential Tests

These tests run in sequence (not parallel):

- audio
- animations
- windows
- graphics
- camera
- sprites
- physics
- timers

### Manual Tests

These tests require user interaction:

- input
- interface
- terminal
- logging

### Skipped Tests

These tests are skipped by default (for now):

- networking

## Test Configuration

Tests are defined in JSON files under `data/tests/`:
