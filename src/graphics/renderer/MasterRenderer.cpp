//
// Created by masy on 06.03.20.
//

#include "cedar/MasterRenderer.h"
#include "cedar/Renderer2D.h"
#include "cedar/Math.h"
#include "cedar/EngineThread.h"

using namespace cedar;

MasterRenderer::MasterRenderer(Window *window)
{
	this->m_window = window;
	this->m_perspectiveProjectionMatrix = new Matrix4f();
	this->m_orthographicProjectionMatrix = new Matrix4f();
	this->m_viewMatrix = new Matrix4f();
}

MasterRenderer::~MasterRenderer()
{
	delete this->m_perspectiveProjectionMatrix;
	delete this->m_orthographicProjectionMatrix;
	delete this->m_viewMatrix;
	Renderer2D::cleanup();
	for (Renderer *renderer : this->m_renderers)
		delete renderer;
}

void MasterRenderer::init()
{
	this->m_perspectiveProjectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::toRadians(90.0f),
			1E-2f,
			4096.0f);

	this->m_orthographicProjectionMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Renderer2D::init(2048, this->m_orthographicProjectionMatrix);

	for (Renderer *renderer : this->m_renderers)
		renderer->init();
}

void MasterRenderer::onResize()
{
	this->m_perspectiveProjectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::toRadians(90.0f),
			1E-2f,
			4096.0f);

	this->m_orthographicProjectionMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);

	for (Renderer *renderer : this->m_renderers)
		renderer->onResize();
}

void MasterRenderer::render(unsigned long currentTime, unsigned long tickCount)
{
	Camera *camera = EngineThread::getInstance()->getCamera();
	if (camera)
	{
		cedar::Vector3f lerpedPosition;
		cedar::Quaternionf lerpedRotation;
		camera->getLerpedPosition(currentTime, &lerpedPosition);
		camera->getSlerpedRotation(currentTime, &lerpedRotation);
		this->m_viewMatrix->translation(0, 0, -(camera->getLerpedZoomLevel(currentTime)));
		this->m_viewMatrix->rotate(&lerpedRotation);
		this->m_viewMatrix->translate(-lerpedPosition.x, -lerpedPosition.y, -lerpedPosition.z);
	}
	else
	{
		this->m_viewMatrix->identity();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	for (Renderer *renderer : this->m_renderers)
		renderer->render(currentTime, tickCount);
}

void MasterRenderer::addRenderer(Renderer *renderer) {
	this->m_renderers.push_back(renderer);
}

const Matrix4f *MasterRenderer::getPerspectiveProjectionMatrix() const
{
	return this->m_perspectiveProjectionMatrix;
}

const Matrix4f *MasterRenderer::getOrthographicProjectionMatrix() const
{
	return this->m_orthographicProjectionMatrix;
}

const Matrix4f *MasterRenderer::getViewMatrix() const
{
	return this->m_viewMatrix;
}
