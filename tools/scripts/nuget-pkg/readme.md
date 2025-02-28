# SplashKit

SplashKit is a software development library designed to empower beginner programmers. It provides a range of methods and classes to help create interactive graphical programs, without taking any control away from the programmer.

To use this package you must install the skm tool from [splashkit.io](https://splashkit.io), and globally install the native library.

```bash
skm global install
```

## SplashKit NuGet Package

The SplashKit NuGet package provides a .NET Standard library for creating 2D games and applications using the SplashKit framework. SplashKit is a free and open-source game development library that simplifies the process of building games and interactive applications.

### Features

- **2D Graphics**: Draw shapes, images, and text to the screen with ease.
- **Input Handling**: Respond to keyboard, mouse, and touch input.
- **Audio**: Play sounds and music in your applications.
- **Networking**: Communicate with other clients and servers over the network.
- **Json File I/O**: Load and save data to json files.
- **Math Utilities**: Perform common mathematical operations.
- **Timers**: Schedule events and manage game time.

### Getting Started

To use the SplashKit NuGet package in your .NET project, follow these steps:

1. **Install the Package**: You can install the SplashKit NuGet package using the NuGet Package Manager in Visual Studio or by running the following command in the Package Manager Console:

   ```shell
   dotnet add package SplashKit
   ```

2. **Import the Namespace**: In your C# code, add the following using statement to access the SplashKit classes and methods:

    *With Object Oriented Code*:

    ```csharp
    using SplashKitSDK;
    ```

    *Using Top-level statements*:

    ```csharp
    using static SplashKitSDK.SplashKit;
    ```

3. **Create a SplashKit Window**: To start using SplashKit, you'll need to create a window for your application. Here's an example:

    *With Object Oriented Code*:

    ```csharp
    using SplashKitSDK;

    public static void Main()
    {
       Window window = new Window("My SplashKit App", 800, 600);

       // Your game or application code goes here

       window.Close();
    }
    ```

    *Using Top-level statements*:

    ```csharp
    using SplashKitSDK;
    using static SplashKitSDK.SplashKit;

    Window window = OpenWindow("My SplashKit App", 800, 600);

    // Your game or application code goes here

    CloseWindow(window);
    ```

4. **Explore the Documentation**: The SplashKit documentation provides detailed information about the available classes, methods, and features. You can find the API documentation on the [SplashKit website](https://www.splashkit.io/api/), which includes many examples to help demonstrated functionality.

### Contributing

If you'd like to contribute to the SplashKit library, please visit the [SplashKit GitHub repository](https://github.com/splashkit/splashkit) and follow the contribution guidelines.
