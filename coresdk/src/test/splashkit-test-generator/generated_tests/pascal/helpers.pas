unit Helpers;

interface
uses splashkit_test, Variants, SysUtils, StrUtils;

function ToStr(const Value: Variant): String; overload;
function ToStr(Value: Boolean): String; overload;
function ToStr(Value: Integer): String; overload;
function ToStr(Value: Double): String; overload;
function ToStr(Value: String): String; overload;
function CreateStringArray(const Values: array of String): ArrayOfString;
function CreateDoubleArray(const Values: array of Double): ArrayOfDouble;
function CreateBooleanArray(const Values: array of Boolean): ArrayOfBoolean;
function CreateJsonArray(const Values: array of Json): ArrayOfJson;
function CreateLineArray(const Values: array of Line): ArrayOfLine;
function CreateCharArray(const Values: array of Char): ArrayOfChar;
function CreateTriangleArray(const Values: array of Triangle): ArrayOfTriangle;

type
  TSpriteFunction = procedure(ptr: Pointer); cdecl;
  TSpriteFloatFunction = procedure(ptr: Pointer; value: Single); cdecl;
  TSpriteEventHandler = procedure(ptr: Pointer; evt: Integer); cdecl;
  TKeyCallback = procedure(key: Integer); cdecl;
  TFreeNotifier = procedure(resource: Pointer); cdecl;

  TSpriteDelegates = class
  private
    class var
      FEventCalled: Boolean;
      FFloatFunctionCallCount: Integer;
      FFunctionCallCount: Integer;
    class procedure HandleSpriteFloat(ptr: Pointer; value: Single); static; cdecl;
    class procedure HandleSprite(ptr: Pointer); static; cdecl;
    class procedure HandleSpriteEvent(ptr: Pointer; evt: Integer); static; cdecl;
  public
    constructor Create;
    function SpriteFloatFunction: TSpriteFloatFunction;
    function SpriteFunction: TSpriteFunction;
    function SpriteEventHandler: TSpriteEventHandler;
    procedure Reset;
    class property EventCalled: Boolean read FEventCalled;
    class property FloatFunctionCallCount: Integer read FFloatFunctionCallCount;
    class property FunctionCallCount: Integer read FFunctionCallCount;
  end;

  TKeyCallbacks = class
  private
    class var
      FKeyTyped: KeyCode;
      FKeyDown: KeyCode;
      FKeyUp: KeyCode;
    class procedure HandleKeyTyped(key: Integer); static; cdecl;
    class procedure HandleKeyDown(key: Integer); static; cdecl;
    class procedure HandleKeyUp(key: Integer); static; cdecl;
  public
    constructor Create;
    function OnKeyTyped: KeyCallback;
    function OnKeyDown: KeyCallback;
    function OnKeyUp: KeyCallback;
    procedure Reset;
    class function GetKeyTyped: KeyCode;
    class function GetKeyDown: KeyCode;
    class function GetKeyUp: KeyCode;
  end;

  TNotifierTracker = class
  private
    class var
      FWasNotified: Boolean;
    class procedure HandleFree(resource: Pointer); static; cdecl;
  public
    constructor Create;
    function OnFree: TFreeNotifier;
    procedure Reset;
    class property WasNotified: Boolean read FWasNotified;
  end;

  AnimationScriptCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  AnimationCleanup = class(TInterfacedObject)
  private
    FAnimation: Animation;
  public
    constructor Create(animation: Animation);
    destructor Destroy; override;
  end;

  AudioCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  SoundEffectCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  MusicCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  WindowCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  BitmapCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  SpriteCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  FontCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  RaspberryCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  JsonCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  ServerCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  ConnectionCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  ResourceCleanup = class(TInterfacedObject)
  private
    FBundleName: String;
  public
    constructor Create(bundleName: String);
    destructor Destroy; override;
  end;

  SpritePackCleanup = class(TInterfacedObject)
  private
    FPackName: String;
  public
    constructor Create(packName: String);
    destructor Destroy; override;
  end;

  TimerCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  LoggerCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  LayoutCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

  InterfaceFontCleanup = class(TInterfacedObject)
  public
    constructor Create;
    destructor Destroy; override;
  end;

