# SplashKit

SplashKit is a software development library designed to empower beginner programmers. It provides a range of methods and classes to help create interactive graphical programs, without taking any control away from the programmer.

To use this package you must install the skm tool from [splashkit.io](https://splashkit.io), and globally install the native library.

```bash
skm global install
```


## Splashkit NuGet Package

The Splashkit NuGet package provides a .NET Standard library for creating 2D games and applications using the Splashkit framework. Splashkit is a free and open-source game development library that simplifies the process of building games and interactive applications.

### Features

- **2D Graphics**: Draw shapes, images, and text to the screen with ease.
- **Input Handling**: Respond to keyboard, mouse, and touch input.
- **Audio**: Play sounds and music in your applications.
- **Networking**: Communicate with other clients and servers over the network.
- **File I/O**: Load and save data to files.
- **Math Utilities**: Perform common mathematical operations.
- **Timers and Scheduling**: Schedule events and manage game time.

### Getting Started

To use the Splashkit NuGet package in your .NET project, follow these steps:

1. **Install the Package**: You can install the Splashkit NuGet package using the NuGet Package Manager in Visual Studio or by running the following command in the Package Manager Console:

   ```
   Install-Package Splashkit
   ```

2. **Import the Namespace**: In your C# code, add the following using statement to access the Splashkit classes and methods:

   ```csharp
   using Splashkit;
   ```

3. **Create a Splashkit Window**: To start using Splashkit, you'll need to create a window for your application. Here's an example:

   ```csharp
   void Main()
   {
       OpenWindow("My Splashkit App", 800, 600);

       // Your game or application code goes here

       CloseWindow();
   }
   ```

4. **Explore the Documentation**: The Splashkit documentation provides detailed information about the available classes, methods, and features. You can find the documentation on the [Splashkit website](https://www.splashkit.io/documentation/).

### Examples

Here are a few examples of how you can use the Splashkit NuGet package:

#### Drawing a Circle

```csharp
void Main()
{
    OpenWindow("Drawing a Circle", 800, 600);

    DrawCircle(Color.Blue(), 400, 300, 50);

    WaitUntilKeyPressed();
    CloseWindow();
}
```

#### Playing a Sound

```csharp
void Main()
{
    OpenWindow("Playing a Sound", 800, 600);

    LoadSound("coin", "coin.wav");
    PlaySound("coin");

    WaitUntilKeyPressed();
    CloseWindow();
}
```

#### Responding to Mouse Input

```csharp
void Main()
{
    OpenWindow("Mouse Input", 800, 600);

    while (!WindowCloseRequested())
    {
        if (MouseClicked(MouseButton.LeftButton()))
        {
            int x, y;
            ReadMousePosition(out x, out y);
            DrawCircle(Color.Red(), x, y, 20);
        }

        RefreshWindow();
    }

    CloseWindow();
}
```

### Contributing

If you'd like to contribute to the Splashkit NuGet package, please visit the [Splashkit GitHub repository](https://github.com/splashkit/splashkit) and follow the contribution guidelines.
