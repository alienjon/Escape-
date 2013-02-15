/*
 * RendererContextInterface.hpp
 *
 *  Created on: Feb 14, 2013
 *      Author: alienjon
 */
#ifndef RENDERERCONTEXTINTERFACE_HPP_
#define RENDERERCONTEXTINTERFACE_HPP_

#include "../Engine/RendererContext.hpp"

/**
 * @brief An interface to retrieve a renderer context.
 */
class RendererContextInterface
{
	public:
	virtual ~RendererContextInterface() {}

	/**
	 * @brief Obtain a renderer context.
	 * @return A renderer context.
	 */
	virtual const RendererContext& getContext() const = 0;

    /**
     * @brief Update the context.
     * @param context Details needed to implement a new screen.
     */
    virtual void updateContext(const RendererContext& context) = 0;
};
#endif /* RENDERERCONTEXTINTERFACE_HPP_ */
