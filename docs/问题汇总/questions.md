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

### 物理系统是如何实现的,RunTime指针的作用

## Gizmo 旋转物体会导致相机位置发生变化

对于AABB包围盒，物体旋转时包围盒大小变化，如果自动重新计算聚焦点会导致相机随着物体的旋转而周期性发生位置变化