implementation

{ TSpriteDelegates }

constructor TSpriteDelegates.Create;
begin
  inherited;
  Reset;
end;

class procedure TSpriteDelegates.HandleSpriteFloat(ptr: Pointer; value: Single); static; cdecl;
begin
  Inc(FFloatFunctionCallCount);
  FEventCalled := True;
end;

class procedure TSpriteDelegates.HandleSprite(ptr: Pointer); static; cdecl;
begin
  Inc(FFunctionCallCount);
  FEventCalled := True;
end;

class procedure TSpriteDelegates.HandleSpriteEvent(ptr: Pointer; evt: Integer); static; cdecl;
begin
  FEventCalled := True;
end;

function TSpriteDelegates.SpriteFloatFunction: TSpriteFloatFunction;
begin
  Result := @HandleSpriteFloat;
end;

function TSpriteDelegates.SpriteFunction: TSpriteFunction;
begin
  Result := @HandleSprite;
end;

function TSpriteDelegates.SpriteEventHandler: TSpriteEventHandler;
begin
  Result := @HandleSpriteEvent;
end;

procedure TSpriteDelegates.Reset;
begin
  FFloatFunctionCallCount := 0;
  FFunctionCallCount := 0;
  FEventCalled := False;
end;

{ TKeyCallbacks }

constructor TKeyCallbacks.Create;
begin
  inherited;
  Reset;
end;

procedure TKeyCallbacks.Reset;
begin
  FKeyTyped := KeyCode(0);
  FKeyDown := KeyCode(0);
  FKeyUp := KeyCode(0);
end;

class procedure TKeyCallbacks.HandleKeyTyped(key: Integer); static; cdecl;
begin
  FKeyTyped := KeyCode(key);
end;

class procedure TKeyCallbacks.HandleKeyDown(key: Integer); static; cdecl;
begin
  FKeyDown := KeyCode(key);
end;

class procedure TKeyCallbacks.HandleKeyUp(key: Integer); static; cdecl;
begin
  FKeyUp := KeyCode(key);
end;

function TKeyCallbacks.OnKeyTyped: KeyCallback;
begin
  Result := @HandleKeyTyped;
end;

function TKeyCallbacks.OnKeyDown: KeyCallback;
begin
  Result := @HandleKeyDown;
end;

function TKeyCallbacks.OnKeyUp: KeyCallback;
begin
  Result := @HandleKeyUp;
end;

class function TKeyCallbacks.GetKeyTyped: KeyCode;
begin
  Result := FKeyTyped;
end;

class function TKeyCallbacks.GetKeyDown: KeyCode;
begin
  Result := FKeyDown;
end;

class function TKeyCallbacks.GetKeyUp: KeyCode;
begin
  Result := FKeyUp;
end;

{ TNotifierTracker }

constructor TNotifierTracker.Create;
begin
  inherited;
  Reset;
end;

class procedure TNotifierTracker.HandleFree(resource: Pointer); static; cdecl;
begin
  FWasNotified := True;
end;

function TNotifierTracker.OnFree: TFreeNotifier;
begin
  Result := @HandleFree;
end;

procedure TNotifierTracker.Reset;
begin
  FWasNotified := False;
end;

{ AnimationScriptCleanup }

constructor AnimationScriptCleanup.Create;
begin
end;

destructor AnimationScriptCleanup.Destroy;
begin
    FreeAllAnimationScripts;
    inherited;
end;

{ AnimationCleanup }

constructor AnimationCleanup.Create(animation: Animation);
begin
    FAnimation := animation;
end;

destructor AnimationCleanup.Destroy;
begin
    FreeAnimation(FAnimation);
    inherited;
end;

{ AudioCleanup }

constructor AudioCleanup.Create;
begin
end;

destructor AudioCleanup.Destroy;
begin
    CloseAudio;
    inherited;
end;

{ SoundEffectCleanup }

constructor SoundEffectCleanup.Create;
begin
end;

destructor SoundEffectCleanup.Destroy;
begin
    FreeAllSoundEffects;
    inherited;
end;

{ MusicCleanup }

constructor MusicCleanup.Create;
begin
end;

destructor MusicCleanup.Destroy;
begin
    FreeAllMusic;
    inherited;
