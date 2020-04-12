//
// Created by masy on 06.03.20.
//

#include <iostream>

#include "cedar/MasterRenderer.h"
#include "cedar/Renderer2D.h"
#include "cedar/Math.h"
#include "cedar/EngineThread.h"
#include "cedar/Cedar.h"
#include "cedar/ScreenRegistry.h"

using namespace cedar;

MasterRenderer::MasterRenderer(Window *window)
{
	this->m_window = window;
	this->m_perspectiveProjectionMatrix = new Matrix4f();
	this->m_orthographicProjectionMatrix = new Matrix4f();
	this->m_projectionViewMatrix = new Matrix4f();
	this->m_invProjectionViewMatrix = new Matrix4f();
	this->m_viewMatrix = new Matrix4f();
	this->m_frustumRayBuilder = new FrustumRayBuilder();
	this->m_clearColor = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
}

MasterRenderer::~MasterRenderer()
{
	delete this->m_perspectiveProjectionMatrix;
	delete this->m_orthographicProjectionMatrix;
	delete this->m_viewMatrix;
	delete this->m_projectionViewMatrix;
	delete this->m_invProjectionViewMatrix;
	delete this->m_frustumRayBuilder;
	Renderer2D::cleanup();
	ScreenRegistry::cleanup();
	for (Renderer *renderer : this->m_renderers)
		delete renderer;
}

void MasterRenderer::init()
{
	this->m_perspectiveProjectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::toRadians(Cedar::getConfig()->getFOV()),
			1E-2f,
			512.0f);

	this->m_orthographicProjectionMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(this->m_clearColor.x, this->m_clearColor.y, this->m_clearColor.z, this->m_clearColor.w);

	Renderer2D::init(2048, this->m_orthographicProjectionMatrix);

	for (Renderer *renderer : this->m_renderers)
		renderer->init();
}

void MasterRenderer::onResize()
{
	glViewport(0, 0, this->m_window->getWidth(), this->m_window->getHeight());
	this->m_perspectiveProjectionMatrix->perspective(
			static_cast<float>(this->m_window->getRatio()),
			cedar::toRadians(90.0f),
			1E-2f,
			512.0f);

	this->m_orthographicProjectionMatrix->orthographic(0.0f, static_cast<float>(this->m_window->getWidth()), static_cast<float>(this->m_window->getHeight()), 0.0f, 1E-6f, 4096);

	for (Renderer *renderer : this->m_renderers)
		renderer->onResize();
}

void MasterRenderer::render(unsigned long currentTime, unsigned long tickCount)
{
	Camera *camera = EngineThread::getInstance()->getCamera();
	if (camera)
	{
		Vector3f position = Vector3f(*camera->getPosition());
		position.negate();
		this->m_viewMatrix->translation(0, 0, -camera->getZoomLevel());
		this->m_viewMatrix->rotate(camera->getRotation());
		this->m_viewMatrix->translate(&position);
	}
	else
	{
		this->m_viewMatrix->identity();
	}

	*this->m_projectionViewMatrix = *this->m_perspectiveProjectionMatrix * *this->m_viewMatrix;
	*this->m_invProjectionViewMatrix = *this->m_projectionViewMatrix;
	this->m_invProjectionViewMatrix->invert();
	this->m_frustumRayBuilder->set(*this->m_projectionViewMatrix);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	for (Renderer *renderer : this->m_renderers)
		renderer->render(currentTime, tickCount);

	Renderer2D::beginBatch();
	for (Screen *screen : *ScreenRegistry::getLoadedScreens())
	{
		if (screen->isVisible())
			screen->render(currentTime);
	}
	Renderer2D::endBatch();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Renderer2D::flush();
}

void MasterRenderer::addRenderer(Renderer *renderer)
{
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

const Matrix4f *MasterRenderer::getProjectionViewMatrix() const
{
	return this->m_projectionViewMatrix;
}

const Matrix4f *MasterRenderer::getInvProjectionViewMatrix() const
{
	return this->m_invProjectionViewMatrix;
}

void MasterRenderer::getMouseRay(Vector3f *origin, Vector3f *rayDir) const {
		float cursorX = static_cast<float>(this->m_window->getInputHandler()->getCursorX());
		float cursorY = static_cast<float>(this->m_window->getInputHandler()->getCursorY());

		float winX = cursorX / static_cast<float>(this->m_window->getWidth());
		float winY = 1.0f - cursorY / static_cast<float>(this->m_window->getHeight());

		this->m_frustumRayBuilder->getOrigin(origin);
		this->m_frustumRayBuilder->getRayDir(winX, winY, rayDir);
		*origin += (*rayDir * 1E-2f);
}

Vector4f MasterRenderer::getClearColor() const {
	return this->m_clearColor;
}

Vector4f *MasterRenderer::getClearColor(Vector4f *storage) const {
	*storage = this->m_clearColor;
	return storage;
}

void MasterRenderer::setClearColor(const Vector4f &newColor) {
	this->m_clearColor = newColor;
	glClearColor(newColor.x, newColor.y, newColor.z, newColor.w);
}
