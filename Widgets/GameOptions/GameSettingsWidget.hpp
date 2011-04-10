/*
 * GameSettingsWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#ifndef GAMESETTINGSWIDGET_HPP_
#define GAMESETTINGSWIDGET_HPP_

#include "../../guichan.hpp"

/**
 * @brief The game setting widget contains items for configuring the game.
 */
class GameSettingsWidget : public gcn::ActionListener,  public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 */
	GameSettingsWidget();

	/**
	 * @brief An action occurred.
	 * @param event The action event.
	 */
	virtual void action(const gcn::ActionEvent& event);

	/**
	 * @brief Adjust the size of the widget.
	 */
	virtual void adjustSize();

	private:
	/**
	 * These are the labels for the various tasks.
	 */
	gcn::Label mResolutionLabel,
			   mOpenGLLabel,
			   mAudioStateLabel,
			   mVolumeLabel;

	/**
	 * These are the controls themselves.
	 */
	gcn::DropDown mResolution;
	gcn::RadioButton mOpenGLEnabled,
					 mOpenGLDisabled,
					 mAudioEnabled,
					 mAudioDisabled;
	gcn::Slider mVolume;
};

#endif /* GAMESETTINGSWIDGET_HPP_ */
