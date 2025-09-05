## 问题汇总

### 错误：C2338	

```bash
static_assert failed: 'formatting of non-void pointers is disallowed'	
Razel	E:\dev\Razel\Razel\vendor\spdlog\include\spdlog\fmt\bundled\base.h	2194	 
```

#### 原因

​	spdlog版本不在可以直接 `spdlog::info("Pointer address: {}", ptr);` 需要对应的格式转换

#### 实际代码：

- old :	`RZ_CORE_INFO("  Vendor: {0}",glGetString(GL_VENDOR));`
- new：    ` RZ_CORE_INFO("  Vendor: {0}",(const char*)glGetString(GL_VENDOR));`

### 问题:SPIR-V流程及原理
```cpp
// TODO:待学习
```

### 问题:GLSub...,...Base,Name
```cpp
// TODO:待学习
```