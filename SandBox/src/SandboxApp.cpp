#include <Razel.h>
#include <Razel/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Sandbox2D.h"

class ExampleLayer :public Razel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Razel::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		Razel::Ref<Razel::VertexBuffer> vertexBuffer;
		vertexBuffer = Razel::VertexBuffer::Create(vertices, sizeof(vertices));
		
		Razel::BufferLayout layout = {
			{Razel::ShaderDataType::Float3,"a_Position"},
			{Razel::ShaderDataType::Float4,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		Razel::Ref<Razel::IndexBuffer> indexBuffer;
		indexBuffer = Razel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Razel::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Razel::Ref<Razel::VertexBuffer> squareVB;
		squareVB = Razel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Razel::ShaderDataType::Float3, "a_Position" },
			{ Razel::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Razel::Ref<Razel::IndexBuffer> squareIB;
		squareIB = Razel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform* vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Razel::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);

		std::string FlatShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1.0);	
			
			}
		)";

		std::string FlatShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color,1.0f);

			}
		)";

		m_FlatColorShader = Razel::Shader::Create("FlatColor",FlatShaderVertexSrc, FlatShaderFragmentSrc);
		
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = Razel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_CppTexture = Razel::Texture2D::Create("assets/textures/C++.png");

		std::dynamic_pointer_cast<Razel::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Razel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);


	}
	
	void OnUpdate(Razel::Timestep ts) override
	{
		//RZ_CORE_TRACE("Timestep: {0}s,{1}ms", ts.GetSeconds(),ts.GetMilliseconds());

		//glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
		static glm::vec3 pos1(0.11f, 0.11f, 0.0f);
		
		m_CameraController.OnUpdate(ts);

		Razel::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
		Razel::RenderCommand::Clear();


		std::dynamic_pointer_cast<Razel::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Razel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		Razel::Renderer::BeginScene(m_CameraController.GetCamera());
		
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos1);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::vec3 Pos = pos + pos1;
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), Pos) * scale;
				Razel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Razel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_CppTexture->Bind();
		Razel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// 三角形
		//Razel::Renderer::Submit(m_Shader, m_VertexArray);
		Razel::Renderer::EndScene();
	}

    void OnEvent(Razel::Event& e) override
    {
		m_CameraController.OnEvent(e);
    }
	void OnImGuiRender()override
	{
		ImGui::Begin("Test");
		ImGui::ColorEdit3("Square Color",glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
private:
	Razel::Ref<Razel::Shader> m_Shader;
	Razel::Ref<Razel::VertexArray> m_VertexArray;

	Razel::Ref<Razel::Shader> m_FlatColorShader;
	Razel::Ref<Razel::VertexArray> m_SquareVA;

	Razel::ShaderLibrary m_ShaderLibrary;

	Razel::Ref<Razel::Texture2D> m_Texture, m_CppTexture;

	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.3f, 0.8f);


	// 正交投影相机
	Razel::OrthographicCameraController m_CameraController;
};

class Sandbox : public Razel::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());

	}
	~Sandbox()
	{
	}

};

Razel::Application* Razel::CreateApplication()
{
	return new Sandbox();
}