end;

{ WindowCleanup }

constructor WindowCleanup.Create;
begin
end;

destructor WindowCleanup.Destroy;
begin
    CloseAllWindows;
    SetCameraPosition(PointAt(0, 0));
    inherited;
end;

{ BitmapCleanup }

constructor BitmapCleanup.Create;
begin
end;

destructor BitmapCleanup.Destroy;
begin
    FreeAllBitmaps;
    inherited;
end;

{ SpriteCleanup }

constructor SpriteCleanup.Create;
begin
end;

destructor SpriteCleanup.Destroy;
begin
    FreeAllSprites;
    inherited;
end;

{ FontCleanup }

constructor FontCleanup.Create;
begin
end;

destructor FontCleanup.Destroy;
begin
    FreeAllFonts;
    inherited;
end;

{ RaspberryCleanup }

constructor RaspberryCleanup.Create;
begin
end;

destructor RaspberryCleanup.Destroy;
begin
    splashkit_test.RaspiCleanup;
    inherited;
end;

{ JsonCleanup }

constructor JsonCleanup.Create;
begin
end;

destructor JsonCleanup.Destroy;
begin
    FreeAllJson;
    inherited;
end;

{ ServerCleanup }

constructor ServerCleanup.Create;
begin
end;

destructor ServerCleanup.Destroy;
begin
    CloseAllServers;
    inherited;
end;

{ ConnectionCleanup }

constructor ConnectionCleanup.Create;
begin
end;

destructor ConnectionCleanup.Destroy;
begin
    CloseAllConnections;
    inherited;
end;

{ ResourceCleanup }

constructor ResourceCleanup.Create(bundleName: String);
begin
    FBundleName := bundleName;
end;

destructor ResourceCleanup.Destroy;
begin
    FreeResourceBundle(FBundleName);
    inherited;
end;

{ SpritePackCleanup }

constructor SpritePackCleanup.Create(packName: String);
begin
    FPackName := packName;
end;

destructor SpritePackCleanup.Destroy;
begin
    FreeSpritePack(FPackName);
    inherited;
end;

{ TimerCleanup }

constructor TimerCleanup.Create;
begin
end;

destructor TimerCleanup.Destroy;
begin
    FreeAllTimers;
    inherited;
end;

{ LoggerCleanup }

constructor LoggerCleanup.Create;
begin
end;

destructor LoggerCleanup.Destroy;
begin
    CloseLogProcess;
    inherited;
end;

{ LayoutCleanup }

constructor LayoutCleanup.Create;
begin
end;

destructor LayoutCleanup.Destroy;
begin
    ProcessEvents();
    ResetLayout();
    SetInterfaceStyle(InterfaceStyle.SHADED_DARK_STYLE);
    ProcessEvents();
    inherited;
end;

{ InterfaceFontCleanup }

constructor InterfaceFontCleanup.Create;
begin
end;

destructor InterfaceFontCleanup.Destroy;
begin
    SetInterfaceFont(GetSystemFont());
    inherited;
end;

function ToStr(Value: Boolean): String; overload;
begin
  Result := BoolToStr(Value, True);
end;

function ToStr(Value: Integer): String; overload;
begin
  Result := IntToStr(Value);
end;

function ToStr(Value: Double): String; overload;
begin
  Result := FloatToStr(Value);
end;

function ToStr(Value: String): String; overload;
begin
  Result := Value;
end;

function ToStr(const Value: Variant): String; overload;
begin
  Result := VarToStr(Value); 
end;

function CreateStringArray(const Values: array of String): ArrayOfString;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateJsonArray(const Values: array of Json): ArrayOfJson;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateDoubleArray(const Values: array of Double): ArrayOfDouble;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateBooleanArray(const Values: array of Boolean): ArrayOfBoolean;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateLineArray(const Values: array of Line): ArrayOfLine;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateCharArray(const Values: array of Char): ArrayOfChar;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

function CreateTriangleArray(const Values: array of Triangle): ArrayOfTriangle;
var
  i: Integer;
begin
  Result := nil;
  SetLength(Result, Length(Values));
  for i := 0 to High(Values) do
    Result[i] := Values[i];
end;

end. 