#pragma once

#include "Lithe.h"

class ExampleLayer : public Lithe::Layer
{
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Lithe::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Lithe::Event& e) override;
private:
    Lithe::ShaderLibrary m_ShaderLibrary;
    Lithe::Ref<Lithe::Shader> m_Shader;
    Lithe::Ref<Lithe::VertexArray> m_VertexArray;

    Lithe::Ref<Lithe::VertexArray> m_SquareVA;
    Lithe::Ref<Lithe::Shader> m_FlatColorShader;

    Lithe::Ref<Lithe::Texture2D> m_Texture, m_YellowBalloonTexture;

    Lithe::OrthographicCameraController m_CameraController;
    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};