/*
 * FPSDisplayWidget.hpp
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */

#ifndef FPSDISPLAYWIDGET_HPP_
#define FPSDISPLAYWIDGET_HPP_

#include <guichan.hpp>

#include "../main.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief An OSD widget to display the FPS.
 */
class FPSDisplayWidget : public gcn::Label
{
	public:
	/**
	 * @brief A widget that displays the current framerate.
	 */
	FPSDisplayWidget();
	virtual ~FPSDisplayWidget();

	/**
	 * @brief Perform internal logic.
	 */
	virtual void logic();

	protected:
	/**
	 * Timer used specifically to keep track of a single second for FPS calculation.
	 */
	Timer mFPSTimer;
};

#endif /* FPSDISPLAYWIDGET_HPP_ */
