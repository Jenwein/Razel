# Razel
Just Learning Hazel Game Engine for Graduation Design

```bash
git clone --recursive https://github.com/Jenwein/Razel.git
```

--or

```bash
git clone https://github.com/Jenwein/Razel.git
git submodule update --recursive --init
```



```mermaid
graph TD
    subgraph Razel引擎
        Core[Core系统]
        Event[事件系统]
        Render[渲染系统]
        Window[窗口系统]
        Layer[层系统]
        
        Core --> Event
        Core --> Window
        Core --> Layer
        Window --> Event
        Layer --> Event
    end
    
    subgraph 事件系统
        EventBase[Event基类]
        AppEvent[应用程序事件]
        KeyEvent[键盘事件]
        MouseEvent[鼠标事件]
        EventDispatcher[事件分发器]
        
        EventBase --> AppEvent
        EventBase --> KeyEvent
        EventBase --> MouseEvent
        EventBase --- EventDispatcher
    end
    
    subgraph 层系统
        LayerClass[Layer基类]
        LayerStackClass[LayerStack]
        
        LayerStackClass --> LayerClass
    end
    
    subgraph 窗口系统
        WindowClass[Window抽象类]
        WindowsWindow[Windows窗口实现]
        
        WindowClass --> WindowsWindow
    end
    
    subgraph 第三方库
        GLFW[GLFW]
        spdlog[spdlog]
        
        WindowsWindow --> GLFW
        Core --> spdlog
    end
    
    subgraph 客户端应用
        Sandbox[Sandbox应用]
        
        Sandbox --> Razel引擎
    end
    
    subgraph 构建系统
        Premake[Premake构建]
        
        Premake --> Razel引擎
        Premake --> Sandbox
    end
```

```mermaid
graph TD
    A[渲染] --> B(屏幕绘制图形);
    B --> C{实时性};
    C -- 是 --> D(每秒约60帧);
    C -- 否 --> E(离线渲染);
    B --> F{高保真度};
    F -- 是 --> G(照片写实);
    F -- 否 --> H(低保真度);
    A --> I[GPU使用];
    I --> J(并行处理);
    I --> K(数学运算);
    A --> L[渲染API];
    L --> M(OpenGL);
    L --> N(Vulkan);
    L --> O(DirectX);
    L --> P(Metal);
    L --> Q[渲染API抽象];
    Q --> R(跨平台支持);
    R --> S(隐藏API差异);
    Q --> T[顶点缓冲区];
    Q --> U[索引缓冲区];
    Q --> V[纹理];
    Q --> W[着色器];
    A --> X[命令队列];
    X --> Y(游戏线程提交);
    Y --> Z(渲染线程处理);
    Z --> AA(异步执行);
```

