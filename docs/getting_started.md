---
layout: docs
title:  "Get Started with Splash Kit!"
date:   2015-11-30 15:14:48
categories: tutorial
---

Splash Kit is designed to help make learning to program fun and engaging. Using Splash Kit you will be able to start marking 

<div>
  <!-- Nav tabs -->
  <ul class="nav nav-tabs" role="tablist">
    <li role="presentation" class="active"><a href="#pseudo-code1" aria-controls="pseudo-code1" role="tab" data-toggle="tab">Pseudocode</a></li>
    <li role="presentation"><a href="#c-code1" aria-controls="c-code1" role="tab" data-toggle="tab">C / C++</a></li>
    <li role="presentation"><a href="#pascal-code1" aria-controls="pascal-code1" role="tab" data-toggle="tab">Pascal</a></li>
    <li role="presentation"><a href="#python-code1" aria-controls="python-code1" role="tab" data-toggle="tab">Python</a></li>
    <li role="presentation"><a href="#swift-code1" aria-controls="swift-code1" role="tab" data-toggle="tab">Swift</a></li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content">
    <div role="tabpanel" class="tab-pane active" id="pseudo-code1">
{% highlight Batch File %}
---
HelloWorld Program
---
uses SplashKit

begin
  Call -- OpenWindow -- title: 'Hello World', width: 800, height: 600
  Call -- ClearScreen -- color: COLOR_WHITE
  Call -- DrawText -- text: 'My First Program!', color: COLOR_BLACK, 
                            x: 50, y: 100, font: 'arial.ttf', size: 32
  Call -- RefreshScreen
  Call -- Delay -- milliseconds: 5000
end
{% endhighlight %}
    </div>
    <div role="tabpanel" class="tab-pane" id="c-code1">
{% highlight c %}
#include "SplashKit.h"

int main()
{
  open_window("Hello World", 800, 600);
  clear_screen(COLOR_WHITE);
  draw_text("My First Program!", ColorBlack, 50, 100, "arial.ttf", 32);
  refresh_screen();
  delay(5000);
}
{% endhighlight %}
    </div>
    <div role="tabpanel" class="tab-pane" id="pascal-code1">
{% highlight pascal %}
program HelloWorld;
uses SplashKit;

begin
  OpenWindow('Hello World', 800, 600);
  ClearScreen(COLOR_WHITE);
  DrawText('My First Program!', ColorBlack, 50, 100, 'arial.ttf', 32);
  RefreshScreen();
  Delay(5000);
end.
{% endhighlight %}
</div>
    <div role="tabpanel" class="tab-pane" id="python-code1">...</div>
    <div role="tabpanel" class="tab-pane" id="swift-code1">...</div>
  </div>

</div>



