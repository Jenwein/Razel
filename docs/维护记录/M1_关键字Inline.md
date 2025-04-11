## 删除大量无用的Inline关键字 | commit--e3a14d1e

A function defined entirely inside a [class/struct/union definition](https://en.cppreference.com/w/cpp/language/classes), whether it's a member function or a non-member friend function, is implicitly an inline function unless it is attached to a [named module](https://en.cppreference.com/w/cpp/language/modules#Module_declarations)(since C++20).
完全定义在类/结构体/联合体定义内部的函数，无论是成员函数还是非成员友元函数，除非它附加到命名模块（自 C++20 起），否则隐式地是一个内联函数。

> [Remove all redundant 'inline' keyword usage. by d-tatianin · Pull Request #159 · TheCherno/Hazel](https://github.com/TheCherno/Hazel/pull/159)
>
> [inline specifier - cppreference.com](https://en.cppreference.com/w/cpp/language/inline)

## 修改BindBuffer目标为GL_ARRAY_BUFFER | commit--e3a14d1e

```cpp
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	:m_Count(count)
{
	RZ_PROFILE_FUNCTION();

	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
```

如果在没有绑定 VAO 的情况下绑定 GL_ELEMENT_ARRAY_BUFFER，OpenGL 会报错或无法正常工作。因此，为了避免这种限制，使用 GL_ARRAY_BUFFER 来绑定缓冲区，这样数据可以独立于 VAO 的状态完成加载。