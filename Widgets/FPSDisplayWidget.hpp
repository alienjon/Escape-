/*
 * FPSDisplayWidget.hpp
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */
#ifndef FPSDISPLAYWIDGET_HPP_
#define FPSDISPLAYWIDGET_HPP_

#include "../Engine/guichan.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief An OSD widget to display the FPS.
 */
class FPSDisplayWidget : public gcn::Label
{
	public:
	/**
	 * @brief A widget that displays the current frame rate.
	 */
	FPSDisplayWidget();

	/**
	 * @brief Perform internal logic.
	 */
	virtual void logic();

	private:
	// Timer used specifically to keep track of a single second for FPS calculation.
	Timer mTimer;

	// The FPS counter.
	unsigned int mCounter;
};

#endif /* FPSDISPLAYWIDGET_HPP_ */
